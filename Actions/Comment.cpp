
#include "Comment.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

Comment::Comment(ApplicationManager*A):Action(A)
{
}

void Comment::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	if (pManager->GetSelectedStatement()!=NULL) 
		S=pManager->GetSelectedStatement();
	else
	{
		Point Position;
		do 
		{
			pOut->PrintMessage("Choose Statement to Comment on");
			pIn->GetPointClicked(Position);
			S = pManager->GetStatement(Position);
		} while (S == NULL);
	}
	pOut->PrintMessage("Write Your Comment");
	C = pIn->GetString(pOut);


	pOut->ClearStatusBar();	
}

void Comment::Execute()
{

	//Check for Statement to connect on 
	Output* O = pManager->GetOutput();
	if (pManager->Statementcurrent() == 0)
	{
		O->PrintMessage("There is no Statements to Comment on !");
		Sleep(1000);
		O->ClearStatusBar();
		return;
	}

	ReadActionParameters();

	S->Comment(C);
	pManager->GetOutput()->ClearStatusBar();
}
