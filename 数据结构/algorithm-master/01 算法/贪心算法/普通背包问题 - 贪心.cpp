#include <stdio.h>
#include <stdlib.h>

#define SIZE 200

typedef struct
{
	int weight;
	int value;
	float avg;
}recond;

// result[] ��¼���˶���, result[k] = x, �� k ������ result[k] ����
float result[SIZE];
int top;

// void *x תΪ recond* ������ (recond *)x, ����ȡ���� *(recond *)x
// ����ȡ avg, (*(recond *)x).ave
int cmp(const void *x, const void *y)
{
	return (*(recond *)x).avg < (*(recond *)y).avg;
}

// ��ͨ������̰�Ľⷨ, ����ֵ����������, ÿ�η����м�ֵ��
float tanxin(recond *r, int c, int n)
{
	float sum = 0.0f;
	int i;
	
	for (i=0; i<n; i++)		// ���ռ�ֵ����������
		r[i].avg = (float)(r[i].value) / r[i].weight;
	qsort(r, n, sizeof(r[0]), cmp);

	for (i=0, top=0; i<n; i++)
	{
		if (r[i].weight <= c)		// ȫ������
		{
			sum += r[i].value;
			c -= r[i].weight;
			result[top++] = (float)r[i].value;		// ��¼���˶���
		}
		else		// ���ַ���, ���˳�
		{
			sum += c * r[i].avg;
			result[top++] = ((float)c / r[i].weight) * r[i].value;
			break;
		}
	}
	return sum;
}

int main(void)
{
	recond r[SIZE];
	float sum;
	int c, n;
	int i;

	printf("���뱳�������������Ʒ����: ");
	scanf("%d %d", &c, &n);
	printf("���� %d ����Ʒ: (���� ��ֵ)\n", n);
	for (i=0; i<n; i++)
		scanf("%d %d", &(r[i].weight), &(r[i].value));
	sum = tanxin(r, c, n);
	printf("\n����ֵ: %0.2f\n", sum);
	for (i=0; i<top; i++)
		printf("\n����Ϊ %d ��, ���� %.2f", r[i].weight, result[i]);
	printf("\n");
	return 0;
}