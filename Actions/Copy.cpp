#include"Copy.h"

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
Copy::Copy(ApplicationManager *pAppManager) :Action(pAppManager)
{
	counter = 0;
}

void Copy::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	for (int i = 0; i < pManager->Statementcurrent(); i++)
		if (pManager->Statementlist()[i]->IsSelected()) 
			counter++;

	if (counter == 0)
	{
		do{
			Point p;
			pOut->PrintMessage("Click on a Valid Statement !");
			pIn->GetPointClicked(p);
			S = pManager->GetStatement(p);
		} while (S == NULL);
	}

	do {
		pOut->PrintMessage("Click a valid position to copy the statement");
		pIn->GetPointClicked(Position);
	} while (IsPoint(Position));
	
	pOut->ClearStatusBar();
}



void Copy::Execute()
{
	Output *pOut = pManager->GetOutput();
	
	
	Output* O = pManager->GetOutput();
	if (pManager->Statementcurrent() == 0)
	{
		O->PrintMessage("There is no Statements to Copy !");
		Sleep(1000);
		O->ClearStatusBar();
		return;
	}


	
	ReadActionParameters();
	Statement* Copied;

	Statement *temp;
	if (counter!=0)
	{
		Point Pmin(1000, 1000);
		for (int i = 0; i < pManager->Statementcurrent(); i++)
			if (pManager->Statementlist()[i]->IsSelected() && (pManager->Statementlist()[i]->getIn().y <= Pmin.y)) //|| pManager->Statementlist()[i]->getIn().x <= Pmin.x))
			{
				temp = pManager->Statementlist()[i];
				Pmin = pManager->Statementlist()[i]->getIn();
			}


		Point Differrence; // Difference between the position and the statement pIn

		Differrence.x = Position.x - temp->getIn().x;
		Differrence.y = Position.y - temp->getIn().y;


		for (int i = 0; i < pManager->Statementcurrent(); i++)
			if (pManager->Statementlist()[i]->IsSelected())
			{
				if (dynamic_cast<Start_End*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
				
					P = IsPointDraw(P, UI.EllipseWidth);
					P = Valid_H(P, UI.EllipseH);

					Copied = new Start_End(P, (Start_End*)pManager->Statementlist()[i]);
				}
				else if (dynamic_cast<Conditional*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					P = IsPointDraw(P, UI.COND_LGN);
					P = Valid_H(P, UI.COND_LGN);
					
					Copied = new Conditional(P, (Conditional*)pManager->Statementlist()[i]);
				}
				else if (dynamic_cast<ReadWrite*>(pManager->Statementlist()[i]))
				{

					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
				
					P = IsPointDraw(P, UI.r_width);
					P = Valid_H(P, UI.r_height);

					Copied = new ReadWrite(P, (ReadWrite*)(pManager->Statementlist()[i]));
				}
				else if (dynamic_cast<SingleOp*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					
					P = IsPointDraw(P, UI.ASSGN_WDTH);
					P = Valid_H(P, UI.ASSGN_HI);

					Copied = new SingleOp(P, (SingleOp*)pManager->Statementlist()[i]);
					}
				else if (dynamic_cast <SmplAssign*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					P = IsPointDraw(P, UI.ASSGN_WDTH);
					P = Valid_H(P, UI.ASSGN_HI);
					Copied = new SmplAssign(P, (SmplAssign*)pManager->Statementlist()[i]);
				}
				else
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					
					P = IsPointDraw(P, UI.ASSGN_WDTH);
					P = Valid_H(P, UI.ASSGN_HI);

					Copied = new Variable(P, (Variable*)pManager->Statementlist()[i]);
					}

				pManager->AddStatement(Copied);
			}
		
	}
	else if (counter == 0)
	{
		if (dynamic_cast<Start_End*>(S))
		{
			Position = IsPointDraw(Position, UI.EllipseWidth);
			Position = Valid_H(Position, UI.EllipseH);
			Copied = new Start_End(Position, (Start_End*)S);
		}
		else if (dynamic_cast<Conditional*>(S))
		{
			Position = IsPointDraw(Position, UI.COND_LGN);
			Position = Valid_H(Position, UI.COND_LGN);
			Copied = new Conditional(Position, (Conditional*)S);
		}
		else if (dynamic_cast<ReadWrite*>(S))
		{
			Position = IsPointDraw(Position, UI.r_width);
			Position = Valid_H(Position, UI.r_height);
			Copied = new ReadWrite(Position, (ReadWrite*)S);
		}
		else if (dynamic_cast<SingleOp*>(S))
		{
			Position = IsPointDraw(Position, UI.ASSGN_WDTH);
			Position = Valid_H(Position, UI.ASSGN_HI);
			Copied = new SingleOp(Position, (SingleOp*)S);
		}
		else if (dynamic_cast <SmplAssign*>(S))
		{
			Position = IsPointDraw(Position, UI.ASSGN_WDTH);
			Position = Valid_H(Position, UI.ASSGN_HI);
			Copied = new SmplAssign(Position, (SmplAssign*)S);
		}
		else if (dynamic_cast<Variable*>(S))
		{
			Position = IsPointDraw(Position, UI.ASSGN_WDTH);
			Position = Valid_H(Position, UI.ASSGN_HI);
			Copied = new Variable(Position, (Variable*)S);
		}
		
		pManager->AddStatement(Copied);
	}


	pManager->GetOutput()->ClearStatusBar();
}