#ifndef __SYS_H
#define __SYS_H

#include<pthread.h>
#include<iostream>
#include<json/json.h>
#include<event.h>
#include"Server.h"
#include"control.h"
#include"workPthread.h"
using namespace std;

class Sys
{
public:
    void run()
    {
        workPthread* wp[3];
        for(int i = 0;i < 3;i++)
        {
            wp[i] = new workPthread();
        }
        struct event* listen_event = event_new(_base,Server::getServer()->getListenFd(),EV_READ|EV_PERSIST,listen_cb,_base);
        event_add(listen_event,NULL);
        event_base_dispatch(_base);
    }
    static void listen_cb(int fd,short event,void* arg)
    {
        int cliFd = Server::getServer()->Accept();
        struct event* cli_event = event_new(_base,cliFd,EV_READ|EV_PERSIST,cli_cb,NULL);
        event_add(cli_event,NULL);
    }
    static void cli_cb(int fd,short event,void *arg)
    {
        string str;
        Server::getServer()->Recv(fd,str);
        Json::Value root;
        Json::Reader read;
        if(-1 == read.parse(str,root))
        {
            cerr << "read fail;errno:" << errno << endl;
            return;
        }
        if(root["TYPE"] == "EXIT")
        {
            Server::getServer()->Close(fd);
            return;
        }
        shareQueue::getshareQueue()->push(make_pair(fd,root));
        //Control::getControl()->process(fd,root);
    }
private:
    static event_base* _base;
};
event_base* Sys::_base = event_base_new();



#endif
