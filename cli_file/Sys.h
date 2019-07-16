#ifndef __SYS_H
#define __SYS_H

#include"rootSys.h"
#include<iostream>
#include<stdlib.h>
using namespace std;


class Sys
{
public:
    void put()
    {
        cout << "1.login" << "    ";
        cout << "2.register" << "    ";
        cout << "3.exit" <<endl;
    }
    void run()
    {
        while(1)
        {
            int n;
            put();
            cin >> n;
            switch(n)
            {
                case 1:Login();break;
                case 2:Register();break;
                case 3:Exit();break;
            }
        }
    }
    void Login()
    {
        cout << "请输入用户名和密码" << endl;
        while(1)
        {
            string name,pw;
            cin >> name >> pw;
            Json::Value val;
            val["NAME"] = name;
            val["PW"] = pw;
            val["TYPE"] = "LOGIN";
            Client::getClient()->Send(val.toStyledString());
            string str;
            Client::getClient()->Recv(str);
            Json::Value root;
            Json::Reader read;
            if(-1 == read.parse(str,root))
            {
                cerr<<"json prase fail;errno:"<<errno<<endl;
                return;
            }
            if(root["REASON"] == "ok")
            {
                _rootSys->run();
                break;
            }
            else
            {
                cout << root["REASON"].asString() << endl;
            }
        }
    }
    void Register()
    {
        cout << "请输入用户名和密码" << endl;
        string name,pw;
        cin >> name >> pw;
        Json::Value val;
        val["NAME"] = name;
        val["PW"] = pw;
        val["TYPE"] = "REGISTER";
        Client::getClient()->Send(val.toStyledString());
        string str;
        Client::getClient()->Recv(str);
        Json::Value root;
        Json::Reader read;
        if(-1 == read.parse(str,root))
        {
            cerr<<"json prase fail;errno:"<<errno<<endl;
            return;
        }
        if(root["REASON"] == "ok")
        {
            cout << "注册成功，已为您自动登录" << endl;
            _rootSys->run();
        }
        else
        {
            cout << root["REASON"].asString() << endl;
        }

    }
    void Exit()
    {
        exit(0);
    }
private:
    rootSys* _rootSys;
};


#endif
