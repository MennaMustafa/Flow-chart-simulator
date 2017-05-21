#pragma once

#include "Statement.h"

class Start_End: public Statement 
{
private:
	Connector *C;
	Point In;
	Point Out;
	Point LeftCorner;
	int St_En;
	bool D_load;
	virtual void UpdateStatementText();

public:
	Start_End(Point,int);
	Start_End(Point,Start_End*);
	Start_End(){}
	string GetLHS(){return "";}

	~Start_End();
	virtual void Draw(Output* pOut) const;
	int getKind(){ return St_En; }


	virtual void setConn(Connector*);
	virtual void getConn(Connector **&arr, int &size);
	virtual Point getIn();
	virtual void getOut(Point * &P, int &size);


	virtual void Move(Point);
	virtual void Edit(Input*, Output*);

	
	virtual void PrintInfo(Output*);

	virtual Point getCorner(){ return this->LeftCorner; }
	virtual Point width_height(){ return Point(UI.EllipseWidth, UI.EllipseH); }

	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	virtual void GenerateCode(ofstream &OutFile);	//write the statement code to a file

	void Start_End::Load(ifstream & In);
	 int Run(map<string, double> &m){ return 1; }
	int Debug(map<string, double>& Vars, Output* O){ return 1; }
	void Start_End::SetLoad(bool b) { D_load = b;}
};