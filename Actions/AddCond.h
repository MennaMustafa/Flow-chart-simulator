#pragma once

#include"Action.h"

#include "..\Statements\Conditional.h"


class AddCond : public Action
{
	Point position;
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS1;	//Right Handside (Value)
	string RHS2;   //Right Handside (Variable)
	string Op; 
	
	double dif; //First and second operand type

public:
	AddCond(ApplicationManager *pAppManager) : Action(pAppManager){}
	virtual void ReadActionParameters();
	virtual void Execute();
};