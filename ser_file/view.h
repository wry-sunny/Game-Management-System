#ifndef __VIEW_H
#define __VIEW_H

#include"DataBase.h"


class View
{
public:
	virtual void process(int fd,Json::Value& val) = 0;
protected:
	static DataBase* _base;
};
DataBase* View::_base = DataBase::getDataBase();

class login_view : public View
{
public:
	void process(int fd,Json::Value& val)
	{
        Json::Value result;
        result["TYPE"] = "LOGIN";
        int i = DataBase::getDataBase()->selectIntoRoot(val);
        if(i == 0)
        {
            result["REASON"] = "未找到用户名，请注册";
        }
        else if(i == 1)
        {
            result["REASON"] = "用户名或密码错误，请重新输入";
        }
        else if(i == 2)
        {
            result["REASON"] = "ok";
        }
        else
        {
            result["REASON"] = "error";
        }
        Server::getServer()->Send(fd,result.toStyledString());
	}
};

class register_view : public View
{
public:
	void process(int fd,Json::Value& val)
	{
        Json::Value result;
        result["TYPE"] = "REGISTER";
        int i = DataBase::getDataBase()->insertIntoRoot(val);
        if(i == 0)
        {
            result["REASON"] = "用户名已注册";
        }
        else if(i == 1)
        {
            result["REASON"] = "ok";
        }
        else
        {
            result["REASON"] = "error";
        }
        Server::getServer()->Send(fd,result.toStyledString());
	}
};

class insert_view : public View
{
public:
	void process(int fd,Json::Value& val)
	{
        Json::Value result;
        result["TYPE"] = "INSERT";
        if(DataBase::getDataBase()->insertIntoUser(val))
        {
            result["REASON"] = "插入成功";
        }
        else
        {
            result["REASON"] = "插入失败";
        }
        Server::getServer()->Send(fd,result.toStyledString());
	}
};

class delete_view : public View
{
public:
	void process(int fd,Json::Value& val)
	{
        Json::Value result;
        result["TYPE"] = "DELETE";
        int i = DataBase::getDataBase()->deleteIntoUser(val);
        if(i == 1)
        {
            result["REASON"] = "删除成功";
        }
        else if(i == 0)
        {
            result["REASON"] = "该ID不存在";
        }
        else
        {
            result["REASON"] = "删除失败";
        }
        Server::getServer()->Send(fd,result.toStyledString());
	}
};

class update_view : public View
{
public:
	void process(int fd,Json::Value& val)
	{
        Json::Value result;
        result["TYPE"] = "UPDATE";
        int i = DataBase::getDataBase()->updateIntoUser(val);
        if(i == 1)
        {
            result["REASON"] = "更新成功";
        }
        else if(i == 0)
        {
            result["REASON"] = "未找到需要更新的对象";
        }
        else
        {
            result["REASON"] = "更新失败";
        }
        Server::getServer()->Send(fd,result.toStyledString());
	}
};

class select_view : public View
{
public:
	void process(int fd,Json::Value& val)
	{
        Json::Value result;
        result["TYPE"] = "SELECT";
        int i = DataBase::getDataBase()->selectIntoUser(fd,val);
        if(i == 1)
        {
            if(val["FD"] != -1)
            {
                result["FD"] = val["FD"];
                result["REASON"] = "成功";
            }
            else
            {
                return;
            }
        }
        else if(i == 0)
        {
            result["REASON"] = "未找到该数据";
            if(val["FD"] != -1)
            {
                result["FD"] = val["FD"];
            }
            else
            {
                result["FD"] = -1;
            }
        }
        else
        {
            result["REASON"] = "查找失败";
        }
        Server::getServer()->Send(fd,result.toStyledString());
	}
};


#endif

