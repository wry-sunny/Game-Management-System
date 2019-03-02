#ifndef __VIEW_H
#define __VIEW_H

#include"DataBase.h"


class View
{
public:
	View(){}
	virtual void process() = 0;
	virtual ~View()
	{}
protected:
	static DataBase* _base;
};
DataBase* View::_base = DataBase::getBase();



class insert_view : public View
{
public:
	insert_view()
		:View()
	{}
	void process()
	{
		cout << "please input name,id,date,remark,limit" << endl;
		string name;
		string id;
		string date;
		string remark;
		string limit;
		cin >> name >> id >> date >> remark >> limit;
		_base->Insert(name, id, date, remark, limit);
	}
	~insert_view()
	{}
};

class delete_view : public View
{
public:
	delete_view()
		:View()
	{}

	void process()
	{
		cout << "please input id" << endl;
		string id;
		cin >> id;
		_base->Delete(id);
	}

	~delete_view()
	{}
};

class update_view : public View
{
public:
	update_view()
	:View()
	{}

	void process()
	{
		cout << "please input id" << endl;
		string id;
		cin >> id;
		_base->Update(id);
	}

	~update_view()
	{}
};

class find_view : public View
{
public:
	find_view()
	:View()
	{}

	void process()
	{
		cout << "please input id" << endl;
		string id;
		cin >> id;
		_base->Find(id);
	}

	~find_view()
	{}
};

class show_view : public View
{
public:
	show_view()
	:View()
	{}

	void process()
	{
		_base->Show();
	}

	~show_view()
	{}
};

#endif
