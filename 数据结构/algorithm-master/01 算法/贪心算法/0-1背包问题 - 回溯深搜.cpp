#include <stdio.h>
#include <windows.h>

#define SIZE 200
inline void copy(int *d, int *s, int n);	// ���鸴��

int c, n;			// ������� c, ���� n
int weight[SIZE];	// ����
int value[SIZE];	// ��ֵ
int used[SIZE];		// ��¼������Щ��Ʒ
int best_value = -0XFFFF;

int v = 0;			// �ݹ�ʱ, ��ʱ�ı���
int w = 0;
int u[SIZE];
// Ϊ�˼������ĵݹ�ջ����, ��һЩ������Ϊȫ�ֱ���


// ���ݷ����0-1��������, ����״̬��
// ���ڵ� i ����Ʒ����ѡ���û���, ����������, ����������
// i ��ʾ�������˵� i ����Ʒ, 
void DFS(int i)
{
	if (i == n)		// ����Ҷ��, ������
	{
		if (v > best_value) 
		{
			best_value = v;		// ��¼���ż�ֵ
			copy(used, u, n);	// ��¼������Щ
		}
	}
	else 
	{
		// �ж��ܲ��ܽ���������, �������ܳ�����������
		if (w + weight[i] <= c)
		{
			w += weight[i];		// ����
			v += value[i];
			u[i] = 1;
			DFS(i + 1);			// ������һ����Ʒ
			w -= weight[i];		// ����ʱ, �ָ��ֳ�
			v -= value[i];		// ��Ӱ����һ������
			u[i] = 0;
		}
		DFS(i + 1);		// �������ǲ��õ�, ֱ�ӽ��뼴��
	}
	return ;
}

int main(void)
{
	int i;

	printf("���뱳�������������Ʒ����: ");
	scanf("%d %d", &c, &n);
	printf("���� %d ����Ʒ: (���� ��ֵ)\n", n);
	for (i=0; i<n; i++)
		scanf("%d %d", weight + i, value + i);
	DFS(0);			// ����
	printf("\nѡ��: ");
	// ͬʱ�����ѡ��Ʒ
	for (i=0; i<n; i++)
	{
		if (used[i]) printf("(%d, %d), ", weight[i], value[i]);
	}
	printf("\n����ֵ: %d\n", best_value);
	return 0;
}

inline void copy(int *d, int *s, int n)
{
	int i;
	for (i=0; i<n; i++) d[i] = s[i];
}