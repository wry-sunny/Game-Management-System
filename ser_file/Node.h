#ifndef __NODE_H
#define __NODE_H

#include<iostream>
#include<string>
using namespace std;

class Node
{
public:
    Node()
    {
        _next = NULL;
    }
    Node(Node& src)
    {
        _name = src._name;
        _id = src._id;
        _date = src._date; 
        _remark = src._remark;
        _limit = src._limit;
        _next = src._next;
    }
    Node& operator=(Node& src)
    {
        if(this == &src)
        {
            return *this;
        }
        
        _name = src._name;
        _id = src._id;
        _date = src._date; 
        _remark = src._remark;
        _limit = src._limit;
        _next = src._next;
    }

private:
    string _name;
    string _id;
    string _date;
    string _remark;
    string _limit;
    Node *_next;


    friend class Link_list;
};


#endif

