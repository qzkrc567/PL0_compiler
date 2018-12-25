#include "stdafx.h"
#include "afxdialogex.h"
#include "base.h"
#include "interpret.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int find(int l, int b, int s[500])
{
	int b1;
	b1 = b;
	while (l)
	{
		b1 = s[b1];
		l--;
	}
	return b1;
}


string interpret(int inputValue[], int len)
{
	runtime = 0;
	string res = "";
	int p = 0;						//���мĴ���
	int b = 1;						//��ַ�Ĵ���
	int t = 0;						//ջ���Ĵ���
	int curInput = 0;				//��ǰ��������
	onePCode i;						//��ǰִ�е�PCode
	int s[STACKSIZE];				//ģ��������ջʽ�洢�ռ�
	cout << "start pl0" << endl;
	s[0] = s[1] = s[2] = s[3] = 0;
	do
	{
		i = code[p++];
		runtime++;
		if (runtime > 10000)
			return res;
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
			case 1:										//����
				s[t] = -s[t];
				break;
			case 2:										//�ӷ�
				t--;
				s[t] = s[t] + s[t + 1];
				break;
			case 3:										//����
				t--;
				s[t] = s[t] - s[t + 1];
				break;
			case 4:										//�˷�
				t--;
				s[t] = s[t] * s[t + 1];
				break;
			case 5:										//����
				t--;
				s[t] = s[t] / s[t + 1];
				break;
			case 6:										//ģ��2������odd�ж�
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
				res += to_string(s[t]) + " ";
				t--;
				break;
			case 15:
				res += "\r\n";
				break;
			case 16:
				if (curInput >= len)
					return "too little input";
				t++;
				s[t] = inputValue[curInput++];	
				break;
			default:
				break;
			}
			break;
		case lod:
			t++;
			s[t] = s[find(i.l, b, s) + i.a];
			break;
		case sto:
			s[find(i.l, b, s) + i.a] = s[t];
			t--;
			break;
		case cal:
			s[t + 1] = find(i.l, b, s);
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
	cout << "finish!\n";
	return res;
}