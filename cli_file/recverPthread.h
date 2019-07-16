#ifndef __RECVERPTHREAD_H
#define __RECVERPTHREAD_H

#include"Server.h"
#include<iostream>
#include<stdlib.h>
#include"Client.h"
#include<pthread.h>
using namespace std;

class recverPthread
{
public:
    recverPthread()
    {
        pthread_t id;
        pthread_create(&id,NULL,run,NULL);
    }
    static void* run(void* arg)
    {
        while(1)
        {
            string str;
            Client::getClient()->Recv(str);
            if(str == "\0")
            {
                return 0;
            }
            Json::Value root;
            Json::Reader read;
            if(-1 == read.parse(str,root))
            {
                cerr<<"json prase fail;errno:"<<errno<<endl;
            }
            if(root["TYPE"] == "SELECT" && root["FD"] != -1)
            {
                int fd = root["FD"].asInt();
                Server::getServer()->Send(fd,str);
            }
            else if(root["TYPE"] == "SELECT" && root["FD"] == -1 && root["REASON"] == "ok")
            {
                cout<<"name:"<< root["NAME"] <<"id:"<< root["ID"] <<"date:"<< root["DATE"] <<"remark:"<< root["REMARK"];
            }
            else
            {
                cout << root["REASON"] << endl;
            }
        }
    }
};

#endif
