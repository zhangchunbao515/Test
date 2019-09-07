
#include <stdio.h>
#include <math.h>

typedef struct
{
	double x, y;
}point;

const double EPS = 1e-7;

inline double fabs(double x)
{
	return x > 0 ? x : -x;
}

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

// �ҳ� n ������ y ֵ��С�ĵ�, y ֵһ������ x ֵ��С
point lowp(point *v, int n)
{
	int i;
	point r;

	r.y = r.x = 0xFFFFFF;
	for (i=0; i<n; i++)
	{
		if (fabs(r.y - v[i].y) < EPS)
		{
			if (v[i].x < r.x) r = v[i];
		}
		else if (v[i].y < r.y) r = v[i];
	}
	return r;
}

// �ҳ� n ������ y ֵ���ĵ�, y ֵһ������ x ֵ��С
point highp(point *v, int n)
{
	int i;
	point r;
	
	r.y = -0xFFFFFF;
	r.x = 0xFFFFFF;
	for (i=0; i<n; i++)
	{
		if (fabs(r.y - v[i].y) < EPS)
		{
			if (v[i].x < r.x) r = v[i];
		}
		else if (v[i].y > r.y) r = v[i];
	}
	return r;
}

// �жϵ� a �� b �ǲ������
inline int equal(point &a, point &b)
{
	if (fabs(a.x - b.x) > EPS) return 0;
	if (fabs(a.y - b.y) > EPS) return 0;
	return 1;
}

// ��͹���� Jarvis ������, �ο� <�㷨����>
void jarvis(point *v, int n, point *stack, int &top)
{
	point high, low, cur;
	int i;
	double jiao, max;
	point tmp, tmp2;

	// �ҳ���͵ĵ�, ����ߵĵ�, ��������͹����
	low = lowp(v, n);
	high = highp(v, n);

	// �ӵ͵������ѵ��ߵ�
	top = 0;
	stack[top++] = low;
	cur = low;
	while (!equal(cur, high))
	{
		// ÿ���Ҹ��н���С��, �� cos ֵ����
		tmp = cur;
		tmp2.x = 100000;
		tmp2.y = cur.y;
		max = -0xFFFFF;
		for (i=0; i<n; i++)
		{
			if (!(v[i].y < cur.y))
			{
				jiao = cos_p(cur, tmp2, cur, v[i]);
				// �н�һ��ѡ��Զ�ĵ�
				if (fabs(max - jiao) < EPS)
				{
					if (v[i].y > tmp.y) tmp = v[i];
				}
				else if (jiao > max)
				{
					max = jiao;
					tmp = v[i];
				}
			}
		}
		stack[top++] = tmp;
		cur = tmp;
	}
	// �Ӹߵ����͵���
	while (!equal(cur, low))
	{
		// ÿ���Ҹ��н���С��, �� cos ֵ����
		tmp = cur;
		tmp2.x = -100000;
		tmp2.y = cur.y;
		max = -0xFFFFF;
		for (i=0; i<n; i++)
		{
			if (!(v[i].y > cur.y))
			{
				jiao = cos_p(cur, tmp2, cur, v[i]);
				if (fabs(max - jiao) < EPS)
				{
					if (v[i].y < tmp.y) tmp = v[i];
				}
				else if (jiao > max)
				{
					max = jiao;
					tmp = v[i];
				}
			}
		}
		stack[top++] = tmp;
		cur = tmp;
	}
	top--;
}

int main(void)
{	
	point v[110];
	int n;
	point stack[110];		// ��¼͹��
	int top;
	int i;

	while (1)
	{
		printf("���� n �Լ� n ����: ");
		scanf("%d", &n);
		for (i=0; i<n; i++)
			scanf("%lf %lf", &(v[i].x), &(v[i].y));
		jarvis(v, n, stack, top);
		printf("͹���㼯: ");
		for (i=0; i<top; i++)
			printf("(%g, %g), ", stack[i].x, stack[i].y);
		printf("\n\n");
	}
	return 0;
}
/*
11
12 7
24 9
30 5
41 9
80 7
50 87
22 9
45 1
50 7
90 60
102 -22
*/