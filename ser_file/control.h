#ifndef __CONTROL_H
#define __CONTROL_H

#include<pthread.h>
#include"model.h"
#include<errno.h>
#include<stdio.h>
#include<fcntl.h>
#include<string>
using namespace std;

//pthread_mutex_t mutex;

class Control
{
public:
    static Control* getControl()
    {
        if(NULL == _control)
        {
            pthread_mutex_lock(&mutex);
            if(NULL == _control)
            {
                _control = new Control();
            }
            pthread_mutex_unlock(&mutex);
        }
        return _control;
    } 

	void process(int fd,Json::Value &val)
	{
        _model.m[val["TYPE"].asString()]->process(fd,val);
    }
private:
    Control(){}
    static Control* _control; 
	Model _model;
};
Control* Control::_control = NULL;


#endif
