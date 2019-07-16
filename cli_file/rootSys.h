#ifndef __ROOTSYS_H
#define __ROOTSYS_H

#include"selecterPthread.h"
#include"recverPthread.h"
#include"Client.h"
#include<iostream>
using namespace std;

class rootSys
{
public:
    void put()
    {
        cout << "1.insert" << "   ";
        cout << "2.delete" << "   ";
        cout << "3.select" << "   ";
        cout << "4.update" << "   ";
        cout << "5.exit" << endl;
    }
    void run()
    {
        recverPthread* recver = new recverPthread();
        selecterPthread* selecter = new selecterPthread();
        while(1)
        {
            int n;
            put();
            cin >> n;
            switch(n)
            {
                case 1:Insert();break;
                case 2:Delete();break;
                case 3:Select();break;
                case 4:Update();break;
                case 5:Exit();return;
            }
            usleep(50000);
        }

    }
    void Insert()
    {
        cout << "请按顺序输入以下信息（NAME，ID，DATA，REMARK）" << endl;
        string name,id,date,remark;
        cin >> name;
        cin >> id;
        cin >> date;
        cin >> remark;
        Json::Value val;
        val["NAME"] = name;
        val["ID"] = id;
        val["DATE"] = date;
        val["REMARK"] = remark;
        val["TYPE"] = "INSERT";
        Client::getClient()->Send(val.toStyledString());
    }
    void Delete()
    {
        cout << "请输入要删除数据到ID" << endl;
        string id;
        cin >> id;
        Json::Value val;
        val["ID"] = id;
        val["TYPE"] = "DELETE";
        Client::getClient()->Send(val.toStyledString());
    }

    void Update()
    {
        cout << "请按顺序更新以下信息（NAME，ID，DATA，REMARK）" << endl;
        string name,id,date,remark;
        cin >> name;
        cin >> id;
        cin >> date;
        cin >> remark;
        Json::Value val;
        val["NAME"] = name;
        val["ID"] = id;
        val["DATE"] = date;
        val["REMARK"] = remark;
        val["TYPE"] = "UPDATE";
        Client::getClient()->Send(val.toStyledString());
    }

    void Select()
    {
        cout << "请输入要查询数据到ID" << endl;
        string id;
        cin >> id;
        Json::Value val;
        val["ID"] = id;
        val["FD"] = -1;
        val["TYPE"] = "SELECT";
        Client::getClient()->Send(val.toStyledString());
    }
    void Exit()
    {
        Json::Value val;
        val["TYPE"] = "EXIT";
        Client::getClient()->Send(val.toStyledString());
        Client::getClient()->Close();
    }
};


#endif
