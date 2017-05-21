#pragma once 
#include"Statement.h"


using namespace std;


class ReadWrite : public  Statement
{
private:
	string s;
	bool state;
	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement
	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.
	bool R_load;
	virtual void UpdateStatementText();

public:
	ReadWrite(Point Lcorner, string s1 ,bool state1);
	ReadWrite(Point Lcorner, ReadWrite *V);
	ReadWrite(){}
	virtual void setConn(Connector*);
	virtual void getConn(Connector **&arr, int &size);
	virtual Point getIn();
	virtual void getOut(Point * &P, int &size);
	bool getKind(){ return state; }
	string getVar(){ return s; }
	void setString(const string &L);
	virtual void Draw(Output* pOut) const;
	virtual void Move(Point p);
	virtual void Edit(Input*, Output*);
	void PrintInfo(Output*Pout);

	virtual Point getCorner(){ return this->LeftCorner; }
	virtual Point width_height(){ return Point(UI.r_width,UI.r_height); }

	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	virtual void GenerateCode(ofstream &OutFile);	//write the statement code to a file
	void Load(ifstream &InFile);
	virtual int Run(map<string, double>& Vars);
	int Debug(map<string, double>& Vars, Output* O);

	virtual string GetLHS();

	void SetR_Load(bool R)
	{
		R_load = R;
	} // True Read, False Write

		void SetLeftCorner(int x, int y);
		void SetIn_Out();
};
