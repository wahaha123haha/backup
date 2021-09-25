#include "MyCopy.h"


void MyCopy::change_path(char *src, char *cat)
{
    strcat(src, (char *)"/");
    strcat(src, cat);
}

MyCopy::MyCopy(char *src_origin, char  *dest_origin)
{
    char src[1024],dest[1024];
    char *current_dir = getcwd(NULL, 0);

    struct stat state_of_entry;
    lstat(src_origin, &state_of_entry);
    if (S_ISDIR(state_of_entry.st_mode)) //目录
    {
        if (chdir(src_origin)) //目录错误
        {
            perror("chdir");
            exit(-1);
        }
        strcpy(src, getcwd(NULL, 0)); //获取源文件夹绝对路径
        chdir(current_dir);
        lstat(dest_origin, &state_of_entry);
        if (S_ISDIR(state_of_entry.st_mode)) //目录
        {
            if (chdir(dest_origin)) //目录错误
            {
                perror("chdir");
                exit(-1);
            }
            strcpy(dest, getcwd(NULL, 0)); //获取目标文件夹绝对路径
            //chdir(current_dir);
            //chdir(dest);
            char dest_end[100],dest_temp[100];
            int i,j;
            for(i=strlen(src_origin)-1,j=0;src_origin[i]!='/';i--){
                dest_temp[j++]=src_origin[i];
            }
            dest_temp[j]='\0';
            for(i=0;i<strlen(dest_temp);i++){
                dest_end[i]=dest_temp[strlen(dest_temp)-i-1];
            }
            dest_end[i]='\0';
            strcat(dest,"/");
            strcat(dest,dest_end);
            copy_dir(src_origin,dest);
            chdir(src);
            search_dfs(src, dest);
        }
        else
        {
            printf("error. No destination directory.\n");
            exit(-1);
        }
    }

    else //文件直接复制
    {
        char dest[1024];
        lstat(dest_origin, &state_of_entry);
        if (S_ISDIR(state_of_entry.st_mode)) //目录
        {
            strcpy(dest, dest_origin); //获取目标文件夹绝对路径
            char *temp=get_myrelativecwd(src_origin);
            strcat(dest,"/");
            strcat(dest,temp);
        }
        else
        {
            strcat(dest, dest_origin);
        }
        copy_file(src_origin, dest);
    }
}

void MyCopy::search_dfs(char *src_path, char *dest_path)
{
    // printf("Searching directory:    %s\n", getcwd(NULL, 0));
    DIR *src_dir = opendir(src_path);
    DIR *dest_dir = opendir(dest_path);
    struct dirent *entry = NULL;
    while ((entry = readdir(src_dir)) != NULL)
    {
        chdir(src_path);
        struct stat state_of_entry;
        lstat(entry->d_name, &state_of_entry);
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        // printf("entry->d_name: %s\n", entry->d_name);
        if (S_ISLNK(state_of_entry.st_mode)) //符号链接
        {
            char src_file[1024];
            char dest_file[1024];
            strcpy(src_file, src_path);
            change_path(src_file, entry->d_name);
            strcpy(dest_file, dest_path);
            change_path(dest_file, entry->d_name);
            // printf("src file: %s\n", src_file);
            // printf("dest file: %s\n", dest_file);
            copy_sln(src_file, dest_file);
        }
        else if (S_ISREG(state_of_entry.st_mode)) //普通文件
        {
            char src_file[1024];
            char dest_file[1024];
            strcpy(src_file, src_path);
            change_path(src_file, entry->d_name);
            strcpy(dest_file, dest_path);
            change_path(dest_file, entry->d_name);
            // printf("src file: %s\n", src_file);
            // printf("dest file: %s\n", dest_file);
            copy_file(src_file, dest_file);
        }
        else if (S_ISDIR(state_of_entry.st_mode)) //目录
        {
            char src[1024];
            char dest[1024];
            strcpy(src, src_path);
            change_path(src, entry->d_name);
            strcpy(dest, dest_path);
            change_path(dest, entry->d_name);
            // printf("src dir: %s\n", src);
            // printf("dest dir: %s\n", dest);
            copy_dir(src, dest);
            search_dfs(src, dest);
        }
    }
}

void MyCopy::copy_file(const char *src_file, const char *dest_file)
{
    int src_fd = open(src_file, O_RDONLY);
    int dest_fd = creat(dest_file, O_WRONLY);

    unsigned char buf[1024];
    int bytes;
    while (1)
    {
        bytes=read(src_fd, buf, sizeof(buf));
        if(bytes==0)
            break;
        write(dest_fd, buf, bytes);
    }

    changeAttr(src_file, dest_file);

    close(src_fd);
    close(dest_fd);
}

void MyCopy::copy_dir(const char *src_dir, const char *dst_dir)
{
    mkdir(dst_dir, 0777);
    changeAttr(src_dir, dst_dir);
}

void MyCopy::copy_sln(const char *src_file, const char *dst_file)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    int len = 0;
    if ((len = readlink(src_file, buf, sizeof(buf))) > 0)
    {
        printf("%s\n", buf);
        if (symlink(buf, dst_file) == -1)
        {
            perror("symlink");
        }
    }
    changeAttr(src_file, dst_file);
}

void MyCopy::changeAttr(const char *src, const char *dst)
{
    struct stat attr_of_src;
    lstat(src, &attr_of_src);
    //修改文件属性
    chmod(dst, attr_of_src.st_mode);
    //修改文件用户组
    chown(dst, attr_of_src.st_uid, attr_of_src.st_gid);

    //修改文件访问、修改时间
    struct timeval time_buf[2];
    time_buf[1].tv_sec = attr_of_src.st_mtime;
    time_buf[0].tv_sec = attr_of_src.st_atime;
    if (S_ISLNK(attr_of_src.st_mode)) {
        if(lutimes(dst, time_buf) == -1)
        {
            printf("%s\n", dst);
            perror("lutimes");
        }
    }
    struct utimbuf tbuf;
    tbuf.actime = attr_of_src.st_atime;
    tbuf.modtime = attr_of_src.st_mtime;
    utime(dst, &tbuf);

    struct stat dst_attr_of_src;
    lstat(dst, &dst_attr_of_src);
    if (dst_attr_of_src.st_mtime != attr_of_src.st_mtime)
        printf("%s : %d\n", dst, attr_of_src.st_mtime);
}
