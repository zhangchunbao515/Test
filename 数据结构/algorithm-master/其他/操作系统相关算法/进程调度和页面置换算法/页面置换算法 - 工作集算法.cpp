
// ����洢�����е�ҳ���û��㷨 - �������㷨
// �ҳ�һ�����ڹ������е�ҳ�沢��̭

// ����ҳ���� 10 ��, ҳ��ֻ�� 5 ��
// ����������� 10 ��ҳ��, ��ҳ�治��ҳ����, �û�ҳ��

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

struct
{
	long int time;			// ʱ��
	struct 
	{
		unsigned exist : 1;		// �ڲ���λ
		unsigned visit : 1;		// ����λ
		unsigned num   : 6;		// ҳ���
	}bit;
}page[10];			// 10 ��ҳ��
int kuang = 5;		//  5 ��ҳ��
int nopage = 0;		// ȱҳ����
const int max_time = 50;		// �������ʱ�� 50 ms

HANDLE mutex;		// ���� page[] ����

// ����ȫ��ҳ��, ���һ��ҳ�汻������, ���������ʱ��
// ���������������ʱ��, ��̭֮
// ���������ʱ��, ��ֹ����̭
// ���û���ҵ���̭��ҳ��, ˵��ȫ��ҳ�涼�ڹ�������
// �Ǿ������̭һ��, �����̭һ��û���޸ĵ�
int working()		// ��̭һ��ҳ��
{
	int min = 0XFFFFF;
	int i, pos = -1;

	for (i=0; i<10; i++)
	{
		if (page[i].bit.visit == 1) page[i].time = clock();
		else
		{
			if (clock() - page[i].time > max_time)
			{ pos = i;   break; }
			else page[i].time = clock();
		}
	}
	if (pos == -1)	// û���ҵ����ʵ�ҳ��, ˵��ȫ��ҳ�涼���ڹ�����
	{
		for (i=0; i<10; i++)		// �����̭һ��
			if (page[i].bit.exist == 1) 
			{ pos = i;   break;}
	}
	printf("��̭ҳ�� %d, ", pos);
	page[pos].bit.visit = page[pos].bit.exist = 0;
	return page[pos].bit.num;
}

void visit(int p)		// ����
{
	if (page[p].bit.exist == 0)
	{
		printf("δ����, ");
		// �����ڴ���, ����ȱҳ�ж�
		nopage++;
		if (kuang) page[p].bit.num = kuang--;
		else page[p].bit.num = working();
	}
	else printf("����, ");
	page[p].bit.exist = 1;
	page[p].bit.visit = 1;
	page[p].time = clock();		// ��¼ʹ��ʱ��
}

// һ��ʱ�ӵδ�, ��ʱ��շ���λ
DWORD WINAPI dida(void *id)
{
	int i;
	
	while (1)
	{
		Sleep(5);
		WaitForSingleObject(mutex, INFINITE);
		printf("��շ���λ...\n");
		for (i=0; i<10; i++) page[i].bit.visit = 0;
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
	for (i=0; i<10; i++) page[i].time = page[i].bit.exist = 0;
	t = CreateThread(NULL, 0, dida, NULL, 0, NULL);
	for (i=0; i<times; i++)
	{
		p = rand() % 10;
		Sleep(1);
		WaitForSingleObject(mutex, INFINITE);
		printf("���� ҳ�� %d, ", p);
		visit(p);
		printf("\n");
		ReleaseSemaphore(mutex, 1, NULL);
	}
	SuspendThread(t);
	CloseHandle(t);
	CloseHandle(mutex);
	printf("\n���ʴ��� %d, ȱҳ���� %d\n", times, nopage);
	return 0;
}