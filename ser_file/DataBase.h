#ifndef __BATABASE_H
#define __BATABASE_H

#include<pthread.h>
#include<errno.h>
#include<json/json.h>
#include<string.h>
#include<iostream>
#include<mysql/mysql.h>
#include"Server.h"
using namespace std;

//pthread_mutex_t mutex;

class DataBase
{
public:
	static DataBase* getDataBase()
	{
        if(NULL == _dataBase)
        {
            pthread_mutex_lock(&mutex);
		    if (NULL == _dataBase)
		    {
			    _dataBase = new DataBase();
		    }
            pthread_mutex_unlock(&mutex);
        }
		return _dataBase;
	}
    
    int insertIntoRoot(Json::Value &val)
    {
        MYSQL_RES *mp_res;
        MYSQL_ROW mp_row;
        char cmd[100] = "select * from root where name='";
        strcat(cmd,val["NAME"].asString().c_str());
        strcat(cmd,"';");
        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr<<"insertRoot query fail;errno:"<<errno<<endl;
            return -1;
        }
        mp_res = mysql_store_result(_mpcon);
        mp_row = mysql_fetch_row(mp_res);
        if(mp_row == NULL)
        {
		    char cnd[100] = "insert into root values('";
            strcat(cnd,val["NAME"].asString().c_str());
            strcat(cnd,"','");
            strcat(cnd,val["PW"].asString().c_str());
            strcat(cnd,"');");
            if(mysql_real_query(_mpcon,cnd,strlen(cmd)))
            {
                cerr << "insertRoot query fail;errno:" << errno << endl;
                return -1;
            }

        }
        else if(mp_row[0] == val["NAME"].asString())
        {
            return 0;
        }

        return 1;
        
    }

	int selectIntoRoot(Json::Value &val)
	{
        MYSQL_RES *mp_res;
        MYSQL_ROW mp_row;
        char cmd[100] = "select * from root where name='";
        strcat(cmd,val["NAME"].asString().c_str());
        strcat(cmd,"';");

        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr<<"selectRoot query fail;errno:"<<errno<<endl;
            return -1;
        }
        mp_res = mysql_store_result(_mpcon);
        mp_row = mysql_fetch_row(mp_res);
        if(mp_row == NULL)
        {
            return 0;
        }
        else if(mp_row[1] != val["PW"].asString())
        {
            return 1;
        }
        mysql_free_result(mp_res);
        return 2;
    }

	int insertIntoUser(Json::Value &val)
	{
		char cmd[100] = "insert into user values('";
        strcat(cmd,val["NAME"].asString().c_str());
        strcat(cmd,"','");
        strcat(cmd,val["ID"].asString().c_str());
        strcat(cmd,"','");
        strcat(cmd,val["DATE"].asString().c_str());
        strcat(cmd,"','");
        strcat(cmd,val["REMARK"].asString().c_str());
        strcat(cmd,"');");
        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr << "insertUser query fail;errno:" << errno << endl;
            return -1;
        }
        return 1;
	}

	int deleteIntoUser(Json::Value &val)
	{
        MYSQL_RES *mp_res;
        MYSQL_ROW mp_row;
        char cmd[100] = "select * from user where id='";
        strcat(cmd,val["ID"].asString().c_str());
        strcat(cmd,"';");
        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr<<"delete 1 Root query fail;errno:"<<errno<<endl;
            return -1;
        }
        mp_res = mysql_store_result(_mpcon);
        mp_row = mysql_fetch_row(mp_res);
        if(mp_row == NULL)
        {
		    return 0;
        }
		char cnd[100] = "delete from user where id='";
        strcat(cnd,val["ID"].asString().c_str());
        strcat(cnd,"';");
        if(mysql_real_query(_mpcon,cnd,strlen(cnd)))
        {
            cerr << "delete 3 user query fail;errno:" << errno << endl;
            return -1;
        }
        return 1;
	}

	int updateIntoUser(Json::Value &val)
	{
        MYSQL_RES *mp_res;
        MYSQL_ROW mp_row;
        char cnd[100] = "select * from user where id='";
        strcat(cnd,val["ID"].asString().c_str());
        strcat(cnd,"';");
        if(mysql_real_query(_mpcon,cnd,strlen(cnd)))
        {
            cerr<<"insertRoot query fail;errno:"<<errno<<endl;
            return -1;
        }
        mp_res = mysql_store_result(_mpcon);
        mp_row = mysql_fetch_row(mp_res);
        if(mp_row == NULL)
        {
		    return 0;
        }
		char cmd[100] = "update user SET name='";
        strcat(cmd,val["NAME"].asString().c_str());
        strcat(cmd,"',date='");
        strcat(cmd,val["DATE"].asString().c_str());
        strcat(cmd,"',remark='");
        strcat(cmd,val["REMARK"].asString().c_str());
        strcat(cmd,"' where id='");
        strcat(cmd,val["ID"].asString().c_str());
        strcat(cmd,"';");
        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr << "updateuser query fail;errno:" << errno << endl;
            return -1;
        }
        return 1;
	}

	int selectIntoUser(int fd,Json::Value &val)
	{
        MYSQL_RES *mp_res;
        MYSQL_ROW mp_row;
        char cmd[100] = "select * from user where id='";
        strcat(cmd,val["ID"].asString().c_str());
        strcat(cmd,"';");

        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr<<"selectuser query fail;errno:"<<errno<<endl;
            return -1;
        }
        mp_res = mysql_store_result(_mpcon);
        mp_row = mysql_fetch_row(mp_res);
        if(mp_row == NULL)
        {
            return 0;
        }
        if(val["FD"] == -1)
        {
            Json::Value root;
            root["NAME"] = mp_row[0];
            root["ID"] = mp_row[1];
            root["DATE"] = mp_row[2];
            root["REASON"] = "ok";
            root["TYPE"] = "SELECT";
            root["FD"] = -1;
            root["REMARK"] = mp_row[3];
            Server::getServer()->Send(fd,root.toStyledString());
        }
        //cout<<"name:"<<mp_row[0]<<"     "<<"id:"<<mp_row[1] << "     " <<"date:"<<mp_row[2]<<"     "<<"remark:"<<mp_row[3]<<endl;
        mysql_free_result(mp_res);
        return 1;
	}
private:
	DataBase()
    {
        _mpcon = mysql_init((MYSQL *)0);
        if(!mysql_real_connect(_mpcon,"127.0.0.1","root","111111",NULL,3306,NULL,0))
        {
            cerr << "sql connect fail;errno:" << errno << endl;
            return;
        }
        if(mysql_select_db(_mpcon,"manage"))
        {
            cerr << "select fail;errno:" << errno << endl;
            return;
        }
    }
	static DataBase* _dataBase;
	MYSQL* _mpcon;
};
DataBase* DataBase::_dataBase = NULL;

#endif
