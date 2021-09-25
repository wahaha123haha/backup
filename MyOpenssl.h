#ifndef MYOPENSSL_H
#define MYOPENSSL_H

#include "mainwindow.h"
#include <string>
using namespace std;
class MyOpenssl{
private:
    string _src;
    string _des;
public:
    MyOpenssl(string src,string des);
    void Encryption(string password);
    void Deciphering(string password);
};

#endif // MYOPENSSL_H
