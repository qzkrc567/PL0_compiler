#pragma once
#include "base.h"
void test(node* set1, node* set2, int n);
void constdeclaration();
void vardeclaration();
void factor(node*);					//����
void term(node*);					//��
void expression(node*);					//���ʽ
void condition(node* fsys);
void statement(node* fsys, int plevel);
void block(int plevel, node* fsys);