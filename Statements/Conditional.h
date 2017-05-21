#pragma once

#include"Statement.h"


class Conditional :
	public Statement
{

private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS1;	//Right Handside (Value)
	string RHS2;   //Right Handside (Variable)
	string Op;
	double def;

	Connector *pConn[2];	//Conditional Stat. has Two Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet[2];	//A point a connection leaves this statement

	Point center;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	string Operator(string);
public:

	Conditional(Point center, string LeftHS ,string op ,double RightHS1,string RightHS2,double);
	
	Conditional(Point, Conditional*); // To Paste // 
	Conditional(){}
	void setLHS(const string &L);
	void setRHS(double R);
	void setRHS(string R);
	void setOp(string p);

	string GetLHS();
	virtual void Draw(Output* pOut) const;

	virtual void setConn(Connector*);
	virtual void getConn(Connector **&arr, int &size);
	virtual Point getIn();
	virtual void getOut(Point * &P, int &size);


	virtual void Edit(Input*, Output*);
	virtual void PrintInfo(Output*);
	virtual void Move(Point);

	virtual Point getCorner();
	virtual Point width_height();

	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	virtual void GenerateCode(ofstream &OutFile);	//write the statement code to a file
	
	
	void Conditional::Load(ifstream &In);
	void Conditional::Operator_S(string x);
	int Run(map<string,double>&);
	int Debug(map<string, double>& Vars,Output* O);
	void setFConn(Connector*x){ pConn[0] = x; }
	void setSConn(Connector*x){ pConn[1] = x; }

	void SetCenter(int x, int Temp, int U);
};
