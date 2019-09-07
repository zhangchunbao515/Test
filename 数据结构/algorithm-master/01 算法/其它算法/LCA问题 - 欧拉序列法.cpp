
// LCA ����� RMQ ת��, ��һ���������ѹ�����, ÿ���㶼�ᱻ���ʵ�����
// �����γ���һ��ŷ������, ���������� a, b ��������������� c 
// ��ô�����ѵ�ʱ��, ����˳�����, ���Ҫ�� a ת�� b 
// ��ô�ض��ᾭ��һ�� c �ڵ�, �ٴ� c �ڵ�ת�� b ���ڵ�������
// Ҳ����˵, c �ڵ�������� a �� b �����о����Ľڵ�֮��, �����С��һ��
// ֻ��Ҫ�ڵ�һ�γ��� a �͵�һ�γ��� b ��ŷ������֮��
// ȥ�������С�ĵ�, ��Ϊ�������������, �� RMQ ��������ֵ

#include <stdio.h>
#include <math.h>

#define NUM 500

int tree[2 * NUM];		// ������
int top_t;
int depth[NUM];			// ���
int eular[NUM];			// ŷ������, ����������ʽ���˳��
int top_e;
int first[NUM];			// ��� i ��ŷ���������״γ��ֵ�λ��
int min[300][300];		// RMQ ��¼��Сֵ���±�

// d �ݹ����, ���ŷ������, ���
void init(int d)
{
	int tmp = tree[top_t];

	top_t++;
	first[tmp] = top_e;
	eular[top_e] = tmp;
	depth[top_e++] = d;		// ��¼���

	if (tree[top_t] != -1) 
	{
		init(d + 1);		// ������
		eular[top_e] = tmp;
		depth[top_e++] = d;
	}
	else top_t++;

	if (tree[top_t] != -1) 
	{
		init(d + 1);		// ������
		eular[top_e] = tmp;
		depth[top_e++] = d;
	}
	else top_t++;
}

void init_RMQ(void)		// ��� "RMQ����.cpp"
{
	int i, j;
	int n = top_e-1;
	int k = (int)(log(top_e) / log(2));

	for (i=1; i<=n; i++) min[i][0] = i;
	for (j=1; j <= n-(j<<1)+1; j++)
	{
		for (i=1; i+(j<<1)-1 <= n; i++)
		{
			if (depth[ min[i][j-1] ] < depth[ min[i+(1<<(j-1))][j-1] ])
				min[i][j] = min[i][j-1];
			else 
				min[i][j] = min[i+(1<<(j-1))][j-1];
		}
	}
}

// ���������С��Ԫ�ص��±�
int RMQ(int a, int b)
{
	int k = (int)(log(b-a+1) / log(2));
	// k ������ b-a ������ݳ�

	if (depth[min[a][k]] < depth[min[b-(1<<k)+1][k]])
		return min[a][k];
	else
		return min[b-(1<<k)+1][k];
}

int LCA(int a, int b)		// ת��Ϊ RMQ ����
{
	if (first[a] < first[b])
		return eular[ RMQ(first[a], first[b]) ];
	else
		return eular[ RMQ(first[b], first[a]) ];
}

int main(void)
{
	int a, b;

	// ���ƶ����������뷽ʽ, -1 ��ʾ����, -2 ��ʾ�������
	// ��������: 0 1 3 -1 -1 4 5 -1 -1 6 -1 -1 2 7 -1 -1 8 -1 -1 -2
	printf("����һ����: ");
	top_t = 0;
	while (1)
	{
		scanf("%d", tree + top_t);
		if (tree[top_t] == -2) break;
		top_t++;
	}
	top_e = top_t = 0;
	init(0);			// ��ʼ��ŷ������, ���
	init_RMQ();			// �������, ��ʼ�� min
	printf("LCA ��ѯ:\n");
	while (1)
	{
		scanf("%d %d", &a, &b);
		printf("�����������: %d\n", LCA(a, b));
	}
	return 0;
}