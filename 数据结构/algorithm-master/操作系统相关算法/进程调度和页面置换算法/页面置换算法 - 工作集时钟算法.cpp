
// ����洢�����е�ҳ���û��㷨 - ������ʱ���㷨
// ���ڹ������㷨��Ҫɨ��ȫ����ҳ��, �ȽϷ�ʱ
// �����ڹ������㷨�ϸĽ�, ��ɨ��ȫ��ҳ��, 
// ֻɨ�����ڴ��е�ҳ��, ��ҳ��, ����ҳ���γ�һ��ѭ������
// Ԥ�����װ�� 5 ��ҳ��, ���γ�ѭ������ (��̬��)

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
		unsigned modify: 1;		// �޸�λ
		unsigned num   : 5;		// ҳ���
	}bit;
}page[10];			// 10 ��ҳ�� 
int page_num[5];	// 5 ��ҳ��
int top = 0;		// ָ��

int nopage = 0;		// ȱҳ����
const int max_time = 50;		// �������ʱ�� 50 ms

HANDLE mutex;		// ���� count[] ����

// �����������ڴ��е�ҳ��, ��������ʹ���, ����λ��Ϊ 0
// ���û���ʹ�, ������û�г����������ʱ��, �����˾���̭
// ���û����, ������ʱ��, ��ֹ����̭, 
// ���û���ҵ����ʵ�ҳ��������̭һ��
int working()
{
	int min = 0XFFFFF;
	int pos = -1;
	int start;

	start = top;		// ��¼ָ�뵱ǰ��λ��
	while ((top + 1) % 5 != start)		// תһȦ
	{
		if (page[top].bit.visit == 1)
		{
			page[top].time = clock();
			page[top].bit.visit = 0;
		}
		else if (page[top].bit.modify == 0 
				&& clock() - page[top].time > max_time)		// û���޸Ĺ�
		{ pos = top;   break; }
		top = (top + 1) % 5;
	}
	if (pos == -1) pos = top;
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
		page[p].bit.num = working();
	}
	else printf("����, ");
	page[p].time = clock();		// ��¼ʹ��ʱ��
	page[p].bit.exist = 1;
	page[p].bit.visit = 1;
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
	for (i=0; i<10; i++)
	{
		page[i].bit.modify = 0;
		page[i].bit.exist = 0;
		page[i].time = 0;
	}
	for (i=0; i<5; i++)		// Ԥ��װ�� 5 ��ҳ��
	{
		page_num[i] = i;
		page[i].bit.exist = 1;
	}
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