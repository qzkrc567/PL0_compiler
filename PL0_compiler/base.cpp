#include "stdafx.h"

#include "base.h"


ifstream fin;
ifstream input("input.txt");
ofstream fa("fa.txt");
ofstream fa1("fa1.txt");
ofstream fa2("fa2.txt");

char ch;				//��ǰ��ȡ���ַ�
string id;				//��ǰ��ʶ�������߱����֣�
string sym;				//��ǰ�ĵ��ʵ�����
string line;			//��ǰ��
string fname;			//�ļ���
string inputValue[50];	//PL0������Ҫ������
int inputCnt = 0;		//���������
double num;				//��ǰ��ȡ��num��double����
int cc;					//��ǰ�ַ�����һ�е�λ��
int cx;					//Pcode������
int err = 0;			//��������
int lev = 0;			//�������߱������ڵĲ���
int dx = 3;				//�������ڵĵ�ַ
int tx = -1;			//������
int linecnt = 0;		//����
string pCode[8] = { "lit", "opr", "lod", "sto", "cal", "ini", "jmp", "jpc" };
struct errors err_msg[ERRMAX];	//������Ϣ
struct instruction code[1001];
struct tableitem table[101];
struct node *declbegsys, *statbegsys, *facbegsys, *tempsetsys;

bool in(string str, struct node* set)
{
	for (int i = 0; i < 32 && !set->pa[i].empty(); i++)
	{
		if (str == set->pa[i])
			return true;
	}
	return false;
}

node* add(node *set1, node *set2)
{
	int cnt = 0;
	node *res = new node();
	for (int i = 0; i < 32 && !set1->pa[i].empty(); i++)
		res->pa[cnt++] = set1->pa[i];
	for (int i = 0; i < 32 && !set2->pa[i].empty(); i++)
		if (!in(set2->pa[i], set1))
			res->pa[cnt++] = set2->pa[i];
	return res;
}

void gen(fuc x, int y, double z)				//����һ��PCode
{
	code[cx].f = x;
	code[cx].l = y;
	code[cx++].a = z;
}

void enter(object k)			//����ű��������
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

int position(string id)				//�ڷ��ű��в���,-1��ʾû�ҵ�
{
	for (int i = 0; i <= tx; i++)
		if (table[i].name == id)
			return i;
	return -1;
}