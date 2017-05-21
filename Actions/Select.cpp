#include"Select.h"
#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"


void Select::ReadActionParameters()
{
	Input* I = pManager->GetInput();
	Output* O = pManager->GetOutput();

	Point p;
	do
	{
		O->PrintMessage("Select a statement or a Connector ");
		I->GetPointClicked(p);
		s = pManager->GetStatement(p);
		c = pManager->GetConnector(p);
	} while (c == NULL&&s == NULL);

	//De-Select all the statemnts and connectors but not the selected one 
	for (int i = 0; i < pManager->Statementcurrent(); i++)
		if (pManager->Statementlist()[i]!=s)
			pManager->Statementlist()[i]->SetSelected(false);
	for (int i = 0; i < pManager->Connectorcurrent(); i++)
		if (pManager->Connectorlist()[i] != c)
			pManager->Connectorlist()[i]->setSelected(false);
	/////////////////////////////////////////////////////////////////



}




void Select::Execute()
{
	Output* O = pManager->GetOutput();
	if (pManager->Statementcurrent() == 0)
	{
		O->PrintMessage("There is no Statements to Select !");
		Sleep(1000);
		O->ClearStatusBar();
		return;
	}


	ReadActionParameters();

	if (s != NULL){
		if (!s->IsSelected())
		{
			s->SetSelected(true);
			pManager->SetSelectedStatement(s);
		}
		else
		{
			s->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
		}
	}
	else if (c!=NULL)
	{ 
		if (!c->getSelected())
		{
			c->setSelected(true);
			pManager->SetSelectedConnector(c);
		}
		else
		{
			c->setSelected(false);
			pManager->SetSelectedConnector(NULL);
		}
	}
	if (s&&s->IsSelected())
		if (s->GetComment() != "\"\"")
		{
			O->PrintMessage(s->GetComment());
		}
}