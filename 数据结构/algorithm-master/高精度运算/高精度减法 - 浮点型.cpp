
// �߾��ȸ����ͼӷ�, ֧�ָ�������������
// ���� x - y = z, Ҫ�� x, y Ϊ����, ��ȥһ����������ת��Ϊ�ӷ�

#include <stdio.h>
#include <string.h>

#define NUM 100000

// x - y = z
char x[NUM];
char y[NUM];
char z[NUM];

// �߾��ȱȽϴ�С, ���� a - b ��ֵ
int cmp(char *a, char *b, int len)
{
	int i;

	// ��ʱλ�����, ��λ�Ƚ�
	for (i=0; i<len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;		// ���
}

// ��С������� a, b ��λ��, �� 1.2, 123.456
// ǰ�� 0 ����� 001.200,  123.456
void duiqi(char *a, char *b)
{
	int lena = strlen(a);
	int lenb = strlen(b);
	int pa, pb;		// С�����λ��
	int d;
	int i, j;

	// ȷ��С����λ��
	for (pa=0; pa<lena; pa++)
		if (a[pa] == '.') break;
	if (a[pa] != '.')		// ����û��С����, ��Ϊ����
	{ a[pa] = '.';  a[pa + 1] = '0';  lena += 2; }
	for (pb=0; pb<lenb; pb++)
		if (b[pb] == '.') break;
	if (b[pb] != '.')
	{ b[pb] = '.';  b[pb + 1] = '0';  lenb += 2; }

	// С������油 0
	d = lenb - pb + pa;
	while (lena < d) a[lena++] = '0';
	d = lena - pa + pb;
	while (lenb < d) b[lenb++] = '0';

	// ����ǰ�油 0
	if (lena < lenb)
	{
		i = lena - 1;
		j = lenb - 1;
		while (i >= 0) a[j--] = a[i--];
		while (j >= 0) a[j--] = '0';
		lena = lenb;
	}
	if (lenb < lena)
	{
		i = lenb - 1;
		j = lena - 1;
		while (i >= 0) b[j--] = b[i--];
		while (j >= 0) b[j--] = '0';
		lenb = lena;
	}
	a[lena] = b[lenb] = '\0';
}

// ���� a - b ������� c ��
void sub(char *a, char *b, char *c)
{
	int flag;		// ����ķ���
	int len, i;
	char *change;
	int cf = 0;
	int tmp = 0;
	int topz = NUM;
	int end = NUM - 2;

	// ��С������� a, b ��λ��
	duiqi(a, b);
	// ȷ������ķ���, �� a > b
	len = strlen(a);
	flag = cmp(a, b, len);
	if (flag < 0) 
	{
		change = a;   a = b;   b = change;
		flag = -1;		// �����Ǹ���
	}
	else if (flag == 0)		// ���
	{
		z[0] = '0';   z[1] = '\0';
		return ;
	}
	else flag = 1;
	z[--topz] = '\0';
	// ��ʱ a �ľ���ֵ���� b, flag ��¼��������
	// ���Լ����, �����н�λ��
	for (i=len-1; i>=0; i--)
	{
		if (a[i] == '.')
		{
			z[--topz] = '.';
			continue;
		}
		tmp = a[i] - b[i] - cf;
		if (tmp < 0)
		{
			tmp += 10;
			cf = 1;
		}
		else cf = 0;
		z[--topz] = tmp + '0';
	}
	// ����ǰ�� 0, ���Ϸ���
	while (z[topz] == '0') topz++;
	if (z[topz] == '.') z[--topz] = '0';
	if (flag < 0) z[--topz] = '-';
	// ������ 0
	while (z[end] == '0') end--;
	// �Ƶ� 0 ��ַ
	for (i=0; topz<=end; i++, topz++)
		z[i] = z[topz];
	if (z[i-1] == '.') z[i-1] = '\0';
	else z[i] = '\0';
}

int main(void)
{
	while (1)
	{
		printf("���� x: ");
		scanf("%s", x);
		printf("���� y: ");
		scanf("%s", y);
		sub(x, y, z);
		printf("���: %s\n\n", z);
	}
	return 0;
}