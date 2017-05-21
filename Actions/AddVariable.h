#pragma once

#include "Action.h"
#include "..\Statements\Variable.h"

//Add Simple Assignment Statement Action
//This class is responsible for 
// 1 - Getting Assignment stat. coordinates from the user
// 2 - Creating an object of Assignment class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddVariable : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	string LeftHS, RightHS;
public:
	AddVariable(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};