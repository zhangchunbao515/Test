// ��д prim ��С������

#include <stdio.h>
#include <string.h>

#define NUM 30		// ��� 30 ������
#define INF 0xFFFFF

// prim �㷨�ʺϳ���ͼ, ������·��������, 
// prim �㷨���� dijskra �㷨, ����ȥ�ɳ�һ������ min_w
// min_w[k] ��ʾ �� k �����С�ߵ�Ȩֵ�� min_w[k]
// ͬʱ���ڷ��ʹ��ĵ� k, Ҫ���з��ʱ��
int prim(int (*m)[NUM], char *v, int len)
{
	int sum = 0;
	int min_w[NUM];		// min_w ��¼��СȨֵ
	char used[NUM];		// ���ʱ��
	int pre[NUM];		// ��¼ǰ�����, ���·��
	int min, pos, i, j;

	for (i=0; i<len; i++) min_w[i] = INF;
	for (i=0; i<len; i++) used[i] = 0;

	min_w[0] = 0;	// ���� 0 Ϊ�������
	// n ����, ������Ҫ n-1 ����, ��������һ��ͼ
	// ���ڵ�һ��ѭ����û���ҵ���, ����ѭ�� n ��
	for (j=0; j<len; j++)
	{
		// ��һ����СȨֵ�ı�, ��¼��Ȩֵ
		min = INF;
		for (i=0; i<len; i++)
		{
			if (!used[i] && min_w[i] < min) 
			{
				min = min_w[i];
				pos = i;		// ��¼�õ� i
			}
		}
		if (min == INF) return -1;		// û���ҵ�, ������ͨͼ
		used[pos] = 1;			// ѡ�� pos ��, ͬʱҪ���
		sum += min;				// �ۼ�Ȩֵ
		if (pos != 0) printf("(%c -> %c), ", v[ pre[pos] ], v[pos]);

		// ������� (pos) ȥ�ɳ� min �е�������
		for (i=0; i<len; i++)
		{
			if (m[pos][i] < min_w[i]) 
			{
				min_w[i] = m[pos][i];
				pre[i] = pos;
			}
		}
	}
	return sum;
}

// ��Ϊ������Ʋ������ַ� 'a''b''c', ����Ҫ�Ҷ�Ӧ��λ��
// �����������, ������ֱ����Ϊ���������λ��
inline int find_addr(char *vex, int len, char a)
{
	int i;
	for (i=0; i<len; i++)
		if (vex[i] == a) return i;
	return -1;
}

int main(void)
{
	char vex[NUM];
	int matrix[NUM][NUM];
	int len, wight;
	char a, b;
	int add1, add2;
	int sum = 0;

	printf("����һ������ͼ, �����붥�㼯: ");
	scanf("%s", vex);   fflush(stdin);
	len = strlen(vex);
	for (a=0; a<len; a++)
		for (b=0; b<len; b++) matrix[a][b] = INF;
	printf("������߼�: ");
	while (1)
	{
		fflush(stdin);
		scanf("%c %c %d", &a, &b, &wight);
		if (a == '0' && b == '0' && wight == 0) break;
		add1 = find_addr(vex, len, a);
		add2 = find_addr(vex, len, b);
		if (!(add1 == -1 || add2 == -1) && wight > 0)
		{
			matrix[add1][add2] = wight;
			matrix[add2][add1] = wight;		// ���������ͼ��Ҫ���
		}
	}
	sum = prim(matrix, vex, len);
	printf("\n��СȨֵ %d\n", sum);

	return 0;
}
