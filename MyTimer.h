#ifndef MYTIMER_H
#define MYTIMER_H

#include "mainwindow.h"
#include <QObject>
#include <string>
#include <QTimerEvent>

using namespace std;

class MyTimer:public QObject{
private:
    string _src;
    string _des;
    int _max_time;
    int _id;
    int _Is_Compress;
    int _Is_Encryption;
    int _Is_Pack;
    string _copy_input_password;
public:
    MyTimer(string src,string des, int max_time,int Is_Encryption,int Is_Pack,int Is_Compress,string password,QObject *parent);
    void timerEvent(QTimerEvent *event) override;
    int get_id();
    void MyTimerEvent();
};

#endif // MYTIMER_H
