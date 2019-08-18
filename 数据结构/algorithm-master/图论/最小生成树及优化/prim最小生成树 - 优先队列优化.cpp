
// ��ͨ�� prim �㷨���ǲ�������ѡ������ķ���
// ÿ��ѡ����С�� s ���� t ����С�ı�, �������ɳ� O(n)
// ����ʹ�����ȶ�����ά�����ѡ��Ĳ��� O(log n)

#include <stdio.h>
#include <queue>

#define NUM 60
#define INF 0xFFFFFF

int m[NUM][NUM];	// �ڽӾ���
int n;

// ���ȶ��еĽ��
// s ���� t ����̱� v �������
typedef struct node
{
	int i;		// ���
	int v;		// ��̱�
	bool operator < (const node &a) const
	{ return (v > a.v); }
}node;

// ʹ�����ȶ����Ż� prim �㷨
int prim()
{
	std::priority_queue<node> q;
	int dis[NUM];		// s ���� t ������С����
	int pre[NUM];		// ��¼ǰ��
	int used[NUM];		// ʹ�ñ��
	int value = 0;
	int i, j;
	node tmp, tmp2;

	for (i=0; i<n; i++)		// ��ʼ��
	{
		pre[i] = -1;
		dis[i] = INF;
		used[i] = 0;
	}
	tmp.i = 0;		// �������Ϊ 0
	q.push(tmp);
	// n ������Ҫ�ɳ� n-1 ��
	for (i=0; i<n; i++)
	{
		if (q.empty()) return -1;		// ����ͨ
		// ������С�ߵ�ʱ�������ܶ��ظ������
		// �� used[] �ж�ȡ���Ľ���Ƿ�ʹ�ù�
		tmp = q.top();
		while (used[tmp.i])
		{
			q.pop();
			tmp = q.top();
		}
		q.pop();
		used[tmp.i] = 1;	// �ҵ���С�ı� tmp.v
		if (tmp.i != 0)		// ������� 0
		{
			value += m[tmp.i][pre[tmp.i]];
			printf("(%d, %d), ", tmp.i, pre[tmp.i]);
		}
		for (j=0; j<n; j++)
		{
			if (!used[j] && m[tmp.i][j] < dis[j])
			{
				dis[j] = m[tmp.i][j];
				pre[j] = tmp.i;
				// (j, dis[j]) ���ɳں����
				tmp2.i = j;
				tmp2.v = dis[j];
				q.push(tmp2);
			}
		}
	}
	return value;
}

int main(void)
{
	int i, j, v;
	
	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = INF;
	printf("����߼�: ");
	while (1)
	{
		scanf("%d %d %d", &i, &j, &v);
		if (!(i || j || v)) break;
		m[i][j] = v;
		m[j][i] = v;
	}
	printf("\n�������߼�: ");
	v = prim();
	printf("\n��СȨֵ: %d\n", v);

	return 0;
}
/*		�����������
6
0 1 6
0 5 1
0 4 5
1 5 5
1 2 3
2 5 6
2 3 6
3 5 4
3 4 2
4 5 5
0 0 0

9
0 1 5
1 2 7
2 3 26
3 4 8
4 5 11
5 6 20
6 0 10
0 7 1
1 7 22
2 7 4
8 7 2
5 7 21
6 7 8
2 8 15
3 8 9
4 8 3
5 8 6
0 0 0
*/