#include <stdio.h>

// max �����ۻ��Ӷκ�, �� max Ϊ���������¼���
int dp(int *num, int n, int *s, int *e)
{
	int max = 0;
	int sum = 0;
	int i;
	
	*e = *s = 0;
	for (i=0; i<n; i++)
	{
		if (max >= 0) max += num[i];
		else { max = num[i];   *s = i; }
		if (max >= sum) { sum = max;  *e = i; }
	}
	return sum;
}

int main(void)
{
	int num[200];
	int n, i;
	int start, end;
	int sum;

	printf("���� n, �� n ������: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", num + i);
	sum = dp(num, n, &start, &end);
	printf("\n����Ӷκ�Ϊ: %d\n�Ӷ�: ", sum);
	if (start >= end) printf("��");
	else 
		for (i=start; i<=end; i++)
			printf("%d, ", num[i]);	
	printf("\n");
	return 0;
}