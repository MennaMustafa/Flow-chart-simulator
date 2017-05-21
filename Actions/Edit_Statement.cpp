#include "Edit_Statement.h"

void Edit_Statement::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();

	if(pManager->GetSelectedStatement() != NULL)
		S = pManager->GetSelectedStatement();
	else
		do
		{
			pOut->PrintMessage("Select Statement to Edit! ");
			Point Selected;
			pIn->GetPointClicked(Selected);
			S = pManager->GetStatement(Selected);
		} while (S==NULL);

}

void Edit_Statement::Execute()
{
	Output* O = pManager->GetOutput();
	if (pManager->Statementcurrent() == 0)
	{
		O->PrintMessage("There is no Statements to Edit !");
		Sleep(1000);
		O->ClearStatusBar();
		return;
	}


	ReadActionParameters();
	S->Edit(pIn,pOut); 
	pManager->GetOutput()->ClearStatusBar();
}