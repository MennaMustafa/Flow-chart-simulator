#include "GenerateCode.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


void GenerateCode::Execute()
{
	Output*pOut = pManager->GetOutput();

	pOut->PrintMessage("Coding...");
	Sleep(1000);
	pOut->ClearStatusBar();

	f.open("Flow_Code.txt");

	Statement* temp;
	for (int i = 0; i < pManager->Statementcurrent(); i++)
	{
		if (dynamic_cast<Start_End*>(pManager->Statementlist()[i]) && ((Start_End*)(pManager->Statementlist()[i]))->getKind() == 1)
		{
			temp = pManager->Statementlist()[i];
			break;
		}
	}

	temp->GenerateCode(f);
	int size; Connector** arr;
	temp->getConn(arr,size);
	temp=arr[0]->getDstStat();
	
	int noVars=0;

	map<string,int>v;

	for (int i = 0; i < pManager->Statementcurrent(); i++)
	{
		if (dynamic_cast<ReadWrite*>(pManager->Statementlist()[i])&&((ReadWrite*)pManager->Statementlist()[i])->getKind()&&v.find(pManager->Statementlist()[i]->GetLHS())==v.end())
		{
			if (noVars==0){f<<"\t"<<"double "; noVars++;}
			else f<<",";
			f<<pManager->Statementlist()[i]->GetLHS();
			v[pManager->Statementlist()[i]->GetLHS()];
		}

		if (dynamic_cast<SingleOp*>(pManager->Statementlist()[i])&&v.find(pManager->Statementlist()[i]->GetLHS())==v.end())
		{
			if (noVars==0){f<<"\t"<<"double "; noVars++;}
			else f<<",";
			f<<pManager->Statementlist()[i]->GetLHS();
			v[pManager->Statementlist()[i]->GetLHS()];
		}

		if (dynamic_cast<SmplAssign*>(pManager->Statementlist()[i])&&v.find(pManager->Statementlist()[i]->GetLHS())==v.end())
		{
			if (noVars==0){f<<"\t"<<"double "; noVars++;}
			else f<<",";
			f<<pManager->Statementlist()[i]->GetLHS();
			v[pManager->Statementlist()[i]->GetLHS()];
		}

		if (dynamic_cast<Variable*>(pManager->Statementlist()[i])&&v.find(pManager->Statementlist()[i]->GetLHS())==v.end())
		{
			if (noVars==0){f<<"\t"<<"double "; noVars++;}
			else f<<",";
			f<<pManager->Statementlist()[i]->GetLHS();
			v[pManager->Statementlist()[i]->GetLHS()];
		}
	}

	if (noVars!=0)
	f<<";"<<endl;


	while (!(dynamic_cast<Start_End*>(temp) && ((Start_End*)(temp))->getKind() == 0))
	{
		if (!dynamic_cast<Conditional*>(temp))
			{
				for (int i=0;i<IND;i++) f<<"\t";
				temp->GenerateCode(f);
			}
		int size;
		Connector **arr;
		temp->getConn(arr, size);

		if (size == 1)
			temp = arr[0]->getDstStat();
		else
		{
			m[temp->getID()]=0;	//0 for if
			Generate_Conditional_Code(temp,temp,' ');
			f << "}" << endl;
			pManager->GetOutput()->ClearStatusBar();
			system("notepad.exe Flow_Code.txt");
			return;
		}
	}

	for (int i=0;i<IND;i++) f<<"\t";
	temp->GenerateCode(f);

	f << "}"<<endl;
	pManager->GetOutput()->ClearStatusBar();
	system("notepad.exe Flow_Code.txt");
	return;
}



void GenerateCode::Generate_Conditional_Code(Statement* cond, Statement *start, char c)
{
	Connector** arr;
	int n;
	start->getConn(arr, n);


	Statement* S[2];
	S[0] = arr[0]->getDstStat();
	S[1] = arr[1]->getDstStat();


	//Searching in the right connector about a loop 
	while (!(dynamic_cast<Start_End*>(S[0]) && ((Start_End*)S[0])->getKind() == 0))
	{
		if (S[0] == cond)
		{
			for (int i = 0; i < IND; i++)
				f << "\t";
			f << "while";
			if (c == '!')
				f << "(!";
			cond->GenerateCode(f);
			if (c == '!')
				f << ")";
			if (cond->GetComment() != "\"\"")
				f << "//" << cond->GetComment();
			f << endl;
			for (int i = 0; i < IND; i++)
				f << "\t";
			f<< "{"<<endl;
			IND++;
			m[cond->getID()] = 1;  
			break;
		}
		Connector** arr1;
		int n;
		S[0]->getConn(arr1, n);
		if (n == 1)S[0] = arr1[0]->getDstStat();
		else
		{
			if (S[0] == start&&start != cond)
				break;
			Generate_Conditional_Code(cond, S[0], c);
			break;
		}
	}

	
	//Searching in the Left connector about a loop 
	while (m[cond->getID()] == 0 && (!(dynamic_cast<Start_End*>(S[1]) && ((Start_End*)S[1])->getKind() == 0)))
	{
		if (S[1] == cond)
		{
			for (int i = 0; i < IND; i++)
				f << "\t";
			f << "while";
			if (start == cond)
				c = '!';
			if (c == '!')
				f << "(!";
			cond->GenerateCode(f);
			if (c == '!')
				f << ")";
			if (cond->GetComment() != "\"\"")
				f << "//" << cond->GetComment();
			f << endl;
			for (int i = 0; i < IND; i++)
				f << "\t";
			f<< "{"<<endl;
			IND++;
			m[cond->getID()] = 1; //1 for while
			break;
		}
		Connector** arr2;
		int n2;
		S[1]->getConn(arr2, n2);
		if (n2 == 1)
			S[1] = arr2[0]->getDstStat();
		else
		{
			//no hope .. it is an If Statement
			if (cond == start)
				c = '!';
			if (S[1] == start&&start != cond)
				break;
			Generate_Conditional_Code(cond, S[1], c);
			break;
		}
	}


	if (m[cond->getID()] == 0 && cond != start)
	{
		return;
	}
	else if (m[cond->getID()] == 1 && cond != start)
		return;
	else if (m[cond->getID()] == 0)
	{
		for (int i = 0; i < IND; i++) f << "\t";
		f << "if";
		cond->GenerateCode(f);
		if (cond->GetComment() != "\"\"")
			f << "// " << cond->GetComment();
		f << endl;
		for (int i = 0; i < IND; i++)
			f << "\t";
		f<< "{"<<endl;
		IND++;
	}

	Connector** arr3;
	int n3;
	cond->getConn(arr3, n3);

	Statement* T[2];
	T[0] = arr3[0]->getDstStat();
	T[1] = arr3[1]->getDstStat();

	int y = 0, u = 1;

	if (c == '!')
	{
		y = 1; u = 0;
	}

	int counter = 0;

	//generating code of the right connector
	while (((T[y] == arr3[y]->getDstStat()) && counter > 0) || !(dynamic_cast<Start_End*>(T[y]) && ((Start_End*)(T[y]))->getKind() == 0))
	{
		counter++;

		if (!dynamic_cast<Conditional*>(T[y]))
		{
			for (int i = 0; i < IND; i++) f << "\t";
			T[y]->GenerateCode(f);
		}

		int size2;
		Connector **arr;
		T[y]->getConn(arr, size2);

		if (size2 == 1)
			T[y] = arr[0]->getDstStat();

		else
		{
			if (T[y] == cond) 
				break;
			if (m.find(T[y]->getID()) == m.end())
			{
				m[T[y]->getID()];
				Generate_Conditional_Code(T[y], T[y]);
			}
			break; 
		}
	}


	if (dynamic_cast<Start_End*>(T[y]) && ((Start_End*)(T[y]))->getKind() == 0)
	{
		for (int i = 0; i < IND; i++)
			f << "\t";
		T[y]->GenerateCode(f);
	}
	IND--;
	f << endl;
	for (int i = 0; i < IND; i++)
		f << "\t";
	f<< "}"<<endl;
	if (m[cond->getID()] == 0)
	{
		for (int i = 0; i < IND; i++)
			f << "\t";
		f << "else ";
		f << endl;
		for (int i = 0; i < IND; i++)
			f << "\t";
		f<< "{"<<endl;
		IND++;
	}


	counter = 0;


	//generating code of left Connector
	while (counter > 0 && T[u] == arr3[u]->getDstStat() || !(dynamic_cast<Start_End*>(T[u]) && ((Start_End*)(T[u]))->getKind() == 0))
	{
		counter++;
		if (!dynamic_cast<Conditional*>(T[u]))
		{
			for (int i = 0; i < IND; i++)
				f << "\t";
			T[u]->GenerateCode(f);
		}
		int size;
		Connector **arr4;
		T[u]->getConn(arr4, size);

		if (size == 1)
			T[u] = arr4[0]->getDstStat();
		else
		{
			if (T[u] == cond)
				break;
			if (m.find(T[u]->getID()) == m.end())
			{
				m[T[u]->getID()];
				Generate_Conditional_Code(T[u], T[u]);
			}
			break;
		}
	}


	if (dynamic_cast<Start_End*>(T[u]) && ((Start_End*)(T[u]))->getKind() == 0)
	{
		for (int i = 0; i < IND; i++) 
			f << "\t";
		T[u]->GenerateCode(f);
	}

	if (m[cond->getID()] == 0)
	{
		IND--;
		for (int i = 0; i < IND; i++)
			f << "\t";
		f << "}"<<endl;
	}
}
