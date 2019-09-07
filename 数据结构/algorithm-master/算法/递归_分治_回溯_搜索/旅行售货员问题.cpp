
// �����ۻ�Ա����, һ������ͼ��, ÿ���߶���Ȩֵ
// ÿ���㶼Ҫ����, ��һ����СȨֵ�Ļ�·

#include <stdio.h>

#define INF 0xFFFFFF
#define NUM 30			// ��󶥵���
int map[NUM][NUM];		// �ڽӾ���
int used[NUM];			// ���ʱ��
int pre[NUM];			// ·����Ϣ

int n;					// ������ < NUM
int value;				// ����ֵ
int tmp_pre[NUM];		// ��ʱ����

// ���ݷ�, ����, ���Ĭ���� 0, v �ǵ�ǰ��ֵ, f �����
void DFS(int s, int v, int f)
{
	int i;
	if (f == n-1)		// ����Ҷ��������
	{
		if (v + map[s][0] < value)		// �γɻ�·, ���� s->0 ��Ȩֵ
		{
			value = v + map[s][0];		// ��¼��Сֵ, ��·��
			for (i=0; i<n; i++) 
				pre[i] = tmp_pre[i];
			pre[0] = s;			// �γɻ�·, s->0
		}
		return ;
	}
	used[s] = 1;
	for (i=0; i<n; i++)		// ���� s �ڽӵ�
	{
		// ��֦, ��� v ���������еķ���, ��û��Ҫ����������
		if (!used[i] && map[s][i] != INF && v < value)
		{
			tmp_pre[i] = s;
			DFS(i, v + map[s][i], f+1);
			tmp_pre[i] = -1;		// ���ݲ���	
		}
	}
	used[s] = 0;		// �������
}

void show(int *pre)		// ����ǰ�����·��
{
	int i = 0;
	printf("·��: ");
	do {
		printf("%d -> ", i);
		i = pre[i];
	} while (i != 0);
	printf("0\n");
}

int main(void)
{
	int i, j;
	int a, b, c;

	printf("���붥����, �߼�: ");
	scanf("%d", &n);
	value = INF;
	for (i=0; i<n; i++)		// ��ʼ��, -1 ��ͨ
	{
		for (j=0; j<n; j++) map[i][j] = INF;
		used[i] = 0;   tmp_pre[i] = -1;
	}
	while (1)
	{
		scanf("%d %d %d", &a, &b, &c);
		if (!(a || b || c)) break;
		map[a][b] = c;
		map[b][a] = c;		// ����ͼ
	}
	DFS(0, 0, 0);		// �����Ϊ 0
	printf("\n��С����: %d\n", value);
	show(pre);			// ���·��
	return 0;
}
/*  ��������
4
0 1 30
0 2 6
0 3 4
1 2 5
2 3 20
3 1 10
0 0 0
*/