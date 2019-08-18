
// ����ļ�������: a x b ��ʾ a �� b ���ųɵ�ƽ���ı��ε��������
// ��ô���� 2 ����ƽ���ı��ε�һ��, �����ε����

#include <stdio.h>

const double EPS = 1e-8;

double fabs(double x)
{
	return x > 0 ? x : -x;
}

// �ж������Ƿ���, ���߷��� 1
int oneline(double x0, double y0, 
			double x1, double y1, 
			double x2, double y2)
{
	// �� (x0, y0)->(x2, y2), (x1, y1)->(x2, y2) �����
	// ���Ϊ 0 �����㹲��
	x1 = x1 - x0;   y1 = y1 - y0;
	x2 = x2 - x0;   y2 = y2 - y0;
	if (fabs(x1 * y2 - x2 * y1) < EPS) return 1;
	else return 0;
}

// �������������������
double area(double *x, double *y)
{
	// ������������������, ���в��
	// �� (x0, y0)->(x2, y2), (x1, y1)->(x2, y2)
	double x1, x2, y1, y2;

	x1 = x[2] - x[0];   y1 = y[2] - y[0];
	x2 = x[1] - x[0];   y2 = y[1] - y[0];
	return fabs(x1 * y2 - x2 * y1) / 2.0;
}

int main(void)
{
	double x[3], y[3];	// (x[i], y[i]) ��һ������

	while (1)
	{
		printf("���������ε�������: ");
		scanf("%lf %lf %lf %lf %lf %lf", 
			x, y, x+1, y+1, x+2, y+2);
		// ���ж��ǲ������㹲����
		if (oneline(x[0], y[0], x[1], y[1], x[2], y[2]))
			printf("����, ���㹲��\n\n");
		else
			printf("���Ϊ: %g\n\n", area(x, y));
	}
	return 0;
}