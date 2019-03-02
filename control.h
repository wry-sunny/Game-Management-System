#ifndef __CONTROL_H
#define __CONTROL_H

#include"model.h"
#include<stdio.h>
#include<fcntl.h>

class Control
{
public:
	Control()
    {}

	Control(Control& src)
    {
        _model = src._model;
    }
	Control& operator=(Control& src)
    {
        if(this == &src)
        {
            return *this;
        }
        _model = src._model;

        return *this;
    }
	void process()
	{
	    //int fp = open("fun_file",O_RDONLY);
	    //char buff[128]= { 0};
    	//while(read(fp,buff,127) > 0)
	    //{
    	//    read(fp,buff,127);
     //   }
        while(1)
        {
            cout << "ÊäÈë";
		    int c;
            cin >> c;
            if(c == 6)
            {
                break;
            }
            _model.m[c]->process();
        }
        //close(fp);
    }
private:
	Model _model;
};



#endif
