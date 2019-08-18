
// ������״����������� 
// �㷨:
// ����һ������, �Ƚ�����ɢ��, ����С���ּ�ľ��뵽 1,
// ���� 100, 20, 2000, 10, תΪ 3, 2, 4, 1
// �� 4 ���� 2000,   3 ���� 1000,   2 ���� 100
// ֻ�跴ӳ�����ִ�С��ϵ����, �����ֶ���û��ϵ
// �ڶ���ɢ�����, 3, 2, 4, 1 �������
// ����һ������ c ��¼ÿ�����ֺ�����Լ�С�ĸ���
// �� c[1] = 2, �� 3 ������ 2, 1 ����С
// ���������� c[] = {2, 1, 1, 0}
// ��ΪҪͳ���Լ���������ĸ����Լ�С, ���Ժ������Ҫ�Ƚ�����״����

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LOWBIT(x) ((x) & (-x))

typedef struct 
{
	int data;
	int i;
}arr;

arr a[500];		// ��ɢ���õ�����
int c[500];		// ��״����
int n;			// �������, 0 �Ų���

int cmp(const void *a, const void *b)	// ��������
{
	arr _a = *((arr *)a);
	arr _b = *((arr *)b);

	return _a.data > _b.data;
}

void add(int i, int d)		// �� i ��Ԫ������ d
{
	while (i <= n)
	{
		c[i] += d;
		i += LOWBIT(i);
	}
}

int sum(int i)		// ǰ n ���
{
	int s = 0;
	
	while (i > 0)
	{
		s += c[i];
		i -= LOWBIT(i);
	}
	return s;
}

int main(void)
{
	int i;
	int ans = 0;

	printf("���� n �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=1; i<=n; i++)
	{
		scanf("%d", &a[i].data);
		a[i].i = i;
	}
	qsort(a+1, n, sizeof(arr), cmp);
	// �������ɢ����, ������ a[i].i
	// ����� for ѭ������д, ��ΪҪ�������Լ�С����,
	// ���Ժ������Ӧ���Ƚ�����״����
	// ͬ����ǰ����Լ�С����, for ��Ӧ������д
	memset(c, 0, sizeof(c));		// ��ʼ����״����
	for (i=n; i>0; i--)
	{
		ans += sum(a[i].i);		// ͳ�Ʊ��Լ�С���ܺ�
		add(a[i].i, 1);			// ���Լ�����������
	}
	printf("�����: %d\n\n", ans);

	return 0;
}