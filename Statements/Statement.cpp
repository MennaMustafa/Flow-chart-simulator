#include "Statement.h"

int Statement::static_ID = 0;

Statement::Statement()	
{ 
	ID = ++static_ID;
	Text = "";
	Selected = false;		
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

void Statement::Comment(string s)
{
	C = s;
}

string Statement::GetComment()
{
	if (C.size() == 0)
		return"\"\"";
	return C;
}




bool Statement::IsValid(string s) //as A variable
{
	if (isdigit(s[0]) || isspace(s[0]))
		return false;
	else if (ispunct(s[0]) && int(s[0]) != 95)
		return false;
	for (unsigned int i = 1; i<s.size(); i++)
	{
		if (isspace(s[i]) || (ispunct(s[i]) && int(s[i]) != 95))
		{
			return false;
			break;
		}
	}
return true;
}

bool Statement::IsPoint(Point P) // in the bars ?
{
	if (P.y <= 117 || P.y >= UI.StBrWdth)
		return false;
	else
		return true;
}

Point Statement::IsPointDraw(Point &P, int Width) // can the Window hold this statement
{
	if (P.x < 0)
	{
		P.x = 0;
		return P;
	}
	else if (P.x + Width > UI.width)
	{
		P.x = UI.width - Width;
		return P;
	}
	else return P; 
}

