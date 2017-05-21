#include "Action.h"
#include <cctype>

bool Action::IsValid(string s) //as A variable
{
	if(isdigit(s[0]) || isspace(s[0]))
		return false;
	else if(ispunct(s[0]) && int(s[0])!= 95)
		return false;
	for(unsigned int i=1; i<s.size() ; i++)
	{
		if(isspace(s[i]) || (ispunct(s[i]) && int(s[i]) != 95))
		{
			return false;
			break;
		}
	}
return true;
}

bool Action::IsPoint(Point P) // in the bars ? // modified
{
	if (P.y <= UI.TlBrWdth || P.y >= UI.height - UI.StBrWdth)
		return true;
	else
		return false;
}


Point Action::IsPointDraw(Point &P, int Width) // Width Validtation
{
	//For Start/End Statments //Smpl Assign
	if (Width == UI.EllipseWidth || Width == UI.ASSGN_WDTH)
	{
		if (P.x <= 0)
		{
			P.x = 3;
			return P;
		}
		else if (P.x + Width > UI.width)
		{
			P.x = (UI.width - Width) - 15;
			return P;
		}
		return  P;
	}

	//For Conditional 
	else if (Width == UI.COND_LGN)
	{
		if (P.x - (Width / sqrt(2)) <= 0)
		{
			P.x = (int)(1.7*(Width / sqrt(2)));
			return P;
		}
		else if (P.x + (Width+20 / sqrt(2)) > UI.width)
		{
			P.x = (int)(UI.width - 2 * (Width / sqrt(2)));
			return P;
		}
		return P;
	}

	//For Read/Write Statements
	else 
	{
		if (P.x <= 0)
		{
			P.x = 30;
			return P;
		}
		else if (P.x + Width > UI.width)
		{
			P.x = (int)(UI.width - (1.3*Width));
			return P;
		}
		return P;
	}

}

Point Action::Valid_H(Point& P, int height) // height Validation
{
	int D = UI.height - UI.StBrWdth;
	//For SimpleAssign statements
	if (height == UI.ASSGN_HI || height == UI.EllipseH)
	{
		int x = P.y + height; //Current

		if (P.y + height > D)
		{
			P.y = P.y - height + ((D - P.y) - 10);
			return P;
		}
		return P;
	}

	//For Conditional 
	else if (height == UI.COND_LGN)
	{

		if ((P.y - (height / sqrt(2))) <= UI.TlBrWdth)
		{
			P.y += (int)((UI.TlBrWdth - 0.6*(P.y - (height / sqrt(2)))));
		}
		else if (P.y + (height+20 / sqrt(2)) > D)
		{
			P.y =(int)( D - (1.5*height / sqrt(2)) - 8);
			return P;
		}
		return P;
	}

	//For ReadWrite Statements 
	else 
	{
		if (P.y + height <= UI.TlBrWdth)
		{
			P.y += ((2 * height) + 35);
			return P;
		}
		else if (P.y + height > D)
		{
			P.y = D - height;
			return P;
		}
		return P;
	}
}

