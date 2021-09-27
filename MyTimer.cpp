#include "MyTimer.h"
#include "MyOpenssl.h"
#include "MyCopy.h"
#include "MyCompress.h"
#include "MyPack.h"
#include <iostream>
using namespace std;


MyTimer::MyTimer(string src,string des,int max_time,int Is_Encryption,int Is_Pack,int Is_Compress,string password,QObject *parent=NULL):QObject(parent){
    this->_src=src;
    this->_des=des;
    this->_max_time=max_time;
    this->_Is_Compress=Is_Compress;
    this->_Is_Encryption=Is_Encryption;
    this->_Is_Pack=Is_Pack;
    this->_copy_input_password=password;
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MyTimer::backup);
    timer->start(_max_time);
}


void MyTimer::backup(){
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
    return;
}




MyTimer::~MyTimer(){
    timer->stop();
    backup();
}
