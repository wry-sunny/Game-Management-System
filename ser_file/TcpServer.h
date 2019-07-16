#ifndef __TCPSERVER_H
#define __TCPSERVER_H

#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<netinet/in.h>
#include<sys/socket.h>
#include<errno.h>
#include<arpa/inet.h>
using namespace std;

class TcpServer
{
private:
    string _ip;
    unsigned short _port;
    int _listenFd;
public:
    TcpServer(string ip,unsigned short port)
    {
	    _ip = ip;
	    _port = port;
	    _listenFd = socket(AF_INET,SOCK_STREAM,0);
	    if(-1 == _listenFd)
	    {
		    cerr<<"listenFd creat fail;errno:"<<errno<<endl;
		    return;
	    }	

	    struct sockaddr_in saddr;
	    saddr.sin_family = AF_INET;
	    saddr.sin_port = htons(_port);
	    saddr.sin_addr.s_addr = inet_addr(_ip.c_str());

	    if(-1 == bind(_listenFd,(struct sockaddr*)&saddr,sizeof(saddr)))
	    {
		    cerr<<"1 bind fail;errno:"<<errno<<endl;
		    return;
	    }	

	    if(-1 == listen(_listenFd,20))
	    {
		    cerr<<"listen fail;errno:"<<errno<<endl;
		    return;
	    }

    }

    int acceptClient()
	{ 
        struct sockaddr_in caddr;
        int len = sizeof(caddr);
        int c = accept(_listenFd,(struct sockaddr*)&caddr,(socklen_t *)&len);

        return c;
	}

    int sendToClient(int cliFd,const string& str)
    {
        if(-1 == send(cliFd,str.c_str(),str.size(),0))
        {
            cerr << "send fail;errno:" << errno << endl;
            return 0;
        }
        return 1;
    }
    int recvFromClient(int cliFd,string& str)
    {
        char buff[256] = {0};
        if(0 >= recv(cliFd,buff,256,0))
        {
            return 0;
        }
        str = buff;
        return 1;
    }
    void closeClient(int cliFd)
    {
        close(cliFd);
    }
    int getListenFd()
    {
        return _listenFd;
    }
    string& getIp()
    {
        return _ip;
    }
    unsigned short getPort()
    {
        return _port;
    }
};

#endif
