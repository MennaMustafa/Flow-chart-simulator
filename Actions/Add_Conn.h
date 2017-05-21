#include"..\Statements\Connector.h"

#include"Action.h"

class Add_Conn :public Action
{
	Statement* S;
	Statement* D;
public:
	Add_Conn(ApplicationManager* pAppManager) : Action(pAppManager){}

	virtual void ReadActionParameters();
	virtual void Execute();

};