#include"Add_one_operator.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>


void Add_One_Operator::ReadActionParameters()
{

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	do{

		pOut->PrintMessage("Conditional Assignment Statement: Click a valid Point to Draw the statement");
		pIn->GetPointClicked(Position);
	} while (IsPoint(Position));

	do{
		pOut->PrintMessage("Enter The Left hand Side");
		LHS = pIn->GetString(pOut);
	} while (!IsValid(LHS));

	do{
		pOut->PrintMessage("Enter the Right hand side First Operand Type (1- double,2-string)");
		dif1 = pIn->GetValue(pOut);
	} while (dif1 != 1 && dif1 != 2);

	if (dif1 == 1)
	{
		pOut->PrintMessage("Enter the Right hand side First operand double type value");
		d1 = pIn->GetValue(pOut);
	}
	else {
		do{
			pOut->PrintMessage("Enter the Right hand side First operand string type value");
			s1 = pIn->GetString(pOut);
		} while (!IsValid(s1));
	}
		string tempOp;
		do{
			pOut->PrintMessage("Enter a Valid Operator");
			tempOp = pIn->GetString(pOut);
		} while (tempOp != "+" && tempOp != "-" && tempOp != "*" && tempOp != "/" );
		Op = tempOp[0];

		do{
			pOut->PrintMessage("Enter the Right hand side Second Operand Type (1- double,2-string)");
			dif2 = pIn->GetValue(pOut);
		} while (dif2 != 1 && dif2 != 2);

		if (dif2 == 1)
		{
			pOut->PrintMessage("Enter the Right hand side First operand double type value");
			d2 = pIn->GetValue(pOut);
		}
		else {
			do{
				pOut->PrintMessage("Enter the Right hand side First operand string type value");
				s2 = pIn->GetString(pOut);
			} while (!IsValid(s2));
			}
}

void Add_One_Operator::Execute()
{
	ReadActionParameters();

	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	Corner = IsPointDraw(Corner, UI.ASSGN_WDTH);
	Corner = Valid_H(Corner, UI.ASSGN_HI);

	SingleOp*pAssign = new SingleOp (Corner, LHS,Op,s1,s2,d1,d2,dif1,dif2);

	pManager->AddStatement(pAssign);

	pManager->GetOutput()->ClearStatusBar();
}