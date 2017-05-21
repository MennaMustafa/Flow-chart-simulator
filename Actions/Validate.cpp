#include "Validate.h"

void Validate::Execute() 
{

	pOut = pManager->GetOutput();
	List = pManager->Statementlist();

	//Check For one start and one End // 

	int St_Count =0 ; int En_Count =0;
	for(int i=0; i<pManager->Statementcurrent(); i++)
	{
		if(dynamic_cast<Start_End*>(List[i]))
		{
			if(dynamic_cast<Start_End*>(List[i])&&((Start_End*)List[i])->getKind() == 0)
				En_Count++;
			else if(dynamic_cast<Start_End*>(List[i])&&((Start_End*)List[i])->getKind() == 1)
				St_Count++;
		}
	}
	if(St_Count > 1|| St_Count==0)
	{
		pOut->PrintMessage("FlowChart Can't contain more/less than one Start!");
		Valid=false;
		Sleep(1000);
		pOut->ClearStatusBar();
		return;
	}
	if(En_Count > 1||En_Count==0)
	{
		pOut->PrintMessage("FlowChart Can't contain more/less than one End!");
		Valid=false;
		Sleep(1000);
		pOut->ClearStatusBar();
		return;
	}

	//Check if Fully Connected 
	Connector**C; int Size; int Count=0;
	for(int i=0; i<pManager->Statementcurrent(); i++)
	{
		if (dynamic_cast<Start_End*>(List[i])&&((Start_End*)(List[i]))->getKind()==0) continue;
		if(!dynamic_cast<Conditional*>(List[i]))
		{
			List[i]->getConn(C,Size);
			if(Size != 1 || C[0]==NULL)
				Count++;
		}
		else if(dynamic_cast<Conditional*>(List[i]))
		{
			List[i]->getConn(C,Size);
			if(Size != 2 || C[0]==NULL || C[1]==NULL)
				Count++;
		}
	}
	
		//One Connector to End statement
		CList = pManager->Connectorlist(); int End=0;
		for(int j=0; j<pManager->Connectorcurrent(); j++)
		{
			if(dynamic_cast<Start_End*>(CList[j]->getDstStat()) != NULL)
			{
				if(((Start_End*)(CList[j]->getDstStat()))->getKind() == 0)
					End++;
			}
		}
		
		if(St_Count==1 && Count==0 && En_Count==1 && End>=1)
		{
			Valid=true;
			pOut->PrintMessage("Congratulation, your flow chart is valid, you can debug, run or generate your code :D ");
		}
		else {
			Valid = false;
			pOut->PrintMessage("Your FlowChart is not fully connected, check missing connectors!");
		}
		Sleep(2000);
		pManager->GetOutput()->ClearStatusBar();
}

bool Validate::getVaild()
{
	return Valid;
}

	