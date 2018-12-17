#pragma once
#include "base.h"
void test(node* set1, node* set2, int n);
void constdeclaration();
void vardeclaration();
void factor(node*);					//因子
void term(node*);					//项
void expression(node*);					//表达式
void condition(node* fsys);
void statement(node* fsys, int plevel);
void block(int plevel, node* fsys);