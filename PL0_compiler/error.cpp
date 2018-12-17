#include "stdafx.h"
#include "base.h"
#include "error.h"
#include <iostream>
#include <string>
using namespace std;
string err_str[35] = {
	"",
	"����˵���е�=д��:=",
	"����˵���е�=��Ӧ��������",
	"����˵���еı�ʶ����Ӧ����=",
	"const,var,procedure��Ӧ���Ǳ�ʶ��",
	"©�˷ֺŻ��߾��",
	"����˵����ķ��Ų���ȷ",
	"Ӧ������俪ʼ��",
	"�������ڲ���䲿�ֵĺ��������ȷ",
	"����β���˾��",
	"���֮��©�˷ֺ�",
	"��ʶ��δ˵��",
	"��ֵ����ߵı�ʶ��Ӧ���Ǳ���",
	"Ӧ���Ǹ�ֵ��",
	"call����Ӧ���Ǳ�ʶ��",
	"call���ʶ��Ӧ���ǹ�����",
	"����������then",
	"��end��ֺ�",
	"whileѭ���������do",
	"����ķ��Ų���ȷ",
	"Ӧ���ǹ�ϵ�����",
	"���ʽ�ڱ�ʶ�����Բ����ǹ���",
	"���ʽ����������",
	"���Ӻ�ķǷ�����",
	"���ʽ�Ŀ�ʼ���Ų����Ǵ˷���",
	"",
	"",
	"",
	"",
	"",
	"",
	"��Խ��",
	"read��������еı�ʶ�����Ǳ���",
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
