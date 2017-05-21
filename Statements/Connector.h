#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "..\GUI\UI_Info.h"
#include "..\GUI\output.h"

#include "Statement.h"

class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	bool Selected;
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	int def;
public:
	Connector(Statement* Src, Statement* Dst,bool);
	
	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void Draw(Output* pOut);

	void Edit(Statement*,Statement*);
	
	void PrintInfo(Output*);
	
	void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	
	void setSelected(bool t){ Selected = t; }
	bool getSelected(){ return Selected; }
	
	// no moving for connectors as we move the statement with its connectors //
};

#endif