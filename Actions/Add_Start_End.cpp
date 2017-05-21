#include "Add_Start_End.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

Add_Start_End::Add_Start_End(ApplicationManager*A, int t): Action(A)
{
	Type=t; //Start or End
}


void Add_Start_End::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	do {
	pOut->PrintMessage("Click a valid point to draw the statement");
	pIn->GetPointClicked(Position);
	} while(IsPoint(Position));
	pOut->ClearStatusBar();	
}

void Add_Start_End::Execute()
{
	ReadActionParameters();

	//Calculating left corner of start/end statement block
	Point Corner;
	Corner.x = Position.x - UI.EllipseWidth / 2;
	Corner.y = Position.y;
	Corner = IsPointDraw(Corner, UI.EllipseWidth);
	Corner = Valid_H(Corner, UI.EllipseH);
	Start_End*S = new Start_End(Corner, Type);

	pManager->AddStatement(S);
	pManager->GetOutput()->ClearStatusBar();

}
