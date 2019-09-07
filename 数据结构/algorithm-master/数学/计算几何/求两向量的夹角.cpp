
// ������������ a, b, ���� cos<a, b>

#include <stdio.h>
#include <math.h>

typedef struct
{
	double x, y;
}point;

// ���� a1->a2 �� b1->b2 �ļнǵ� cos ֵ
// ���ù�ʽ a . b = |a| * |b| * cos<a, b>
double cos_p(point &a1, point &a2, point &b1, point &b2)
{
	double x1 = a2.x - a1.x;
	double y1 = a2.y - a1.y;
	double x2 = b2.x - b1.x;
	double y2 = b2.y - b1.y;
	double y = x1 * x2 + y1 * y2;
	double da = sqrt((x1 * x1) + (y1 * y1));
	double db = sqrt((x2 * x2) + (y2 * y2));

	return y / (da * db);
}

int main(void)
{
	point a1, a2, b1, b2;
	double k;

	while (1)
	{
		// a1 Ϊ�������, a2 Ϊ�յ�
		printf("���� a, b ��������: ");
		scanf("%lf %lf %lf %lf", &a1.x, &a1.y, &a2.x, &a2.y);
		scanf("%lf %lf %lf %lf", &b1.x, &b1.y, &b2.x, &b2.y);
		k = cos_p(a1, a2, b1, b2);
		printf("cos<a, b> = %g\n\n", k);
	}
	return 0;
}