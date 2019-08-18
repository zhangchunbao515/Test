
// �� P, Q �������߶�
// �� P x Q > 0 , �� P �� Q ��˳ʱ�뷽��
// �� P x Q < 0 , �� P �� Q ����ʱ�뷽��
// �� P x Q = 0 , �� P �� Q ����, Ҳ����ͬ��Ҳ���ܷ���

#include <stdio.h>

const double EPS = 1e-8;

int abs(double x)
{
	return x > 0 ? x : -x;
}

// ���� P, Q ���, P x Q = px * qy - py * qx
double cmul(double px, double py, double qx, double qy)
{
	return px * qy - py * qx;
}

int main(void)
{
	double px1, py1, px2, py2;
	double qx1, qy1, qx2, qy2;
	double ji;

	while (1)
	{
		// ����˳�� p1(x1, y1)  p2(x2, y2), ���� P = p1->p2 
		printf("�����߶� P �������˵�: ");
		scanf("%lf %lf %lf %lf", &px1, &py1, &px2, &py2);
		printf("�����߶� Q �������˵�: ");
		scanf("%lf %lf %lf %lf", &qx1, &qy1, &qx2, &qy2);
		// �� p2 - p1
		px1 = px2 - px1;   py1 = py2 - py1;
		qx1 = qx2 - qx1;   qy1 = qy2 - qy1;
		ji = cmul(px1, py1, qx1, qy1);
		if (abs(ji) < EPS) printf("P �� Q ����\n\n");
		else if (ji > 0) printf("P �� Q ��˳ʱ�뷽��\n\n");
		else if (ji < 0) printf("P �� Q ����ʱ�뷽��\n\n");
	}
	return 0;
}