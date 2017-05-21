#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();	

	window* CreateWind(int, int, int , int);
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode

	void CreateStatusBar();

	Input* CreateInput(); //creates a pointer to the Input object	
	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area

	// -- Statements Drawing Functions
	void DrawAssign(Point Left, int width, int height, string Text, bool Selected=false);
	void DrawCond(Point Center,int length, string Text, bool Selected = false);
	void DrawConn(Point p1, Point p2, bool selected = false);
	void DrawEllipse(Point Left,int ,int , string Text, bool Selected = false);

	//TODO: Add similar functions for drawing all other statements.
	//		e.g. DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
	//		Decide the parameters that should be passed to each of them
	void DrawRead(Point left, int width, int height, string text, bool selected = false);
	void DrawWrite(Point left, int width, int height, string text, bool selected = false);

		
	void PrintMessage(string msg);	//Prints a message on Status bar
	
	~Output();
};

#endif