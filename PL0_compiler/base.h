#pragma once

#include <fstream>
using namespace std;

#define LOIT 100		//符号表长度
#define MAXLEV 3		//最大层数
#define STACKSIZE 500	//运行栈大小
#define ERRMAX 50		//最大错误数量
//extern CFile fin;
//extern ifstream input;
//extern ofstream fa;
//extern ofstream fa1;

extern char ch;					//当前读取的字符
extern string id;				//当前标识符（或者保留字）
extern string sym;				//当前的单词的类型
extern double num;				//当前读取的num，int类型
extern string line;				//当前行
extern string fname;			//文件名
extern char inputcode[10001];	//输入的代码
extern int cur;					//输入代码的指针
extern DWORD codeLength;		//代码长度
extern int cc;					//当前字符在这一行的位置
extern int cx;					//Pcode的数量
extern int err;					//错误数量
extern int lev;					//函数或者变量所在的层数
extern int dx;					//变量所在的地址
extern int tx;					//表索引
extern int linecnt;				//行数
extern int runtime;				//PCode运行次数

extern string pCode[8];		

enum fuc { lit, opr, lod, sto, cal, ini, jmp, jpc };		//PCode种类
enum object { constant, variable, procedure };				//标识符的类型

struct errors
{
	int type;
	int lineNum;
	int charNum;
	string info;
};
extern errors err_msg[ERRMAX];	//错误信息
struct tableitem
{
	string name;			//名字
	enum object kind;		//变量？常量？过程名？
	int value;				//常量的值
	int level;				//变量和过程的层次
	int addr;				//变量的地址
	int size;				//大小
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
lit 0, a:将常量值取到运行栈顶，a域为常数的值
opr 0, a:关系运算和算术运算指令。将栈顶和次站定的内容进行运算，结果放在次栈顶
lod 1, a:将变量放到栈顶。a为变量所在说明层中的相对位置，l为调用层与说明层的层差值
sto 1, a:将栈顶的内容送入某变量单元中。a，l同上
cal 1, a:调用过程的指令。a为被调用过程的目标程序的入口地址，l为层差
ini 0, a:为被调用的过程在运行栈中开辟数据区。a为开辟的单元个数
jmp 0, a:无条件跳转到a域的地址
jpc 0, a:在栈顶的布尔值为假时，跳到a域的地址
*/

bool in(string str, struct stringSet* set);				//判断字符串str是否在字符串集set中
stringSet* add(stringSet *set1, stringSet *set2);		//求两个字符串集的并集
void newPCode(fuc x, int y, double z);					//新增一行PCode
void enter(object k);									//向符号表中添加项
int position(string id);								//在符号表中查找,-1表示没找到