
// str_to_int();		�ַ���ת����
// int_to_str();		����ת�ַ���
// str_to_double();		�ַ���ת������
// double_to_str();		������ת�ַ���

#include <stdio.h>

// �ַ���ת����, ֧��������
int str_to_int(char *str)
{
	int flag;
	char *cur = str;
	int r = 0;

	// �жϷ���
	if (*str == '-') { flag = -1;   cur = str + 1; }
	else if (*str == '+') { flag = 1;   cur = str + 1; }
	else flag = 1;

	while (*cur != '\0')
	{
		r = r * 10 + *cur - '0';
		cur++;
	}
	return r * flag;
}

// ����ת�ַ���, *str ���ؽ��, ֧�ָ���
void int_to_str(int a, char *str)
{
	char *cur = str;
	char stack[20];		// int ����� 10 λ��
	int top = 0;

	if (a < 0) { *cur++ = '-';   a *= -1; }
	do
	{
		stack[top++] = a % 10 + '0';
		a /= 10;
	}while (a != 0);
	while (top != 0)
	{
		*cur++ = stack[--top];
	}
	*cur = '\0';
}

// �ַ���ת������, ֧��������
double str_to_double(char *str)
{
	int flag = -1;
	char *cur = str;
	double r = 0.0;
	int point = 0;		// �ж�С������ǰ���Ǻ�
	double d;			// ����

	// �жϷ���
	if (*str == '-') { flag = -1;   cur = str + 1; }
	else if (*str == '+') { flag = 1;   cur = str + 1; }
	else flag = 1;

	while (*cur != '\0')
	{
		if (*cur == '.')		// ����С����
		{
			point = 1;
			d = 1;
			cur++;
		}
		if (point) 
		{
			d *= 0.1;
			r += (*cur - '0') * d;
		}
		else 
		{
			r = r * 10 + *cur - '0';
		}
		cur++;
	}
	return r * flag;
}

// ������ת�ַ���, ֧�ָ���
// �㷨: �������ʹ�С�����λ�ò������
// �� 123.456 ��� 123 �� 0.456
// 123 ���� int_to_str ����
// 0.456 �� 10 ȡ������,  num ��ʾ������С��λ��
void double_to_str(double f, char *str, int num)
{
	char *cur = str;
	int a;
	int i;

	if (f < 0) { *cur++ = '-';   f *= -1; }
	a = (int)f;
	f -= (double)a;
	int_to_str(a, cur);
	while (*cur != '\0') cur++;
	*cur++ = '.';
	for (i=0; i<num; i++)
	{
		f *= 10;
		a = (int)f;
		f -= a;
		*cur++ = a + '0';
	}
	*cur = '\0';
}

int main(void)
{
	char str[100];
	int a;
	double f;

	// ע�����ݲ�Ҫ���� int, double �ı�ʾ��Χ
	// �����ݿ��Բ��ø߾���
	while (1)		// ���� str_to_int()
	{
		printf("�ַ���ת����: ");
		scanf("%s", str);
		a = str_to_int(str);
		printf("����: %d\n", a);
	}
	while (1)		// ���� int_to_str()
	{
		printf("����ת�ַ���: ");
		scanf("%d", &a);
		int_to_str(a, str);
		printf("�ַ���: %s\n", str);
	}
	while (1)		// ���� str_to_double()
	{
		printf("�ַ���ת������: ");
		scanf("%s", str);
		f = str_to_double(str);
		printf("������: %lf\n", f);
	}
	while (1)		// ���� double_to_str()
	{
		printf("������ת�ַ���: ");
		scanf("%lf", &f);
		double_to_str(f, str, 6);
		printf("�ַ���: %s\n", str);
	}
	return 0;
}