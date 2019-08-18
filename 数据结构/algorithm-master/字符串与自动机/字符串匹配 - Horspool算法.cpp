
// BF �㷨������������Ƚ�, Horspool ��������Ƚ�
// ����
// ƥ�䴮��abcbcsdxzcxx
// ģʽ����cbcac
// ���ұߵ� c ��ʼ�ȶ�, ���� a �� b ��ƥ��, ������ģʽ������ b
// ģʽ��������� b, �� b ����, ����ͼ
// ƥ�䴮��abcbcsdxzcxx
// ģʽ����  cbcac
// �����ٴ����ұߵ� c ��ʼƥ��, c �� d ��ƥ��
// ��ģʽ������ d, ����ģʽ����û�� d, ��ģʽ��������ǰ����
// ƥ�䴮��abcbcsdxzcxx
// ģʽ����       cbcac

#include <stdio.h>
#include <string.h>

// �� r ���� d, ÿ�δ� d ���ұ߿�ʼƥ��
// ƥ��ʧ�����һ���һ����ƥ��ľ���
int find(char *r, char *d)
{
	int lenr = strlen(r);
	int lend = strlen(d) - 1;
	int i, j, cur;
	char c;
	
	i = j = lend;		// i, j �������ұ�
	while (1)
	{
		cur = j;		// j ��ǰ��λ��
		while (r[j] == d[i]) { i--;   j--; }
		if (i == 0) return j + 1;		// �ҵ�
		c = r[j];
		j = 0;
		// d ���һ���
		while (i > 0 && d[i] != c) { i--;  j++; }
		if (i == 0) j = cur + lend;
		else j = cur + j;
		if (j > lenr) return -1;
		i = lend;
	}
}

int main(void)
{
	char r[300];
	char d[300];
	int pos;

	r[0] = '^';   d[0] = '$';
	// 0 ��Ԫ�����ڱ�, r[0] != d[0]
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
