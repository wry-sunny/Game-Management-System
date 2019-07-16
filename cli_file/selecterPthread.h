#ifndef __SELECTERPTHREAD_H
#define __SELECTERPTHREAD_H

#include<pthread.h>
#include<iostream>
#include<json/json.h>
#include<event.h>
#include"Client.h"
#include"Server.h"
using namespace std;

class selecterPthread
{
public:
    selecterPthread()
    {
        pthread_t id;
        pthread_create(&id,NULL,run,_base);
    }
    static void* run(void* arg)
    {
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
        string id;
        Server::getServer()->Recv(fd,id);
        if(id == "exit")
        {
            Server::getServer()->Close(fd);
            return;
        }
        Json::Value val;
        val["TYPE"] = "SELECT";
        val["ID"] = id;
        val["FD"] = fd;
        Client::getClient()->Send(val.toStyledString());
    }
private:
    static event_base* _base;
};
event_base* selecterPthread::_base = event_base_new();



#endif
