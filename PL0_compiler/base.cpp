#include "stdafx.h"

#include "base.h"


//CFile fin;
//ifstream input("input.txt");
//ofstream fa("fa.txt");
//ofstream fa1("fa1.txt");

char ch;				//当前读取的字符
string id;				//当前标识符（或者保留字）
string sym;				//当前的单词的类型
string line;			//当前行
string fname;			//文件名
char inputcode[10001];
double num;				//当前读取的num，double类型
int cur;
int cc;					//当前字符在这一行的位置
int cx;					//Pcode的数量
int err = 0;			//错误数量
int lev = 0;			//函数或者变量所在的层数
int dx = 3;				//变量所在的地址
int tx = -1;			//表索引
int linecnt = 0;		//行数
int runtime = 0;		
DWORD codeLength;
string pCode[8] = { "lit", "opr", "lod", "sto", "cal", "ini", "jmp", "jpc" };
struct errors err_msg[ERRMAX];	//错误信息
struct onePCode code[1001];
struct tableitem table[101];
struct stringSet *declarationbeginsys, *statementbeginsys, *factorbeginsys, *blocksetsys;

bool in(string str, struct stringSet* set)
{
	for (int i = 0; i < 32 && !set->pa[i].empty(); i++)
	{
		if (str == set->pa[i])
			return true;
	}
	return false;
}

stringSet* add(stringSet *set1, stringSet *set2)
{
	int cnt = 0;
	stringSet *res = new stringSet();
	for (int i = 0; i < 32 && !set1->pa[i].empty(); i++)
		res->pa[cnt++] = set1->pa[i];
	for (int i = 0; i < 32 && !set2->pa[i].empty(); i++)
		if (!in(set2->pa[i], set1))
			res->pa[cnt++] = set2->pa[i];
	return res;
}

void newPCode(fuc x, int y, double z)				//新增一行PCode
{
	code[cx].f = x;
	code[cx].l = y;
	code[cx++].a = z;
}

void enter(object k)			//向符号表中添加项
{
	tx++;
	table[tx].kind = k;
	table[tx].name = id;
	if (k == constant)
	{
		table[tx].value = num;
	}
	else if (k == variable)
	{
		table[tx].level = lev;
		table[tx].addr = dx++;
	}
	else if (k == procedure)
	{
		table[tx].level = lev;
	}
}

int position(string id)				//在符号表中查找,-1表示没找到
{
	for (int i = tx; i >= 0; i--)
		if (table[i].name == id)
			return i;
	return -1;
}