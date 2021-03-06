#include "stdafx.h"
#include "base.h"
#include "error.h"
#include "lex.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string keyword[13] = { "begin", "call", "const", "do", "end", "if", "odd", "procedure", "read", "then", "var", "while", "write"};

void getChar() //读入一个字符，如果要换行，把一行的代码存入line
{
	if (cc == line.size())
	{
		linecnt++;
		line = "";
		if (cur >= codeLength)
		{
			err_msg[err].info = "lexical program incomplete";
			err_msg[err].lineNum = linecnt;
			err_msg[err++].charNum = cc;
			printf("一共有%d个错误\n", err);
			for (int i = 0; i < err; i++)
				cout << setw(3) << i << setw(30) << err_msg[i].info << setw(3) << err_msg[i].lineNum << setw(5) << err_msg[i].charNum << endl;

			cout << "lexical program incomplete!" << endl;
			ch = '\a';
			return;
		}
		cc = 0;
		while (cur < codeLength)
		{
			ch = inputcode[cur++];
			if (ch != '\n')
			{
				cout << ch;
				line += ch;
			}
			else break;
		}
		if (cur < codeLength)
		{
			cout << ch;
			line += ch;
		}
		else
		{
			cout << endl;
			line += '\n';
		}
	}
	ch = line[cc++];
	if (ch == '\r')
		ch = line[cc++];
}

void getsym()
{
	while (ch == ' ' || ch == '\t' || ch == '\n')
		getChar();
	if (ch >= '0' && ch <= '9') //数字
	{
		string temp = "";
		while (ch >= '0' && ch <= '9')
		{
			temp += ch;
			getChar();
		}
		if (ch == '.')
		{
			while (ch >= '0' && ch <= '9')
			{
				temp += ch;
				getChar();
			}
			num = atof(temp.c_str());
		}
		else
			num = atof(temp.c_str());
		sym = "number";
		if (num > INT_MAX)
		{
			num = INT_MAX;
			error(25);
		}//数越界
	}
	else if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))	//标识符或者保留字
	{
		id = "";
		id += ch;
		getChar();
		while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9'))
		{
			id += ch;
			getChar();
		}
		sym = "ident";
		for (int i = 0; i < 13; i++)
			if (id == keyword[i])
			{
				sym = keyword[i] + "sym";
				break;
			}
	}
	else if (ch == ':')
	{
		getChar();
		if (ch == '=')
		{
			sym = "assign";
			getChar();
		}
		else
			sym = "nul";
	}
	else if (ch == '<')
	{
		getChar();
		if (ch == '=')
		{
			sym = "leq";
			getChar();
		}
		else if (ch == '>')
		{
			sym = "neq";
			getChar();
		}
		else
			sym = "less";
	}
	else if (ch == '>')
	{
		getChar();
		if (ch == '=')
		{
			sym = "geq";
			getChar();
		}
		else
			sym = "gtr";
	}
	else
	{
	if (ch == '+')
		sym = "plus";
	else if (ch == '-')
		sym = "minus";
	else if (ch == '*')
		sym = "mul";
	else if (ch == '/')
		sym = "div";
	else if (ch == '(')
		sym = "lpar";
	else if (ch == ')')
		sym = "rpar";
	else if (ch == '=')
		sym = "eql";
	else if (ch == ',')
		sym = "comma";
	else if (ch == '.')
		sym = "dot";
	else if (ch == '#')
		sym = "neq";
	else if (ch == ';')
		sym = "semi";
	else if (ch == '\a')
	{
		sym = "non";
		return;
	}
	else
		sym = "undefined";
		getChar();
	}
}