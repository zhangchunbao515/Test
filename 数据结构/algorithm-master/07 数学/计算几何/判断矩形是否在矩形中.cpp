
// ������͹��, ����ֻҪ�жϾ��ε��ĸ��㶼����һ�������ڼ���

#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct
{
	double x, y;
}point;

// �ж� k �ڲ��ھ��� a ��, �� k �ڱ��Ϸ��� 0
int dian(point &k, point &a1, point &a2)
{
	double x1 = MIN(a1.x, a2.x);
	double x2 = MAX(a1.x, a2.x);
	double y1 = MIN(a1.y, a2.y);
	double y2 = MAX(a1.y, a2.y);

	if (x1 < k.x && k.x < x2 && y1 < k.y && k.y < y2)
		return 1;
	return 0;
}

// �ж� a �������Ƿ���� b, ���жϵ��ڱ��ϵ����
int in(point &a1, point &a2, point &b1, point &b2)
{
	int sum = 0;
	double tmp;

	// �ֱ���֤���� b ���ĸ����ǲ����� a ��
	sum += dian(b1, a1, a2);
	sum += dian(b2, a1, a2);
	tmp = b1.x;			// ���� x ֵ, �����һ�ԶԽǵ�
	b1.x = b2.x;
	b2.x = tmp;
	sum += dian(b1, a1, a2);
	sum += dian(b2, a1, a2);
	// �ĵ�ȫ��ͨ��, sum == 4
	if (sum == 4) return 1;
	else return 0;
}

int main(void)
{
	point a1, a2, b1, b2;

	while (1)
	{
		// �ж� a �������Ƿ���� b
		printf("������� a �Խǵ�������: ");
		scanf("%lf %lf %lf %lf", &a1.x, &a1.y, &a2.x, &a2.y);
		printf("������� b �Խǵ�������: ");
		scanf("%lf %lf %lf %lf", &b1.x, &b1.y, &b2.x, &b2.y);
		if (in(a1, a2, b1, b2))
			printf("����\n\n");
		else 
			printf("������\n\n");
	}
	return 0;
}