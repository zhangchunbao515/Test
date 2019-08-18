#include <iostream>
#include <stdio.h>
#include <string.h>
#include "my_stack.h"	// �ṩջģ��
using namespace std;


// �Ƚ���������ȼ�
// true �ǳ�ջ����,  false ����ջ
inline bool cmp(char old, char n)
{
	// ()�����ȼ����
	if (n == '(') return false;
	if (n == ')' && old != '(') return true;
	if (n == ')' && old == '(') return false;

	// �˳������ȼ��ڶ�
	if (old == '*' || old == '/') return true;
	if (n == '*' || n == '/') return false;

	// �ȽϼӼ���
	if (old == '+' || old == '-') return true;
	else return false;
}

// �ж��ǲ�������
inline bool number(char ch)
{
	if (ch >= '0' && ch <= '9') return true;
	if (ch == '.') return true;
	return false;
}

double result(double a, char flag, double b)
{
	switch (flag)
	{
	case '+' : return a + b;
	case '-' : return a - b;
	case '*' : return a * b;
	case '/' : return a / b;
	}
	return 0;
}

// ���������, ���ջ,
// ������������Ƚ����ȼ�
// ֪��������ջΪ��
double calc(char *str)
{
	stack<char> OP;		// ������ջ
	stack<double> NUM;	// ����ջ
	int pos;
	double real, real2;
	char ch;

	OP.push('#');	// ���㴦�������
	pos = strlen(str);
	str[pos++] = '#';
	str[pos] = '\0';
	pos = 0;
	while (!OP.empty())
	{
		if (number(str[pos]))	// ���������
		{
			sscanf(str+pos, "%lf", &real);
			NUM.push(real);
			// ��ȥ str �е�����
			while (number(str[pos])) pos++;
		}
		else	// ������ַ�
		{
			// �Ƚ����ȼ�
			if (cmp(OP.top(), str[pos]))
			{
				// OP ������ȼ���, ��ջ����
				real2 = NUM.top();   NUM.pop();
				real = NUM.top();   NUM.pop();
				ch = OP.top();   OP.pop();
				// ������ѹ��ջ
				NUM.push(result(real, ch, real2));
			}
			else 
			{
				// ˢ��һ������, ����ջ
				if (str[pos] == ')' && OP.top() == '(') OP.pop();
				else if (str[pos] == '#' && OP.top() == '#') OP.pop();
				else if (str[pos] != '\0')  OP.push(str[pos]);
				else break;
				pos++;
			}
		}
	}
	// ������ջ����,��ʾ����ɹ�
	if (OP.empty()) return NUM.top();
	return 0;
}

int main()
{
	char str[150];
	double result = 1.154541654162;

	while (1)
	{
		system("cls");
		cout << endl;
		cout << "���ʽ��ֵ --- ��֧�ִ����ŵ���������";
		cout << endl << endl;
		cout << "��������ʽ: ";
		cin >> str;
		cout << endl << "������: ";
		cout << calc(str) << endl << endl;
		system("pause");
	}
	return 0;
}
