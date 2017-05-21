#include"Add_Conn.h"

#include "..\ApplicationManager.h"
#include"..\Statements\Start_End.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

void Add_Conn::ReadActionParameters()
{
	Input *i = pManager->GetInput();
	Output *o = pManager->GetOutput();

	Connector**arr;
	int size;
	bool valid;
	do{
		valid = false;
		o->PrintMessage("Click on The Valid Source Statemnt : ");
		Point p;
		i->GetPointClicked(p);
		S = pManager->GetStatement(p);
		if (S != NULL){
			S->getConn(arr, size);
			for (int i = 0; i < size; i++)
				if (arr[i] == NULL)
				{
					valid = true;
					break;
				}
		}
	} while (S==NULL||!valid||((dynamic_cast<Start_End*>(S) && ((Start_End*)S)->getKind() == 0))); // 0 for End , Casting
	
	do{
		o->PrintMessage("Click on a valid Destination Statemnt : ");
		Point p;
		i->GetPointClicked(p);
		D = pManager->GetStatement(p);

		
	} while (D==NULL||S==D||(dynamic_cast<Start_End*>(D) && ((Start_End*)D)->getKind() == 1));
}
void Add_Conn::Execute()
{
	Output *o = pManager->GetOutput();

	bool valid = false;
	
	//Check for at least 2 statements to connect between 
	if (pManager->Statementcurrent() >= 2)
	{
		for (int i = 0; i < pManager->Statementcurrent(); i++)
		{
			if ((dynamic_cast<Start_End*>(pManager->Statementlist()[i]) && ((Start_End*)pManager->Statementlist()[i])->getKind() == 0)) {
				continue;
			}
			Connector **arr; int n;
			pManager->Statementlist()[i]->getConn(arr, n);
			for (int k = 0; k < n; k++)
			{
				if (arr[k] == NULL)
				{
					for (int j = 0; j < pManager->Statementcurrent(); j++)
					{
						if (pManager->Statementlist()[j] != pManager->Statementlist()[i] && !(((dynamic_cast<Start_End*>(pManager->Statementlist()[j]) && ((Start_End*)pManager->Statementlist()[j])->getKind() == 1))))
						{
							valid = true;
							break;
						}
					}
				}
				if (valid)break;
			}
			if (valid)break;
		}
	
		if (!valid)
		{
			o->PrintMessage("there is no valid Connectors to be drawn !");
			Sleep(2000);
			o->ClearStatusBar();
			return;
		}
	}
	else
	{
		o->PrintMessage("there is not enough Statements to connect !");
		Sleep(2000);
		o->ClearStatusBar();
		return;
	}
	
	ReadActionParameters();
	Connector *C = new Connector(S,D,false);
	pManager->AddConnector(C);
	pManager->GetOutput()->ClearStatusBar();
}