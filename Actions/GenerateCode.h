#include"Action.h"

#include"../Statements/Start_End.h"
#include"../Statements/Conditional.h"

#include<vector>
#include<fstream>
using namespace std;

class GenerateCode:public Action
{
	map<int ,int>m;
	ofstream f;
	int IND; // for Indentation

	void Generate_Conditional_Code(Statement* cond ,Statement* start,char c=' '); // Responsible for generating conditional statement whether it is if condition or while loop
// job : searching for any connector from the starting statement to connect the conditional again (while loop) and continue generating to the end

public:
	GenerateCode(ApplicationManager* A) :Action(A){ IND = 1; }
	void ReadActionParameters(){}
	void Execute();
};