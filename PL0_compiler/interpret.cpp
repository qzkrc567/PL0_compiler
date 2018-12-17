#include "stdafx.h"
#include "base.h"
#include "interpret.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int base(int l, int *b, int s[STACKSIZE])
{
	int b1;
	b1 = *b;
	while (l)
	{
		b1 = s[b1];
		l--;
	}
	return b1;
}


void interpret()
{
	for (int i = 0; i < cx; i++)
		cout << setw(3) << i << setw(5) << pCode[code[i].f] << setw(3) << code[i].l << setw(5) << code[i].a << endl;
	int p = 0;						//运行寄存器
	int b = 1;						//基址寄存器
	int t = 0;						//栈顶寄存器
	int curInput = 0;				//当前的输入数
	instruction i;
	int s[STACKSIZE];
	cout << "start pl0" << endl;
	s[0] = s[1] = s[2] = s[3] = 0;
	do
	{
		i = code[p++];
		//cout << setw(5) << pCode[i.f] << setw(3) << i.l << setw(5) << i.a << endl;
		switch (i.f)
		{
		case lit:
			t++;
			s[t] = i.a;
			break;
		case opr:
			switch (i.a)
			{
			case 0:
				t = b - 1;
				p = s[t + 3];
				b = s[t + 2];
				break;
			case 1:										//负号
				s[t] = -s[t];
				break;
			case 2:										//加法
				t--;
				s[t] = s[t] + s[t + 1];
				break;
			case 3:										//减法
				t--;
				s[t] = s[t] - s[t + 1];
				break;
			case 4:										//乘法
				t--;
				s[t] = s[t] * s[t + 1];
				break;
			case 5:										//除法
				t--;
				s[t] = s[t] / s[t + 1];
				break;
			case 6:
				s[t] %= 2;
				break;
			case 8:
				t--;
				s[t] == s[t + 1] ? s[t] = 1 : s[t] = 0;
				break;
			case 9:
				t--;
				s[t] == s[t + 1] ? s[t] = 0 : s[t] = 1;
				break;
			case 10:
				t--;
				s[t] < s[t + 1] ? s[t] = 1 : s[t] = 0;
				break;
			case 11:
				t--;
				s[t] >= s[t + 1] ? s[t] = 1 : s[t] = 0;
				break;
			case 12:
				t--;
				s[t] > s[t + 1] ? s[t] = 1 : s[t] = 0;
				break;
			case 13:
				t--;
				s[t] <= s[t + 1] ? s[t] = 1 : s[t] = 0;
				break;
			case 14:
				cout << s[t];
				fa2 << s[t];
				t--;
				break;
			case 15:
				cout << endl;
				fa2 << endl;
				break;
			case 16:
				t++;
				cout << "? ";
				fa2 << "? ";
				string::size_type sz;
				s[t] = stoi(inputValue[curInput++], &sz);
				cout << s[t] << endl;
				fa2 << s[t] << endl;
				break;
			default:
				break;
			}
			break;
		case lod:
			t++;
			s[t] = s[base(i.l, &b, s) + i.a];
			break;
		case sto:
			s[base(i.l, &b, s) + i.a] = s[t];
			t--;
			break;
		case cal:
			s[t + 1] = base(i.l, &b, s);
			s[t + 2] = b;
			s[t + 3] = p;
			b = t + 1;
			p = i.a;
			break;
		case ini:
			t += i.a;
			break;
		case jmp:
			p = i.a;
			break;
		case jpc:
			if (s[t] == 0)
				p = i.a;
			t--;
			break;
		}
	} while (p);
	fa2.close();
	cout << "finish!\n";
}