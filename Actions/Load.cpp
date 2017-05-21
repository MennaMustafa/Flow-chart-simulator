#include "Load.h"


Load::Load(ApplicationManager*A):Action(A)
{
	pOut = pManager->GetOutput();
}

void Load::Execute()
{
	pOut->ClearDrawArea();

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



	pOut->PrintMessage("Loading...");
	//User Enter File's name
	InFile.open("Flow_Chart.txt");

	pManager->Loading(InFile);

	InFile.close();

	pManager->GetOutput()->ClearStatusBar();
}
