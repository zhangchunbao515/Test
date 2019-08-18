
// ����С��, ��С����������������

#include <stdio.h>
#include <string.h>
#include <queue>

#define NUM 50			// �������
#define INF 0XFFFFFF

typedef struct node		// ���ȶ��еĽ��
{
	int i;		// �����
	int e;		// ����
	int h;		// �߶�
	bool operator < (const node &a) const
	{ return (h < a.h); }
}node;

// ����߶�
void height(int (*r)[NUM], node *h, int n, int t)
{
	int used[NUM];
	int i, tmp;
	std::queue<int> q;

	for (i=0; i<n; i++) used[i] = 0;
	h[t].h = 0;			// ���߶����
	q.push(t);
	used[t] = 1;
	while (!q.empty())
	{
		tmp = q.front();   q.pop();
		for (i=0; i<n; i++)
		{
			if (!used[i] && r[i][tmp] != 0)
			{
				h[i].h = h[tmp].h + 1;
				q.push(i);
				used[i] = 1;
}}}}

// �� a ���� b
inline void PUSH(int (*r)[NUM], node *w, int a, int b)
{
	int max;		// ����ƽ���

	max = r[a][b] > w[a].e ? w[a].e : r[a][b];
	r[a][b] -= max;
	r[b][a] += max;
	w[a].e -= max;
	w[b].e += max;
}

// ���ȶ��� + Ԥ���ƽ� �������, ͬʱ��� s ��, t ��
// �㷨����:
// ��ʼ��ÿ�����ĸ߶�, ����
// ��ʼ��Դ����Ϣ, �����
// ��Դ�㿪ʼ�ƽ�, �ƽ�������ر�����
// ֱ������Ϊ��
// �� s ����й���, �ҳ� s ��, ʣ�µľ��� t ����
int maxflow(int (*m)[NUM], int n, int s, int t)
{
	std::priority_queue<node *> q;	// ���ȶ���
	std::queue<int> q2;
	int used[NUM];
	int r[NUM][NUM];
	node w[NUM];		// ��¼�����Ϣ, �߶�, ������
	node *tmp;
	short int f = 1;
	int i, j;
	int min_h;

	for (i=0; i<n; i++)		// ���ƻ� m[][], ��ʼ��
	{
		for (j=0; j<n; j++) r[i][j] = m[i][j];
		w[i].i = i;
		w[i].e = 0;
	}
	height(r, w, n, t);
	w[s].e = INF;
	w[s].h++;
	q.push(w + s);
	while (!q.empty())
	{
		tmp = q.top();   q.pop();
		if (f) f = 0;
		else if (tmp->i == s || tmp->i == t) continue;
		for (i=0; i<n; i++)
		{
			if (r[tmp->i][i] != 0 && tmp->h > w[i].h)
			{
				PUSH(r, w, tmp->i, i);
				if (i != t && i != s) q.push(w + i);
			}
		}
		if (tmp->i != s && tmp->e > 0)		// ��������, �ر����� 
		{
			min_h = INF;
			for (i=0; i<n; i++)
				if (r[tmp->i][i] != 0 && w[i].h < min_h) 
					min_h = w[i].h;
			tmp->h = min_h + 1;
			q.push(tmp);
		}
	}
	for (i=0; i<n; i++) used[i] = 0;
	q2.push(s);
	used[s] = 1;			// �� s �㷢��һ�ι���
	while (!q2.empty())
	{
		j = q2.front();   q2.pop();
		for (i=0; i<n; i++)
		{
			if (!used[i] && r[j][i] != 0)
			{
				used[i] = 1;
				q2.push(i);
			}
		}
	}
	printf("\n s ��: ");
	for (i=0; i<n; i++)
		if (used[i]) printf("%d, ", i);
	printf("\n t ��: ");
	for (i=0; i<n; i++)
		if (!used[i]) printf("%d, ", i);
	return w[t].e;
}

int main(void)
{
	int n;
	int matrix[NUM][NUM];		// �ڽӾ���
	int a, b, c;

	memset(matrix, 0, sizeof(matrix));
	printf("������һ����Ȩ����ͼ: ");
	printf("�������: ");
	scanf("%d", &n);
	printf("�߼�: ");
	while (1)
	{
		scanf("%d %d %d", &a, &b, &c);
		if (!(a || b || c)) break;
		matrix[a][b] = c;
	}
	printf("����Դ��ͻ��: ");
	scanf("%d %d", &a, &b);
	printf("\n��С������: %d\n", maxflow(matrix, n, a, b));

	return 0;
}
