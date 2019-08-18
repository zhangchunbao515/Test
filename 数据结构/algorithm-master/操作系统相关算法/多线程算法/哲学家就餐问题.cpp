#include <stdio.h>
#include <windows.h>

// ��ѧ�ҾͲ�����
#define MAX 5			// �����ѧ��
#define LEFT  ((i - 1 + MAX) % MAX)
#define RIGHT ((i + 1) % MAX)		// ���ƶ���
#define EATING   0
#define THINKING 1
#define HUNGRY   2
unsigned int status[MAX];
HANDLE s[MAX];		// ÿ����ѧ��һ���ź���
HANDLE mutex;

void test(HANDLE *s, int i)
{
	if (status[i] == HUNGRY 
		&& status[LEFT] != EATING 
		&& status[RIGHT] != EATING)
	{
		printf("%d ����ѧ�����ڳ�...\n", i);
		status[i] = EATING;
		ReleaseSemaphore(*s, 1, NULL);	// ��һ���ź�, ��ʾ�Ե���
	}
}

void take_fork(int i)		// �� i ���ò���
{
	WaitForSingleObject(mutex, INFINITE);
	printf("%d �ų����������\n", i);
	status[i] = HUNGRY;
	test(s + i, i);			// ���Գ�, δ���ܳԵ�
	ReleaseSemaphore(mutex, 1, NULL);

	// ����Ե���, s[i] ���ź�, ����ֱ�ӽ���, ���� s[i] ���ź�
	// ���û�Ե�, ������, �ȴ������˳���, �������Լ�
	WaitForSingleObject(s[i], INFINITE);
}

void put_fork(int i)		// �� i �ŷŲ���
{
	WaitForSingleObject(mutex, INFINITE);
	status[i] = THINKING;		// ����״̬
	printf("%d �ų���, �������ڽ��ĳ�\n", i);
	test(s + LEFT, LEFT);		// �����ҳԵ��ź�
	test(s + RIGHT, RIGHT);
	ReleaseSemaphore(mutex, 1, NULL);
}

DWORD WINAPI go(void *id)		// �����ѧ���ò���
{
	int i = *(int *)id;

	take_fork(i);
	put_fork(i);
	return 0;
}

int main(void)
{
	HANDLE t[MAX];		// ÿ����ѧ��һ���߳�
	int i;
	int id[5] = {1, 2, 3, 4, 5};
	
	mutex = CreateSemaphore(NULL, 1, MAX, NULL);
	for (i=0; i<MAX; i++)		// �����ź���, ��ʼ�� 0
	{
		s[i] = CreateSemaphore(NULL, 0, MAX, NULL);
		status[i] = THINKING;
	}
	for (i=0; i<MAX; i++)
		t[i] = CreateThread(NULL, 0, go, id + i, 0, NULL);

	Sleep(500);
	for (i=0; i<MAX; i++) CloseHandle(t[i]);
	for (i=0; i<MAX; i++) CloseHandle(s[i]);
	CloseHandle(mutex);

	return 0;
}
