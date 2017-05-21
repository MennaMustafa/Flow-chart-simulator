#include "Action.h"
#include"../Statements/Statement.h"

class Comment: public Action 
{
private:
	Statement*S;
	string C; // Comment
public:
	Comment(ApplicationManager*AppManager);
	void Execute();
	virtual void ReadActionParameters();

};