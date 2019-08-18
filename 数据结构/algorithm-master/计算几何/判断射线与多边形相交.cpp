
// �ж������������ཻ
// �����������, ����һ������, �ж��ཻ�Ķ����
// �ж��������߶��ཻ:
// ����ж��߶κ����������
// ����ж��߶����������ߵ����"ǰ��"

#include <stdio.h>
#include <malloc.h>

typedef struct		// ��
{
	double x, y;
}point;

typedef struct		// �����
{
	point *base;
	int n;
}duo;

// �ж����� p1->p2,  ���߶� q1-q2 �Ƿ��ཻ, �ཻ���� 1
// �����߶� q1-q2 ������Ҫ������� p1->p2
// �������㲻������������"����", ���������С�� 0
int shexian(point &p1, point &p2, point &q1, point &q2)
{
	double x1, y1, x2, y2, x3, y3;

	// (x1, y1) �� p1->q1, (x2, y2) �� p1->q2, (x3, y3) �� p1->p2
	// ����ĳ˻�ҪС�ڵ��� 0, ���� 0 ����ֱ���ж�
	x1 = q1.x - p1.x;   y1 = q1.y - p1.y;
	x2 = q2.x - p1.x;   y2 = q2.y - p1.y;
	x3 = p2.x - p1.x;   y3 = p2.y - p1.y;
	if ((x1*y3 - x3*y1) * (x2*y3 - x3*y2) > 0) return 0;

	// Ȼ���õ㼯�ж� p1->q1 �� p1->p2 �ļн��ǲ���С�ڵ��� 90
	if (x1 * x3 + y1 * y3 < 0) return 0;
	if (x2 * x3 + y2 * y3 < 0) return 0;
	return 1;
}

// ��� n ����������������ཻ�Ķ���ε��±�
// û�������
// ���� a -> b, a - b �����߶�, ���������߶��ཻ
// ������������һ���߶���������ཻ, �����
void find(duo *v, int n, point &a, point &b, int *result)
{
	int i, j, k;
	int top = 0;

	for (i=0; i<n; i++)		// ���� n �������
	{
		for (j=0; j<v[i].n; j++)	// ���� v[i] �����б�
		{
			k = (j + 1) % v[i].n;
			// �����˵���ཻ
			if (shexian(a, b, v[i].base[j], v[i].base[k]))
			{
				result[top++] = i;
				break;
			}
		}
	}
	result[top] = -1;		// ��־����
}

int main(void)
{
	point a, b;		// ���� a -> b ���� b ��������
	duo *v;
	int n, i, j;
	int result[300];	// ��¼���

	while (1)
	{
		printf("�������θ���: ");
		scanf("%d", &n);
		v = (duo *)malloc(n * sizeof(duo));
		for (i=0; i<n; i++)
		{
			printf("��ʱ������� %d �������: ", i + 1);
			scanf("%d", &(v[i].n));
			v[i].base = (point *)malloc(v[i].n * sizeof(point));
			for (j=0; j<v[i].n; j++)
				scanf("%lf %lf", &(v[i].base[j].x), &(v[i].base[j].y));
		}
		printf("�������ߵ����: ");
		scanf("%lf %lf", &a.x, &a.y);
		printf("�������ߵķ���(ĳ��): ");
		scanf("%lf %lf", &b.x, &b.y);
		
		// ����ཻ����ε��±�, û�������
		find(v, n, a, b, result);
		if (result[0] == -1) printf("û���ཻ�Ķ����\n");
		else 
		{
			printf("\n�ཻ�Ķ����: ");
			i = 0;
			while (result[i] != -1) 
				printf("%d, ", result[i++]);
			printf("\n\n");
		}
		// �ͷ���Դ
		for (i=0; i<n; i++) 
			free(v[i].base);
		free(v);
	}
	return 0;
}
/*		һ���������
4
4
1 1 2 1 2 2 1 2
4
3 0 4 0 4 1 3 1
4
6 0 7 1 6 2 5 1
4
8 -1 9 -1 9 1 8 1
0 0
1 0
*/