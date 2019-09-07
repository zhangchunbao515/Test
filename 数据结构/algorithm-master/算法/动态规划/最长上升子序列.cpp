#include <stdio.h>

#define SIZE 300

// �ݹ����, ���·������, ��ǵݹ�ķ���
void show(int *num, int *pre, int pos)
{
	if (pos != -1) 
	{
		show(num, pre, pre[pos]);
		printf("%d, ", num[pos]);
	}
}

// ÿ�δ� d[] ������ѡһ����Ҳ������Լ���·��
// �ڸó����ϼ�һ��Ϊ�Լ�����󳤶�
// d[i] = max{d[k] + 1}, k < i, a[k] <= a[i]
// ������ d[] ������һ�����ĳ��ȷ���
int dp(int *num, int n)
{
	int d[SIZE];	// ��¼Ŀǰ��󳤶�
	int i, j;
	int max, len = -0xFFFFF;
	int pos;			// len ��¼��󳤶�, pos ��¼ len ��λ��
	int pre[SIZE];		// ��¼���ĸ����ֶ���, j ��ǰ���� pre[j]

	for (i=0; i<n; i++) d[i] = 1;	// ��ʼ���� 1
	for (i=0; i<n; i++) pre[i] = -1;	// ��ʼ���� -1, ��ʾ��ǰ��
	for (i=1; i<n; i++)		// �� d[i]
	{
		max = 0;
		for (j=i-1; j>=0; j--)	// ȥǰ���Ҹ���󳤶�, �Ҳ����Ļ� max = 0
		{
			if (num[j] <= num[i] && d[j] >= max)
			{
				max = d[j];
				pre[i] = j;		// ��¼�����ĸ�����
			}
		}
		d[i] = max + 1;		// �ټ�һ, ΪĿǰ�������
		if (d[i] >= len)
		{
			len = d[i];		// ������󳤶�
			pos = i;		// ��¼���λ��
		}
	}
	printf("\n����������: ");
	show(num, pre, pos);
	return len;
}

int main(void)
{
	int i, n;
	int num[SIZE];
	int len;

	printf("���� n, �� n ������: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", num + i);
	len = dp(num, n);
	printf("\n����������� %d\n", len);

	return 0;
}
