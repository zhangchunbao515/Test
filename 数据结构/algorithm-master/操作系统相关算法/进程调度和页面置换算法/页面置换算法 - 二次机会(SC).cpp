
// ����洢�����е�ҳ���û��㷨 - �ڶ��λ��� (SC)
// �ĸ�ҳ���Ƚ���, �ĸ�ҳ�治һ���ȳ�ȥ, ��Ҫ�ο�����λ, 
// �����������, ������λ��Ϊ 0, ����һ�λ���
// ����ҳ���� 10 ��, ҳ��ֻ�� 5 ��
// ����������� 10 ��ҳ��, ��ҳ�治��ҳ����, �����û��㷨

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <queue>

struct 
{
	unsigned exist : 1;		// �ڲ���λ
	unsigned visit : 1;		// ����λ
	unsigned num   : 6;		// ҳ���
}page[10];			// 10 ��ҳ��
int kuang = 5;		//  5 ��ҳ��

std::queue<int> q;		// ʹ�� STL �Ķ���
int nopage = 0;			// ȱҳ����
HANDLE mutex;			// ����ҳ�����

int FIFO()		// �Ƚ��ȳ��û�
{
	int page_num;	// Ҫ��̭��ҳ���

	while (1)
	{
		page_num = q.front();
		q.pop();
		if (page[page_num].visit == 1)		// �����ʹ�
		{
			page[page_num].visit = 0;		// ����λ��Ϊ 0
			q.push(page_num);			// ������λ���, �ӻض�β
		}
		else { page[page_num].exist = 0;  break;}	// ��̭
	}
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

// ÿ��һ��ʱ�ӵδ�, ������з���λ
DWORD WINAPI clear(void *id)
{
	int i, size, t;
	while (1)
	{
		Sleep(3);		// ÿ�� 3 ms, ���һ�η���λ
		WaitForSingleObject(mutex, INFINITE);
		printf("����λ�������㱻����...\n");
		size = q.size();
		for (i=0; i<size; i++)
		{
			t = q.front();
			q.pop();
			page[t].visit = 0;
			q.push(t);
		}
		ReleaseSemaphore(mutex, 1, NULL);
	}
	return 0;
}

int main(void)
{
	int p;		// ���ʵ�ҳ��
	int i, times = 20;
	HANDLE t;

	mutex = CreateSemaphore(NULL, 1, 2, NULL);
	srand(time(NULL));
	for (i=0; i<10; i++) page[i].exist = 0;
	t = CreateThread(NULL, 0, clear, NULL, 0, NULL);
	for (i=0; i<times; i++)
	{
		p = rand() % 10;
		WaitForSingleObject(mutex, INFINITE);
		printf("���� ҳ�� %d, ", p);
		visit(p);
		printf("\n");
		ReleaseSemaphore(mutex, 1, NULL);
	}
	SuspendThread(t);
	printf("\n���ʴ��� %d, ȱҳ���� %d\n", times, nopage);
	CloseHandle(t);
	CloseHandle(mutex);
	return 0;
}
