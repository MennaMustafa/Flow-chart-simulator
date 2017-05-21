#include "Edit_Conn.h"

Edit_Conn::Edit_Conn(ApplicationManager*A): Action(A)
{ 
}

void Edit_Conn::ReadActionParameters() 
{

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	if(pManager->GetSelectedConnector() != NULL)
	{
		 C = pManager->GetSelectedConnector();
	}	
	else
	{
		do
		{
			pOut->PrintMessage("Select Connector to Edit! ");
			Point Selected;
			pIn->GetPointClicked(Selected);
			C= pManager->GetConnector(Selected);
		}while(C==NULL);
	}

	
		do
		{
			pOut->PrintMessage("Click on The Valid Source Statemnt : ");
			Point p;
			pIn->GetPointClicked(p);
			Source = pManager->GetStatement(p);
		} while (Source==NULL||(dynamic_cast<Start_End*>(Source) && ((Start_End*)Source)->getKind() == 0)); // 0 for End , Casting


		do
		{
			pOut->PrintMessage("Click on a valid Destination Statemnt : ");
			Point X;
			pIn->GetPointClicked(X);
			Dist = pManager->GetStatement(X);

		} while (Dist==NULL||dynamic_cast<Start_End*>(Dist) && ((Start_End*)Dist)->getKind() == 1);
		pOut->ClearStatusBar();	

}

void Edit_Conn::Execute() 
{
	if (pManager->Connectorcurrent() == 0)
	{
		pManager->GetOutput()->PrintMessage("No Connectors to Edit !");
	}
	ReadActionParameters();
	C->Edit(Source,Dist);
	pManager->GetOutput()->ClearStatusBar();
}