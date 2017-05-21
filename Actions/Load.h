#include "Action.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <fstream>

class Load : public Action {
private:
	ifstream InFile;
	Output*pOut;
public:

	Load(ApplicationManager*Ap);
	void ReadActionParameters(){};
	virtual void Execute();

};