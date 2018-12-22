#pragma once
#include "base.h"
void testFollow(node* set1, node* set2, int n);
void constdeclaration();
void vardeclaration();
void factor(node*);					//因子
void term(node*);					//项
void expression(node*);					//表达式
void condition(node*);
void statement(node*, int);
void block(int, node*);