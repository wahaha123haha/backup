#ifndef MYTIMER2_H
#define MYTIMER2_H

#include "mainwindow.h"
#include <QObject>
#include <string>
#include <QTimerEvent>
#include <QTimer>

using namespace std;

class MyTimer2{
private:
    string _src;
    string _des;
    int _max_time;
    int _Is_Compress;
    int _Is_Encryption;
    int _Is_Pack;
    string _copy_input_password;
    QTimer _timer;
public:
    MyTimer2(string src,string des, int max_time,int Is_Encryption,int Is_Pack,int Is_Compress,string password);
    void MyTimerEvent();
};

#endif // MYTIMER2_H
