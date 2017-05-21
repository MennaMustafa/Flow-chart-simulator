#include "Action.h"

#include <fstream>
class Save : public Action
{
private:
	ofstream OutFile;
public: 
	Save(ApplicationManager *pAppManager);
	void ReadActionParameters(){}
	void Execute();
};