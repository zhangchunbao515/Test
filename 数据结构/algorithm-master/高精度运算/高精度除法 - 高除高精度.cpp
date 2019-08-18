
// �߾��ȳ���, �߾��ȳ��Ը߾���
// �����̵�ʱ��, ���ϵ��ü���ȷ����
// ���Ի���Ҫ�߾��ȼ���ģ��

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define NUM 1000000

// ���� a / b
char a[NUM];		// ����
char b[NUM];		// ������
char c[NUM];		// ��
char r[NUM];		// ����

// �߾��ȱȽϴ�С, ���� a - b ��ֵ
// �ȽϷ�Χ�� [sa..ea] �� [sb..eb]
int cmp(char *a, int sa, int ea, char *b, int sb, int eb)
{
	int i, j;
	int lena = ea - sa;
	int lenb = eb - sb;

	if (lena < lenb) return -1;
	else if (lenb < lena) return 1;
	// ��ʱλ�����, ��λ�Ƚ�
	for (i=sa, j=sb; i<ea; i++, j++)
	{
		if (a[i] != b[j])
			return a[i] - b[j];
	}
	return 0;		// ���
}

// ���ǰ�� 0
void clear_zero(char *a)
{
	int i, j;
	int len = strlen(a);

	for (i=0; i<len; i++)
	{
		if (a[i] != '0') break;
	}
	if (i != 0)
	{
		for (j=0; i<len; i++, j++)
			a[j] = a[i];
		if (j == 0) {a[j] = '0';  a[j + 1] = '\0';}
		else a[j] = '\0';
	}
}

// �߾��ȼ��� a = a - b,  a >= b ������ָ���
void sub(char *a, int left, int right, char *b)
{
	int lenb = strlen(b);
	int i;
	int tmp;
	int topa = right;
	int cf = 0;

	for (i=lenb-1; i>=0; i--)
	{
		tmp = a[--topa] - b[i] - cf;
		if (tmp < 0)
		{
			tmp += 10; 
			cf = 1;
		}
		else cf = 0;
		a[topa] = tmp + '0';
	}
	if (cf) a[--topa]--;
}

// ���� a / b, ���ڲ��� c, r, ���سɹ���־
int div(char *a, char *b, char *c, char *r)
{
	int f, s, i;
	int lena, lenb;
	char *tmp;
	int left, right;	// tmp �Ĺ�������
	int topa, topc;

	clear_zero(a);		// ���ǰ�� 0
	clear_zero(b);
	lena = strlen(a);	// �Ƚ� a, b ��С
	lenb = strlen(b);
	f = cmp(a, 0, lena, b, 0, lenb);	// ���� a - b
	if (f < 0)			// a < b
	{
		c[0] = '0';   c[1] = '\0';
		strcpy(r, a);
		return 1;
	}
	else if (f == 0)	// a == b
	{
		c[0] = '1';   c[1] = '\0';
		r[0] = '0';   r[1] = '\0';
		return 1;
	}
	// ��ʱ a > b �� lena >= lenb
	tmp = (char *)malloc(lena * sizeof(char) + 10);
	if (tmp == NULL) return 0;		// �ڴ治��

	// ׼�����̵Ĳ��ָ��Ƶ� tmp
	for (i=0; i<lenb; i++) tmp[i] = a[i];
	topc = left = 0;
	topa = right = lenb;
	while (1)
	{
		s = 0;
		// ��� tmp >= b �����߾��ȼ���, ȷ���� s
		while (cmp(tmp, left, right, b, 0, lenb) >= 0)
		{
			// tmp ��ȥ b, ������� tmp ��
			sub(tmp, left, right, b);
			while (left < right && tmp[left] == '0') 
				left++;		// �������� 0
			s++;
		}
		c[topc++] = s + '0';
		if (a[topa] == '\0') break;
		tmp[right++] = a[topa++];
	}
	tmp[right] = '\0';
	strcpy(r, tmp + left);		// ��������
	if (r[0] == '\0') {r[0] = '0';  r[1] = '\0'; }
	c[topc] = '\0';
	clear_zero(c);			// ���ǰ�� 0
	free(tmp);

	return 1;
}

int main(void)
{
	int i;

	while (1)
	{
		printf("�������: ");
		scanf("%s", a);
		printf("���뱻����: ");
		scanf("%s", b);

		// ��ⱻ�����ǲ��� 0
		for (i=0; b[i]!='\0'; i++)
			if (b[i] != '0') break;
		if (b[i] == '\0') return 0;

		if (div(a, b, c, r))		// ���� a / b
			printf("��: %s\n����: %s\n\n", c, r);
		else printf("�ڴ治��\n\n");
	}
	return 0;
}
