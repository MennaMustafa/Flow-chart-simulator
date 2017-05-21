#include "Conditional.h"


Conditional::Conditional(Point cen, string LeftHS, string op, double RightHS1, string RightHS2,double x)
{
	LHS = LeftHS;
	RHS1 = RightHS1;
	RHS2 = RightHS2;
	this->Op = op;
	def = x;

	UpdateStatementText();

	this->center = cen;

	pConn[0] = pConn[1] = NULL;	//No connectors yet

	Inlet.x = center.x;
	Inlet.y = center.y-UI.COND_LGN;


	//feh moshkela hna 
	Outlet[0].x = center.x+ UI.COND_LGN;
	Outlet[0].y = center.y;
	Outlet[1].x = center.x - UI.COND_LGN;
	Outlet[1].y = center.y;

}


Conditional::Conditional(Point cen, Conditional *cond)
{
	
	this->C = cond->C;

	this->LHS = cond->LHS;
	this->RHS1 = cond->RHS1;
	this->RHS2 = cond->RHS2;
	this->Op = cond->Op;
	this->def = def;
	UpdateStatementText();
	
	this->center = cen;
	pConn[0]=pConn[1] = NULL;	//No connectors yet


	Inlet.x = center.x;
	Inlet.y = center.y - UI.COND_LGN / 2;

	Outlet[0].x = center.x + UI.COND_LGN;
	Outlet[0].y = center.y;
	Outlet[1].x = center.x - UI.COND_LGN;
	Outlet[1].y = center.y;
}


void Conditional:: setLHS(const string &L)
{
	this->LHS = L;
}
void Conditional::setRHS(double R)
{
	this->RHS1 = R;
	def = 1;
}
void Conditional::setRHS(string R)
{
	this->RHS2 = R;
	def = 2;
}
void Conditional::Draw(Output* pOut) const
{
	pOut->DrawCond(center, UI.COND_LGN, Text, Selected);
}
void Conditional::setOp(string p)
{
	Op = p;
}

void Conditional::Edit(Input* I, Output* O)
{
	string L;

	do 
	{
		O->PrintMessage("Enter The Left Hand Side: ");
		L = I->GetString(O);
		setLHS(L);
	} while (!IsValid(L));
	
	O->PrintMessage("Enter The Operation :");
	string p;
	do
	{
		p = I->GetString(O);
	} while (p != "<=" && p != ">=" && p != "==" && p != "!=" && p != ">" && p != "<");
	setOp(p);
	O->PrintMessage("Enter the Right hand side Type (1- double,2-string)");
	double d;
	do
	{
		d = I->GetValue(O);
	} while (d != 1 && d != 2);
	if (d == 1)
	{
		double x;
		O->PrintMessage("Enter Right hand side");
		x = I->GetValue(O);
		setRHS(x);
	}
	else
	{
		string x;
		do
		{
			O->PrintMessage("Enter Right hand side");
			x = I->GetString(O);
			setRHS(x);
		}while (!IsValid(x));
	}
	UpdateStatementText();
}



string Conditional::GetLHS()
{
	return this->LHS;
}




void Conditional::PrintInfo(Output* Pout)
{
	ostringstream S;
	S << "ID = " << ID << ", Comment: " << C;
	Pout->PrintMessage(S.str());
}
void Conditional::Move(Point q)
{
	center = q;

	Inlet.x = center.x;
	Inlet.y = center.y - UI.COND_LGN;

	//feh moshkela hna 
	Outlet[0].x = center.x + UI.COND_LGN;
	Outlet[0].y = center.y;
	Outlet[1].x = center.x - UI.COND_LGN;
	Outlet[1].y = center.y;


}

void Conditional::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    ==  ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS << Op;
		if (def==2) T << RHS2;
		else T << RHS1;
		this->Text = T.str();
	}
}



void Conditional::setConn(Connector*x)
{
	if (pConn[0] == NULL)
		pConn[0] = x;
	else if (pConn[1] == NULL)
		pConn[1] = x;
}

void Conditional::getConn(Connector **&arr, int &size)
{
	size = 2;
	arr = new Connector*[size];
	arr[0] = pConn[0];
	arr[1] = pConn[1];
}


Point Conditional::getIn()
{
	return Inlet;
}

void Conditional::getOut(Point * &P, int &size)
{
	size = 2;
	P = new Point[size];
	P[0] = Outlet[0];
	P[1] = Outlet[1];
}



void Conditional::Save(ofstream &OutFile)
{
	if (def == 1)
		OutFile << "COND" << "   " << ID << "   " << center.x << "   " << center.y - UI.COND_LGN << "   " << this->LHS << "  " << Operator(this->Op) << "   " << this->RHS1 << "    " << GetComment() << endl;
	else
		OutFile << "COND" << "   " << ID << "   " << center.x << "   " << center.y - UI.COND_LGN << "   " << this->LHS << "  " << Operator(this->Op) << "   " << this->RHS2 << "   " << GetComment() << endl;
}

string Conditional::Operator(string x)
{
	if (x == "==") return "Equ";
	else if (x == "!=") return "NotEqu";
	else if (x == ">") return "GRT";
	else if (x == "<") return "SML";
	else if (x == ">=") return "GrtEqu";
	else return "SmlEqu";
 }


void Conditional::GenerateCode(ofstream &OutFile)
{
	if (def == 1)
		OutFile << "(" << LHS << " " << Op << " " << RHS1 << ")";
	else
		OutFile << "(" << LHS << " " << Op << " " << RHS2 << ")";
}


void Conditional::Operator_S(string x)
{
	if (x == "Equ")
		Op = "==";
	else if (x == "NotEqu")
		Op = "!=";
	else if (x == "GRT")
		Op = ">";
	else if (x == "SML")
		Op = "<";
	else if (x == "GrtEqu")
		Op = ">=";
	else if (x == "SmlEqu")
		Op = "<=";
}

void Conditional::Load(ifstream &In)
{
	int I;
	int Temp; double d;
	int x;
	string comment;
	string T, L;
	string oper;
	In >> I >> x;
	SetID(I);
	In >> Temp;
	SetCenter(x, Temp, UI.COND_LGN);
	In >> L >> oper >> T;
	setLHS(L);
	Operator_S(oper);
	if (IsValid(T))
	{
		setRHS(T);
		In >> comment;
		def = 2;
	}
	else
	{
		stringstream s(T);
		s >> d;
		setRHS(d);
		In >> comment;
		def = 1;
	}
	Comment(comment);

	//Inlet & Outlet
	//UpdateStatementText();

	pConn[0] = pConn[1] = NULL;	//No connectors yet

	Inlet.x = center.x;
	Inlet.y = center.y - UI.COND_LGN;


	Outlet[0].x = center.x + UI.COND_LGN;
	Outlet[0].y = center.y;
	Outlet[1].x = center.x - UI.COND_LGN;
	Outlet[1].y = center.y;

	UpdateStatementText();

}



int Conditional::Run(map<string, double>& Vars)
{
	if (LHS==""||(def==2&&RHS2==""))
		return 3;
	if (Vars.find(LHS) == Vars.end())
		return 0;
	
	else if (def == 2 && Vars.find(RHS2) == Vars.end())
		return 0;
	

	else
	{
		if (Op == "!=")
			if (def == 1)
			{
				if (Vars[LHS] != RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] != Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else if (Op=="==")
			if (def == 1)
			{
				if (Vars[LHS] == RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] == Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else if (Op==">")
			if (def == 1)
			{
				if (Vars[LHS] > RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] > Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else if (Op=="<")
			if (def == 1)
			{
				if (Vars[LHS] < RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] < Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else if (Op=="<=")
			if (def == 1)
			{
				if (Vars[LHS] <= RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] <= Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else 
			if (def == 1)
			{
				if (Vars[LHS] >= RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] >= Vars[RHS2])
					return 1;
				else
					return 2;
			}
	}
}



int Conditional::Debug(map<string, double>& Vars, Output* O)
{
	O->ClearStatusBar();

	
	if (LHS==""||(def==2&&RHS2==""))
		return 3;

	if (Vars.find(LHS) == Vars.end())
		return 0;

	else if (def == 2 && Vars.find(RHS2) == Vars.end())
		return 0;

	else
	{
		if (Op == "!=")
			if (def == 1)
			{
				if (Vars[LHS] != RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] != Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else if (Op == "==")
			if (def == 1)
			{
				if (Vars[LHS] == RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] == Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else if (Op == ">")
			if (def == 1)
			{
				if (Vars[LHS] > RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] > Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else if (Op == "<")
			if (def == 1)
			{
				if (Vars[LHS] < RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] < Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else if (Op == "<=")
			if (def == 1)
			{
				if (Vars[LHS] <= RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] <= Vars[RHS2])
					return 1;
				else
					return 2;
			}
		else
			if (def == 1)
			{
				if (Vars[LHS] >= RHS1)
					return 1;
				else
					return 2;
			}
			else
			{
				if (Vars[LHS] >= Vars[RHS2])
					return 1;
				else
					return 2;
			}
	}
}

void Conditional::SetCenter(int x, int Temp, int U)
	{
		center.x = x;
		center.y = Temp + U;
	}


Point Conditional::getCorner()
{
	Point R;
	R.x = center.x - UI.COND_LGN;
	R.y = center.y - UI.COND_LGN;
	return R;
}
Point Conditional::width_height()
{
	Point R;
	R.x = UI.COND_LGN;
	R.y = UI.COND_LGN;
	return R;
}
