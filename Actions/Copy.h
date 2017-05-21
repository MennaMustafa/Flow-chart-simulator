#pragma once
#include "Action.h"
#include"../Statements/Statement.h"


class Copy : public Action
{
private:
	Point Position;
	Statement *S;
	int counter;

public:
	Copy(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

