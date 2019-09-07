
// ����ͼ�����ƥ���� - �������㷨
// ���ϵĲ��ҽ�������·����ƥ����

#include <stdio.h>

#define NUM 70
#define NO -1

int used[NUM];
int link[NUM];
// link[b] = a;		��ʾ b �Ѿ�ƥ�䵽 a ��
// a, b �ֱ�����������ͬ�ļ���, ֻ���¼����һ�����ϵ�ƥ���������
// ��Ϊ��� b ƥ���� a ��, b �Ͳ�������ƥ�� c ��
// ���� b һ����, ƥ���˵� a, c ��������, �Ͳ��Ƕ���ƥ����
// ���� link[] ֻ��¼ b ���ϵ�ƥ�����


// ����һ����������·, ����β��δƥ��ĵ�, ����ƥ��δƥ�佻��
// ��: [δƥ��, ƥ��, δƥ��, ƥ��, ,,, δƥ��]
int findpath(int (*m)[NUM], int cur)
{
	int i;

	// ���� cur �ܵ��ı�, ����ƥ��
	for (i=0; i<NUM; i++)
	{
		if (!used[i] && m[cur][i])		// ��������
		{
			used[i] = 1;
			// ��� i ��û��ƥ���, �� cur->i ��ûƥ�����, ��ֱ��ƥ��
			// ��� i ���Ѿ�ƥ�����, ���Դ� linkk[i] ��ƥ��
			if (link[i] == -1 || findpath(m, link[i]))
			{
				link[i] = cur;		// ����ʱ����ƥ��
				return 1;
			}
		}
	}
	return 0;
}

// ����ƥ��
int pipei(int (*m)[NUM], int n)
{
	int count = 0;		// �ҵ�������·����
	int i, j;

	for (i=0; i<NUM; i++) link[i] = NO;
	for (i=0; i<n; i++)		// �������е�
	{
		for (j=0; j<NUM; j++) used[j] = 0;
		if (findpath(m, i)) count++;
	}
		// һ������·�ķ�ת, ����һ��ƥ��
	return count;
}

int main(void)
{
	int i, j;
	int n;
	int m[NUM][NUM];	// m ���ɾ�̬�ڽӱ���
	int k;
	int a, b;

	printf("���� A ���ϵ�ĸ���:");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<NUM; j++) m[i][j] = 0;
	while (1)
	{
		// ����ʱ, Լ�� a ���� a ��, b ���� b ��
		scanf("%d %d", &a, &b);
		if (a == 0 && b == 0) break;
		m[a][b] = 1;
	}
	k = pipei(m, n);		// ���ƥ��
	printf("\n���ƥ����: %d\nƥ��ı�: ", k);
	for (i=0; i<NUM; i++)
	{
		if (link[i] != NO)
			printf("(%d, %d), ", link[i], i);
	}
	putchar('\n');
	return 0;
}
