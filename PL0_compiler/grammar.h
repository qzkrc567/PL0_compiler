#pragma once
#include "base.h"
void testFollow(stringSet* set1, stringSet* set2, int n);//�ж���һ�������Ƿ�Ϸ�
void constdeclaration();						//��������
void vardeclaration();							//��������
void block(int, stringSet*);					//��
void statement(stringSet*, int);				//���
void expression(stringSet*);					//���ʽ
void term(stringSet*);							//��
void factor(stringSet*);						//����
void condition(stringSet*);						//�ж����
