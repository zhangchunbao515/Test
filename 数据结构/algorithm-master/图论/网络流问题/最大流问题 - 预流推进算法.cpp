
// ���������, Ԥ���ƽ��㷨

// maxflow()		ʹ����ͨ���н����ƽ�
// maxflow2()		ʹ�����ȶ��н����ƽ�, ���߶����� (��)

// ����·�㷨�������, �ǲ��ϵĴ�Դ�㵽���������·���е�
// ��Ԥ���ƽ��㷨����ģ��ˮ��, һ��һ������ƽ���, ���㷨��
// �����Դ���������޶��ˮ, ��󿴻�����ж���ˮ����
// ˮ���ʹ���, Ϊ����ʹˮ�ܴ�Դ��������, ��Ҫһ���߶Ⱥ��� height[i] ��˵�����ĸ߶�
// ���涨�� height[a] > height[b] ʱ, ˮ���ܴ� a ���� b, 
// �߶Ⱥ�����֤��ˮ���������в������ѭ��������ɵ���ѭ��
// ��Ȼ height[Դ��] = ���޸�, height[���] = 0, ���м���ĸ߶��ǵ����Ĺ��Ѿ���

// ����Դ�������޶��ˮ��, ������Ҫһ������ e[i] ����ʾĳ������ˮ��
// ��Դ�㿪ʼ, ��Դ����ڽӵ�, ȫ������ˮ, �����
// �ٰ��ڽӵ���ˮ, ���ڽӵ�ĵʹ��ƽ�, height[] ����С�ĵط�
// �����ȫ���ƽ��� (e[i] == 0) �����, ��������ƽ���
// ��߸ý��ĸ߶�, �������, ������һ���ƽ�
// a ����ߵĸ߶� height[a] = min{ height[�ڽӵ�] } + 1
// �ر�Ǻ�ͱ�֤��������һ���ط�����, Ҳ���ܻ�����Դ��
// ��Ϊ�����еĽ��, ���ϱ���߸߶�, ʹ�û�㱥�ͺ�, ʣ�µĲ�������ֻ������Դ����

#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define NUM 50		// ��󶥵���
#define INF 0xFFFFFF

// ���Ѽ���ÿ�����ĸ߶�, �ӻ�㿪ʼ
void BFS(int (*m)[NUM], int *h, int n, int t)
{
	std::queue<int> q;
	short int used[NUM];
	int cur, i;

	memset(used, 0, sizeof(used));
	h[t] = 0;		// ���߶����
	q.push(t);
	used[t] = 1;
	while (!q.empty()) {
		cur = q.front();   q.pop();
		for (i=0; i<n; i++) {
			if (!used[i] && m[i][cur] != 0) {
				h[i] = h[cur] + 1;
				used[i] = 1;
				q.push(i);
}}}}

// һ��ˮ���ƽ�����, �� a ��ˮ���� b
inline void PUSH(int (*r)[NUM], int *e, int a, int b)
{
	int min;		// �ƽ���

	// ���� a->b ���ƽ���, �����ܵ��ƽ�, ���������͹ܵ��ĸ�С
	min = e[a] > r[a][b] ? r[a][b] : e[a];
	e[b] += min;		// �޸�����
	e[a] -= min;
	r[a][b] -= min;
	r[b][a] += min;		// ��¼��������, ���ܱ���������ƻ���
}

// �㷨����:
// ���Ѽ���ÿ�����ĸ߶�
// ��Դ����ڽӵ�ȫ������, �����
// �Ӷ���ȡ��һ�����, ����ݵĵ��ƽ�
// ����õ㻹������ (cap[i] == 0), ��߸߶�, �������
// ֱ������Ϊ��, ȥ���ͳ�������
int maxflow(int (*m)[NUM], int n, int s, int t)
{
	int h[NUM];			// �߶Ⱥ���
	int e[NUM];			// �������
	int r[NUM][NUM];	// m[][] �ĸ���
	queue<int> q;
	int i, j, tmp, min;
	short int f = 1;

	memset(e, 0, sizeof(e));
	for (i=0; i<n; i++)			// ���ƶ�һ�� m[][]
		for (j=0; j<n; j++) r[i][j] = m[i][j];
	BFS(m, h, n, t);		// ����ÿ�����ĸ߶�
	e[s] = INF;				// Դ�����޶��ˮ
	h[s]++;					// Դ�����޸�
	// s ���ܻ��и߶���ȵĽ��, ����� 1, �������н������ߵ���
	q.push(s);
	while (!q.empty())		// ��ͨ���д���
	{
		// ȡ��һ�����, �����ƽ�
		tmp = q.front();   q.pop();
		if (f) f = 0;				// ��һ��Դ��������ڽӵ��ƽ�
		else if (tmp == t || tmp == s) continue;	// ����Դ����
		for (i=0; i<n; i++)
		{					// tmp �� i ��, �ſ����ƽ�
			if (r[tmp][i] != 0 && h[tmp] > h[i])
			{
				PUSH(r, e, tmp, i);		// �ƽ� tmp -> i
				if (i != t) q.push(i);
			}	// ��� t û��Ҫ����ӽ����ƽ���, ��Ӻ�߶�Ҳ����͵�, �޷��ƽ�
		}
		// ��� tmp û���ƽ���, Ҫ��߸߶�, ׼���ٴ��ƽ�
		// ���Ÿ߶Ȳ�������, ����Ҫô�Ƶ����, Ҫô�ƻ�Դ��
		if (tmp != s && e[tmp] != 0)	// Դ�����޶��ˮ, �����ٱ����
		{
			min = INF;
			for (i=0; i<n; i++)		// ��һ����͵��ڽӵ�
				if (r[tmp][i] != 0 && h[i] < min)
					min = h[i];
			h[tmp] = min + 1;		// ���һ���߶�
			q.push(tmp);		// �����
		}
	}
	return e[t];	// ��㴦�����������������
}


// --------------------------------------------------------------------------
// ---------------------- maxflow2() ���ȶ����ƽ� ---------------------------
// --------------------------------------------------------------------------
// maxflow2() ������� maxflow() һ��, ֻ���� maxflow2() ʹ�����ȶ��д���
// ���ս��߶�����, ��͵����˴��ڵ�����ߵĵ�, ���ȱ����ڽӵ��ˮ
// ˮ����ӵʹ�����ߴ�, ���Խ�㱻�ر�ǵļ���С�˺ܶ�
// ʹ�����ȶ��б���ͨ���п�

typedef struct node		// ���ȶ��еĽ��
{
	int i;		// ����
	int h;		// ���߶�
	int e;		// �������
	bool operator < (const node &b) const	// �Ƚ���, ���ȶ���ʹ��
	{ return (h < b.h); }
}node;

// ��Ϊ���˽ṹ����h[], e[], ���ò�����дһ�� BFS()
void BFS2(int (*m)[NUM], node *re, int n, int t)
{
	std::queue<int> q;
	short int used[NUM];
	int cur, i;

	memset(used, 0, sizeof(used));
	re[t].h = 0;		// ���߶����
	q.push(t);
	used[t] = 1;
	while (!q.empty()) {
		cur = q.front();   q.pop();
		for (i=0; i<n; i++) {
			if (!used[i] && m[i][cur] != 0) {
				re[i].h = re[cur].h + 1;
				used[i] = 1;
				q.push(i);
}}}}
// ��дһ�� PUSH(), a �� b �ƽ�
inline void PUSH2(int (*r)[NUM], node *w, int a, int b)
{
	// �����ƽ��� min, s ���������ܵ������Ƚ�
	int min = r[a][b] > w[a].e ? w[a].e : r[a][b];
	w[a].e -= min;
	w[b].e += min;
	r[a][b] -= min;
	r[b][a] += min;		// ��¼��������
}

// ��ʼ maxflow2(), ���n ��, Դ�� s, ��� t
int maxflow2(int (*m)[NUM], int n, int s, int t)
{
	priority_queue<node *> q;		// ���ȶ���
	int r[NUM][NUM];			// m[][] �ĸ���
	node w[NUM];		// ��¼���߶�, ����, Ҳ�����ýṹ����˸���
	node *tmp;
	int i, j;
	short int f = 1;
	int min;

	for (i=0; i<n; i++)		// ���ƶ�һ�� m[][]
	{
		for (j=0; j<n; j++) r[i][j] = m[i][j];
		w[i].i = i;   w[i].e = 0;
	}
	BFS2(r, w, n, t);		// ������߶�
	w[s].e = INF;			// Դ�����޶��ˮ
	w[s].h++;				// Դ�����޸�, ��� 1, ��Ϊ��ߵ�
	q.push(&w[s]);
	while (!q.empty())
	{
		tmp = q.top();   q.pop();
		if (f) f = 0;			// ��һ������Դ������Χ�ƽ�
		else if (tmp->i == t || tmp->i == s) continue;
		for (i=0; i<n; i++)		// ���ڽӵ��ƽ�
		{						// �� i ���
			if (r[tmp->i][i] != 0 && tmp->h > w[i].h)
			{
				PUSH2(r, w, tmp->i, i);
				q.push(&w[i]);
			}
		}
		if (tmp->i != s && tmp->e != 0)	// ����Դ��, �һ�������, ���ر��
		{
			// ��һ����͵��ڽӵ�
			min = INF;
			for (i=0; i<n; i++)
				if (r[tmp->i][i] != 0 && w[i].h < min) 
					min = w[i].h;
			tmp->h = min + 1;
			q.push(tmp);	// �ٴ����
		}
	}
	return w[t].e;
}

int main(void)
{
	int n;
	int matrix[NUM][NUM];		// �ڽӾ���
	int a, b, c, d, e;

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
	d = maxflow(matrix, n, a, b);		// ��ͨ���д���
	e = maxflow2(matrix, n, a, b);		// ���ȶ��д���
	printf("\n�����: %d\n�����: %d\n", d, e);
	return 0;
}
