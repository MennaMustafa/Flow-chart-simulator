#include "Save.h"

#include <cctype>

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

Save::Save(ApplicationManager*Ap): Action(Ap)
{
}

void Save::Execute()
{
	Output*pOut = pManager->GetOutput();

	pOut->PrintMessage("Saving...");

	OutFile.open("Flow_Chart.txt");

	OutFile << pManager->Statementcurrent() << endl;

	for(int i=0; i<pManager->Statementcurrent(); i++)
	{
		(pManager->Statementlist())[i]->Save(OutFile);
	}
	OutFile << pManager->Connectorcurrent() << endl ;

	for(int i=0; i<pManager->Connectorcurrent(); i++)
	{
		(pManager->Connectorlist())[i]->Save(OutFile);
	}
	OutFile.close();
	pOut->PrintMessage("Your Flow Chart is saved, Check the File!");
	Sleep(1000);
	
	
	system("notepad.exe Flow_Chart.txt");

	pManager->GetOutput()->ClearStatusBar();
}