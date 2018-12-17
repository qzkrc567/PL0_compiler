#include "stdafx.h"
#include "base.h"
#include "error.h"
#include <iostream>
#include <string>
using namespace std;
string err_str[35] = {
	"",
	"常数说明中的=写成:=",
	"常数说明中的=后应该是数字",
	"常数说明中的标识符后应该是=",
	"const,var,procedure后应该是标识符",
	"漏了分号或者句号",
	"过程说明后的符号不正确",
	"应该是语句开始符",
	"程序体内部语句部分的后跟符不正确",
	"程序尾丢了句号",
	"语句之间漏了分号",
	"标识符未说明",
	"赋值号左边的标识符应该是变量",
	"应该是赋值号",
	"call后面应该是标识符",
	"call后标识符应该是过程名",
	"条件语句后少then",
	"少end或分号",
	"while循环语句中少do",
	"语句后的符号不正确",
	"应该是关系运算符",
	"表达式内标识符属性不能是过程",
	"表达式中少右括号",
	"因子后的非法符号",
	"表达式的开始符号不能是此符号",
	"",
	"",
	"",
	"",
	"",
	"",
	"数越界",
	"read语句括号中的标识符不是变量",
	"",
	""
};
void error(int n)
{
	if (err < ERRMAX)
	{
		err_msg[err].type = n;
		err_msg[err].info = err_str[n];
		err_msg[err].lineNum = linecnt;
		err_msg[err++].charNum = cc - 1;
	}
	if (fa1.is_open())
	{
		int i;
		cout << "***";
		fa1 << "***";
		for (i = 0; i < cc - 3; i++)
		{
			cout << " ";
			fa1 << " ";
		}
		cout << "error" << n << endl;
		fa1 << "error" << n << endl;
	}
}

void display()
{
	for (int i = 0; i < err; i++)
		printf("%3d\n%30s\n%5d\n%5d\n", i, err_msg[i].info, err_msg[i].lineNum, err_msg[i].charNum);
}
