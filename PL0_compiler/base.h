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
extern string line;				//��ǰ��
extern string fname;			//�ļ���
extern char inputcode[10001];
extern double num;				//��ǰ��ȡ��num��int����
extern int cur;
extern int cc;					//��ǰ�ַ�����һ�е�λ��
extern int cx;					//Pcode������
extern int err;					//��������
extern int lev;					//�������߱������ڵĲ���
extern int dx;					//�������ڵĵ�ַ
extern int tx;					//������
extern int linecnt;				//����
extern DWORD codeLength;
extern string pCode[8];

enum fuc { lit, opr, lod, sto, cal, ini, jmp, jpc };
enum object { constant, variable, procedure };

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
	int level;				//�����ͺ����Ĳ��
	int addr;				//�����ĵ�ַ
	int size;				//��С
};
extern struct tableitem table[LOIT + 1];

struct node
{
	string pa[32];
};
extern struct node *declbegsys, *statbegsys, *facbegsys, *tempsetsys;

struct instruction
{
	enum fuc f;		//function code
	int l;				//level
	int a;				//displacement address
};
extern instruction code[1001];
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

bool in(string str, struct node* set);
node* add(node *set1, node *set2);

void newPCode(fuc x, int y, double z);				//����һ��PCode
void enter(object k);			//����ű��������

int position(string id);				//�ڷ��ű��в���,-1��ʾû�ҵ�