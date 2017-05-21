#include "AddReadWrite.h"
#include"..\Statements\ReadWrite.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddReadWrite::AddReadWrite(ApplicationManager *pAppManager, bool s) : Action(pAppManager)
{
	s1 = s; // True if Read False if Write
}

void AddReadWrite::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	do
	{
		pOut->PrintMessage("Variable Statement: Click to add the statement");
		pIn->GetPointClicked(Position);
	} while (IsPoint(Position));

	do
	{
		pOut->PrintMessage("Please enter a Valid statenemt");
		 l = pIn->GetString(pOut);
	} while (!IsValid(l));
	pOut->ClearStatusBar();

}

void AddReadWrite::Execute()
{
	ReadActionParameters();

	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x + 20;
	Corner.y = Position.y;
	Corner = IsPointDraw(Corner, UI.r_width);
	Corner = Valid_H(Corner, UI.r_height);
	Statement*pReadWrite;
	if (s1)
		pReadWrite = new ReadWrite(Corner, l, 1);
	else
		pReadWrite = new ReadWrite(Corner, l, 0);


	pManager->AddStatement(pReadWrite);

	pManager->GetOutput()->ClearStatusBar();
}

