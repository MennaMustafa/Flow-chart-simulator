#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 915;
	UI.height = 700;
	UI.wx = 15;
	UI.wy =15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StBrWdth = 50;
	UI.TlBrWdth = 116;
	UI.MnItWdth = 80;

	UI.DrawClr = BLUE;
	UI.HiClr = RED;
	UI.MsgClr = BLACK; //New!

	UI.ASSGN_WDTH = 160;
	UI.ASSGN_HI = 33;

	UI.COND_LGN = 43;

	UI.r_width = 100;
	UI.r_height = 33;
	
	UI.EllipseH = 46;   //height of ellipse item
	UI.EllipseWidth = 80;  //width of ellipse item



	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	pWind->DrawImage("images\\bg1.jpg", 0, UI.TlBrWdth);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");

	pWind->SetPen(BLACK, 2);
	CreateDesignToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height - UI.StBrWdth, UI.width, UI.height - UI.StBrWdth);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the Design Menu
void Output::CreateDesignToolBar()
{
	UI.AppMode = DESIGN;	//Design Mode
	int i = 0;
	pWind->DrawImage("images\\lasttool.jpg", 0, 0); //NEW !
}


void Output::CreateSimulationToolBar()
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	///TODO: add code to create the simulation tool bar
	pWind->DrawImage("images\\bg1.jpg", 0, 0);
	pWind->DrawImage("images\\newsim.jpg", 0, 0);

	pWind->SetPen(BLACK, 2); //New!
	pWind->DrawLine(0, UI.height - UI.StBrWdth, UI.width, UI.height - UI.StBrWdth);

}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	pWind->DrawLine(0, UI.height - UI.StBrWdth, UI.width, UI.height - UI.StBrWdth);
	pWind->DrawImage("images\\statusbar.jpg", 0, UI.height - 47);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	if (UI.AppMode == DESIGN)
	{
		pWind->SetPen(BLACK, 1);
		pWind->DrawImage("images\\bg.jpg", 0, UI.TlBrWdth,UI.width,UI.height-UI.StBrWdth-UI.TlBrWdth);
	}
	else
	{
		pWind->SetPen(BLACK, 1);
		pWind->DrawImage("images\\bg.jpg", 0, UI.TlBrWdth, UI.width, UI.height - UI.StBrWdth - UI.TlBrWdth); //New !
	}
	CreateStatusBar();

}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(20,BOLD, BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int) (UI.StBrWdth/1.5), msg);
	pWind->SetPen(UI.MsgClr, 2);//newly added
}

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20,BOLD, BY_NAME, "Arial");   
	pWind->DrawString(Left.x+15, Left.y + height/4, Text);

}
//////////////////////////////////////////////////////////////////////////////////////////

//Conditional Statement

void Output::DrawCond(Point p,int length, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color
	
	int x[] = {p.x-length,p.x,p.x+length,p.x};
	int y[] = {p.y,p.y-length,p.y,p.y+length};
	
	pWind->DrawPolygon(x,y,4);

	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20,BOLD, BY_NAME, "Arial");
	pWind->DrawString(p.x - (3 * length) / 4, p.y-10, Text);

}

void Output::DrawConn(Point p1, Point p2, bool selected)
{
	if (selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color
		
	
	if (p1.y > p2.y) //for loop Connector
		{
		pWind->DrawLine(p1.x, p1.y, p1.x, p1.y+10);
		pWind->DrawLine(p1.x, p1.y+10, p1.x + 100, p1.y+10);
		pWind->DrawLine(p1.x + 100, p1.y+10, p1.x + 100, p2.y - 10);
		pWind->DrawLine(p1.x + 100, p2.y -10, p2.x, p2.y -10);
		pWind->DrawLine(p2.x, p2.y -10, p2.x, p2.y-5);
		
		//Head of the Connector 
		pWind->DrawLine(p2.x, p2.y, p2.x - 5, p2.y - 5);
		pWind->DrawLine(p2.x, p2.y, p2.x + 5, p2.y - 5);
	}


	else if (p1.y < p2.y)
	{
		pWind->DrawLine(p1.x, p1.y, p1.x, p1.y+10);
		pWind->DrawLine(p1.x, p1.y+10, p2.x, p1.y+10);
		pWind->DrawLine(p2.x, p1.y+10, p2.x, p2.y - 5);

		// Head of the Connector
		pWind->DrawLine(p2.x, p2.y, p2.x - 5, p2.y - 5);
		pWind->DrawLine(p2.x, p2.y, p2.x + 5, p2.y - 5);
	}
	else if (p1.y == p2.y)
	{
		pWind->DrawLine(p1.x, p1.y, p1.x, p1.y - 10);
		pWind->DrawLine(p1.x, p1.y - 10, p2.x, p2.y - 10);
		pWind->DrawLine(p2.x, p2.y - 10, p2.x, p2.y - 5);
		
		//Head of the Connector
		pWind->DrawLine(p2.x, p2.y, p2.x - 5, p2.y - 5);
		pWind->DrawLine(p2.x, p2.y, p2.x + 5, p2.y - 5);
	}
}


//Read and Write statement
void Output::DrawRead(Point Left, int r_width, int r_height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color 
	int a[4] = { Left.x, Left.x - 20, Left.x + r_width, Left.x + r_width + 20 };
	int b[4] = { Left.y, Left.y + r_height, Left.y + r_height, Left.y };
	//Draw the statement block polygon
	pWind->DrawPolygon(a, b, 4);
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20,BOLD, BY_NAME, "Arial");   
	pWind->DrawString(Left.x + 15, Left.y + 7, "Read " + Text);
}
void Output::DrawWrite(Point Left, int r_width, int r_height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color 
	int a[4] = { Left.x, Left.x - 20, Left.x + r_width, Left.x + r_width + 20 };
	int b[4] = { Left.y, Left.y + r_height, Left.y + r_height, Left.y };
	//Draw the statement block polygon
	pWind->DrawPolygon(a, b, 4);
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20,BOLD, BY_NAME, "Arial");   
	pWind->DrawString(Left.x + 15, Left.y + 7, "Write " + Text);
}

void Output::DrawEllipse(Point Left,int EllipseWidth,int EllipseH, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HiClr, 3);
	else
		pWind->SetPen(UI.DrawClr, 3);

	pWind->DrawEllipse(Left.x, Left.y, Left.x + EllipseWidth, Left.y + EllipseH, FILLED);

	pWind->SetPen(BLACK);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(Left.x + 25, Left.y + 15, Text);
}

Output::~Output()
{
	delete pWind;
}
