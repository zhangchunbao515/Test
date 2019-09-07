#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int number(char c)
{
	if ((c >= '0' && c <= '9') 
		|| (c == '.')) return 1;
	else return 0;
}

int cmp(char op, char b)
{
	// �������ȼ�
	// ����� (
	// ������ * / 
	// ������ + -
	// ������ )
	// ����� #
	// 1 ��ִ�����㣬0 �ǽ�ջ
	if (b == '(') return 0;
	else 
	{
		if (op == '*' || op == '/') return 1;
		else if ((op == '+' || op == '-') 
			&& (b != '*' && b != '/')) return 1;
		else return 0;
	}
}

float cal(float a, char c, float b)
{
	switch (c)
	{
	case '+' : return a + b; break;
	case '-' : return a - b; break;
	case '*' : return a * b; break;
	case '/' : return a / b; break;
	default : return 0;
	}
}

int error(char c)
{
	if (c == '+' 
		||c == '-' 
		||c == '*' 
		||c == '/') return 0;
	else return 1;
}

// 0. �Ȱ� # ѹ��ջ������Ϊ���ڱ��ʽ�������#
// 1. ����ǰ�����־ͽ�����ջ
// 2. ���������֣��ͱȽ����ȼ�
// 3. ���ȼ��߾ͳ�ջ���㣬���ˣ��������ջ
// 4. ���ȼ��;Ͳ������������ջ
// 5. ֱ��������ջΪ�գ�����ѭ��
// 6. ������ջ����, ���ʽ����
// 7. ȥ����ջ����ȡ���ս��
status calc(char *s, float *back)
{
	opstack op;		// ������ջ
	numstack num;	// ����ջ
	int pos = 0;
	float f;
	float a, b;
	char flag;

	opcreate(&op);
	numcreate(&num);
	oppush(&op, '#');	// ��# ���㴦��
	while (s[pos] != '\0') pos++;	// �ں���Ҳ�� #
	s[pos] = '#';
	s[pos + 1] = '\0';
	pos = 0;
	while (op.base != op.top)
	{
		// ���������ֻ����ַ�
		if (number(s[pos]))
		{
			sscanf(s+pos, "%f", &f);
			while (number(s[pos])) pos++;
			numpush(&num, f);
		}
		else 
		{
			// �Ƚ����ȼ�
			if (cmp(opgettop(&op), s[pos]))
			{
				// ��������
				if (!numpop(&num, &a)) break;
				if (!numpop(&num, &b)) break;
				if (!oppop(&op, &flag)) break;
				f = cal(b, flag, a);
				numpush(&num, f);
			}
			else 
			{
				// s[pos] ��ջ, pos++
				if (s[pos] != '\0')
				{
					oppush(&op, s[pos++]);
				}
				// ˢ��һ������ƥ��
				flag = opgettop(&op);
				if (flag == ')' || flag == '#')
				{
					// ɾ��һ������
					oppop(&op, &flag);
					oppop(&op, &flag);
				}
			}
		}
	}
	if (op.top == op.base)
	{
		numpop(&num, back);
		opdestory(&op);
		numdestory(&num);
		return OK;
	}
	else 
	{
		opdestory(&op);
		numdestory(&num);
		return ERROR;
	}
}

int main(void)
{
	char buf[200] = {0};
	int flag;
	float back;

	while (1)
	{
		printf("\n--- ���ʽ��ֵ, ��֧����������\n");
		printf("\n--- ������һ�����ʽ: ");
		gets(buf);
		flag = 0;
		if (buf[0] != '\0')
		{
			flag = calc(buf, &back);
			if (flag)
			{
				printf("\n--- ������:  %g\n", back);
			}
			else printf("\n--- ���ʽ����!\n");
		}
		else printf("\n--- û������!\n");
		printf("\n--- ���س�����������...");
		fflush(stdin);
		getchar();
		system("cls");
	}
	return 0;
}