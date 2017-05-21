#include"Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

class Select : public Action
{
	Statement * s;
	Connector* c;
public:
	Select(ApplicationManager *pAppManager) : Action(pAppManager){}
	virtual void ReadActionParameters();
	virtual void Execute();
};