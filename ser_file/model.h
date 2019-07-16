#include"view.h"
#include<map>
#include<string>

class Model
{
public:
	Model()
	{
		m.insert(make_pair("LOGIN", new login_view()));
		m.insert(make_pair("REGISTER", new register_view()));
		m.insert(make_pair("INSERT", new insert_view()));
		m.insert(make_pair("DELETE", new delete_view()));
		m.insert(make_pair("SELECT", new select_view()));
		m.insert(make_pair("UPDATE", new update_view()));

	}
	~Model()
	{
		m.clear();
	}
private:
	map<string, View*> m;
    friend class Control;	
};
