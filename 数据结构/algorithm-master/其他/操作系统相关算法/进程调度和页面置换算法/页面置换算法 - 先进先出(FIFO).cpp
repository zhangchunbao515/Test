
// ����洢�����е�ҳ���û��㷨 - �Ƚ��ȳ� (FIFO)
// �ĸ��Ƚ���, �ĸ�ҳ����ȳ�ȥ
// ����ҳ���� 10 ��, ҳ��ֻ�� 5 ��
// ����������� 10 ��ҳ��, ��ҳ�治��ҳ����, �û�ҳ��

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>

int nopage = 0;

struct 
{
	unsigned exist : 1;		// �ڲ���λ
	unsigned visit : 1;		// ����λ
	unsigned num   : 6;		// ҳ���
}page[10];			// 10 ��ҳ��
int kuang = 5;		//  5 ��ҳ��

std::queue<int> q;		// ʹ�� STL �Ķ���

int FIFO()		// �Ƚ��ȳ��û�
{
	int page_num;	// Ҫ��̭��ҳ���

	page_num = q.front();
	q.pop();
	page[page_num].exist = 0;		// ��̭
	printf("��̭ҳ�� %d, ", page_num);

	return page[page_num].num;		// ���ظ�ҳ��ռ�õ�ҳ���
}

void visit(int p)		// ���Է��� p ��ҳ��
{
	if (page[p].exist == 0)
	{
		printf("δ����, ");
		nopage++;
		// ����ҳ����, ����ȱҳ�ж�
		if (kuang) page[p].num = kuang--;	// ҳ���п���
		else page[p].num = FIFO();		// ҳ������, ��Ҫ��̭һ��
		q.push(p);
	}
	else printf("����  , ");
	page[p].exist = 1;
	page[p].visit = 1;
}

int main(void)
{
	int p;		// ���ʵ�ҳ��
	int i, times = 20;

	srand(time(NULL));
	for (i=0; i<10; i++) page[i].exist = 0;
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
