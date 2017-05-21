#include "..\ApplicationManager.h"

#include"Delete.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"



void Delete::Execute() //Statement has priority
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();


	Output* O = pManager->GetOutput();
	if (pManager->Statementcurrent() == 0)
	{
		O->PrintMessage("There is no Statements to Delete !");
		Sleep(1000);
		O->ClearStatusBar();
		return;
	}

	bool valid = false;
	for (int i = 0; i < pManager->Statementcurrent(); i++)
		if (pManager->Statementlist()[i]->IsSelected())
		{
			valid = true;
			Connector** C; int size;
			pManager->Statementlist()[i]->getConn(C, size);

			for (int j = 0; j < size; j++)
				if (C[j])
					pManager->DeleteConnector(C[j]);

			for (int k = 0; k < pManager->Connectorcurrent(); k++)
				if (pManager->Connectorlist()[k]->getDstStat() == pManager->Statementlist()[i])
					pManager->DeleteConnector(pManager->Connectorlist()[k]);

			pManager->DeleteStatement(pManager->Statementlist()[i]);
			i--;
		}

	for (int i = 0; i < pManager->Connectorcurrent(); i++)
		if (pManager->Connectorlist()[i]->getSelected())
		{
			pManager->DeleteConnector(pManager->Connectorlist()[i]);
			valid = true;
		}

	Statement *S;
	Connector *C;

	if (!valid)
	{
		Point P;
		string c;
		do{
			pOut->PrintMessage("Please Select a statement to delete");
			pIn->GetPointClicked(P);
			S = pManager->GetStatement(P);
			C = pManager->GetConnector(P);
			if (S == NULL&&C==NULL)
			{
				pOut->PrintMessage("Do you want to clear all the area? (Y/N) ");
				c = pIn->GetString(pOut);
				if (c == "Y" || c == "y")
					break;
			}
		} while (S == NULL&&C == NULL);

		if (c == "Y" || c == "y")
		{
			for (int i = 0; i < pManager->Connectorcurrent(); i++)
			{
				pManager->DeleteConnector(pManager->Connectorlist()[i]);
				i--;
			}


			for (int i = 0; i < pManager->Statementcurrent(); i++)
			{
				pManager->DeleteStatement(pManager->Statementlist()[i]);
				i--;
			}
			pOut->ClearStatusBar();
			return;
		}

		if (S != NULL)
		{
			Connector** C; int size;
			S->getConn(C, size);

			for (int j = 0; j < size; j++)
				if (C[j])
					pManager->DeleteConnector(C[j]);

			for (int k = 0; k < pManager->Connectorcurrent(); k++)
				if (pManager->Connectorlist()[k]->getDstStat() == S)
					pManager->DeleteConnector(pManager->Connectorlist()[k]);

			pManager->DeleteStatement(S);

		}
		if (C != NULL)
		{
			pManager->DeleteConnector(C);
		}

		pManager->GetOutput()->ClearStatusBar();
	}
}