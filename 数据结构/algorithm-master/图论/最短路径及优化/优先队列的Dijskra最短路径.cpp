
// dijskra ���·��, �����ȶ����Ż�
// δ�Ż� dijskra �㷨, ÿ�ζ�Ҫ�������н��, ��һ����С��·�������ɳ�
// ���� N �����ʱ�� O(N), �൱��ѡ������, ���Ӷ� O(N^2)

// ���ȶ������� O(1) ʱ�������Сֵ, ���ǲ���Ҫ O(log N) ��ʱ��
// �൱�ڶ�����,  O(log N) + O(1) < O(N), �Ż���, ���Ӷ�Ϊ O(N log N)

#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

#define SIZE 30			// ��� 30 ����
#define INF 0xFFFFF
void show(int *pre, int end);		// ���·��

typedef pair<int , int> p;		// ��� (dis[i], i), Ҳ���ýṹ����
struct cmp						// STL �ıȽϺ���, ��ϸ�÷��ٶ�STL
{
	bool operator() (const p a, const p b)
	{ return a.first > b.first; }		// dis[i] С�ķ�ǰ��
};

// ʹ�����ȶ��е� dijskra ���·��, O(n log n)
int short_path_p(int (*m)[SIZE], int n, int start, int end)
{
	int dis[SIZE];		// �� start �����������Сֵ
	int used[SIZE];		// ���ʱ��
	int pre[SIZE];		// ��¼ǰ��
	int i, j;
	priority_queue <p, vector<p>, cmp > q;
	// STL ���ȶ��� priority_queue, ��ϸ�÷��ٶ�STL
	
	for (i=0; i<n; i++) dis[i] = INF;
	for (i=0; i<n; i++) used[i] = 0;
	dis[start] = 0;
	pre[start] = -1;
	q.push(make_pair(dis[start], start));	// �� (dis[start], start) ���
	while (!q.empty())
	{
		// �����ȶ������ø���С��
		p u = q.top();   q.pop();
		if (used[u.second]) continue;
		used[u.second] = 1;
		for (j=0; j<n; j++)		// �� pos �ɳ�������
		{
			if (!used[j] && dis[u.second] + m[u.second][j] < dis[j])
			{
				dis[j] = dis[u.second] + m[u.second][j];
				pre[j] = u.second;
				q.push(make_pair(dis[j], j));	// �� (dis[j], j) ���
				// ���ܻ�����ظ��� (dis[j], j) ���� dis[j] С�Ļ���ǰ��
			}
		}
	}
	printf("\n���");
	show(pre, end);
	return dis[end];
}

// ��ͨ����: dijskra ���·��, O(n^2)
int short_path(int (*m)[SIZE], int n, int start, int end)
{
	int dis[SIZE];		// �� start �����������Сֵ
	int used[SIZE];		// ���ʱ��
	int pre[SIZE];		// ��¼ǰ��
	int i, j, pos;
	int min;

	for (i=0; i<n; i++) dis[i] = INF;
	for (i=0; i<n; i++) used[i] = 0;
	dis[start] = 0;
	pre[start] = -1;
	for (i=0; i<n; i++)		// n ����, ��Ҫ n-1 ����, ѭ�� n-1 ��
	{
		pos = min = INF;
		for (j=0; j<n; j++)		// �������н��, �Ҹ���С��
		{
			if (!used[j] && dis[j] < min)
			{
				min = dis[j];
				pos = j;
			}
		}
		if (pos == INF) return -1;		// ͼ����ͨ
		used[pos] = 1;
		for (j=0; j<n; j++)		// �� pos �ɳ�������
		{
			if (!used[j] && dis[pos] + m[pos][j] < dis[j])
			{
				dis[j] = dis[pos] + m[pos][j];
				pre[j] = pos;
			}
		}
	}
	printf("\n���");
	show(pre, end);
	return dis[end];
}

void show(int *pre, int end)	// �ݹ����, ��·�������÷ǵݹ��
{
	if (end == -1) return ;
	show(pre, pre[end]);
	printf(" -> %d", end);
}

int main(void)
{
	short int kind;			// ͼ������
	int m[SIZE][SIZE];		// �ڽӾ���
	int num;				// �������
	int a, b, c;		// m[a][b] = c
	int s, e;
	int sum;

	printf("����һ��ͼ, 0.����ͼ,  1.����ͼ :");
	scanf("%d", &kind);
	printf("�������: ");
	scanf("%d", &num);
	printf("�������, �յ�:");
	scanf("%d %d", &s, &e);
	for (a=0; a<num; a++)
		for (b=0; b<num; b++) m[a][b] = INF;
	for (a=0; a<num; a++) m[a][a] = 0;
	while (1)
	{
		scanf("%d %d %d", &a, &b, &c);
		if (!(a || b || c)) break;
		m[a][b] = c;
		if (kind) m[b][a] = c;
	}
//	sum = short_path(m, num, s, e);
	sum = short_path_p(m, num, s, e);
	printf("\n��СȨֵ: %d\n", sum);

	return 0;
}
