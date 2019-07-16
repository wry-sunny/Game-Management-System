#ifndef __SERVER_H
#define __SERVER_H

#include "TcpServer.h"
#include <pthread.h>

pthread_mutex_t mutex; 

class Server
{
private:
    Server()
    {
        _tcpServer = new TcpServer("127.0.0.1",6000);
    }
    static Server* _server;
    TcpServer* _tcpServer;
public:
    static Server* getServer()
    {
        if(NULL == _server)
        {
            pthread_mutex_lock(&mutex);
            if(NULL == _server)
            {
                _server = new Server();
            }
            pthread_mutex_unlock(&mutex);
        }
        return _server;

    }
    int Accept()
    {
        return _tcpServer->acceptClient();
    }
    int Send(int cliFd,const string& str)
    {
        return _tcpServer->sendToClient(cliFd,str);
    }
    int Recv(int cliFd,string& str)
    {
        return _tcpServer->recvFromClient(cliFd,str);
    }
    int getListenFd()
    {
        return _tcpServer->getListenFd();
    }
    void Close(int cliFd)
    {
        _tcpServer->closeClient(cliFd);
    }

};
Server* Server::_server = NULL;


#endif
