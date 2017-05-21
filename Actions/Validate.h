#include "Action.h"

#include "..\Statements\Start_End.h"
#include "..\Statements\Conditional.h"
#include "..\Statements\Connector.h"
#include "..\Statements\ReadWrite.h"
#include "..\Statements\SingleOp.h"
#include "..\Statements\SmplAssign.h"
#include "..\Statements\Variable.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

class Validate : public Action 
{
private:
	Statement*S;
	Statement**List;
	Connector**CList;
	Output*pOut;
	bool Valid;
public:

	Validate(ApplicationManager*A) : Action(A) {}
	virtual void Execute();
	bool getVaild();
	void ReadActionParameters(){}
	~Validate(){}
};