#include"Action.h"
#include<map>

class Run :public Action
{
private:
	map<string, double> variables;
public:
	Run(ApplicationManager *a) :Action(a){}
	void ReadActionParameters(){}
	virtual void Execute();

};