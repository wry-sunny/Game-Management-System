#include<iostream>
#include<stdlib.h>
#include"Sys.h"
using namespace std;


int main()
{
    /*
    string str;
    while(1)
    {
        Client::getClient()->Send("hello");
        Client::getClient()->Recv(str);
        cout <<  str << endl;
    }*/

    Sys s;
    s.run();
    exit(0);
}
