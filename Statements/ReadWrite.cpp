#include"ReadWrite.h"


ReadWrite::ReadWrite(Point Lcorner, string s1,bool state1) //true for read and false for write
{
	s = s1;
	state = state1;


	UpdateStatementText();

	LeftCorner = Lcorner;

	pConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.r_width / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.r_height;

	R_load = false;
}
void ReadWrite::setString(const string &L)
{
     s = L;
	UpdateStatementText();
}


void ReadWrite::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 
	if (state)
	pOut->DrawRead(LeftCorner, UI.r_width, UI.r_height, Text, Selected);
	else
		pOut->DrawWrite(LeftCorner, UI.r_width, UI.r_height, Text, Selected);

}


//This function should be called when LHS or RHS changes
void ReadWrite::UpdateStatementText()
{
	if (s == "")	//No left handside ==>statement have no valid text yet
		Text = "     ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << s;
		Text = T.str();
	}

}
void ReadWrite::Move(Point p)
{
	this->LeftCorner.x = p.x;
	this->LeftCorner.y = p.y;
	Inlet.x = LeftCorner.x + UI.r_width / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.r_height;

}
void ReadWrite::Edit(Input*I, Output*O)
{
	if (state)
		O->PrintMessage("Enter data which you you want to read");
	else
		O->PrintMessage("Enter data which you you want to write");
	string s2;
	do
	{
		s2 = I->GetString(O);
		setString(s2);
	} while (!IsValid(s2));
	UpdateStatementText();
}



void ReadWrite::PrintInfo(Output*Pout)
{
	ostringstream S;
	
	S << "ID = " << ID << ", Comment: " << C;
	if (state)
		S << " Read statement" << endl;
	else
		S << " Write statement" << endl;
	Pout->PrintMessage(S.str());
}




ReadWrite::ReadWrite(Point Lcorner, ReadWrite* V)
{
	s = V->s;
	state = V->state;

	UpdateStatementText();

	LeftCorner = Lcorner;
	this->C = V->C;

	pConn = NULL;	//No connectors yet

	Inlet.x = V->Inlet.x;
	Inlet.y = V->Inlet.y;

	Outlet.x = Inlet.x;
	Outlet.y = V->Outlet.y;
}

void ReadWrite::setConn(Connector*x)
{ pConn = x; }

void ReadWrite::getConn(Connector **&arr, int &size)
{ 
	size = 1;
	arr = new Connector*[size];
	arr[0] = pConn;
}

Point ReadWrite::getIn()
{ return Inlet;}

void ReadWrite::getOut(Point * &P, int &size)
{
	size = 1;
	P = new Point[size];
	P[0] = Outlet;
}


void ReadWrite::Save(ofstream &OutFile)
{
	if (state)
		OutFile << "READ" << "   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << s << "   " << GetComment() << endl;
	else
		OutFile << "WRITE" << "   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << s <<"    "<< GetComment() <<endl;
}

void ReadWrite::GenerateCode(ofstream &OutFile)
{
	
	if (state)
		OutFile<<"cin>>" << s << ";";
	else
		OutFile << "cout<<" << s << ";";

	if (GetComment() != "\"\"")OutFile << "  //" << GetComment();
	OutFile << endl;
}



void ReadWrite::Load(ifstream &InFile)
{

	int I, z, w;
	string comment, s1;
	if (R_load)
	{

		InFile >> I >> z >> w >> s1 >> comment;
		setString(s1);
		state = true;
		UpdateStatementText();
		Comment(comment);
		SetID(I);
		SetLeftCorner(z, w);
	}
	else
	{
		InFile >> I >> z >> w >> s1 >> comment;
		setString(s1); state = false;
		UpdateStatementText();
		Comment(comment);
		SetID(I);

		SetLeftCorner(z, w);
	}
	//Inlet & Outlet
	pConn = NULL;	//No connectors yet
	SetIn_Out();
}

int ReadWrite::Run(map<string, double>& Vars)//true for read
{
	if (s=="")
		return 3;
	else
		return 1;

}
int ReadWrite::Debug(map<string, double>& Vars, Output* O)
{ 
	if (s=="")
		return 3;
	else
		return 1;
}

string ReadWrite::GetLHS()
{
	return s;
}



void ReadWrite::SetLeftCorner(int x, int y)
{
	LeftCorner.x = x;
	LeftCorner.y = y;
}
void ReadWrite::SetIn_Out()
{
	Inlet.x = LeftCorner.x + (UI.r_width / 2);
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.r_height;
	}
