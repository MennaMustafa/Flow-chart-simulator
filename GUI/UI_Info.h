#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\DEFS.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	
	int width, height;	//Window width and height
	int wx, wy;			//Window starting coordinates

	int StBrWdth;		//Status Bar Width
	int TlBrWdth;		//Tool Bar Width
	int MnItWdth;		//Menu Item Width
	
	color DrawClr;		//Drawing color
	color HiClr;		//Highlighting color
	color MsgClr;		//Messages color

	int ASSGN_WDTH;		//Assignment statement default width
	int ASSGN_HI;		//Assignment statement default height
	
	int COND_LGN;		//Conditional length

	int r_width;		//Read and Write 
	int r_height;		//Read and write
	int EllipseH ;   //height of ellipse item
	int EllipseWidth;  //width of ellipse item


}UI;	//create a single global object UI 

struct Point	
{
	int x,y;
	Point(int a=0, int b=0)	//constructor
	{ x=a;	y=b;}
};

#endif