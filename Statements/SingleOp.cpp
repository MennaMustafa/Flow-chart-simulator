#include"SingleOp.h"


SingleOp::SingleOp(Point Corner, string L, char op, string s1, string s2, double d1, double d2, double dif1, double dif2)
{
	this->LeftCorner = Corner;
	this->LHS = L;
	this->Op = op;
	this->d1 = d1;
	this->d2 = d2;
	this->s1 = s1;
	this->s2 = s2;
	this->dif1 = dif1;
	this->dif2 = dif2;

	UpdateStatementText();
	this->pConn = NULL;

	
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	
	}



void SingleOp:: Draw(Output* pOut) const
{
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

void SingleOp::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside

		ostringstream T;
		if (dif1==2&&dif2==2)
		T << LHS << " = " << s1<<Op<<s2;
		else if (dif1==2&&dif2==1)
			T << LHS << " = " << s1 << Op << d2;
		else if (dif1==1&&dif2==1)
			T << LHS << " = " << d1 << Op << d2;
		else if (dif1==1&&dif2==2)
			T << LHS << " = " << d1 << Op << s2;
		Text = T.str();
	}

}

void SingleOp::Edit(Input*I, Output*O)
{
		string s;
		double d;
		do
		{
			O->PrintMessage("Enter The Left hand side : ");
			s = I->GetString(O);
			this->LHS = s;
		} while (!IsValid(s));

		do
		{
			O->PrintMessage("Enter The Right hand side first operand type (1-string 2-double) : ");
			d = I->GetValue(O);
		} while (d != 1 && d != 2);
		
		if (d == 1)
		{
			do
			{
				O->PrintMessage("Enter First operand");
				s1 = I->GetString(O); //setters
				this->dif1=2;
			} while (!IsValid(s1));
		}
		else {
				O->PrintMessage("Enter First operand");
				d1 = I->GetValue(O); //setters
				dif1=1;
		}

		string c;
		do
		{
			O->PrintMessage("Enter The Right hand side operatoer : ");
			c = I->GetString(O);
		} while (c != "+" && c != "-" && c != "*" && c != "/");
		Op = c[0]; //setters

		O->PrintMessage("Enter The Right hand side Second operand type (1-string 2-double) : ");
		double a;
		do
		{
			a = I->GetValue(O);
		} while (a != 1 && a != 2);

		if (a == 1) {
			do {
				O->PrintMessage("Enter Second operand");
				s2 = I->GetString(O); //setters
				dif2=2;
			} while (!IsValid(s2));
		}
		else {
				O->PrintMessage("Enter First operand");
				d2 = I->GetValue(O); //setters
				dif2=1;
		}

		UpdateStatementText();
	}



void SingleOp::Move(Point m)
{
	this->LeftCorner = m;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

}


void SingleOp::PrintInfo(Output*Pout)
{
	ostringstream S;
	S << "ID = " << ID << ", Comment: " << C;
	Pout->PrintMessage(S.str());
}




SingleOp::SingleOp(Point Q , SingleOp *S)
{
	this->C = S->C;
	LHS = S->LHS;
	Op = S->Op;
	s1 = S->s1;
	s2 = S->s2;
	d1 = S->d1;
	d2 = S->d2;
	this->LeftCorner = Q;
	this->dif1 = S->dif1;
	this->dif2 = S->dif2;
	pConn = NULL;
	Inlet = S->Inlet;
	Outlet = S->Outlet;
}


void SingleOp::setConn(Connector*x)
{ pConn = x; }
void SingleOp::getConn(Connector **&arr, int &size)
{
	size = 1;
	arr = new Connector*[size];
	arr[0] = pConn;
}
Point SingleOp::getIn()
{ return Inlet; }
void SingleOp::getOut(Point * &P, int &size)
{
	size = 1;
	P = new Point[size];
	P[0] = Outlet;
}

string SingleOp::OperatorChecker(char c)
{
	switch (c)
	{
	case'+': return "PLUS"; break;
	case '*': return"MUL"; break;
	case'-': return "MINUS"; break;
	default: return "DIV"; break;
	}
}


void SingleOp::Save(ofstream &OutFile)
{
	if (dif1 == 2 && dif2 == 2) 
	{
		OutFile << "SNGLOP" << "   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << this->LHS << "    ";
		OutFile << this->s1 << "   " << OperatorChecker(this->Op) << "   " << this->s2 << "   " << GetComment() << endl;
	}
	else if (dif1 == 2 && dif2 == 1) 
	{
		OutFile << "SNGLOP" << "   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << this->LHS << "    ";
		OutFile << this->s1 << "   " << OperatorChecker(this->Op) << "   " << this->d2 << "   " << GetComment() << endl;
	}
	else if (dif1 == 1 && dif2 == 2) 
	{
		OutFile << "SNGLOP" << "   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << this->LHS << "    ";
		OutFile << this->d1 << "   " << OperatorChecker(this->Op) << "   " << this->s2 << "   " << GetComment() << endl;
	}
	else if (dif1 == 1 && dif2 == 1)
	{
		OutFile << "SNGLOP" << "   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << this->LHS << "    ";
		OutFile << this->d1 << "   " << OperatorChecker(this->Op) << "   " << this->d2 << "   " << GetComment() << endl;
	}
}

void SingleOp::GenerateCode(ofstream &OutFile)
{
	if (dif1 == 2 && dif2 == 2) // Ex: x=y+z //
		OutFile << this->LHS << "=" << this->s1 << this->Op << this->s2 << ";";
	else if (dif1 == 2 && dif2 == 1) //Ex: X=y*2 //
		OutFile << this->LHS << "=" << this->s1 << this->Op << this->d2 << ";";
	else if (dif1 == 1 && dif2 == 2) //Ex: X=y*2 //
		OutFile << this->LHS << "=" << this->d1 << this->Op << this->s2 << ";";
	else if (dif1 == 1 && dif2 == 1) //Ex: X=2*2 //
		OutFile << this->LHS << "=" << this->d1 << this->Op << this->d2 << ";";
	if (GetComment() != "\"\"") OutFile << "  //" << GetComment();
	OutFile << endl;
}


void SingleOp::Operator_S(string x)
{
	if (x == "PLUS")
		Op = '+';
	else if (x == "MUL")
		Op = '*';
	else if (x == "MINUS")
		Op = '-';
	else if (x == "DIV")
		Op = '/';
}


void SingleOp::Load(ifstream &In)
{
	int I; double x, y, z;
	string T1, T2, comment;
	string oper, L;
	In >> I >> LeftCorner.x >> LeftCorner.y >> L >> T1;
	SetID(I);
	setLHS(L);
	if (IsValid(T1))
	{
		s1 = T1;
		In >> oper >> T2;
		if (IsValid(T2))
		{
			setS2(T2);
			In >> comment;
			dif1 = dif2 = 2;
		}
		else
		{
			stringstream I(T2);
			I >> x;
			setD2(x);
			In >> comment;
			dif1 = 2;
			dif2 = 1;
		}

		Operator_S(oper);
		Comment(comment);
	}
	else
	{
		stringstream r(T1);
		r >> y;
		setD1(y);
		In >> oper >> T2;
		if (IsValid(T2))
		{
			setS2(T2);
			In >> comment;
			dif1 = 1;
			dif2 = 2;
		}
		else
		{
			stringstream q(T2);
			q >> z;
			setD2(z);
			In >> comment;
			dif1 = dif2 = 1;
		}
		Operator_S(oper);
		Comment(comment);
	}

	//Inlet & Outlet

	this->pConn = NULL;


	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();

}

int SingleOp::Run(map<string, double> &Vars)
{
	if (dif1==2&&s1=="")
		return 3;
	else if (dif2==2&&s2=="")
		return 3;

	else if (dif1 == 2 && Vars.find(s1) == Vars.end()) return 0;
	else if (dif2 == 2 && Vars.find(s2) == Vars.end()) return 0;
	
	else
	{
		if (Op == '+')
		{
			if (dif1 == 1 && dif2 == 1) Vars[LHS] = d1 + d2;
			else if (dif1 == 1 && dif2 == 2) Vars[LHS] = d1 + Vars[s2];
			else if (dif1 == 2 && dif2 == 1) Vars[LHS] = Vars[s1] + d2;
			else if (dif1 == 2 && dif2 == 2) Vars[LHS] = Vars[s1] + Vars[s2];
		}
		else if (Op == '-')
		{
			if (dif1 == 1 && dif2 == 1) Vars[LHS] = d1 - d2;
			else if (dif1 == 1 && dif2 == 2) Vars[LHS] = d1 - Vars[s2];
			else if (dif1 == 2 && dif2 == 1) Vars[LHS] = Vars[s1] - d2;
			else if (dif1 == 2 && dif2 == 2) Vars[LHS] = Vars[s1] - Vars[s2];
		}
		else if (Op == '*')
		{
			if (dif1 == 1 && dif2 == 1) Vars[LHS] = d1 * d2;
			else if (dif1 == 1 && dif2 == 2) Vars[LHS] = d1 * Vars[s2];
			else if (dif1 == 2 && dif2 == 1) Vars[LHS] = Vars[s1] * d2;
			else if (dif1 == 2 && dif2 == 2) Vars[LHS] = Vars[s1] * Vars[s2];
		}
		else if (Op == '/')
		{
			if (dif1 == 1 && dif2 == 1)
				if (d2!=0)
					Vars[LHS] = d1 / d2;
				else return -1;
			else if (dif1 == 1 && dif2 == 2)
				if (Vars[s2]!=0)
					Vars[LHS] = d1 / Vars[s2];
				else return -1;
			else if (dif1 == 2 && dif2 == 1) 
				if (d2!=0)
					Vars[LHS] = Vars[s1] / d2;
				else return -1;
			else if (dif1 == 2 && dif2 == 2)
				if (Vars[s2]!=0)
					Vars[LHS] = Vars[s1] / Vars[s2];
				else return -1;
		}

	}
	return 1;
}




int SingleOp::Debug(map<string, double>& Vars, Output* O)
{

	if (dif1==2&&s1=="")
		return 3;
	else if (dif2==2&&s2=="")
		return 3;

	else if (dif1 == 2 && Vars.find(s1) == Vars.end()) 
		return 0;
	else if (dif2 == 2 && Vars.find(s2) == Vars.end())
		return 0;

	else
	{
		if (Op == '+')
		{
			if (dif1 == 1 && dif2 == 1)Vars[LHS] = d1 + d2;
			else if (dif1 == 1 && dif2 == 2) Vars[LHS] = d1 + Vars[s2];
			else if (dif1 == 2 && dif2 == 1) Vars[LHS] = Vars[s1] + d2;
			else if (dif1 == 2 && dif2 == 2) Vars[LHS] = Vars[s1] + Vars[s2];
		}
		else if (Op == '-')
		{
			if (dif1 == 1 && dif2 == 1) Vars[LHS] = d1 - d2;
			else if (dif1 == 1 && dif2 == 2) Vars[LHS] = d1 - Vars[s2];
			else if (dif1 == 2 && dif2 == 1) Vars[LHS] = Vars[s1] - d2;
			else if (dif1 == 2 && dif2 == 2) Vars[LHS] = Vars[s1] - Vars[s2];
		}
		else if (Op == '*')
		{
			if (dif1 == 1 && dif2 == 1) Vars[LHS] = d1 * d2;
			else if (dif1 == 1 && dif2 == 2) Vars[LHS] = d1 * Vars[s2];
			else if (dif1 == 2 && dif2 == 1) Vars[LHS] = Vars[s1] * d2;
			else if (dif1 == 2 && dif2 == 2) Vars[LHS] = Vars[s1] * Vars[s2];
		}
		else if (Op == '/')
		{
			if (dif1 == 1 && dif2 == 1) 
				if (d2 != 0)
					Vars[LHS] = d1 / d2;
				else return -1;
			else if (dif1 == 1 && dif2 == 2)
				if (Vars[s2] != 0)
					Vars[LHS] = d1 / Vars[s2];
				else return -1;
			else if (dif1 == 2 && dif2 == 1)
				if (d2 != 0)
					Vars[LHS] = Vars[s1] / d2;
				else return -1;
			else if (dif1 == 2 && dif2 == 2)
				if (Vars[s2] != 0)
					Vars[LHS] = Vars[s1] / Vars[s2];
				else return -1;
			
		}

	}

	string s;
	stringstream Q(s);
	Q << LHS << " =" << Vars[LHS];
	O->PrintMessage(Q.str());
	return 1;

}

string SingleOp::GetLHS() 
{
	return LHS;
}