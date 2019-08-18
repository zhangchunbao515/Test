
// ���� x - y = z
// x �� y ��Ҫ������, ��ȥһ����������ת��Ϊ�߾��ȼӷ�

#include <stdio.h>
#include <string.h>

#define NUM 1000000

char x[NUM], y[NUM], z[NUM];
int lenx, leny, lenz;

// ���� x - y
// �Ƚ����������Ĵ�С, ȷ������
// �þ���ֵ��ļ�ȥС��, �ټ��Ϸ���
void sub(void)
{
	int flag;
	char *a, *b;		// �� a - b
	int lena, lenb;
	int tmp, i, min;
	int cf = 0;			// ��λ��־

	lenx = strlen(x);
	leny = strlen(y);
	lenz = NUM;
	z[--lenz] = '\0';
	if (lenx == leny)
	{
		flag = strcmp(x, y);		// flag �� 1, 0, -1 ����
		if (flag == 0)
		{
			z[--lenz] = '0';
			return ;
		}
	}
	else flag = (lenx > leny);		// flag == 1 ������, �����Ǹ���
	if (flag == 1) { a = x;  lena = lenx;  b = y;  lenb = leny; }
	else { a = y;  lena = leny;  b = x;  lenb = lenx; }

	// a �Ǵ��� b ��, ����ѭ���� lenb
	for (i=0, min=lenb; i<min; i++)
	{
		tmp = a[--lena] - b[--lenb] - cf;
		if (tmp < 0)
		{
			tmp += 10;
			cf = 1;
		}
		else cf = 0;
		z[--lenz] = tmp + '0';
	}
	if (lena)
	{
		// 10000 - 9 ��Ҫһֱ��ǰ��λ
		while (lena && cf)
		{
			tmp = a[--lena] - '0' - cf;
			if (tmp < 0)
			{
				tmp += 10;
				cf = 1;
			}
			else cf = 0;
			z[--lenz] = tmp + '0';
		}
		while (lena) z[--lenz] = a[--lena];
	}
	// ��Ϊǰ�汣֤�˴�����С��, ������� cf �����н�λ
	while (z[lenz] == '0') lenz++;			// ����ǰ�� 0
	if (flag != 1) z[--lenz] = '-';
}

int main(void)
{
	while (1)
	{
		printf("\n���� x: ");
		scanf("%s", x);
		printf("���� y: ");
		scanf("%s", y);
		sub();		// ���� x - y
		printf("���  : %s\n", z + lenz);
	}
	return 0;
}