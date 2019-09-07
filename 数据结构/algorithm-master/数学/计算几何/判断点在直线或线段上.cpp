
// �жϵ��ڲ����߶���, ���Ϊ Q, �߶�Ϊ P1, P2
// �ж��ڲ���ֱ����, ֻ����ֱ������ȡ���� p1, p2
// ���ж� q, p1, p2 �����Ƿ���, ������ (q->p1), (p1->p2) �Ĳ���ǲ��� 0

#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

const double EPS = 1e-8;

typedef struct		// ������
{
	double x;
	double y;
}point;

inline double fabs(double x)
{
	return x > 0 ? x : -x;
}

// �ж� q �ڲ��� p1, p2 ���߶���
int on_segment(point &q, point &p1, point &p2)
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

int main(void)
{
	point q, p1, p2;

	while (1)
	{
		printf("�����߶� P �������˵�: ");
		scanf("%lf %lf %lf %lf", &p1.x, &p1.y, &p2.x, &p2.y);
		printf("����һ����: ");
		scanf("%lf %lf", &q.x, &q.y);
		if (on_segment(q, p1, p2))
			printf("��\n\n");
		else 
			printf("����\n\n");
	}
	return 0;
}