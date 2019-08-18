
// �� n �������Ҿ��������������

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

#define INF 0xFFFFFF

typedef struct
{
	double x, y;
}point;

// ��¼�� a, b ������ dis, �ҳ��������ͬʱ�ҳ�������
typedef struct
{
	point *a;
	point *b;
	double dis;
}recond;

point p[100010];		// ԭ����
point *x[100010];		// x ����Ԥ����
point *y[100010];		// y ����Ԥ����

inline double dist(point *a1, point *a2)
{
	return sqrt((a1->x-a2->x)*(a1->x-a2->x)+(a1->y-a2->y)*(a1->y-a2->y));
}

inline double fabs(double x)
{
	return x > 0 ? x : -x;
}

int cmpx(const void *x, const void *y)
{
	point *a = (point *)x;
	point *b = (point *)y;

	return (a->x < b->x);
}

int cmpy(const void *x, const void *y)
{
	point *a = (point *)x;
	point *b = (point *)y;

	return (a->y < b->y);
}

// ������ĵ��
recond min_close(int s, int n)
{
	recond r;
	int i, j, top;
	double dis;

	if (n - s == 1)		// һ����
	{
		r.dis = INF;
		return r;
	}
	else if (n - s == 2)	// ������
	{
		r.a = x[0];
		r.b = x[1];
		r.dis = dist(x[0], x[1]); 
		return r;
	}
	else if (n - s == 3)	// ������
	{
		r.dis = INF;
		for (i=0; i<3; i++)
		{
			j = (i + 1) % 3;
			dis = dist(x[i], x[j]);
			if (dis < r.dis)
			{
				r.dis = dis;
				r.a = x[i];
				r.b = x[j];
			}
		}
	}
	// �������ϵĵ�
	int mid = (n + s) / 2;
	recond d1 = min_close(s, mid);
	recond d2 = min_close(mid, n);
	r = d1.dis < d2.dis ? d1 : d2;

	top = 0;
	// �� x[mid] ������, ��������չ r.dis ���
	for (i=s; i<n; i++)
		if (fabs(x[i]->x - x[mid]->x) < r.dis)
			y[top++] = x[i];
			// y ��¼ x ����С�� r.dis �ĵ�
			// Ҳ���Ǽ�¼���ڿ���ڵĵ�, �����ж�ȫ���ĵ�
	// �� y �����С��������, ö����С����
	std::sort(y, y + top, cmpy);
	for (i=0; i<top; i++)
	{
		for (j=i+1; j<top; j++)
		{
			if (y[j]->y - y[i]->y < r.dis)
			{
				dis = dist(y[j], y[i]);
				if (dis < r.dis)
				{
					r.dis = dis;
					r.a = y[j];
					r.b = y[i];
				}
			}
			else break;
			// y �����������, һ�γ���, ����Ķ�����
		}
	}
	return r;
}

int main(void)
{
	recond r;
	int n;
	int i;

	while (1)
	{
		printf("���� n �Լ� n ����: ");
		scanf("%d", &n);
		for (i=0; i<n; i++)
		{
			scanf("%lf %lf", &(p[i].x), &(p[i].y));
			x[i] = p + i;
		}
		std::sort(x, x + n, cmpx);
		r = min_close(0, n);
		printf("������: (%g, %g), (%g, %g)\n", 
			r.a->x, r.a->y, r.b->x, r.b->y);
		printf("�������: %g\n\n", r.dis);
	}
	return 0;
}