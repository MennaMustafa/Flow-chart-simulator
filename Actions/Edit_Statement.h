#include "Action.h"

#include "..\Statements\Start_End.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

class Edit_Statement : public Action 
{
private:
	Statement*S;
	Output *pOut;
	Input *pIn;
public:
	Edit_Statement(ApplicationManager*Ap): Action(Ap){}
	
	virtual void ReadActionParameters();
	virtual void Execute();



};