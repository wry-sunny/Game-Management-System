#ifndef __SYS_H
#define __SYS_H

#include<iostream>
#include<json/json.h>
#include"Client.h"
#include<string>
#include<errno.h>
#include<stdlib.h>
using namespace std;


class Sys
{
public:
    void put()
    {
        cout << "请输入id信息" << endl;
    }
    void run()
    {
        while(1)
        {
            put();
            string id;
            string str;
            cin >> id;
            if(id == "exit")
            {
                Client::getClient()->Send(id);
                Client::getClient()->Close();
                exit(0);
            }
            Client::getClient()->Send(id);
            Client::getClient()->Recv(str);
            Json::Value root;
            Json::Reader read;
            if(-1 == read.parse(str,root))
            {
                cerr << "json parse fail;errno:" << errno << endl;
                return;
            }
            cout << root["REASON"] <<endl;
        }
    }
};

#endif
