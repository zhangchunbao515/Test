
// K ������ı�, �ϲ�Ϊһ�������
// ��ÿ����ĵ�ǰԪ�ط������,  ÿ��ɾ����Сֵ�������±���, 
// Ȼ����������Сֵ���ڵı����һ��Ԫ��

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>

// 10 ������Ϊ 100 �������
int table[10][100];
int top[10];
int cur[10];

typedef struct node		// ���
{
	int data;		// ����
	int num;		// ��ı��
	bool operator < (const node &a) const
	{ return data > a.data; }
}node;

int main(void)
{
	void sort(int *num, int left, int right);
	std::priority_queue<node> q;
	node tmp;
	int i, j;

	srand(time(NULL));
	for (i=0; i<10; i++)		// ������� 10 ����
	{
		cur[i] = 0;
		top[i] = rand() % 10 + 1;		// ��������
		for (j=0; j<top[i]; j++)
		{
			table[i][j] = rand() % 1000;
		}
		sort(table[i], 0, top[i]-1);	// ����
	}
	printf("10 �������:\n");
	for (i=0; i<10; i++)
	{
		printf("(%d): ", i+1);
		for (j=0; j<top[i]; j++)
		{
			printf("%d, ", table[i][j]);
		}
		printf("\n");
	}
	printf("\n�ϲ���: ");
	for (i=0; i<10; i++)		// ��Ԫ���
	{
		if (cur[i] < top[i])
		{
			tmp.data = table[i][cur[i]++];
			tmp.num = i;
			q.push(tmp);
		}
	}
	while (!q.empty())
	{
		tmp = q.top();
		q.pop();
		printf("%d, ", tmp.data);
		i = tmp.num;		// ͬʱ�ѱ�� i �ı����
		if (cur[i] < top[i])
		{
			tmp.data = table[i][cur[i]++];
			tmp.num = i;
			q.push(tmp);
		}
	}
	putchar('\n');
	return 0;
}

// ��������
int move(int *num, int left, int right)
{
	int key = num[left];

	while (left < right)
	{
		while (left < right && num[right] >= key) right--;
		num[left] = num[right];
		while (left < right && num[left] <= key) left++;
		num[right] = num[left];
	}
	num[left] = key;
	return left;
}

void sort(int *num, int left, int right)
{
	int m;

	if (left < right)
	{
		m = move(num, left, right);
		sort(num, left, m);
		sort(num,  m + 1, right);
	}
}