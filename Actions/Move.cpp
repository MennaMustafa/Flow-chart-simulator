#include"Move.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include"../Statements/Conditional.h"
#include"../Statements/ReadWrite.h"
#include"../Statements/SingleOp.h"
#include"../Statements/SmplAssign.h"
#include"../Statements/Start_End.h" 
#include"../Statements/Variable.h"
#include <sstream>
using namespace std;
Move::Move(ApplicationManager *pAppManager) :Action(pAppManager)
{
	counter = 0;
}
void Move::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	for (int i = 0; i < pManager->Statementcurrent(); i++)
	if (pManager->Statementlist()[i]->IsSelected())
		counter++;
	if (counter == 0)
	{
		do
		{
			Point p;
			pOut->PrintMessage("Click on a Valid Statement !");
			pIn->GetPointClicked(p);
			S = pManager->GetStatement(p);
		} while (S == NULL);
	}

	do {
		pOut->PrintMessage("Click a valid position to Move the statement");
		pIn->GetPointClicked(Position);
	} while (IsPoint(Position));

	pOut->ClearStatusBar();
}
void Move::Execute()
{
	Output *pOut = pManager->GetOutput();
	
	Output* O = pManager->GetOutput();
	if (pManager->Statementcurrent() == 0)
	{
		O->PrintMessage("There is no Statements to Move !");
		Sleep(1000);
		O->ClearStatusBar();
		return;
	}

		
	ReadActionParameters();
	Statement* Moved;
	Statement *temp;
	if (counter != 0)
	{

		Point Pmin(1000, 1000);
		for (int i = 0; i < pManager->Statementcurrent(); i++)
		{
			if (pManager->Statementlist()[i]->IsSelected())
			{

				if (pManager->Statementlist()[i]->getIn().y < Pmin.y) //|| pManager->Statementlist()[i]->getIn().x <= Pmin.x)
				{
					temp = pManager->Statementlist()[i];
					Pmin = pManager->Statementlist()[i]->getIn();
				}

			}
		}


		Point Differrence; // Difference between the position and the statement pIn


		Differrence.x = Position.x - temp->getIn().x;
		Differrence.y = Position.y - temp->getIn().y;


		for (int i = 0; i < pManager->Statementcurrent(); i++)
		{
			if (pManager->Statementlist()[i]->IsSelected())
			{
				if (dynamic_cast<Start_End*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y); //call constructor of point
					P = IsPointDraw(P, UI.EllipseWidth);
					P = Valid_H(P, UI.EllipseH);
					Moved = pManager->Statementlist()[i];
					pManager->Statementlist()[i]->Move(P);
				}

				else if (dynamic_cast<Conditional*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					P = IsPointDraw(P, UI.COND_LGN);
					P = Valid_H(P, UI.COND_LGN);
					Moved = pManager->Statementlist()[i];
					pManager->Statementlist()[i]->Move(P);
				}
				else if (dynamic_cast<ReadWrite*>(pManager->Statementlist()[i]))
				{

					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					P = IsPointDraw(P, UI.r_width);
					P = Valid_H(P, UI.r_height);
					Moved = pManager->Statementlist()[i];
					pManager->Statementlist()[i]->Move(P);
				}
				else if (dynamic_cast<SingleOp*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					P = IsPointDraw(P, UI.ASSGN_WDTH);
					P = Valid_H(P, UI.ASSGN_HI);
					Moved = pManager->Statementlist()[i];
					pManager->Statementlist()[i]->Move(P);
				}
				else if (dynamic_cast <SmplAssign*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					P = IsPointDraw(P, UI.ASSGN_WDTH);
					P = Valid_H(P, UI.ASSGN_HI);
					Moved = pManager->Statementlist()[i];
					pManager->Statementlist()[i]->Move(P);
				}
				else
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					P = IsPointDraw(P, UI.ASSGN_WDTH);
					P = Valid_H(P, UI.ASSGN_HI);
					Moved = pManager->Statementlist()[i];
					pManager->Statementlist()[i]->Move(P);
				}
			}
		}
	}


	if (counter == 0)
	{
		Moved = S;
		Point Q=Moved->width_height();
		Position = IsPointDraw(Position, Q.x);
		Position = Valid_H(Position, Q.y);
		S->Move(Position);
	}

	pManager->GetOutput()->ClearStatusBar();
}