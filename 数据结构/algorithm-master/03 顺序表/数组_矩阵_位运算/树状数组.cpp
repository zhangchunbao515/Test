#include <stdio.h>
#include <string.h>

// ��״�������������ͺ���Ч, ���� O(log n) �����

// �� n ��������, ���� 2^k
inline int lowbit(int t)
{
	return t & (-t);
}

// ����a[i], ͬʱҲҪ�޸����и����� a[i] �� c[] ���
void add(int *c, int pos, int data, int n)
{
	while (pos <= n)
	{
		c[pos] += data;
		pos += lowbit(pos);		// ��˫�׽����
	}
}

// ��ǰ n ���
int sum(int *c, int n) 
{
	int sum = 0;

	while (n > 0)
	{
		sum += c[n];
		n -= lowbit(n);
	}
	return sum;
}

// ������ [a,b] �ĺ�
int sum_a_b(int *c, int a, int b)
{
	return sum(c, b) - sum(c, a-1);
}

int main(void)
{
	int c[100];		// ��״����
	int i, n;
	int data;
	int a, b;
	
	memset(c, 0, sizeof(c));
	printf("��������, ���� n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=1; i<=n; i++)
	{
		scanf("%d", &data);
		add(c, i, data, n);		// ͬʱ�޸� c ���� 
	}
	printf("������һ���������: ");
	scanf("%d %d", &a, &b);
	printf("\n��Ϊ: %d\n", sum_a_b(c, a, b));

	return 0;
}