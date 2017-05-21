#pragma once
#include "Action.h"
#include "..\Statements\Start_End.h"

class Add_Start_End : public Action 
{
private:
	Point Position;
	int Type;
public:
	Add_Start_End(ApplicationManager *pAppManager,int);

	//Read start/end statements position
	virtual void ReadActionParameters();
	
	//Create and add an start/end statement to the list of statements
	virtual void Execute() ;

};