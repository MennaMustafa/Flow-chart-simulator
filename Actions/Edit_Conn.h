#include "Action.h"
#include "..\Statements\Connector.h"
#include "..\Statements\Start_End.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

class Edit_Conn : public Action 
{
private:
	Statement* Source;
	Statement* Dist;
	Connector*C;
public:
	Edit_Conn(ApplicationManager*Ap);
	
	virtual void ReadActionParameters();
	virtual void Execute();

};