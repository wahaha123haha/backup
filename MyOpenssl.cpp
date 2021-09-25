#include "MyOpenssl.h"

MyOpenssl::MyOpenssl(string src,string des){
    this->_src=src;
    this->_des=des;
}

void MyOpenssl::Encryption(string password){
    string relative(get_myrelativecwd((char*)_src.c_str()));
    string parentpwd(get_parentpwd((char*)_src.c_str()));
    chdir(parentpwd.c_str());
    string order="tar -zcvf - "+relative+"|openssl des3 -salt -k "+password+"|dd of="+_des+"/"+relative+".des3";
    system(order.c_str());
}

void MyOpenssl::Deciphering(string password){
    string order="dd if="+_src+"|openssl des3 -d -k "+password+"|tar zxf - -C "+_des;
    system(order.c_str());
}
