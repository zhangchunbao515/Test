
// �ж��߶��ڲ��ڶ������

#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct
{
	double x, y;
}point;

const double EPS = 1e-7;

// �ж��߶� a-b �ڲ��ڶ���� v ��
// �����߶ε������˵�Ҫ�ڶ������, ���Ǳ�Ҫ����
// ��Ϊ����ο����ǰ���, �߶�ĳһ�ο����ڶ��������
int in(point *v, int n, point &a, point &b)
{
	// �ж� a �Ƿ��ڶ������
	int in_duo(point *v, int n, point &a);
	// �ж��߶� a-b, c-d �Ƿ��ཻ
	int xiangjiao(point &a, point &b, point &c, point &d);
	// �ж� k �ڲ����߶� a-b ��
	int on_segment(point &k, point &a, point &b);
	int i, j, k;

	// �ж� a, b �����ڲ��ڶ������
	if (!in_duo(v, n, a)) return 0;
	if (!in_duo(v, n, b)) return 0;
	for (i=0; i<n; i++)		// �������б� v[i]-[j]
	{
		j = (i + 1) % n;
		// �������˵���ཻ
		if (xiangjiao(a, b, v[i], v[j])) return 0;

		// ��� i �����߶� a-b ��, �ж��ǲ�������
		// �ж� i ��ǰ��������߶��ǲ��Ǻ�� a-b
		if (on_segment(v[i], a, b))
		{
			k = (i - 1) % n;
			if (xiangjiao(v[j], v[k], a, b))
				return 0;
		}
	}
	return 1;
}

int main(void)
{
	point vex[400];		// ��� 400 ����
	int n, i;
	point a, b;		// �߶� a-b

	while (1)
	{
		printf("��ʱ������һ�������: ");
		scanf("%d", &n);		// ������
		for (i=0; i<n; i++)
			scanf("%lf %lf", &vex[i].x, &vex[i].y);
		printf("����һ���߶�: ");
		scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y);
		if (in(vex, n, a, b))
			printf("��\n\n");
		else 
			printf("����\n\n");
	}
	return 0;
}


inline double fabs(double x)
{
	return x > 0 ? x : -x;
}

// �ж� k �ڲ����߶� a-b ��
int on_segment(point &k, point &a, point &b)
{
	double x1 = MIN(a.x, b.x);
	double x2 = MAX(a.x, b.x);
	double y1 = MIN(a.y, b.y);
	double y2 = MAX(a.y, b.y);

	if (x1 <= k.x && k.x <= x2 && y1 <= k.y && k.y <= y2)
	{
		// a->k, a->b �������������, �ж��ǲ��� 0
		x1 = k.x - a.x;
		y1 = k.y - a.y;
		x2 = b.x - a.x;
		y2 = b.y - a.y;
		if (fabs(x1 * y2 - x2 * y1) < EPS)
			return 1;
	}
	return 0;
}

// �ж� p1, p1 �ڲ��� Q ������, �ڷ��� 1
int two_side(point &p1, point &p2, point &q1, point &q2)
{
	double x1, y1, x2, y2, x3, y3;

	// q1->p1 (x1, y1), q1->p2 (x2, y2), q1->q2 (x3, y3)
	x1 = p1.x - q1.x;   y1 = p1.y - q1.y;
	x2 = p2.x - q1.x;   y2 = p2.y - q1.y;
	x3 = q2.x - q1.x;   y3 = q2.y - q1.y;
	if ((x1*y3 - x3*y1) * (x2*y3 - x3*y2) < 0) return 1;
	return 0;
}

// �ж��߶� a-b, c-d �Ƿ��ཻ, ���ж������˵�
int xiangjiao(point &a, point &b, point &c, point &d)
{
	if (two_side(a, b, c, d) && two_side(c, d, a, b))
		return 1;
	return 0;
}

// �ж� k ���ڲ��ڶ���� s ��
int in_duo(point *s, int n, point &k)
{
	point t;		// ��ˮƽ���� t <- k
	point tmp;
	int count = 0;
	int i, j;

	t.y = k.y;
	t.x = -0xFFFFF;
	for (i=0; i<n; i++)		// ����ÿһ���� s[i-1] - s[i]
	{
		j = (i + 1) % n;
		if (on_segment(k, s[i], s[j]))	// �� k �ڱ���
			return 1;
		else 
		{
			// �ж��߶��ǲ���ˮƽ��, ˮƽ�߶κ���
			if (fabs(s[i].y - s[j].y) > EPS) 
			{
				// �ҳ��߶��нϸߵĵ� tmp
				if (s[i].y < s[j].y) tmp = s[j];
				else tmp = s[i];
				// �ж� tmp �ڲ���������
				if (on_segment(tmp, k, t)) 
					count++;
				// ������������ཻ
				else if (xiangjiao(k, t, s[i], s[j]))
					count++;
			}
		}
	}
	if (count % 2 == 1) return 1;
	else return 0;
}
