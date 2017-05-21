#include"Cut.h"

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
Cut::Cut(ApplicationManager *pAppManager) :Action(pAppManager)
{
	counter = 0;
}

void Cut::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	for (int i = 0; i < pManager->Statementcurrent(); i++)
	if (pManager->Statementlist()[i]->IsSelected()) counter++;
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
		pOut->PrintMessage("Click a valid position to cut the statement");
		pIn->GetPointClicked(Position);
	} while (IsPoint(Position));

	pOut->ClearStatusBar();
}



void Cut::Execute()
{
	Output *pOut = pManager->GetOutput();
	
	
	Output* O = pManager->GetOutput();
	if (pManager->Statementcurrent() == 0)
	{
		O->PrintMessage("There is no Statements to Cut !");
		Sleep(1000);
		O->ClearStatusBar();
		return;
	}
	
	
	
	ReadActionParameters();
	Statement* Cut;
	Statement *temp;
	if (counter != 0)
	{

		Point Pmin(1000, 1000); //Minimum y to move 

		for (int i = 0; i < pManager->Statementcurrent(); i++)
		{
			if (pManager->Statementlist()[i]->IsSelected())
			{
				if (pManager->Statementlist()[i]->getIn().y <= Pmin.y)
				{
					temp = pManager->Statementlist()[i];
					Pmin = pManager->Statementlist()[i]->getIn();
				}
			}
		}


		Point Differrence; // Difference between the position and the statement pmin

		Differrence.x = Position.x - temp->getIn().x;
		Differrence.y = Position.y - temp->getIn().y;


		for (int i = 0; i < pManager->Statementcurrent(); i++)
		{
			if (pManager->Statementlist()[i]->IsSelected())
			{
				if (dynamic_cast<Start_End*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
			
					Cut = pManager->Statementlist()[i];

					Connector **arr; int n = 1;                                                       
					pManager->Statementlist()[i]->getConn(arr, n);
					for (int i = 0; i < n; i++) // Delete Statement Connectors, if Distination is not selected
					{
						if (arr[i]!=NULL)
						{
							if (!(arr[i]->getDstStat()->IsSelected()))
								pManager->DeleteConnector(arr[i]);
						}
					}

					P = IsPointDraw(P, UI.EllipseWidth);
					P = Valid_H(P, UI.EllipseH);

					Cut->Move(P);
				}

				else if (dynamic_cast<Conditional*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
				
					Cut = pManager->Statementlist()[i];

					Connector **arr; int n = 2;                                                         
					pManager->Statementlist()[i]->getConn(arr, n);
					for (int i = 0; i < n; i++)
					if (arr[i] != NULL)
					{
						if (!(arr[i]->getDstStat()->IsSelected()))
							pManager->DeleteConnector(arr[i]);
					}

					P = IsPointDraw(P, UI.COND_LGN);
					P = Valid_H(P, UI.COND_LGN);
					Cut->Move(P);
				}
				else if (dynamic_cast<ReadWrite*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);

					Cut = pManager->Statementlist()[i];

					Connector **arr; int n = 1;                                                        
					pManager->Statementlist()[i]->getConn(arr, n);
					for (int i = 0; i < n; i++)
					if (arr[i] != NULL)
					{
						if (!(arr[i]->getDstStat()->IsSelected()))
							pManager->DeleteConnector(arr[i]);
					}

					P = IsPointDraw(P, UI.r_width);
					P = Valid_H(P, UI.r_height);
					
					Cut->Move(P);
				}
				else if (dynamic_cast<SingleOp*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);

					Cut = pManager->Statementlist()[i];

					Connector **arr; int n = 1;                                                        
					pManager->Statementlist()[i]->getConn(arr, n);
					for (int i = 0; i < n; i++)
					if (arr[i] != NULL)
					{
						if (!(arr[i]->getDstStat()->IsSelected()))
							pManager->DeleteConnector(arr[i]);
					}

					P = IsPointDraw(P, UI.ASSGN_WDTH);
					P = Valid_H(P, UI.ASSGN_HI);
					Cut->Move(P);
				}
				else if (dynamic_cast <SmplAssign*>(pManager->Statementlist()[i]))
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					
					Cut = pManager->Statementlist()[i];

						Connector **arr; int n = 1;                                                         
						pManager->Statementlist()[i]->getConn(arr, n);
						for (int i = 0; i < n; i++)
						if (arr[i] != NULL)
						{
							if (!(arr[i]->getDstStat()->IsSelected()))
								pManager->DeleteConnector(arr[i]);
						}
						P = IsPointDraw(P, UI.ASSGN_WDTH);
						P = Valid_H(P, UI.ASSGN_HI);
						Cut->Move(P);
				}
				else
				{
					Point P(pManager->Statementlist()[i]->getIn().x + Differrence.x, pManager->Statementlist()[i]->getIn().y + Differrence.y);
					Cut = pManager->Statementlist()[i];

					Connector **arr; int n = 1;                                                        
					pManager->Statementlist()[i]->getConn(arr, n);
					for (int i = 0; i < n; i++)
					if (arr[i] != NULL)
					{
						if (!(arr[i]->getDstStat()->IsSelected()))
							pManager->DeleteConnector(arr[i]);
					}

					P = IsPointDraw(P, UI.ASSGN_WDTH);
					P = Valid_H(P, UI.ASSGN_HI);
					Cut->Move(P);
					
				}


				//now the statement is Cutted , Deleting the connectors if source is not selected

				for (int j = 0; j < pManager->Connectorcurrent(); j++)
				{
					if (pManager->Connectorlist()[j]->getDstStat() == pManager->Statementlist()[i])         
					if (!pManager->Connectorlist()[j]->getSrcStat()->IsSelected())
						pManager->DeleteConnector(pManager->Connectorlist()[j]);
				}
			}
			
		}
	}

	if (counter == 0)
	{
		if (dynamic_cast<Start_End*>(S)) 
		{
			Cut = S;
			Connector **Arr; int size = 1;                   // delete el connector el 5areg mn el statment 
			S->getConn(Arr, size);
			for (int i = 0; i < size; i++)
			if (Arr[i]!=NULL)
				pManager->DeleteConnector(Arr[i]);
		}
		else if (dynamic_cast<Conditional*>(S)) // && IsPointDraw(t, UI.COND_LGN).x == Position.x&&IsPointDraw(t, UI.COND_LGN).y == Position.y)
		{
			Cut = S;
			Connector **Arr; int size = 2;
			S->getConn(Arr, size);
			for (int i = 0; i < size; i++)
			{
				if (Arr[i]!=NULL)
				pManager->DeleteConnector(Arr[i]);
			}
			//pManager->DeleteStatement(S);

		}

		else if (dynamic_cast<ReadWrite*>(S))//  && IsPointDraw(t, UI.r_width).x == Position.x&&IsPointDraw(t, UI.r_height).y == Position.y)
		{
			Cut = S;
			Connector **Arr; int size = 1;
			S->getConn(Arr, size);
			for (int i = 0; i < size; i++)
			if (Arr[i]!=NULL)
				pManager->DeleteConnector(Arr[i]);
			//pManager->DeleteStatement(S);

		}
		else if (dynamic_cast<SingleOp*>(S))// && IsPointDraw(t, UI.ASSGN_WDTH).x == Position.x&&IsPointDraw(t, UI.ASSGN_HI).y == Position.y)
		{
			Cut = S;
			Connector **Arr; int size = 1;
			S->getConn(Arr, size);
			for (int i = 0; i < size; i++)
			if (Arr[i]!=NULL)
				pManager->DeleteConnector(Arr[i]);
			//pManager->DeleteStatement(S);

		}
		else if (dynamic_cast <SmplAssign*>(S))// && IsPointDraw(t, UI.ASSGN_WDTH).x == Position.x&&IsPointDraw(t, UI.ASSGN_HI).y == Position.y)
		{
			Cut = S;
		
				Connector **Arr; int size = 1;
				S->getConn(Arr, size);
				for (int i = 0; i < size; i++)
				if (Arr[i]!=NULL)
					pManager->DeleteConnector(Arr[i]);
				//pManager->DeleteStatement(S);
			
		}
		else if (dynamic_cast <Variable*>(S))// && IsPointDraw(t, UI.ASSGN_WDTH).x == Position.x&&IsPointDraw(t, UI.ASSGN_HI).y == Position.y)
		{
			Cut = S;
			Connector **Arr; int size = 1;
			S->getConn(Arr, size);
			for (int i = 0; i < size; i++)
			if (Arr[i]!=NULL)
				pManager->DeleteConnector(Arr[i]);
			
		}
		else
		{
			pOut->PrintMessage("Some Statements are invalid to be cut !");
			return;
		}

		

		for (int j = 0; j < pManager->Connectorcurrent(); j++)                                  //delete el conector el da5el 3la el statement 
		{
			if (pManager->Connectorlist()[j]->getDstStat() == S)
				pManager->DeleteConnector(pManager->Connectorlist()[j]);
		}

		Point Q = S->width_height();

		Position = IsPointDraw(Position, Q.x);
		Position = Valid_H(Position, Q.y);
	
		S->Move(Position);
	}
}