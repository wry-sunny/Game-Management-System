#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "control.h"
#include <string.h>
#include<ctype.h>

class System
{
public:
    System(){}
    System(System& src)
    {
        _name = src._name;
        _pw = src._pw;
    }
    System& operator=(System& src)
    {
        if(this == &src)
        {
            return *this;
        }
        _name = src._name;
        _pw = src._pw;

        return *this;

    }
    void Register()
    {
        int fp = open("info_file",O_RDWR|O_CREAT,0600);
        char buff[128] = {0};
        char tmp[128] = {0};
        char *brr[128] = {0};
        int i = 0;
        while(read(fp,buff,127) > 0)
        {
            strcat(tmp,buff);
        }
        if(strcmp(tmp,"\0") != 0)
        {
            char *arr[128] = {0};
        
            char *s = strtok(tmp,"\r\n");
            while(s != NULL)
            {
                arr[i++] = s;
                s = strtok(NULL,"\r\n");
            }
            s = strtok(arr[0]," ");
            brr[0] = s;
            i = 1;
            while(s != NULL && arr[i] != 0)
            {
                s = strtok(arr[i]," ");
                brr[i++] = s;
            }
        }
        
        cout << "请输入要注册到用户名：" << endl;
        cin >> _name;
        i = 0;
        while(brr[i] != 0)
        {
            if(_name == brr[i])
            {
                cout << "此用户名已被使用" << endl;
                cout << "请重新输入要注册到用户名：" << endl;
                cin >> _name;
                i = 0;
                continue;
            }
            i++;
        }
      
        cout << "请设置密码:" << endl;
        cin >> _pw;
        
        string a;
        string b;
        string c;
        b = _name + " ";
        a = b + _pw;
        c = a + "\n";
        const char *d = c.c_str();
        lseek(fp,0,SEEK_END);
        write(fp,d,strlen(d));

        close(fp);
    }
    void login()
    {
        int fp = open("info_file",O_RDONLY | O_CREAT,0600);
        char buff[128] = {0};
        char *arr[128] = {0};
        char tmp[128] = {0};
        int i = 1;
        while(read(fp,buff,127) > 0)
        {
            strcat(tmp,buff);
        }
        if(strcmp(tmp,"\0") == 0)
        {
            cout << "您还没有账号，请先进行注册" << endl;
            close(fp);
            Register();
            int fp = open("info_file",O_RDONLY);
            while(read(fp,buff,127) > 0)
            {
                strcat(tmp,buff);
            }
        }
        if(tmp != 0)
        {
        
            char *s = strtok(tmp," ");
            arr[0] = s;
            while(s != NULL)
            {
                if(i%2 != 0)
                {
                    s = strtok(NULL,"\r\n");
                    arr[i++] = s;
                }
                else
                {
                    s = strtok(NULL," ");
                    arr[i++] = s;
                }
            }
        }

        i = 0;
        int j = 0;
        int count = 0;
        cout << "请输入所要登录的用户名：" << endl;
        cin >> _name;
        while(arr[i] != 0)
        {
            while(arr[i] != 0)
            {
                if(_name == arr[i])
                {
                    j = i+1;
                    cout << "请输入密码：" << endl;
                    cin >> _pw;
                    while(1)
                    {
                        if(_pw == arr[j])
                        {
                            Control control;
                            control.process();
                            close(fp);
                            return;
                        }
                        if(count == 3)
                        {
                            break;
                        }
                        else
                        {
                            cout << "密码错误，请重新输入：" << endl;
                            cin >> _pw;
                            count++;
                        }
                    }
                }
                i+=2;
            }
            cout << "用户名或密码错误，请重新输入用户名：" << endl;
            cin >> _name;
            i = 0;
            count = 0;
        }
        close(fp);
    }
private:
    string _name;
    string _pw;
};


#endif
