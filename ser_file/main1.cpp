#include<iostream>
#include"DataBase.h"
#include<json/json.h>
using namespace std;

int main()
{
    Json::Value val;
    /*val["NAME"] = "ws";
    val["PW"] ="123456";*/
    val["NAME"] = "ws";
    val["PW"] = "123456";
    val["ID"] = "123456";
    val["DATE"] = "2018/12/24";
    val["REMARK"] = "随地吐痰";
    DataBase::getDataBase()->selectIntoRoot(val);
    return 0;
}
