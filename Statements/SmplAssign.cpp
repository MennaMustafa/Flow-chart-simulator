#include "SmplAssign.h"
#include <sstream>

using namespace std;

SmplAssign::SmplAssign(Point Lcorner, string LeftHS, double RightHS)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;
	
	pConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}

SmplAssign::SmplAssign(Point N, SmplAssign* S) //Paste//
{
	this->C = S->C;
	LHS = S->LHS;
	RHS = S->RHS;
	LeftCorner = N;

	pConn = NULL;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();

}


void SmplAssign::PrintInfo(Output*Pout) {
	ostringstream S;
	S << "ID = " << ID << ", Comment: " << C;
	Pout->PrintMessage(S.str());
}



void SmplAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void SmplAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void SmplAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}


//This function should be called when LHS or RHS changes
void SmplAssign::UpdateStatementText()
{
	if(LHS=="")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T<<LHS<<" = "<<RHS;	
		Text = T.str();	 
	}
}

void SmplAssign::Edit(Input*I, Output*O)
{
	string s;
	double d;
	do
	{
		O->PrintMessage("Enter The Left hand side : ");
		s = I->GetString(O);
		setLHS(s);
	} while (!IsValid(s));

		O->PrintMessage("Enter The Right hand side : ");
		d = I->GetValue(O);
		setRHS(d);
		UpdateStatementText();
}




void SmplAssign::Move(Point m)
{
	this->LeftCorner = m;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;


}



void SmplAssign::setConn(Connector*x)
{ pConn = x; }
void SmplAssign::getConn(Connector **&arr, int &size)
{
	size = 1;
	arr = new Connector*[size];
	arr[0] = pConn;
}
Point SmplAssign::getIn()
{ return Inlet; }
void SmplAssign::getOut(Point * &P, int &size)
{ 
	size = 1;
	P = new Point[size];
	P[0] = Outlet;
}

void SmplAssign::GenerateCode(ofstream &OutFile)
{
	OutFile << this->LHS << "=" << this->RHS << ";";
	if (GetComment() != "\"\"") OutFile<<"//" << GetComment();
	OutFile<<endl;
}

void SmplAssign::Save(ofstream &OutFile)
{
	OutFile << "SmplAssign" << "   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << this->LHS << "   " << this->RHS << "   " << GetComment() << endl;
}

void SmplAssign::Load(ifstream&In)
{
	int I; double d;
	string comment, L;
	In >> I >> LeftCorner.x >> LeftCorner.y >> L >> d >> comment;
	Comment(comment);
	SetID(I); setLHS(L); setRHS(d);

	//Inlet & Outlet
	pConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();
}


int SmplAssign::Run(map<string, double>& Vars)
{
	if (LHS=="") return 3;	
	else 
		{
			Vars[LHS] = RHS;
			return 1;
		}
}



int SmplAssign::Debug(map<string, double>& Vars, Output* O)
{
	if (LHS=="") return 3;

		Vars[LHS] = RHS;
		string s;
		stringstream Q(s);
		Q << LHS << " =" << Vars[LHS];
		O->PrintMessage(Q.str());
		return 1;
}

string SmplAssign::GetLHS()
{
	return LHS;
}