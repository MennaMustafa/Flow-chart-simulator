#include"Action.h"
#include<map>

class Debug :public Action
{
private:
	map<string, double> variables;
public:
	Debug(ApplicationManager *a) :Action(a){}
	void ReadActionParameters(){}
	virtual void Execute();

};