
// ��㵽�߶ε���̾���

#include <stdio.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct
{
	double x, y;
}point;

const double EPS = 1e-7;

inline double fabs(double x)
{
	return x > 0 ? x : -x;
}

// �ж� q �ڲ��� p1, p2 ���߶���
int on_segment(point &p1, point &p2, point &q)
{
	double x1 = MIN(p1.x, p2.x);
	double x2 = MAX(p1.x, p2.x);
	double y1 = MIN(p1.y, p2.y);
	double y2 = MAX(p1.x, p2.x);

	// ���ȵ�Ҫ���߶εķ�Χ�� [x1..x2], [y1..y2]
	if (x1 <= q.x && q.x <= x2 
		&& y1 <= q.y && q.y <= y2)
	{
		// ���ж� q->p1,  p2->p1 �Ĳ���Ƿ�Ϊ 0
		// ���Ϊ x1 * y2 - x2 * y1
		x1 = p1.x - q.x;
		y1 = p1.y - q.y;
		x2 = p1.x - p2.x;
		y2 = p1.y - p2.y;
		if (fabs(x1 * y2 - x2 * y1) < EPS) return 1;
	}
	return 0;		// ����
}

// ���� a->b, a->k �ĵ��
double dianji(point &a, point &b, point &k)
{
	double x1 = b.x - a.x;
	double y1 = b.y - a.y;
	double x2 = k.x - a.x;
	double y2 = k.y - a.y;

	return x1 * x2 + y1 * y2;
}

// �ж� k ��ֱ�� a-b ��ͶӰ�ڲ��� a-b ��
int on_line(point &a, point &b, point &k)
{
	if (dianji(a, k, b) < 0) return 0;
	if (dianji(b, a, k) < 0) return 0;
	return 1;
}

// �������������
double area(point &a, point &b, point &k)
{
	double x1 = b.x - a.x;
	double y1 = b.y - a.y;
	double x2 = k.x - a.x;
	double y2 = k.y - a.y;
	double s;
	
	s = x1 * y2 - x2 * y1;
	s = fabs(s);
	return s / 2.0;
}

// ����������
double dis(point &a, point &b)
{
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

// ��� k ���߶� a-b ����̾���
double distance(point &a, point &b, point &k)
{
	double d1, d2;

	// �����߶���, �����˵�
	if (on_segment(a, b, k)) return 0;

	// �㴹ֱ���߶ε�ͶӰ���߶���
	if (on_line(a, b, k))
	{
		// ������߶ε���������һ��������
		// �����εĸ߼�����̾���, 2 * ��� / �ױ�
		return 2 * area(a, b, k) / dis(a, b);
	}
	else 
	{	// ��Ĵ�ֱ���벻���߶���, ö�ٵ������˵�ľ���
		d1 = dis(a, k);
		d2 = dis(b, k);
		return d1 > d2 ? d2 : d1;
	}
}

int main(void)
{
	point a, b;
	point k;
	double dis;

	while (1)
	{
		printf("����һ���߶κ�һ����: ");
		scanf("%lf %lf %lf %lf %lf %lf", 
			&a.x, &a.y, &b.x, &b.y, &k.x, &k.y);
		dis = distance(a, b, k);
		printf("��̾���: %g\n\n", dis);
	}
	return 0;
}