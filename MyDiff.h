#ifndef MYDIFF_H
#define MYDIFF_H

#include "mainwindow.h"
#include <string>
#include "MyCompress.h"
#include "MyPack.h"
using namespace std;

class MyDiff{
private:
    string _src;
    string _des;
public:
    MyDiff(string src,string des);
    void FindDiff();
};

#endif // MYDIFF_H
