
// ����洢�����е�ҳ���û��㷨 - �ϻ��㷨
// ���ö����Ƶ�˼��������ҳ���ʹ�ó̶�
// ����ҳ���� 10 ��, ҳ��ֻ�� 5 ��
// ����������� 10 ��ҳ��, ��ҳ�治��ҳ����, �����û��㷨

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

struct 
{
	unsigned exist : 1;		// �ڲ���λ
	unsigned visit : 1;		// ����λ
	unsigned num   : 6;		// ҳ���
}page[10];			// 10 ��ҳ��
int kuang = 5;		//  5 ��ҳ��
int nopage = 0;		// ȱҳ����

unsigned short int count[10];
// �ϻ��㷨����Ҫ 8 ��λ����ʾҳ����ϻ��̶�
// C ������ unsigned short int ��С, ռ 2 ���ֽ� 16 ��λ, ���� 8 ���˷���
// char ��Ȼռ 1 ���ֽ�, �������ǰ����з��������͵�

HANDLE mutex;		// ���� count[] ����

int old()		// ��̭һ��ҳ��
{
	int min = 0XFFFFF;
	int i, pos;

	for (i=0; i<10; i++)
	{
		if (page[i].exist == 1 && count[i] < min)
		{
			min = count[i];
			pos = i;
		}
	}
	printf("��̭ҳ�� %d, ", pos);
	page[pos].visit = page[pos].exist = 0;
	count[pos] = 0;
	return page[pos].num;
}

void visit(int p)		// ����
{
	if (page[p].exist == 0)
	{
		printf("δ����, ");
		// �����ڴ���, ����ȱҳ�ж�
		nopage++;
		if (kuang) page[p].num = kuang--;
		else page[p].num = old();
	}
	else printf("����, ");
	page[p].exist = 1;
	page[p].visit = 1;
	// λ����, �ڰ�λ�ó� 1, 80 H = 1000 0000 B, �ٻ�һ��
//	count[p] = count[p] | 0x80;			// C ����д��
	__asm
	{
		MOV EBX, p
		ADD EBX, EBX			// ˫�ֽ�, ���Ե�ַ����
		MOV AX, [count+EBX]
		OR  AL, 80H				// ��һ��
		MOV [count+EBX], AX
	}
	// ���д��, �� C ����д����Ч
}

// һ��ʱ�ӵδ�, ��������������һλ, �ϻ�
DWORD WINAPI dida(void *id)
{
//	int i;
	while (1)
	{
		Sleep(50);
		WaitForSingleObject(mutex, INFINITE);
		printf("һ��ʱ�ӵδ�...\n");
//		for (i=0; i<10; i++)
//			count[i] = count[i] >> 1;
		__asm			// �û���������������Ч
		{
			MOV ECX, 10
			MOV EBX, 0
LP:			MOV AX, [count+EBX]
			SHR AX, 1				// ����һλ
			MOV [count+EBX], AX
			ADD EBX, 2
			LOOP LP
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
	for (i=0; i<10; i++) count[i] = 0;
	t = CreateThread(NULL, 0, dida, NULL, 0, NULL);
	for (i=0; i<times; i++)
	{
		p = rand() % 10;
		Sleep(1);			// ����һ���ٶ�, ��Ȼû����ʱ�ӵδ���,
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