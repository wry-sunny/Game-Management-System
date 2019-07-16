#ifndef __WORKPTHREAD_H
#define __WORKPTHREAD_H

#include<iostream>
#include<pthread.h>
#include"shareQueue.h"
using namespace std;

class workPthread
{
public:
    workPthread()
    {
        pthread_t id;
        pthread_create(&id,NULL,run,NULL);
    }
    static void* run(void *arg)
    {
        while(1)
        {
            pair<int,Json::Value> data = shareQueue::getshareQueue()->pop();
            Control::getControl()->process(data.first,data.second);
        }
    }
};

#endif
