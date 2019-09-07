
// ������������
// ����ļ�������, a x b ��ʾ a, b �ųɵ�ƽ���ı��ε����
// ���� 2 ���������ε����

#include <stdio.h>

#define NUM 400

typedef struct
{
	double x, y;
}point;

// ���������, �������
// ������λ��ɶ������������
double area(point *p, int n)
{
	double sum = 0.0;
	double x1, y1, x2, y2;
	point d = p[0];
	int i;

	// n ������ n - 2 ��������, i �� 2 ��ʼѭ��
	for (i=2; i<n; i++)
	{
		x1 = p[i-1].x - d.x;
		y1 = p[i-1].y - d.y;
		x2 = p[i].x - d.x;
		y2 = p[i].y - d.y;
		sum += x1 * y2 - x2 * y1;
	}
	sum = sum > 0 ? sum : -sum;
	return sum / 2.0;
}

int main(void)
{
	int n, i;
	point p[NUM];

	while (1)
	{
		// ��˳ʱ����������, ע�ⲻҪ���� n �㹲��
		printf("���� n, �Լ�˳ʱ������ n ��������: ");
		scanf("%d", &n);
		if (n < 3) return 0;	// С�� 3 ����
		for (i=0; i<n; i++)
			scanf("%lf %lf", &(p[i].x), &(p[i].y));
		printf("���Ϊ: %g\n\n", area(p, n));
	}
	return 0;
}
