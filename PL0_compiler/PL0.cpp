#include "stdafx.h"
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
	cout << "请输入文件名：";
	cin >> fname;
	fin.open(fname);
	while (getline(input, inputValue[inputCnt]))
	{
		inputCnt++;
		if (inputCnt >= 50)
			break;
	}
	for (int i = 0; i < inputCnt; i++)
		cout << inputValue[i] << endl;
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



	err = 0;
	cc = 0;
	ch = ' ';
	getsym();
}

void start()
{
	block(0, add(statbegsys, tempsetsys));
	fa.close();
	fa1.close();
	if (sym != "dot") error(9);
	if (err == 0)
	{
		for(int i = 0; i < cx; i++)
			cout << setw(3) << i + 1 << setw(5) <<pCode[code[i].f] << setw(5) << code[i].l << setw(5) << code[i].a << endl;
	}
	else
	{
		printf("一共有%d个错误\n", err);
		for(int i = 0; i < err; i++)
			cout << setw(3) << i+1 << setw(35) << err_msg[i].info << setw(3) << err_msg[i].lineNum << setw(5) << err_msg[i].charNum << endl;
	}
	fin.close();
}

int compiler()
{
	init();
	start();
	return 0;
}