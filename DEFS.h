#ifndef DEFS_H
#define DEFS_H

//This file contais some global constants and definitions to be used in the project.


enum ActionType //The actions supported (you can add more if needed)
{
	ADD_SMPL_ASSIGN, //Add simple assignment statement 
	//ADD_VAR_ASSIGN,	//Add variable assignment statement ??
	ADD_CONDITION, //Add a conditional statement (for if and while-loop statements)

	ADD_Single_OP,
	ADD_One_Variable,
	No_Action,

	ADD_CONNECTOR, //Add a connector between two statements 

	EDIT_STAT,	//Edit a statement
	EDIT_CONN,

	SELECT,		//Select a statement, a connector 
	MULTI_SELECT,

	DEL,		//Delete a figure(s) 
	MOVE,		//Move a figure(s) 

	SAVE,		//Save the whole graph to a file 
	LOAD,		//Load a graph from a file 
	EXIT,		//Exit the application 
	STATUS,		//A click on the status bar 
	DSN_TOOL,	//A click on an empty place in the design tool bar 
	DSN_MODE,	//Switch to Design mode 
	SIM_TOOL,	//A click on an empty place in the Simulation tool bar 
	SIM_MODE,	//Switch to simulatiom mode 

	ADD_ellipse_start,
	ADD_ellipse_END,

	ADD_Read,
	ADD_Write,

	COPY,
	CUT,

	COMMENT,
	RUN,
	DEBUG,
	VALID,
	Generate,

	ZoomIn,
	ZoomOut,

	UNDO,
	REDO,
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
	ITM_SMPL_ASSIGN,//simple assignment statement
	ITM_COND,		//conditional statement


	ITM_EXIT,		//Exit
	
	//TODO: Add more items names here
	
	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum
	
};


enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	ITM_RUN,	//Run
	ITM_STP,	//Step by step
	
	//TODO:Add more items names here
	
	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
};




#ifndef NULL
#define NULL 0
#endif

#endif