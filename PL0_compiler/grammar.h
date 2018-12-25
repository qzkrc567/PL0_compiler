#pragma once
#include "base.h"
void testFollow(stringSet* set1, stringSet* set2, int n);//判断下一个符号是否合法
void constdeclaration();						//常量声明
void vardeclaration();							//变量声明
void block(int, stringSet*);					//块
void statement(stringSet*, int);				//语句
void expression(stringSet*);					//表达式
void term(stringSet*);							//项
void factor(stringSet*);						//因子
void condition(stringSet*);						//判断语句
