
// ����Բ�ĵ����������ߵĴ�ֱ����, �ҳ���С�ľ��� m
// �жϰ뾶�Ƿ�С�� m

#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define fabs(a) ((a) > 0 ? (a) : (-a))
#define EPS (1e-8)

typedef struct
{
	double x, y;
}point;

// �ж�Բ�ڲ��ھ�����
int in(point &k, double &r, point &a1, point &a2)
{
	double x1 = MIN(a1.x, a2.x);
	double x2 = MAX(a1.x, a2.x);
	double y1 = MIN(a1.y, a2.y);
	double y2 = MAX(a1.y, a2.y);

	// ����Բ�ĵ������ߵľ���
	x1 = k.x - x1;
	x2 = x2 - k.x;
	y1 = k.y - y1;
	y2 = y2 - k.y;
	// �ҳ���̵ľ�����뾶�Ƚ�
	x1 = MIN(x1, x2);
	y1 = MIN(y1, y2);
	x1 = MIN(x1, y1);
	// r == x1 �����Ҫ�� EPS �ж�
	if (r < x1) return 1;
	else if (fabs(r - x1) < EPS) return 1;
	else return 0;
}

int main(void)
{
	point a1, a2, k;
	double r;

	while (1)
	{
		printf("������ε������ԽǶ���: ");
		scanf("%lf %lf %lf %lf", &a1.x, &a1.y, &a2.x, &a2.y);
		printf("����Բ�ĺͰ뾶: ");
		scanf("%lf %lf %lf", &k.x, &k.y, &r);
		if (in(k, r, a1, a2)) printf("����\n\n");
		else printf("������\n\n");
	}
	return 0;
}
