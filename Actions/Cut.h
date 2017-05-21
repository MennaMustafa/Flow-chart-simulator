#pragma once
#include "Action.h"
#include"../Statements/Statement.h"


class Cut : public Action
{
private:
	Point Position;
	Statement *S;      // if (count==0) (there are no selected statments )get statment from usert in S
	int counter;

public:
	Cut(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

