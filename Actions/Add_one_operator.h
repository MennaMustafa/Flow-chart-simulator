#include"..\Statements\SingleOp.h"

#include"Action.h"


class Add_One_Operator
	: public Action
{
	Point Position;
	string LHS;
	char Op; //Operator
	string s1; //First operand if it's string
	string s2; //Second operand if it's string
	double d1; //First operand if it's double
	double d2; //Second operand if it's double

	double dif1, dif2; //indicate kind of first and second operands

public:
	Add_One_Operator(ApplicationManager *pAppManager) : Action(pAppManager){}
	
	virtual void ReadActionParameters();
	virtual void Execute();
};