#include"Debug.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
#include "..\ApplicationManager.h"


void Debug::Execute()
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

	pOut->PrintMessage("Start Debugging. click to move one step");
	Sleep(1000);

	while (!(dynamic_cast<Start_End*>(temp) && ((Start_End*)(temp))->getKind() == 0))
	{
		int Running = temp->Debug(variables,pOut);

		if (dynamic_cast<ReadWrite*>(temp) && ((ReadWrite*)temp)->getKind()) //read
		{
			string var = ((ReadWrite*)temp)->getVar();
			pOut->PrintMessage("Enter the value of " + var + " :");
			double val = pIn->GetValue(pOut);
			variables[var] = val;
			string x;
			stringstream Q(x);
			Q << var << "=" << val;

		}
		else if (dynamic_cast<ReadWrite*>(temp) && !((ReadWrite*)temp)->getKind())//write
		{
			string var = ((ReadWrite*)temp)->getVar();
			double val = variables[var];
			string x;
			stringstream Q(x);
			Q << val<<"                   //Output";
			pOut->PrintMessage(Q.str());

		}

		if (Running == 0)
		{
			pOut->PrintMessage("Undeclared identifier. Aborting ...");
			Sleep(2000);
			pOut->ClearStatusBar();
			return;
		}
		else if (Running == 1) //Regular Statement or Conditional yes side 
		{
			Connector **arr2;
			int n;

			temp->SetSelected(true);
			pManager->UpdateInterface();
			Point P;
			pIn->GetPointClicked(P);
			temp->SetSelected(false);
			pManager->UpdateInterface();

			temp->getConn(arr2, n);
			temp = arr2[0]->getDstStat();
		}
		else if (Running == 2) //Conditional no side 
		{
			Connector **arr2;
			int n;

			temp->SetSelected(true);
			pManager->UpdateInterface();
			Point P;
			pIn->GetPointClicked(P);
			temp->SetSelected(false);
			pManager->UpdateInterface();

			temp->getConn(arr2, n);
			temp = arr2[1]->getDstStat();
		}
		else if (Running == -1)
		{
			pOut->PrintMessage("Attemping to divide by zero. Aborting...");
			Sleep(2000);
			pOut->ClearStatusBar();
			return;
		}
		else if (Running==3)
		{
			pOut->PrintMessage("some variables in the flow chart are wrong . Aborting...");
			Sleep(2000);
			pOut->ClearStatusBar();
			return;
		}
	}
	pOut->ClearStatusBar();
}