#ifndef __BATABASE_H
#define __BATABASE_H

#include"Node.h"
#include"Link_list.h"

class DataBase
{
public:
	DataBase(){}
	static DataBase* getBase()
	{
		if (NULL == _Base)
		{
			_Base = new DataBase();
		}
		return _Base;
	}

	DataBase(DataBase& src)
	{
		Link_list list(src._list);
		_list = list;
	}
	DataBase& operator=(DataBase& src)
	{
		if (this == &src)
		{
			return *this;
		}
		Link_list list(src._list);
		_list = list;

		return *this;
	}
	void Insert(string name, string id, string date, string remark, string limit)
	{
		_list.Insert(name, id, date, remark, limit);
	}
	void Delete(string id)
	{
		_list.Delete(id);
	}
	void Update(string id)
	{
		_list.Update(id);
	}
	void Find(string id)
	{
		_list.Find(id);
	}
	void Show()
	{
		_list.Show();
	}
private:
	static DataBase* _Base;
	Link_list _list;
};
DataBase* DataBase::_Base = NULL;

#endif
