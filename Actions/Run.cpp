#include"Run.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
#include "..\ApplicationManager.h"


void Run::Execute()
{
	Output*pOut = pManager->GetOutput();
	Input*pIn = pManager->GetInput();

	Statement* temp;
	for (int i = 0; i < pManager->Statementcurrent(); i++)
		if (dynamic_cast<Start_End*>(pManager->Statementlist()[i]) && ((Start_End*)(pManager->Statementlist()[i]))->getKind() == 1)
			temp = pManager->Statementlist()[i];

	Connector**arr;
	int size;

	temp->getConn(arr, size);
	temp = arr[0]->getDstStat();


	while (!(dynamic_cast<Start_End*>(temp) && ((Start_End*)(temp))->getKind() == 0))
	{
		int Running = temp->Run(variables);

		if (dynamic_cast<ReadWrite*>(temp) && ((ReadWrite*)temp)->getKind()) //read
		{
			string var=((ReadWrite*)temp)->getVar();
			pOut->PrintMessage("Enter the value of "+var+" :");
			double val= pIn->GetValue(pOut);
			variables[var] = val;
		}

		else if (dynamic_cast<ReadWrite*>(temp) && !((ReadWrite*)temp)->getKind())//write
		{
			string var = ((ReadWrite*)temp)->getVar();

			
			if (variables.find(var) == variables.end())
			{
				pOut->PrintMessage("Undeclared identifier. Aborting ...");
				Sleep(3000);
				pOut->ClearStatusBar();
				return;
			}
			double val = variables[var];
			string x;
			stringstream Q(x);
			Q<< val<<"                        //Output";
			pOut->PrintMessage(Q.str());
			Sleep(3000);
		}
		if (Running == 0)
		{
			pOut->PrintMessage("Undeclared identifier. Aborting ...");
			Sleep(3000);
			pOut->ClearStatusBar();
			return;
		}
		else if (Running == 1) //Regular Statement , or Conditional right Connector
		{
			Connector **arr2;
			int n;
			temp->getConn(arr2, n);
			temp = arr2[0]->getDstStat();
		}
		else if (Running == 2) // Conditional left Connector
		{
			Connector **arr2;
			int n;
			temp->getConn(arr2, n);
			temp = arr2[1]->getDstStat();
		}
		else if (Running == -1)
		{
			pOut->PrintMessage("Attemping to divide by zero. Aborting...");
			Sleep(3000);
			pOut->ClearStatusBar();
			return;
		}
		else if (Running==3)
		{
			pOut->PrintMessage("Some variablesare wrong. Aborting...");
			Sleep(3000);
			pOut->ClearStatusBar();
			return;
		}
	}
	pOut->PrintMessage("Program has exited with code of 0*0");
	Sleep(3000);
	pOut->ClearStatusBar();
}