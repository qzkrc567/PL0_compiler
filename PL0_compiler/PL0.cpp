#include "stdafx.h"
#include "PL0.h"
#include "lex.h"
#include "error.h"
#include "base.h"
#include "grammar.h"
#include "interpret.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void init()
{
	
	declbegsys = new node;
	declbegsys->pa[0] = "constsym";
	declbegsys->pa[1] = "varsym";
	declbegsys->pa[2] = "proceduresym";
	statbegsys = new node;
	statbegsys->pa[0] = "beginsym";
	statbegsys->pa[1] = "callsym";
	statbegsys->pa[2] = "ifsym";
	statbegsys->pa[3] = "whilesym";
	facbegsys = new node;
	facbegsys->pa[0] = "ident";
	facbegsys->pa[1] = "number";
	facbegsys->pa[2] = "lpar";
	tempsetsys = new node;
	tempsetsys->pa[0] = "dot";
	tempsetsys->pa[1] = "constsym";
	tempsetsys->pa[2] = "varsym";
	tempsetsys->pa[3] = "proceduresym";
	tempsetsys->pa[3] = "non";

	cur = 0;
	err = 0;
	cc = 0;
	cx = 0;
	line = "";
	ch = ' ';
	lev = 0;
	dx = 3;
	tx = -1;
	linecnt = 0;
	getsym();
}

vector<vector<string>> compiler(char* Buf, DWORD len)
{
	for (int i = 0; i < len; i++)
	{
		inputcode[i] = Buf[i];
		if (i == 225)
		{
			cout << "" << endl;
		}
	}
	cout << inputcode << endl;
	codeLength = len;
	init();
	vector<vector<string>> res;
	vector<string> type;
	block(0, add(statbegsys, tempsetsys));
	//fa.close();
	//fa1.close();
	if (sym != "dot") error(9);
	if (err == 0)
	{
		type.push_back("ok");
		res.push_back(type);
		for (int i = 0; i < cx; i++)
		{
			vector<string> temp;
			temp.push_back(pCode[code[i].f]);
			temp.push_back(to_string(code[i].l));
			temp.push_back(to_string(code[i].a));
			res.push_back(temp);
		}
	}
	else
	{
		//printf("一共有%d个错误\n", err);
		type.push_back("error");
		res.push_back(type);
		for (int i = 0; i < err; i++)
		{
			vector<string> temp;
			temp.push_back(to_string(err_msg[i].lineNum));
			temp.push_back(to_string(err_msg[i].charNum));
			temp.push_back(err_msg[i].info);
			res.push_back(temp);
		}
	}
	return res;
}