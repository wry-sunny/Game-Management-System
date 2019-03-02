#include"view.h"
#include<map>

class Model
{
public:
	Model()
	{
		m.insert(make_pair(1, new insert_view()));
		m.insert(make_pair(2, new delete_view()));
		m.insert(make_pair(3, new update_view()));
		m.insert(make_pair(4, new find_view()));
		m.insert(make_pair(5, new show_view()));
	}
	~Model()
	{
		m.clear();
	}
private:
	map<int, View*> m;

	friend class Control;
};
