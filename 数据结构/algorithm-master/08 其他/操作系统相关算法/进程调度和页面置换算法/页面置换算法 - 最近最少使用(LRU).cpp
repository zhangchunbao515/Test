
// ����洢�����е�ҳ���û��㷨 - �������ʹ�� (LRU)
// ÿ��ҳ��һ��������, ����һ��, ��������һ
// ȱҳ�ж�ʱ, ��̭���ʴ������ٵ�ҳ��
// ����ҳ���� 10 ��, ҳ��ֻ�� 5 ��
// ����������� 10 ��ҳ��, ��ҳ�治��ҳ����, �����û��㷨

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct 
{
	unsigned exist : 1;		// �ڲ���λ
	unsigned visit : 1;		// ����λ
	unsigned num   : 6;		// ҳ���
}page[10];				// 10 ��ҳ��
long int count[10];		// ������
int kuang = 5;			//  5 ��ҳ��

int nopage = 0;			// ȱҳ����

int LRU()
{
	int i, pos;
	int min = 0XFFFFF;

	for (i=0; i<10; i++)
	{
		if (page[i].exist == 1)		// �������ڴ��е�ҳ��
		{
			if (count[i] < min)
			{
				min = count[i];
				pos = i;
			}
		}
	}
	printf("��̭ҳ�� %d, ", pos);
	page[pos].exist = 0;		// ��̭
	count[pos] = 0;				// ����������
	return page[pos].num;
}

void visit(int p)		// ����ҳ��
{
	if (page[p].exist == 0)		// ����
	{
		printf("δ����, ");
		nopage++;
		if (kuang) page[p].num = kuang--;
		else page[p].num = LRU();
	}
	else printf("����  , ");
	page[p].exist = 1;
	page[p].visit = 1;
	count[p]++;		// ������
}

int main(void)
{
	int p;		// ���ʵ�ҳ��
	int i, times = 20;

	srand(time(NULL));
	for (i=0; i<10; i++) count[i] = page[i].exist = 0;
	for (i=0; i<times; i++)
	{
		p = rand() % 10;
		printf("���� ҳ�� %d, ", p);
		visit(p);
		printf("\n");
	}
	printf("\n���ʴ��� %d, ȱҳ���� %d\n", times, nopage);

	return 0;
}
