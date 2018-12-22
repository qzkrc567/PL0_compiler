#include "stdafx.h"
#include "grammar.h"
#include "error.h"
#include "lex.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void test(node* set1, node* set2, int n)	//测试当前符号是否合法，若不合法，打印出错标志并继续跳读
{
	if (sym == "non")
		return;
	if (!in(sym, set1))
	{
		error(n);
		set1 = add(set1, set2);
		while (!in(sym, set1))
			getsym();
	}
}

void constdeclaration()				//声明常量
{
	if (sym == "ident")
	{
		getsym();
		if (sym == "eql" || sym == "assign")
		{
			if (sym == "assign")
				error(1);			//常数说明中的“=”写成“:=”
			getsym();
			if (sym == "number")
			{
				enter(constant);
				getsym();
			}
			else error(2);			//常数说明中的“=”后面应该是数字
		}
		else error(3);				//常数说明后面应该是“=”
	}
	else error(4);					//const,var,procedure后面应该是标识符
}

void vardeclaration()				//声明变量
{
	if (sym == "ident")
	{
		enter(variable);
		getsym();
	}
	else error(4);					//const,var,procedure后面应该是标识符
}

void factor(node* fsys)				//因子
{
	node* temp = new node;
	int i;
	temp->pa[0] = "rpar";
	test(facbegsys, fsys, 24);
	while (in(sym, facbegsys))
	{
		if (sym == "ident")
		{
			i = position(id);
			if (i == -1) error(11);									//标识符未声明！
			else
			{
				if (table[i].kind == constant) gen(lit, 0, table[i].value);
				else if (table[i].kind == variable) gen(lod, lev - table[i].level, table[i].addr);
				else if (table[i].kind == procedure) error(21);		//表达式内的标识符不能是函数名！
			}
			getsym();
		}
		else if (sym == "number")
		{
			if (num > INT_MAX)
			{
				error(31);
				num = 0;
			}
			gen(lit, 0, num);
			getsym();
		}
		else if (sym == "lpar")
		{
			getsym();
			expression(add(temp, fsys));
			if (sym == "rpar") getsym();
			else error(22);			//无右括号
		}
		test(add(temp, fsys), facbegsys, 23);	//查看因子后有无非法符号
	}
}

void term(node *fsys)				//项
{
	string mulop;
	node *temp = new node;
	temp->pa[0] = "mul";
	temp->pa[1] = "div";
	factor(add(temp, fsys));
	while (in(sym, temp))
	{
		mulop = sym;
		getsym();
		factor(add(temp, fsys));
		if (mulop == "mul") gen(opr, 0, 4);
		else gen(opr, 0, 5);
	}
}

void expression(node* fsys)					//表达式
{
	string addop;
	node* temp = new node;
	temp->pa[0] = "plus";
	temp->pa[1] = "minus";
	if (in(sym, temp))
	{
		addop = sym;
		getsym();
		term(add(fsys, temp));
		if (addop == "minus") gen(opr, 0, 1);
	}
	else term(add(fsys, temp));
	while (in(sym, temp))
	{
		addop = sym;
		getsym();
		term(add(fsys, temp));
		if (addop == "plus") gen(opr, 0, 2);
		else gen(opr, 0, 3);
	}
}

void condition(node* fsys)
{
	string relop;
	string tempset[6] = { "eql", "neq", "less", "gtr", "geq", "leq" };
	node* temp1 = new node();
	for (int i = 0; i < 6; i++)
		temp1->pa[i] = tempset[i];
	node* temp2 = new node();
	temp2->pa[0] = "dosym";
	if (sym == "oddsym")
	{
		getsym();
		expression(fsys);
		gen(opr, 0, 6);
	}
	else
	{
		expression(add(temp1, fsys));
		if (!in(sym, temp1)) error(20);
		else
		{
			relop = sym;
			getsym();
			expression(add(fsys, temp2));
			for (int i = 0; i < 6; i++)
				if (relop == tempset[i])
					gen(opr, 0, i + 8);
		}
	}
}

void statement(node* fsys, int plevel)
{
	node* temp1 = new node;
	temp1->pa[0] = "rpar";
	temp1->pa[1] = "comma";
	node* temp2 = new node;
	temp2->pa[0] = "thensym";
	temp2->pa[1] = "dosym";
	node* temp3 = new node;
	temp3->pa[0] = "semi";
	temp3->pa[1] = "endsym";
	node* temp4 = new node;
	temp4->pa[0] = "semi";
	node* temp5 = new node;
	temp1->pa[0] = "dosym";
	node* temp6 = new node;

	int i, cx1, cx2;
	if (sym == "ident")
	{
		i = position(id);
		if (i == -1) error(11);
		else
		{
			if (table[i].kind != variable)
			{
				error(12);
				i = 0;
			}
		}
		getsym();
		if (sym == "assign") getsym();
		else error(13);
		expression(fsys);
		if (i != -1) gen(sto, plevel - table[i].level, table[i].addr);
	}
	else if (sym == "readsym")
	{
		getsym();
		if (sym != "lpar") error(24);
		else
		{
			do
			{
				getsym();
				if (sym == "ident") i = position(id);
				else i = -1;
				if (i == -1) error(35);
				else
				{
					gen(opr, 0, 16);
					gen(sto, plevel - table[i].level, table[i].addr);
				}
				getsym();
			} while (sym == "comma");
		}
		if (sym != "rpar")
		{
			error(22);
			while (!in(sym, fsys)) getsym();
		}
		else getsym();
	}
	else if (sym == "writesym")
	{
		getsym();
		if (sym == "lpar")
		{
			do
			{
				getsym();
				expression(add(temp1, fsys));
				gen(opr, 0, 14);
			} while (sym == "comma");
			if (sym != "rpar") error(33);
			else getsym();
		}
		gen(opr, 0, 15);
	}
	else if (sym == "callsym")
	{
		getsym();
		if (sym != "ident") error(14);
		else
		{
			i = position(id);
			if (i == -1) error(11);
			else
			{
				if (table[i].kind == procedure)
					gen(cal, plevel - table[i].level, table[i].addr);
				else error(15);
			}
			getsym();
		}
	}
	else if (sym == "ifsym")
	{
		getsym();
		condition(add(temp2, fsys));
		if (sym == "thensym") getsym();
		else error(16);
		cx1 = cx;
		gen(jpc, 0, 0);
		statement(fsys, plevel);
		code[cx1].a = cx;
	}
	else if (sym == "beginsym")
	{
		getsym();
		statement(add(temp3, fsys), plevel);
		while (in(sym, add(temp4, statbegsys)))
		{
			if (sym == "semi") getsym();
			else error(10);
			statement(add(temp3, fsys), plevel);
		}
		if (sym == "endsym")getsym();
		else error(17);
	}
	else
	{
		if (sym == "whilesym")
		{
			cx1 = cx;
			getsym();
			condition(add(temp5, fsys));
			cx2 = cx;
			gen(jpc, 0, 0);
			if (sym == "dosym") getsym();
			else error(18);
			statement(fsys, plevel);
			gen(jmp, 0, cx1);
			code[cx2].a = cx;
		}
	}
	test(fsys, temp6, 19);
}

void block(int plevel, node* fsys)
{
	int dx0 = 3, cx0, tx0;
	node* temp1 = new node;
	temp1->pa[0] = "semi";
	temp1->pa[1] = "endsym";
	node* temp2 = new node;
	temp2->pa[0] = "ident";
	temp2->pa[1] = "proceduresym";
	node* temp3 = new node;
	temp3->pa[0] = "semi";
	node* temp4 = new node;
	temp4->pa[0] = "ident";
	temp4->pa[0] = "non";
	node* temp5 = new node;

	lev = plevel;
	tx0 = tx;
	table[tx].addr = cx;
	gen(jmp, 0, 1);
	if (plevel > MAXLEV) error(32);
	do
	{
		if (sym == "constsym")
		{
			getsym();
			do
			{
				constdeclaration();
				while (sym == "comma")
				{
					getsym();
					constdeclaration();
				}
				if (sym == "semi") getsym();
				else error(5);
			} while (sym == "ident");
		}
		if (sym == "varsym")
		{
			getsym();
			do
			{
				dx0++;
				vardeclaration();
				while (sym == "comma")
				{
					getsym();
					dx0++;
					vardeclaration();
				}
				if (sym == "semi") getsym();
				else error(5);
			} while (sym == "ident");
		}
		while (sym == "proceduresym")
		{
			getsym();
			if (sym == "ident")
			{
				enter(procedure);
				getsym();
			}
			else error(4);
			if (sym == "semi") getsym();
			else error(4);
			int temp_tx = tx;
			block(plevel + 1, add(temp3, fsys));
			tx = temp_tx;
			lev--;
			if (sym == "semi")
			{
				getsym();
				test(add(statbegsys, temp2), fsys, 6);
			}
			else error(5);
		}
		test(add(statbegsys, temp4), declbegsys, 7);
	} while (in(sym, declbegsys));
	code[table[tx0].addr].a = cx;
	table[tx0].addr = cx;
	table[tx0].size = dx0;
	cx0 = cx;
	gen(ini, 0, dx0);
	statement(add(temp1, fsys), plevel);
	gen(opr, 0, 0);
	test(fsys, temp5, 8);
}