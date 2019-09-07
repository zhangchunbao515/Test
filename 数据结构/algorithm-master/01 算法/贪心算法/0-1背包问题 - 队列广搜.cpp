
// 0-1�������� - ���й���, �ֳƷ�֧���޷�, ��dijskra���й����㷨һ��
// ��֧���޷�����ݷ�������:
// ���ݷ������������������Ľ�, ��N�ʺ��ȫ���Ϸ�����
// ��֧���޷�����һ�����������Ľ�, ��N�ʺ��һ���Ϸ�����
// 0-1��������ĺϷ���ֻ��һ��, ������ֵ, �������ַ����Կ�

#include <cstdio>
#include <queue>

using namespace std;

#define NUM 100		// ��󱳰���

typedef struct node		// ���ȶ��н��, ����ֵ����
{
	int v;		// value
	int w;		// weight
	int i;		// �� i ����Ʒ
	bool operator < (const node &n) const	// ������
	{ return (v < n.v); }
}node;

// ���ü�ֵ�������, ��ͷ�ǵ�ǰ�������ļ�ֵ
// �ӵ� 1 ����Ʒ��ʼ, �û���, ֱ������Ϊ��
// ����ǰ����������������, ���м�֦
// ���Զ��н��Ӧ��������Ԫ��, (��ֵ, ����, �� i ��)
int BFS(int c, int n, int *w, int *v)
{
	priority_queue<node> q;		// stl ���ȶ���
	int max_v = 0;
	node tmp;
	
	tmp.v = 0;		// һ�����õĸ����, ���ڽ���ѭ��
	tmp.w = 0;
	tmp.i = -1;
	q.push(tmp);
	while (!q.empty())
	{
		tmp = q.top();   q.pop();
		if (tmp.v > max_v) max_v = tmp.v;		// ��¼���ֵ
		tmp.i++;				// ȥ����һ����Ʒ
		if (tmp.i < n)			// ���������Ʒ
		{
			q.push(tmp);		// ����, �Һ������
			// ���û����������, ������, �������
			if (tmp.w + w[tmp.i] <= c)
			{
				tmp.w += w[tmp.i];
				tmp.v += v[tmp.i];
				q.push(tmp);
			}
		}
	}
	return max_v;
}

int main(void)
{
	int weight[NUM];	// ����
	int value[NUM];		// ��ֵ
	int n, c;
	int max_value = 0;
	int i;

	printf("���뱳�������������Ʒ����: ");
	scanf("%d %d", &c, &n);
	printf("���� %d ����Ʒ: (���� ��ֵ)\n", n);
	for (i=0; i<n; i++)
		scanf("%d %d", weight + i, value + i);
	max_value = BFS(c, n, weight, value);	// ����
	printf("\n����ֵ: %d\n", max_value);
	return 0;
}
