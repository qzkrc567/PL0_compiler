#pragma once
#include "base.h"
void testFollow(node* set1, node* set2, int n);
void constdeclaration();
void vardeclaration();
void factor(node*);					//����
void term(node*);					//��
void expression(node*);					//���ʽ
void condition(node*);
void statement(node*, int);
void block(int, node*);