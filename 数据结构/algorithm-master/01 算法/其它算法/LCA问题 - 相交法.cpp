
// ��һ���������������������������
// ���������������, �������α����ʵĽ��������������

#include <stdio.h>

int tree[1000];		// ��������̬�洢
int add[5000];		// ����ַ
int num[500];		// ������������
int top;
int n;				// �����
int used[500];		// ���ʴ���

// num ��������, pos �������±�, f �����±�
void create(int pos)
{
	if (num[top] == -1)
	{
		top++;
		return ;
	}
	tree[pos] = num[top++];
	add[num[top-1]] = pos;
	create(2 * pos);
	create(2 * pos + 1);
}

int LCA(int a, int b)
{
	int i, pos;

	for (i=0; i<n; i++) used[i] = 0;
	pos = add[a];
	while (pos != 0)		// �� a ������
	{
		used[pos]++;
		pos /= 2;
	}
	pos = add[b];
	while (pos != 0)		// �� b ������
	{
		if (used[pos] == 1)
		{
			i = tree[pos];
			break;
		}
		pos /= 2;
	}
	return i;
}

int main(void)
{
	int a, b;

	// ���ƶ����������뷽ʽ, -1 ��ʾ����, -2 ��ʾ�������
	// ��������: 0 1 3 -1 -1 4 5 -1 -1 6 -1 -1 2 7 -1 -1 8 -1 -1 -2
	printf("����һ����: ");
	top = 0;
	while (1)
	{
		scanf("%d", num + top);
		if (num[top] == -2) break;
		top++;
	}
	n = top;
	top = 0;
	create(1);
	printf("LCA ��ѯ:\n");
	while (1)
	{
		scanf("%d %d", &a, &b);
		printf("�����������: %d\n", LCA(a, b));
	}
	return 0;
}