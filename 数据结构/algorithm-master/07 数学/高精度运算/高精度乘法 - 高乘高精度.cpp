
// �߾��ȳ˷�, ���������Դ�����, ��֧�ָ���С��
// �㷨: ģ���˹�����Ĺ���
// ���� 123456 * 789  ������ 9, 8, 7 ���� 123456
// ���м�����Ӽ���, ������Ҫ�߾��ȼӷ�ģ��

// ��������:
// ��Ϊ 123456 * 789 = 123456 * 780 + 123456 * 9
// �˹�������һλһλ���, һ�������� n λ, ��ôҪ�� n ��
// �� int �ܱ�ʾ�ķ�Χ��, һ�ο��Բ� 4 λ, ��ôҪ�� n/4 ��
// ��Ϊ���Լ��������������ַ�, ���Ի���ÿ 4 λת��������
// һ�� int ���� 4 λ����

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>

#define NUM 1000000		// ���� 10^5000000

// x + y = z �� int �������򱣴�, �� len ָʾ����
int x[NUM], lenx;
int y[NUM], leny;
int z[2 * NUM], lenz;
// Ϊ�˽�Լ�ڴ�, x, y, z ���Ը�Ϊ��̬����
// ����˳�����������ʵ��ʹ�ö�̬����, ����Ҫ�������Ӵ���

// ����ģ��, ÿ 4 λת��������
void input(int *base, int *len)
{
	char *buf;
	int lenb, i, cur;
	int tmp;
	int flag = 1;

	*len = 0;
	buf = (char *)malloc(4 * NUM * sizeof(char));
	if (buf == NULL) return ;
	scanf("%s", buf);
	lenb = strlen(buf);
	while (lenb >= 4)
	{
		cur = lenb - 4;
		for (tmp=i=0; i<4; i++)
			tmp = tmp * 10 + buf[cur++] - '0';
		base[(*len)++] = tmp;
		lenb -= 4;
	}
	if (lenb)
	{
		for (tmp=i=0; i<lenb; i++)
			tmp = tmp * 10 + buf[i] - '0';
		base[(*len)++] = tmp;
	}
	free(buf);
}

void show(int *base, int len)		// ���ģ��
{
	int i;;

	printf("%d", base[len - 1]);
	for (i=len-2; i>=0; i--)
		printf("%04d", base[i]);
	putchar('\n');
}

// ���߾��� a ��;��� b ���, ������� c ��
void _mul(int *a, int lena, int b, int *c, int *top)
{
	int tmp, i;
	int cf = 0;

	for (i=0; i<lena; i++)
	{
		tmp = b * a[i] + cf;
		c[(*top)++] = tmp % 10000;
		cf = tmp / 10000;
	}
	if (cf) c[(*top)++] = cf;
}

// ���߾��� a, b ���, ������� b ��
void _add(int *a, int lena, int *b, int *lenb)
{
	int i;
	int tmp, cf;

	// ͨ����λ�� 0 �� a, b ��λ������
	while (lena < *lenb) a[lena++] = 0;
	while (*lenb < lena) b[(*lenb)++] = 0;
	for (cf=i=0; i<lena; i++)
	{
		tmp = a[i] + b[i] + cf;
		b[i] = tmp % 10000;
		cf = tmp / 10000;
	}
	if (cf) b[(*lenb)++] = cf;
}

// ���� a * b ��������� c ��
void mul(int *a, int lena, int *b, int lenb, int *c, int *lenc)
{
	int i, j;
	int t, *tmp;
	int top;		// tmp �� top ��¼�м���

	if (lena < lenb)	// ��֤ a ��λ����
	{
		t = lena;   lena = lenb;   lenb = t;
		tmp = a;   a = b;   b = tmp;
	}
	*lenc = 0;
	tmp = (int *)malloc(2 * NUM * sizeof(int));
	if (tmp == NULL) return ;
	for (i=0; i<lenb; i++)		// �� b ���� a
	{
		for (top=j=0; j<i; j++) tmp[top++] = 0;
		_mul(a, lena, b[i], tmp, &top);
		_add(tmp, top, c, lenc);
		// _mul �߾��ȳ˵;���ģ��, ���� tmp �м���
		// _add �м��� tmp �ۼӵ� c ��
	}
	free(tmp);
}

int main(void)
{
	while (1)
	{
		printf("\n��������� x: ");
		input(x, &lenx);
		printf("��������� y: ");
		input(y, &leny);
		mul(x, lenx, y, leny, z, &lenz);	// ���� x * y = z
		printf("���: ");
		show(z, lenz);
	}
	return 0;
}
