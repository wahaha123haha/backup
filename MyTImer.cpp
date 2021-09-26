#include "MyTimer.h"
#include <iostream>
using namespace std;
extern int time_flag;

MyTimer::MyTimer(string src,string des,int max_time,int Is_Encryption,int Is_Pack,int Is_Compress,string password,QObject *parent=NULL):QObject(parent){
    this->_src=src;
    this->_des=des;
    this->_max_time=max_time;
    this->_id=this->startTimer(this->_max_time);
    this->_Is_Compress=Is_Compress;
    this->_Is_Encryption=Is_Encryption;
    this->_Is_Pack=Is_Pack;
    this->_copy_input_password=password;
}

int MyTimer::get_id(){
    return _id;
}

void MyTimer::MyTimerEvent(){
    long long starttime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    long long currenttime;
    long long i;
    while(time_flag){
        currenttime=QDateTime::currentDateTime().toMSecsSinceEpoch();
        i=currenttime-starttime;
        if(i%_max_time!=0){
            i++;
            continue;
        }
        if(this->_Is_Encryption==1){
            MyOpenssl mo(_src,_des);
            mo.Encryption(_copy_input_password);
            i++;
            continue;
        }
        if(this->_Is_Compress==1){
            MyCompress mc((char*)_src.c_str(),(char*)_des.c_str());
            mc.Compress();
            i++;
            continue;
        }
        if(this->_Is_Pack==1){
            MyPack mp((char*)_src.c_str(),(char*)_des.c_str());
            mp.Pack();
            i++;
            continue;
        }
        MyCopy((char*)_src.c_str(),(char*)_des.c_str());
        i++;
    }
}

void MyTimer::timerEvent(QTimerEvent *event){
    if(event->timerId()==this->_id){
        if(this->_Is_Encryption==1){
            MyOpenssl mo(_src,_des);
            mo.Encryption(_copy_input_password);
            return;
        }
        if(this->_Is_Compress==1){
            MyCompress mc((char*)_src.c_str(),(char*)_des.c_str());
            mc.Compress();
            return;
        }
        if(this->_Is_Pack==1){
            MyPack mp((char*)_src.c_str(),(char*)_des.c_str());
            mp.Pack();
            return;
        }
        MyCopy((char*)_src.c_str(),(char*)_des.c_str());
    }
}

