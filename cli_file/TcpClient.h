#ifndef __TCPCLIENT_H
#define __TCPCLIENT_H

#include<iostream>
#include<string>
#include<unistd.h>
#include<netinet/in.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;

class TcpClient
{
private:
    string _ip;
    unsigned short _port;
    int _fd;
public:
    TcpClient(string ip,unsigned short port)
	{
        _ip = ip;
        _port = port;
		_fd = socket(AF_INET,SOCK_STREAM,0);
		if(-1 == _fd)
		{
			cerr << "fd creat fail;errno:" << errno << endl;
			return;
		}

		struct sockaddr_in saddr;
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons(_port);
		saddr.sin_addr.s_addr = inet_addr(_ip.c_str());

		if(-1 == connect(_fd,(struct sockaddr*)&saddr,sizeof(saddr)))
		{
			cerr << "connect fail;errno:" << errno << endl;
			return;
		}

	}
    int sendToServer(const string& str)
    {
        if(-1 == send(_fd,str.c_str(),str.size(),0))
        {
            cerr << "send fail;errnoo:" << errno << endl;
            return 0;
        }
        return 1;
    }
    int recvFromServer(string& str)
    {
        char buff[128] = {0};
        if(0 >= recv(_fd,buff,128,0))
        {
            return 0;
        }
        str = buff;
        return 1;
    }
    void closeClient()
    {
        close(_fd);
    }
    int getFd()
    {
        return _fd;
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
