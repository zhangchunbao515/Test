
// ���η���һά����������
// �� x ������ n ����, ��������������
// �ֳ������Կ�����������, ������, �������ҽ��紦

#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a.dis) > (b.dis) ? (b) : (a))
#define fabs(a)   ((a) > (0) ? (a) : (-(a)))

// ��¼���� (a, b) ������, ����Ϊ dis
typedef struct
{
	double a, b;
	double dis;
}recond;

// �� num �������������
recond min_close(double *num, int n)
{
	recond re;
	recond left, right;
	int mid;

	if (n == 1)		// ֻ��һ������������
	{
		re.a = re.b = num[0];
		re.dis = 0xFFFFFF;
		return re;
	}
	else if (n == 2)
	{
		re.a = num[0];
		re.b = num[1];
		re.dis = num[0] - num[1];
		re.dis = fabs(re.dis);
		return re;
	}
	else	// �������ϵĵ�
	{
		mid = n / 2;		// ����һ��
		left = min_close(num, mid);
		right = min_close(num + mid, n - mid);

		// �ҳ�������, ������, ���������Сֵ
		re.a = num[mid];
		re.b = num[mid + 1];
		re.dis = num[mid] - num[mid + 1];
		re.dis = fabs(re.dis);
		re = MIN(re, left);
		re = MIN(re, right);
		return re;
	}
}

// ����ȽϺ���
int cmp(const void *x, const void *y)
{
	double a, b;

	a = *((double *)x);
	b = *((double *)y);

	return a > b;
}

int main(void)
{
	int n, i;
	double num[300];
	recond d;

	while (1)
	{
		printf("���� n, �Լ� n ����: ");
		scanf("%d", &n);
		for (i=0; i<n; i++)
			scanf("%lf", num + i);
		qsort(num, n, sizeof(num[0]), cmp);		// ��С��������
		d = min_close(num, n);
		printf("\n������: %g, %g\n�������: %g\n\n", 
			d.a, d.b, d.dis);
	}
	return 0;
}