#ifndef MYCOMPRESS_H
#define MYCOMPRESS_H

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

class MyCompress{
private:
    char _src[1024];
    char _des[1024];
public:
    MyCompress(char *src,char *des);
    void Compress();
    void ReCompress();
};

#endif // MYCOMPRESS_H
