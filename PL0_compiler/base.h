#pragma once

#include <fstream>
using namespace std;

#define LOIT 100		//���ű���
#define MAXLEV 3		//������
#define STACKSIZE 500	//����ջ��С
#define ERRMAX 50		//����������
//extern CFile fin;
//extern ifstream input;
//extern ofstream fa;
//extern ofstream fa1;

extern char ch;					//��ǰ��ȡ���ַ�
extern string id;				//��ǰ��ʶ�������߱����֣�
extern string sym;				//��ǰ�ĵ��ʵ�����
extern double num;				//��ǰ��ȡ��num��int����
extern string line;				//��ǰ��
extern string fname;			//�ļ���
extern char inputcode[10001];	//����Ĵ���
extern int cur;					//��������ָ��
extern DWORD codeLength;		//���볤��
extern int cc;					//��ǰ�ַ�����һ�е�λ��
extern int cx;					//Pcode������
extern int err;					//��������
extern int lev;					//�������߱������ڵĲ���
extern int dx;					//�������ڵĵ�ַ
extern int tx;					//������
extern int linecnt;				//����
extern int runtime;				//PCode���д���

extern string pCode[8];		

enum fuc { lit, opr, lod, sto, cal, ini, jmp, jpc };		//PCode����
enum object { constant, variable, procedure };				//��ʶ��������

struct errors
{
	int type;
	int lineNum;
	int charNum;
	string info;
};
extern errors err_msg[ERRMAX];	//������Ϣ
struct tableitem
{
	string name;			//����
	enum object kind;		//��������������������
	int value;				//������ֵ
	int level;				//�����͹��̵Ĳ��
	int addr;				//�����ĵ�ַ
	int size;				//��С
};
extern struct tableitem table[LOIT + 1];

struct stringSet
{
	string pa[32];
};
extern struct stringSet *declarationbeginsys, *statementbeginsys, *factorbeginsys, *blocksetsys;

struct onePCode
{
	enum fuc f;
	int l;
	int a;
};
extern onePCode code[1001];
/*
lit 0, a:������ֵȡ������ջ����a��Ϊ������ֵ
opr 0, a:��ϵ�������������ָ���ջ���ʹ�վ�������ݽ������㣬������ڴ�ջ��
lod 1, a:�������ŵ�ջ����aΪ��������˵�����е����λ�ã�lΪ���ò���˵����Ĳ��ֵ
sto 1, a:��ջ������������ĳ������Ԫ�С�a��lͬ��
cal 1, a:���ù��̵�ָ�aΪ�����ù��̵�Ŀ��������ڵ�ַ��lΪ���
ini 0, a:Ϊ�����õĹ���������ջ�п�����������aΪ���ٵĵ�Ԫ����
jmp 0, a:��������ת��a��ĵ�ַ
jpc 0, a:��ջ���Ĳ���ֵΪ��ʱ������a��ĵ�ַ
*/

bool in(string str, struct stringSet* set);				//�ж��ַ���str�Ƿ����ַ�����set��
stringSet* add(stringSet *set1, stringSet *set2);		//�������ַ������Ĳ���
void newPCode(fuc x, int y, double z);					//����һ��PCode
void enter(object k);									//����ű��������
int position(string id);								//�ڷ��ű��в���,-1��ʾû�ҵ�