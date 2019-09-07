
// �ж��߶� P(p1, p2), Q(q1, q2) �Ƿ��ཻ
// �߶� P �������˵� p1, p2 �ж� p1, p2 �ڲ��� Q ������
// �� Q ��ȡһ�� q1 ����������� q1->p1, q1->p2
// �������������� q1->q2 �����, ��� p1, p2 �����˵Ļ�
// ��ô q1->p1, q1->p2 �϶���һ���� q1->q2 ��˳ʱ��, һ������ʱ��
// ��ô�� q1->p1, q1->p2 �ֱ��� q1->q2 �������˿϶�С�ڵ��� 0
// ���� 0 ��������߶��غ�
// �ڰ� Q �������˵���������ж�, ���ͨ�����ཻ
// �ж�ֱ�����߶��ཻ�Ļ�, ֻ���ж��߶ε��������ǲ�����ֱ�ߵ�����

#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct
{
	double x, y;
}point;

const double EPS = 1e-8;

inline double fabs(double x)
{
	return x > 0 ? x : -x;
}

// �жϵ� q �ڲ��� p1-p2 ���߶���
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

// �ж� p1, p1 �ڲ��� Q ������, �ڷ��� 1
int two_side(point &p1, point &p2, point &q1, point &q2)
{
	// ������� q1->p1 �� q1->q2 ��˳ʱ��(����ʱ��), ����Ϊ��
	// �� q1->p2 �� q1->q2 ����ʱ��(��˳ʱ��), ����Ϊ��
	// ���Բ���ĳ˻�С�� 0, ���� 0 ���غ�
	double x1, y1, x2, y2, x3, y3;

	// q1->p1 (x1, y1), q1->p2 (x2, y2), q1->q2 (x3, y3)
	x1 = p1.x - q1.x;   y1 = p1.y - q1.y;
	x2 = p2.x - q1.x;   y2 = p2.y - q1.y;
	x3 = q2.x - q1.x;   y3 = q2.y - q1.y;
	if ((x1*y3 - x3*y1) * (x2*y3 - x3*y2) < 0) return 1;
	return 0;
}

// �ж��߶� (p1, p2) (q1, q2) �Ƿ��ཻ, �ཻ���� 1
int segment_intersect(point &p1, point &p2, point &q1, point &q2)
{
	// ���ж� p1, p2 �ڲ��� Q ������
	// ���ж� q1, q2 �ڲ��� P ������
	// �ж��߶���ֱ���ཻ�Ļ�, ֻ���ж�һ��
	if (two_side(p1, p2, q1, q2)
		&& two_side(q1, q2, p1, p2)) 
		return 1;

	// ��һ��������һ���߶��ϵ�ʱ��, ����ĳ˻�Ϊ 0
	// ���ھ�������, ����ֱ��ж��ĸ����ڲ����߶���
	if (on_segment(p1, q1, q2)) return 1;
	else if (on_segment(p2, q1, q2)) return 1;
	else if (on_segment(q1, p1, p2)) return 1;
	else if (on_segment(q2, p1, p2)) return 1;

	return 0;
}

int main(void)
{
	point p1, p2;
	point q1, q2;

	while (1)
	{
		// ����˳�� p1.x, p1.y, p2.x, p2.y
		printf("�����߶� p �������˵�: ");
		scanf("%lf %lf %lf %lf", &p1.x, &p1.y, &p2.x, &p2.y);
		printf("�����߶� q �������˵�: ");
		scanf("%lf %lf %lf %lf", &q1.x, &q1.y, &q2.x, &q2.y);
		if (segment_intersect(p1, p2, q1, q2))
			printf("�ཻ\n\n");
		else 
			printf("���ཻ\n\n");
	}
	return 0;
}