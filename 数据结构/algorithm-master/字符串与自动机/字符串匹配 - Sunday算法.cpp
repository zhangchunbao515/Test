
// Sunday ���㷨�� Horspool ����
// ���磺
// ƥ�䴮��abcbczdxzc
// ģʽ����zbcac
// ��������Ƚ�, c �� c ƥ��, a �� b �Ͳ�ƥ����
// �����ҵ�ƥ�䴮�� c ����һ���ַ� z
// ����ģʽ������û�� z, �����, ���� z ����
// ƥ�䴮��abcbczdxzc
// ģʽ����     zbcac
// ���ģʽ���е�û�� z, ����
// ƥ�䴮��abcbcedxzcs
// ģʽ����zbcac
// e ����ģʽ����, ��ô������ e
// ƥ�䴮��abcbcedxzcs
// ģʽ����      zbcac

#include <stdio.h>
#include <string.h>

// �� r ���� d, ����ƥ��λ��
int find(char *r, char *d)
{
	int lenr = strlen(r);
	int lend = strlen(d) - 1;
	int i, j, cur;
	char c;

	i = j = lend;
	while (1)
	{
		cur = j;
		while (r[j] == d[i]) { i--;  j--; }
		if (i == 0) return j + 1;
		i = lend;				// i �ص����ұ�
		c = r[cur + 1];			// Ѱ�� cur + 1 ���ַ�
		while (i > 0 && d[i] != c) i--;
		if (i == 0) j = cur + lend + 1;
		else j = cur + lend - i + 1;
		if (j > lenr) return -1;
		i = lend;
	}
}

int main(void)
{
	char r[300];
	char d[300];
	int pos;

	r[0] = '#';   d[0] = '^';
	// 0 �ŵ�Ԫ���ڱ�, r[0] != d[0]
	while (1)
	{
		printf("����ԭ��: ");
		scanf("%s", r + 1);
		printf("����ģʽ��: ");
		scanf("%s", d + 1);
		pos = find(r, d);
		if (pos != -1)
			printf("�ҵ�, ��ʼλ��: %d\n\n", pos);
		else 
			printf("δ�ҵ�!\n\n");
	}
	return 0;
}
