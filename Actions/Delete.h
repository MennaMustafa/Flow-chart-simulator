#include"Action.h"

class Delete :public Action
{
public :
	Delete(ApplicationManager*pApp) :Action(pApp){}
	void ReadActionParameters(){}
	void Execute();
};