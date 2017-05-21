#include "Connector.h"
#include"Conditional.h"


Connector::Connector(Statement* Src, Statement* Dst,bool x=false)	
//When a connector is created, it must have a source statement and a destination statement
//There are no free connectors in the folwchart
{
	SrcStat = Src;
	DstStat = Dst;
	End = Dst->getIn();
	Point *p;
	int n;
	def = 0;
	Src->getOut(p, n);
	if (n == 1) Start = p[0];
	else //conditional Statement 
	{
		Connector**C;
		Src->getConn(C, n);
		if (C[0] == NULL)
			Start = p[0];
		else if (C[1] == NULL)
		{
			Start = p[1];
			def = 1;
		}
	}
	Src->setConn(this);
	Selected = x;
}

//Edit//
void Connector::Edit(Statement*S, Statement*E)
{
	SrcStat = S;
	DstStat = E;
	End = E->getIn();
	Point *p;
	int n;
	S->getOut(p, n);
	if (n == 1) Start = p[0];
	else //conditional Statement 
	{
		Connector**C;
		S->getConn(C, n);
		if (C[0] == NULL) Start = p[0];
		else if (C[1] == NULL) Start = p[1];
	}
	S->setConn(this);
}


//print info//

void Connector::PrintInfo(Output*P)
{
	ostringstream S;
	S << " --- Source is: ("<<Start.x<<","<<Start.y<<") --- "<< "Distination is: ("<<End.x<<","<<End.y<<")"; 
	P->PrintMessage(S.str());
}


//Setters & Getters //
void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

void Connector::Draw(Output* pOut) 
{
	End = DstStat->getIn();
	Point *p;
	int n;
	SrcStat->getOut(p, n);
	Start = p[def];
	///TODO: Call output to draw a connector from SrcStat to DstStat on the output window
	pOut->DrawConn(Start, End, Selected);
}

void Connector::Save(ofstream &OutFile)
{
	int Outlet_branch = 0;
	OutFile << SrcStat->getID() << "   " << DstStat->getID() << "   ";
	if (dynamic_cast<Conditional*>(SrcStat))
	{
		Connector**arr;
		int size;
		SrcStat->getConn(arr, size);
		if (this == arr[0])
			Outlet_branch = 1;
		else if (this == arr[1])
			Outlet_branch = 2;

		OutFile << Outlet_branch << endl;
	}
	else
		OutFile << Outlet_branch << endl;
}

