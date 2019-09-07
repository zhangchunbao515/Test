
// ����ͼ�����ƥ�� - ������� - ��� <�㷨����> 409 ҳ
// �ڶ���ͼ�ϼ��� s, t ��, ��һ������� (Ԥ���ƽ�������·)
// �ڲ����������з��������ı�, �������ƥ����

// ���ݵ�����
// �������ͼ�ĵ����뷽ʽ, ���ܱ�֤������Ƕ���ͼ
// ��Ҫ����Ҫ��һ��Ⱦɫ���ж϶���ͼ
// ��������߼�(a, b)ʱ, Լ�� a ���� s ��, b ���� t ��

#include <stdio.h>
#include <queue>

#define NUM  80			// ��󶥵���
#define NUM2 300		// ������
#define INF 0xFFFFF
#define MIN(a, b) ((a) > (b) ? (b) : (a))

struct		// �߼����鱣�����ͼ
{
	int a;
	int b;
}e[NUM2];
int top = 0;

typedef struct node		// ���н��
{
	int i;
	int e;
	int h;
	bool operator < (const node &a) const
	{ return (h < a.h); }
}node;

// ���Ѽ���߶�
void height(int (*can)[NUM], int n, node *w, int t)
{
	std::queue<int> q;
	int used[NUM];
	int i, tmp;

	for (i=0; i<n; i++) used[i] = 0;
	w[t].h = 0;
	q.push(t);
	used[t] = 1;
	while (!q.empty())
	{
		tmp = q.front();   q.pop();
		for (i=0; i<n; i++)
		{
			if (!used[i] && can[i][tmp] > 0)
			{
				w[i].h = w[tmp].h + 1;
				q.push(i);
				used[i] = 1;
			}
		}
	}
}

// Ԥ���ƽ�������� + ���ȶ����Ż�
void max_flow(int (*can)[NUM], int n, int s, int t)
{
	std::priority_queue<node *> q;
	node w[NUM];		// ��¼�������, �߶�
	node *tmp;
	int min;
	int f = 1;
	int i;

	height(can, n, w, t);		// ��ʼ�� w[]
	for (i=0; i<n; i++)
	{
		w[i].i = i;
		w[i].e = 0;
	}
	w[s].h++;
	w[s].e = INF;
	q.push(w + s);
	while (!q.empty())		// �����ƽ�
	{
		tmp = q.top();   q.pop();
		if (f) f = 0;
		else if (tmp->i == s || tmp->i == t) continue;
		for (i=0; i<n; i++)
		{		// ��·��, �Ҹ߶ȱ� i ��, �����ƽ�
			if (can[tmp->i][i] != 0 && tmp->h > w[i].h)
			{
				min = MIN(can[tmp->i][i], tmp->e);
				can[tmp->i][i] -= min;
				can[i][tmp->i] += min;
				tmp->e -= min;
				w[i].e += min;
				if (i != t || i != s) q.push(w + i);
			}
		}
		// tmp ��������δ�ƽ���
		if (tmp->i != s && tmp->e > 0)
		{
			min = INF;
			for (i=0; i<n; i++)
				if (can[tmp->i][i] != 0 && w[i].h < min)
					min = w[i].h;
			tmp->h = min + 1;
			q.push(tmp);
		}
	}
}

// ������ƥ��, �����ȶ��е�Ԥ���ƽ�
// �㷨����:
// ���ݱ߼����鹹���������, ��ǰ����, ����Դ����
// Ԥ���ƽ��������
// ���ȥ��ǰ�������������������ı�, ͳ������
int pipei(int n)
{
	int count = 0;			// ƥ������
	int can[NUM][NUM];		// ��������
	int i, j;
	int s = n++;		// ����Դ�� n-2
	int t = n++;		// ���ӻ�� n-1
	int a, b;

	for (i=0; i<n; i++)		// ��ʼ��
		for (j=0; j<n; j++)
			can[i][j] = 0;
	for (i=0; i<top; i++)	// �����������
	{
		a = e[i].a;   b = e[i].b;
		can[a][b] = 1;
		can[s][a] = 1;
		can[b][t] = 1;
	}
	max_flow(can, n, s, t);		// ����һ�������
	for (i=0; i<top; i++)
	{
		a = e[i].a;   b = e[i].b;
		if (can[b][a] > 0)		// �з�������
		{
			printf("(%d, %d), ", a, b);
			count++;
		}
	}
	return count;
}

int main(void)
{
	int n;
	int a, b;
	int max;

	printf("���붥�������߼�: ");
	scanf("%d", &n);
	while (1)
	{
		scanf("%d %d", &a, &b);
		if (a == 0 && b == 0) break;
		e[top].a = a;
		e[top++].b = b;
	}
	printf("\nƥ��ı�: ");
	max = pipei(n);
	printf("\n������ƥ����: %d\n", max);

	return 0;
}