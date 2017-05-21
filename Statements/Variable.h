#pragma once 
#include"Statement.h"


using namespace std;


class Variable : public  Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (Value)

	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Variable(Point Lcorner, string LeftHS = "", string RightHS = "");
	Variable(Point Lcorner, Variable* V);
	Variable(){}

	void setLHS(const string &L);
	void setRHS(string R);


	virtual void setConn(Connector*);
	virtual void getConn(Connector **&arr, int &size);
	virtual Point getIn();
	virtual void getOut(Point * &P, int &size);


	virtual void Draw(Output* pOut) const;
	virtual void Move(Point p);
	virtual void Edit(Input*, Output*);
	void PrintInfo(Output*Pout);


	virtual Point getCorner(){ return this->LeftCorner; }
	virtual Point width_height(){ return Point(UI.ASSGN_WDTH, UI.ASSGN_HI); }

	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	virtual void GenerateCode(ofstream &OutFile);	//write the statement code to a file

	void Variable::Load(ifstream& In);
	int Run(map<string, double> &Vars);
	int Debug(map<string, double>& Vars, Output* O);

	virtual string GetLHS();
};
