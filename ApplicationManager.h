#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include<map>

#include "Statements\Statement.h"
#include"Statements\Conditional.h"
#include"Statements\Start_End.h"
#include"Statements\ReadWrite.h"
#include"Statements\SingleOp.h"
#include"Statements\SmplAssign.h"
#include"Statements\Variable.h"


class Input;
class Output;

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)

	Statement *pSelectedStat; //a pointer to the last selected statement
	Connector *pSelectedConn; //a pointer to the last selected statement 

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	bool IsPointBetween(Point, Point, Point) const; //To get Connector between two points

public:
	ApplicationManager();
	~ApplicationManager();

	// -- Actions Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType); //Creates an action and executes it

	Statement** Statementlist() { return StatList; }
	Connector** Connectorlist() { return ConnList;}
	int Statementcurrent() { return StatCount; }
	int Connectorcurrent() { return ConnCount; }


	// -- Statements/Connector Management Functions
	void AddStatement(Statement* pStat); //Adds a new Statement to the Flowchart
	Statement *GetStatement(Point P) const;	//search for a statement where point P belongs

	void AddConnector(Connector* pConn); //Adds a new Connector to the Flowchart
	Connector *GetConnector(Point P) const;	//search for a Connector where point P belongs


	Statement *GetSelectedStatement() const;	//Returns the selected Statement
	void SetSelectedStatement(Statement *pStat); //Set the Statement selected by the user

	Connector *GetSelectedConnector() const;	//Returns the selected Connector
	void SetSelectedConnector(Connector *pStat); //Set the Connector selected by the user

	void DeleteConnector(Connector *); 
	void DeleteStatement(Statement *);


	void ApplicationManager::Loading(ifstream &In);//Load Action 

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	
};

#endif