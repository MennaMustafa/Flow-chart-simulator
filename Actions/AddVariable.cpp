#include "AddVariable.h"


#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddVariable::AddVariable(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddVariable::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	do
	{
		pOut->PrintMessage("Variable Statement: Click to add the statement");
		pIn->GetPointClicked(Position);
	} while (IsPoint(Position));

	pOut->ClearStatusBar();
	do
	{
		pOut->PrintMessage("Please enter a Valid left hand side");
		LeftHS = pIn->GetString(pOut);
	} while (!IsValid(LeftHS));
	do
	{
		pOut->PrintMessage("Please enter a Valid right hand side");
		RightHS = pIn->GetString(pOut);
	} while (!IsValid(RightHS));

}

void AddVariable ::Execute()

{
	ReadActionParameters();

	//Calculating left corner of assignement statement block
	Point Corner;

	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	Corner = IsPointDraw(Corner, UI.ASSGN_WDTH);
	Corner = Valid_H(Corner, UI.ASSGN_HI);


	
	
	Variable *pAssign = new Variable(Corner, LeftHS, RightHS);
	pManager->AddStatement(pAssign);
	pManager->GetOutput()->ClearStatusBar();
}

