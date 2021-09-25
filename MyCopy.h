#ifndef MY_COPY_H
#define MY_COPY_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <time.h>
#include <sys/time.h>
#include "mainwindow.h"

class MyCopy{
private:

    //文件夹复制采用dfs或者bfs进行搜索是等价的
    void search_dfs(char *src_path, char *dest_path);
    //复制文件
    void copy_file(const char *src_file, const char *dst_file);
    //复制文件夹
    void copy_dir(const char *src_dir, const char *dst_dir);
    //复制软链接
    void copy_sln(const char *src_file, const char *dst_file);
    //修改文件属性与源文件保持一致
    void changeAttr(const char *src, const char *dst);
    //修改路径
    void change_path(char *src, char *cat);
public:
    MyCopy(char *src_path,char *dest_path);
};

#endif // MY_COPY_H
