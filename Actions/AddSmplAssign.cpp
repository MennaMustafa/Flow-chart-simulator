#include "AddSmplAssign.h"

#include <cctype>

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddSmplAssign::AddSmplAssign(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddSmplAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	do {
		pOut->PrintMessage("Simple Value Assignment Statement: Click to add the statement");
		pIn->GetPointClicked(Position);
	} while(IsPoint(Position));

	do
	{
		pOut->PrintMessage("Enter a Valid Left hand side");
		LHS = pIn->GetString(pOut);
	} while (!IsValid(LHS));

	pOut->PrintMessage("Enter the right hand side");
	RHS = pIn->GetValue(pOut);

	pOut->ClearStatusBar();		
}

void AddSmplAssign::Execute()
{
	ReadActionParameters();
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	Corner = IsPointDraw(Corner, UI.ASSGN_WDTH);
	Corner = Valid_H(Corner, UI.ASSGN_HI);
	
	
	SmplAssign *pAssign = new SmplAssign(Corner, LHS, RHS);

	pManager->AddStatement(pAssign);
	pManager->GetOutput()->ClearStatusBar();
}

