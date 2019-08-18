#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// n�ʺ����⣨���������
// ��ʵ�������Ϊ n �� n �������ı���
// �����������ƺ����ֵ����ı���
// �������������ײ�ͱ�ʾ�ҵ��Ϸ��Ľ�

static int num = 0;		// ͳ�ƺϷ�����

// �����ͼ
void show(char (*map)[20], int n, int num)
{
	int i, j;

	printf("�� %d ����:\n", num);
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
			printf("%2c", map[i][j]);
		printf("\n");
	}
	printf("\n");
}

// �ж� x�� i�У��ܲ�����
short int OK(char (*map)[20], int n, int x, int i)
{
	int j;
	int tx = x, ti = i;	// �����һ��x,i

	// ���ͬһ�У��оͲ��ü���ˣ���Ϊ����Ҫ�ŵ�ǰ��
	for (j=0; j<x; j++)
	{
		if (map[j][i] == '*')  return 0;
	}
	// �����Խ�
	while ((x+1) && (i+1))
	{
		if (map[x][i] == '*')  return 0;
		x--;   i--;
	}
	// ����ҶԽ�
	while ((tx+1) && (ti+1))
	{
		if (map[tx][ti] == '*')  return 0;
		tx--;   ti++;
	}
	return 1;
}

// �������
// �������� n ���ʱ����Ȼ�ҵ�����
int DFS(char (*map)[20], int n, int x)
{
	int i;

	// ������̷�����(�ҵ���)���������
	if (n == x)  show(map, n, ++num);
	else 
	{
		// ���û���������������
		for (i=0; i<n; i++)   // ̽�⵱ǰx�У��������ĺ����ֵܷ��ı���
		{
			if (OK(map, n, x, i))   // ������Է�
			{
				map[x][i] = '*';	// ����ʱ�����
				DFS(map, n, x+1);	// �����ݹ�����
				map[x][i] = '.';	// ����ʱ����ͼ
			}
		}
	}
	return num;
}

// N�ʺ�, �����������ĺϷ�������
int Nqueen(int n)
{
	char map[20][20];

	memset(map, '.', sizeof(map));	// ��ʼ����ͼ
	num = 0;
	return DFS(map, n, 0);		// ��ʼ����
}

int main(void)
{
	int n;
	int num;
	
	while (1)
	{
		printf("������ʺ�����");
		scanf("%d", &n);
		system("cls");
		
		num = Nqueen(n);  // ���������
		
		printf("���ҵ� %d ���Ϸ�������\n\n", num);
	}
	return 0;
}
