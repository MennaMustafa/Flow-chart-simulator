#include "ApplicationManager.h"
#include<cmath>

///////////////////////////////////////////// Actions Include////////////////////////////
#include "Actions\AddSmplAssign.h"
#include"Actions\Add_Conn.h"
#include"Actions\Add_one_operator.h"
#include"Actions\Add_Start_End.h"
#include"Actions\AddCond.h"
#include"Actions\AddReadWrite.h"
#include"Actions\AddVariable.h"
#include"Actions\Comment.h"
#include"Actions\Copy.h"
#include"Actions\Cut.h"
#include"Actions\Debug.h"
#include"Actions\Delete.h"
#include"Actions\Edit_Conn.h"
#include"Actions\Edit_Statement.h"
#include"Actions\GenerateCode.h"
#include"Actions\Load.h"
#include"Actions\Move.h"
#include"Actions\multipleSelect.h"
#include"Actions\Run.h"
#include"Actions\Save.h"
#include"Actions\Select.h"
#include"Actions\Validate.h"
//////////////////////////////////////////////////////////////////////////////




#include "GUI\Input.h"
#include "GUI\Output.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pSelectedConn = NULL;

	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
		case ADD_SMPL_ASSIGN:
			pAct = new AddSmplAssign(this);
			break;

		case ADD_CONDITION:
			pAct = new AddCond(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case EXIT:
			return;
			break;

		case STATUS: //If user clicked in status Bar 
			return;

		case No_Action: //free click
			return;
		
		case ADD_Single_OP:
			pAct = new Add_One_Operator(this);
			break;
		
		case ADD_One_Variable:
			pAct = new AddVariable(this);
			break;
		case ADD_CONNECTOR:
			pAct = new Add_Conn(this);
			break;
		case EDIT_STAT:
			pAct = new Edit_Statement(this);
			break;
		case EDIT_CONN:
			pAct = new Edit_Conn(this);
			break;
		case MULTI_SELECT:
			pAct = new multipleSelect(this);
			break;
		case DEL:
			pAct = new Delete(this);
			break;
		case MOVE:
			pAct = new Move(this);
			break;
		case SAVE:
			pAct = new Save(this);
			break;
		case LOAD:
			pAct = new Load(this);
			break;
		case DSN_MODE:
			pOut->CreateDesignToolBar();
			break;
		case SIM_MODE:
			pOut->CreateSimulationToolBar();
			break;
		case ADD_ellipse_start:
			pAct = new Add_Start_End(this,1);
			break;
		case ADD_ellipse_END:
			pAct = new Add_Start_End(this, 0);
			break;
		case ADD_Read:
			pAct = new AddReadWrite(this, true);
			break;
		case ADD_Write:
			pAct = new AddReadWrite(this, false);
			break;
		case COPY:
			pAct = new Copy(this);
			break;
		case CUT:
			pAct = new Cut(this);
			break;
		case COMMENT:
			pAct = new Comment(this);
			break;
		case RUN:
			pAct = new Validate(this);
			pAct->Execute();
			if (((Validate*)pAct)->getVaild())
			{
				delete pAct;
				pAct = new Run(this);
			}
			break;
		case DEBUG:
			pAct = new Validate(this);
			pAct->Execute();
			if (((Validate*)pAct)->getVaild())
			{
				delete pAct;
				pAct = new Debug(this);
			}
			break;
		case VALID:
			pAct = new Validate(this);
			break;
		case Generate:
			pAct = new Validate(this);
			pAct->Execute();
			if (((Validate*)pAct)->getVaild())
			{
				delete pAct;
				pAct = new GenerateCode(this);
			}
			break;
			}



	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//
//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	for (int i = 0; i < StatCount;i++) 
	{
		if (dynamic_cast<Conditional*>(StatList[i]))
		{
			if (P.x >= StatList[i]->getCorner().x && (P.x <= StatList[i]->getCorner().x + (1.4*StatList[i]->width_height().x)*sqrt(2)) && (P.y >= StatList[i]->getCorner().y) && (P.y <= StatList[i]->getCorner().y + (1.4*StatList[i]->width_height().y)*sqrt(2)))
			//law Conditional 
			return StatList[i];
		}
		else if ((P.x >= StatList[i]->getCorner().x) && (P.x <= StatList[i]->getCorner().x + StatList[i]->width_height().x) && (P.y >= StatList[i]->getCorner().y) && (P.y <= StatList[i]->getCorner().y + StatList[i]->width_height().y))
			return StatList[i];
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}


//==================================================================================//
//						Connectors Management Functions								//
//==================================================================================//

void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}

Connector* ApplicationManager::GetSelectedConnector() const //Returns the selected Connector
{
	return this->pSelectedConn;
}
void ApplicationManager::SetSelectedConnector(Connector *pStat) //Set the Connector selected by the user
{
	pSelectedConn = pStat;
}



//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<ConnCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;	
}

bool ApplicationManager::IsPointBetween(Point q, Point w, Point e) const
{
	if (q.x >= min(w.x,e.x)&&q.x <= max(w.x,e.x)&&q.y >= min(w.y,e.y)&&q.y <= max(w.y,e.y))
		return true;
	else return false;

}


Connector* ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getStartPoint().y > ConnList[i]->getEndPoint().y)
		{
			if (IsPointBetween(P, ConnList[i]->getStartPoint(), Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y+10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y+10), Point(ConnList[i]->getStartPoint().x + 100, ConnList[i]->getStartPoint().y +10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x + 100, ConnList[i]->getStartPoint().y +10), Point(ConnList[i]->getStartPoint().x+100, ConnList[i]->getEndPoint().y - 10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x+100, ConnList[i]->getEndPoint().y - 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 10))
				|| IsPointBetween(P, Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x - 5, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x + 5, ConnList[i]->getEndPoint().y - 5))
				)
				return ConnList[i];
		}
		else if (ConnList[i]->getStartPoint().y < ConnList[i]->getEndPoint().y)
		{

			if (IsPointBetween(P, ConnList[i]->getStartPoint(), Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y+10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y+10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getStartPoint().y + 10))
				|| IsPointBetween(P, Point(ConnList[i]->getEndPoint().x, ConnList[i]->getStartPoint().y + 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y-5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x - 5, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x + 5, ConnList[i]->getEndPoint().y - 5))
				)
				return ConnList[i];
		}
		else if (ConnList[i]->getStartPoint().y == ConnList[i]->getEndPoint().y)
		{
			if (IsPointBetween(P, ConnList[i]->getStartPoint(), Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y - 10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y - 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 10))
				|| IsPointBetween(P, Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x - 5, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x + 5, ConnList[i]->getEndPoint().y - 5))
				)
				return ConnList[i];
		}
	}
	return NULL;
}




void ApplicationManager::DeleteConnector(Connector *C)
{
	Connector**arr; int n;
	C->getSrcStat()->getConn(arr, n);
	if (n == 1)
		C->getSrcStat()->setConn(NULL); 
	else if (n == 2)
	{
		if (arr[0] == C) ((Conditional*)(C->getSrcStat()))->setFConn(NULL);
		else  ((Conditional*)(C->getSrcStat()))->setSConn(NULL);
	}


	for (int i = 0; i < ConnCount;i++)
		if (ConnList[i] == C)
		{
			delete ConnList[i];
			ConnList[i] = ConnList[ConnCount - 1];
			ConnList[ConnCount - 1] = NULL;
			ConnCount--;
			break;
		}
}
void ApplicationManager::DeleteStatement(Statement *S)
{
	for (int i = 0; i < StatCount; i++)
		if (StatList[i] == S)
		{
			delete StatList[i];
			StatList[i] = StatList[StatCount - 1];
			StatList[StatCount- 1] = NULL;
			StatCount--;
			break;
		}
}



void ApplicationManager::Loading(ifstream &In)
{
	int I, L;
	map<int, int>m;
	In >> I;
	if (In.is_open())
	{
		string Type;
			for (int i = 0; i<I; i++)
			{
				In >> Type;

				if (Type == "STRT")
				{
					Statement*S = new Start_End();
					AddStatement(S);
					(dynamic_cast<Start_End*>(S))->SetLoad(true);
					S->Load(In);
				}
				else if (Type == "END")
				{
					Statement*S = new Start_End();
					AddStatement(S);
					(dynamic_cast<Start_End*>(S))->SetLoad(false);
					S->Load(In);
				}
				else if (Type == "VARIABLE")
				{
					Statement*S = new Variable();
					AddStatement(S);
					S->Load(In);
				}
				else if (Type == "SmplAssign")
				{
					Statement*S = new SmplAssign();
					AddStatement(S);
					S->Load(In);
				}
				else if (Type == "SNGLOP")
				{
					Statement*S = new SingleOp();
					AddStatement(S);
					S->Load(In);
				}
				else if (Type == "READ")
				{
					Statement*S = new ReadWrite();
					AddStatement(S);
					(dynamic_cast<ReadWrite*>(S))->SetR_Load(true);
					S->Load(In);
				}
				else if (Type == "WRITE")
				{
					Statement*S = new ReadWrite();
					AddStatement(S);
					(dynamic_cast<ReadWrite*>(S))->SetR_Load(false);
					S->Load(In);
				}
				else if (Type == "COND")
				{
					Statement*S = new Conditional();
					AddStatement(S);
					S->Load(In);
				}
			}
			In >> L;

			//TODO Outlet Branch
			int I1, I2, I3;
			Statement*S = NULL;
			Statement*D = NULL;
			for (int t = 0; t < L; t++)
			{
				In >> I1 >> I2 >> I3;
				if (I3 == 0 || I3 == 1)
				{
					for (int i = 0; i < StatCount; i++)
					{
						if (StatList[i]->getID() == I1)
							S = StatList[i];
					}
					for (int j = 0; j < StatCount; j++)
					{
						if (StatList[j]->getID() == I2)
							D = StatList[j];
					}
					Connector*C = new Connector(S, D, false);
					AddConnector(C);

				}
				else m[I1] = I2;
			}
			map<int, int>::iterator it;
			for ( it = m.begin(); it !=m.end(); it++)
			{
				for (int i = 0; i < StatCount; i++)
				{
					if (StatList[i]->getID() ==it->first )
						S = StatList[i];
				}
				for (int j = 0; j < StatCount; j++)
				{
					if (StatList[j]->getID() ==it->second )
						D = StatList[j];
				}
				Connector*C = new Connector(S, D, false);
				AddConnector(C);
			}

		}
	}

