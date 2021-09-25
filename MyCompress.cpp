#include "MyCompress.h"

MyCompress::MyCompress(char *src_origin,char *des_origin){
    strcpy(this->_src,src_origin);
    strcpy(this->_des,des_origin);
}

void MyCompress::Compress(){
    char dest[1024];
    char*dest_end=get_myrelativecwd(_src);
    strcpy(dest,_des);
    strcat(dest,"/");
    strcat(dest,dest_end);
    strcat(dest,".tar.gz");
    char order[1024];
    strcpy(order,"tar -zcf ");
    strcat(order,dest);
    strcat(order," ");
    strcat(order,dest_end);
    char *parent=get_parentpwd(_src);
    chdir(parent);
    system(order);
}

void MyCompress::ReCompress(){
    char dest[1024];
    strcpy(dest,_des);
    char order[1024];
    strcpy(order,"tar -zxf ");
    strcat(order,_src);
    strcat(order," -C ");
    strcat(order,dest);
/*    char *parent=get_parentpwd(_src);
    chdir(parent);
    char *tmp=get_current_dir_name()*/;
    system(order);
}
