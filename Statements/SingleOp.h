#ifndef SingleOp_H
#define SingleOp_H

#include "Statement.h"


class SingleOp :public Statement
{
private:
	string LHS;
	char Op;
	string s1;
	string s2;
	double d1;
	double d2;
	double dif1, dif2;

	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	string OperatorChecker(char);
public:

	SingleOp(Point ,string ,char ,string ,string ,double ,double ,double ,double);
	SingleOp(Point, SingleOp*);//copy constructor 
	SingleOp(){}

	virtual void Draw(Output* pOut) const;

	virtual void setConn(Connector*);
	virtual void getConn(Connector **&arr, int &size);
	virtual Point getIn();
	virtual void getOut(Point * &P, int &size);

	virtual void Move(Point m);
	virtual void Edit(Input*, Output*);
	virtual void PrintInfo(Output*Pout);


	virtual Point getCorner(){ return LeftCorner; }
	virtual Point width_height(){ return Point(UI.ASSGN_WDTH,UI.ASSGN_HI);}

	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	virtual void GenerateCode(ofstream &OutFile);	//write the statement code to a file

	void SingleOp::Operator_S(string x);
	void SingleOp::Load(ifstream &In);
	virtual int Run(map<string, double> &Vars);
	int Debug(map<string, double>& Vars, Output* O);

	void setLHS(string s)
	{LHS = s;}

	void setS1(string l)
	{s1 = l;}

	void setS2(string s) { s2 = s; }
	void setD1(double d) { d1 = d; }
	void setD2(double d) { d2 = d; }

	virtual string GetLHS();
};
#endif