#include"AddCond.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>


using namespace std;

void AddCond::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	do{

	pOut->PrintMessage("Conditional Assignment Statement: Click a valid Point to Draw the statement");
	pIn->GetPointClicked(position);
	} while (IsPoint(position));


	do{
		pOut->PrintMessage("Enter The Left hand Side");
		LHS = pIn->GetString(pOut);
	} while (!IsValid(LHS));
	
	do{
		pOut->PrintMessage("Enter the Right hand side Type (1- double,2-string)");
		dif = pIn->GetValue(pOut);
	} while (dif != 1 && dif != 2);

	pOut->PrintMessage("Enter the Right hand side: ");

	if (dif == 1) RHS1 = pIn->GetValue(pOut);
	else
	{
		do{
			RHS2 = pIn->GetString(pOut);
		} while (!IsValid(RHS2));
	}
	do{
		pOut->PrintMessage("Enter a Valid Operator");
		Op = pIn->GetString(pOut);
	} while (Op != "<=" && Op != ">=" && Op != "==" && Op != "!=" && Op != ">" && Op != "<"); 

	pOut->ClearStatusBar();
}

void AddCond::Execute()
{
	ReadActionParameters();

	position = IsPointDraw(position, UI.COND_LGN);
	position = Valid_H(position, UI.COND_LGN);

	Conditional *p = new Conditional(position,LHS,Op,RHS1,RHS2,dif);

	pManager->AddStatement(p);

	pManager->GetOutput()->ClearStatusBar();
}
