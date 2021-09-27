#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <string>
#include <QTimerEvent>
#include <QTimer>

using namespace std;

class MyTimer:public QObject{
private:
    string _src;
    string _des;
    int _max_time;
    int _Is_Compress;
    int _Is_Encryption;
    int _Is_Pack;
    string _copy_input_password;
    QTimer *timer;
public:
    MyTimer(string src,string des, int max_time,int Is_Encryption,int Is_Pack,int Is_Compress,string password,QObject *parent);
    void backup();
    ~MyTimer();
};

#endif // MYTIMER_H
