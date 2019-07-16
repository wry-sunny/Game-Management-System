#ifndef __SHAREQUEUE_H
#define __SHAREQUEUE_H

#include<iostream>
#include<queue>
#include<json/json.h>
#include<string>
using namespace std;

class shareQueue
{
public:
    static shareQueue* getshareQueue()
    {
        if(NULL == _shareQueue)
        {
            pthread_mutex_lock(&mutex);
            if(NULL == _shareQueue)
            {
                _shareQueue = new shareQueue();
            }
            pthread_mutex_unlock(&mutex);
        }
        return _shareQueue;
    }
    void push(pair<int,Json::Value> data)
    {
        _que.push(data);
    }
    pair<int,Json::Value> pop()
    {
        pair<int,Json::Value> data;
        pthread_mutex_lock(&mutex);
        while(_que.empty()){}
        data = _que.front();
        _que.pop();
        pthread_mutex_unlock(&mutex);
        return data;
    }
private:
    shareQueue(){}
    static shareQueue* _shareQueue;
    queue<pair<int,Json::Value> > _que;
};
shareQueue* shareQueue::_shareQueue = NULL;

#endif
