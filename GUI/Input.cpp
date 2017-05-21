#include "Input.h"
#include "Output.h"




Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}


string Input::GetString(Output *pO) const 
{
	string Str;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Str;
		if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() > 0)Str.resize(Str.size() - 1);
		}
		else
			Str += Key;
		pO->PrintMessage(Str);
	}
	
}


double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{

	int ctr = 0;
	string Str;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return 0;	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			break;
		if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() > 0)Str.resize(Str.size() - 1);
		}
		else if (Key >= 48 && Key <= 57) //keys nymber
			Str += Key;
		else if (Key == 46)
		{
			if (ctr == 0)
			{
				Str += Key;
				ctr++;
			}
		}
		else if (Key == 45)
			if (Str.size()==0)
				Str += Key;
		pO->PrintMessage(Str);
	}

	stringstream i(Str);
	double D=0;
	i >> D;
	
	return D;
}

ActionType Input::GetUserAction() const
{
	//This function reads the position where the user clicks to determine the desired action

	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y <= 57)
		{
			//Check whick Menu item was clicked
			if (x >= 0 && x <= 63)
				return SIM_MODE;
			if (x > 63 && x <= 139)
				return ADD_ellipse_start;
			if (x > 139 && x <= 234)
				return ADD_Read;
			if (x > 234 && x <= 305)
				return ADD_One_Variable;
			if (x > 305 && x <= 379)
				return ADD_SMPL_ASSIGN;
			if (x > 379 && x <= 457)
				return ADD_Single_OP;
			if (x > 457 && x <= 532)
				return ADD_ellipse_END;
			if (x > 532 && x <= 592)
				return ADD_CONDITION;
			if (x > 592 && x <= 646)
				return ADD_CONNECTOR;
			if (x > 646 && x <= 717)
				return COPY;
			if (x > 717 && x <= 781)
				return CUT;
			if (x > 781 && x <= 838)
				return MOVE;
			if (x > 838 && x <= 908)
				return  COMMENT;
			return DSN_TOOL;	//a click on empty part of the tool bar

		}
		else if (y >= 60 && y <= UI.TlBrWdth)
		{
			if (x >= 0 && x <= 63)
				return LOAD;
			if (x > 63 && x <= 139)
				return SAVE;
			if (x > 139 && x <= 234)
				return ADD_Write;
			if (x > 234 && x <= 305)
				return SELECT;
			if (x > 305 && x <= 379)
				return MULTI_SELECT;
			if (x > 379 && x <= 457)
				return UNDO;
			if (x > 457 && x <= 532)
				return REDO;
			if (x > 532 && x <= 592)
				return ZoomIn;
			if (x > 592 && x <= 646)
				return ZoomOut;
			if (x > 646 && x <= 717)
				return EDIT_CONN;
			if (x > 717 && x <= 781)
				return EDIT_STAT;
			if (x > 781 && x <= 838)
				return DEL;
			if (x > 838 && x <= 908)
				return  EXIT;
		}

		//[2] User clicks on the drawing area
		if (y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
		{
			return No_Action;	//user want to select/unselect a statement in the flowchart
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//Application is in Simulation mode
	{
		//return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
		if (y >= 0 && y <= 78)
		{
			if (x >= 0 && x <= 77)
				return DSN_MODE;
			else if (x>77 && x <= 157)
				return RUN;
			else if (x>157 && x <= 234)
				return DEBUG;
			else if (x>234 && x <= 314)
				return VALID;
			else if (x>314 && x <= 395)
				return Generate;
			else return No_Action;
		}
		else {
			return No_Action;
		}
	}

}
Input::~Input()
{
}
