#ifndef MYPACK_H
#define MYPACK_H
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

class MyPack{
private:
    char _src[1024];
    char _des[1024];
public:
    MyPack(char *src,char *des);
    void Pack();
    void RePack();
};

#endif // MYPACK_H
