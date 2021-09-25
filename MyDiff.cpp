#include "MyDiff.h"

MyDiff::MyDiff(string src,string des){
    this->_src=src;
    this->_des=des;
}

void MyDiff::FindDiff(){
    auto gz=_src.find(".tar.gz");
    auto tar=_src.find(".tar");
    string pwd(get_parentpwd((char*)_src.c_str()));
    if(gz!=string::npos){
        MyCompress mc((char*)_src.c_str(),(char*)pwd.c_str());
        mc.ReCompress();
        string t_rcwd(get_myrelativecwd((char*)_src.c_str()));
        string rcwd=t_rcwd.substr(0,t_rcwd.size()-7);
        string order="diff -r "+_des+" "+pwd+'/'+rcwd+">"+pwd+"/diff.txt";
        system(order.c_str());
        string del="rm -rf "+pwd+"/"+rcwd;
        system(del.c_str());
        return;
    }
    if(tar!=string::npos){
        MyPack mp((char*)_src.c_str(),(char*)pwd.c_str());
        mp.RePack();
        string t_rcwd(get_myrelativecwd((char*)_src.c_str()));
        string rcwd=t_rcwd.substr(0,t_rcwd.size()-4);
        string order="diff -r "+_des+" "+pwd+'/'+rcwd+">"+pwd+"/diff.txt";
        system(order.c_str());
        string del="rm -rf "+pwd+"/"+rcwd;
        system(del.c_str());
        return;
    }
    string order="diff -r "+_des+" "+_src+">"+pwd+"/diff.txt";
    system(order.c_str());
}
