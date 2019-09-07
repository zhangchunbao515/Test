#include <stdio.h>
#include <math.h>
#include <string.h>

void show(int (*map)[16], int size)
{
	int i, j;
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			if (map[i][j])
				printf("%3d", map[i][j]);
			else printf("%3c", '*');
		}
		printf("\n\n");
	}
}

static int c = 1;		// ���̱����

// ���̸���, ���(sx, sy),  �����(x, y), ���̴�С size * size
void chess(int (*map)[16], int sx, int sy, int x, int y, int size)
{
	int mid;
	int num;
	
	if (size == 1) return ;	// ����Ϊ 1 ��ֹ�ݹ�
	else 
	{
		num = c++;
		mid = size / 2;
		if (x < sx+mid && y < sy+mid)		// �����Ͻ�
			chess(map, sx, sy, x, y, mid);
		else	// �������Ͻ�, ���Ͻǵ����½��ѱ�Ϳ��
		{
			map[sx+mid-1][sy+mid-1] = num;
			chess(map, sx, sy, sx+mid-1, sy+mid-1, mid);
		}
		if (x < sx+mid && y >= sy+mid)	// �����Ͻ�
			chess(map, sx, sy+mid, x, y, mid);
		else 
		{
			map[sx+mid-1][sy+mid] = num;
			chess(map, sx, sy+mid, mid-1, mid, mid);
		}
		if (x >= sx+mid && y < sy+mid)	// �����½�
			chess(map, sx+mid, sy, x, y, mid);
		else
		{
			map[sx+mid][sy+mid-1] = num;
			chess(map, sx+mid, sy, mid, mid-1, mid);
		}
		if (x >= sx+mid && y >= sy+mid)	// �����½�
			chess(map, sx+mid, sy+mid, x, y, mid);
		else
		{
			map[sx+mid][sy+mid] = num;
			chess(map, sx+mid, sy+mid, sx+mid, sy+mid, mid);
		}
	}
}

int main(void)
{
	int k;
	int map[16][16];
	int x, y;
	int size;

	memset(map, 0, sizeof(map));
	printf("���̸�������, ���̴�С 2^k * 2^k, k = [1..4]\n");
	printf("������ k: ");
	scanf("%d", &k);
	size = (int)pow(2, k);
	printf("���������ⷽ������: ");
	scanf("%d %d", &x, &y);
	chess(map, 0, 0, x, y, size);
	show(map, size);

	return 0;
}