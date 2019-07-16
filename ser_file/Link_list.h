#ifndef __BLACKLIST_H
#define __BLACKLIST_H

#include"Node.h"
#include<iomanip>
class Link_list
{
public:
    Link_list()
    {
        _count = 0;
    }
	Link_list(Link_list& src)
	{
		Node *p = src._head._next;
		Node *q = &_head;
		for (int i = 0; i < src._count; i++)
		{
			Node *s = new Node;
			s->_name = p->_name;
			s->_id = p->_id;
			s->_date = p->_date;
			s->_remark = p->_remark;
			s->_limit = p->_limit;
			s->_next = q->_next;
			q->_next = s;
			_count++;
			q = q->_next;
			p = p->_next;
		}
	}
	Link_list& operator=(Link_list& src)
	{
		if (this == &src)
		{
			return *this;
		}
		Node *p = src._head._next;
		Node *q = &_head;
		if (NULL != _head._next)
		{
			delete _head._next;
		}
		for (int i = 0; i < src._count; i++)
		{
			Node *s = new Node;
			s->_name = p->_name;
			s->_id = p->_id;
			s->_date = p->_date;
			s->_remark = p->_remark;
			s->_limit = p->_limit;
			s->_next = q->_next;
			q->_next = s;
			_count++;
			q = q->_next;
			p = p->_next;
		}
		return *this;
	}
	void Insert(string name, string id, string date, string remark, string limit)
	{
		Node *p = &_head;

		while (p->_next != NULL)
		{
			p = p->_next;
		}

		Node *s = new Node;
		s->_name = name;
		s->_id = id;
		s->_date = date;
		s->_remark = remark;
		s->_limit = limit;
		s->_next = p->_next;
		p->_next = s;

		_count++;
	}
	void Update(string id)
	{
		Node *p = _head._next;

		while (p != NULL)
		{
			if (p->_id == id)
			{
		        cout<< "please input new name,id,date,remark,limit" << endl;
		        string name;
		        string nid;
		        string date;
		        string remark;
		        string limit;
		        cin >> name >> nid >> date >> remark >> limit;
		        if (name != "0")
		        {
			        p->_name = name;
		        }
		        if (nid != "0")
		        {
			        p->_id = nid;
		        }
		        if (date != "0")
		        {
			        p->_date = date;
		        }
		        if (remark != "0")
		        {
			        p->_remark = remark;
		        }
		        if (limit != "0")
		        {
			        p->_limit = limit;
			    }
				break;
		    }
			p = p->_next;
		}
        if(p == NULL)
        {
            cout << "not find id" << endl;
        }
	}
	void Delete(string id)
	{
		Node *p = &_head;
		int count = _count;
		while (p->_next != NULL)
		{
			if (p->_next->_id == id)
			{
				Node *q = p->_next;
				p->_next = q->_next;

				delete q;
				_count--;
				break;
			}

			p = p->_next;
		}

		if (p->_next == NULL && _count == count)
		{
			cout << "not found id" << endl;
		}

	}
	void Find(string id)
	{
		Node *p = _head._next;

		while (p != NULL)
		{
			if (p->_id == id)
			{
				cout << "name" << "   " << setw(8);
				cout << "id" << "     " << setw(8);
				cout << "date" << "       " << setw(8);
				cout << "remark" << "       " << setw(8);
				cout << "limit" << endl;

				cout << p->_name << "   " << setw(10);
				cout << p->_id << "   " << setw(10);
				cout << p->_date << "   " << setw(10);
				cout << p->_remark << "   " << setw(10);
				cout << p->_limit << endl;
				cout << endl;
				break;
			}
			p = p->_next;
		}
		if (p == NULL)
		{
			cout << "not found id" << endl;
		}


	}

	void Show()
	{
		Node *p = _head._next;

		cout << "name" << "   " << setw(8);
		cout << "id" << "      " << setw(8);
		cout << "date" << "      " << setw(8);
		cout << "remark" << "      " << setw(8);
		cout << "limit" << endl;

		while (p != NULL)
		{
			cout << p->_name << "   " << setw(10);
			cout << p->_id << "   " << setw(10);
			cout << p->_date << "    " << setw(10);
			cout << p->_remark << "    " << setw(10);
			cout << p->_limit << endl;
			cout << endl;
			p = p->_next;
		}
	}
private:
    Node _head;
    int _count;

};


#endif

