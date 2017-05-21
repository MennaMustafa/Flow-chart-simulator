#include"multipleSelect.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
void multipleSelect::ReadActionParameters()
{
	Input* I = pManager->GetInput();
	Output* O = pManager->GetOutput();
	Point p;
	if (pManager->GetSelectedStatement() != NULL)
	{
		pManager->GetSelectedStatement()->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
	}

	do{
		O->PrintMessage("Select a statement or a Connector ");
		I->GetPointClicked(p);
		s = pManager->GetStatement(p);
		c = pManager->GetConnector(p);
	} while (c == NULL&&s == NULL);
}

void multipleSelect::Execute()
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
	if (s != NULL)
	{
		if (!s->IsSelected())
			s->SetSelected(true);
		else
			s->SetSelected(false);
	}
	else if (c != NULL)
	{
		if (!c->getSelected())
			c->setSelected(true);
		else
			c->setSelected(false);
	}

	pManager->GetOutput()->ClearStatusBar();
}