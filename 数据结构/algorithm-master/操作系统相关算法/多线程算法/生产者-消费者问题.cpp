
// ���ź������������, ����������
// �����߳��Խ��빲��۷�����, ��������������, ���ý���
// ������ empty �ź������ƿղ۵�����, ��ֵ empty = N

// ͬ��: ��������Ҫ���빲���������, ������ǿյ�, Ҳ���ý���
// ������ full �ź����������۵�����, ��ֵ full = 0

// �����ߺ������߲���ͬʱ���ʹ����, ������ mutex ���ƹ���۷���

#include <stdio.h>
#include <windows.h>

#define N 10		// �۵Ĵ�С
int buffer[N];		// �����
int pro = 0;		// �����ߵ��±�
int con = 0;		// �����ߵ��±�

HANDLE mutex;		// ���ƹ����/��Ļ����
HANDLE full;		// ��������
HANDLE empty;		// �ղ�����

DWORD WINAPI producer(void *id)		// ������
{
	while (1)
	{
		WaitForSingleObject(empty, INFINITE);	// �����ղ�����, ���Լ�һ
		buffer[pro] = rand() % 100;
		WaitForSingleObject(mutex, INFINITE);
		printf("�����߷��� %d\n", buffer[pro]);
		ReleaseSemaphore(mutex, 1, NULL);
		pro = (pro + 1) % N;
		ReleaseSemaphore(full, 1, NULL);	// ��������һ
	}
	return 0;
}

DWORD WINAPI consumer(void *id)		// ������
{
	while (1)
	{
		WaitForSingleObject(full, INFINITE);	// ������������, ���Լ�һ
		WaitForSingleObject(mutex, INFINITE);
		printf("����������: %d\n", buffer[con]);
		ReleaseSemaphore(mutex, 1, NULL);
		con = (con + 1) % N;
		ReleaseSemaphore(empty, 1, NULL);	// �ղ�����һ
	}
	return 0;
}

int main(void)
{
	HANDLE p, c;	// �����߳�

	// ��������߳� 2 ��
	mutex = CreateSemaphore(NULL, 1, 2, NULL);		// ����������
	empty = CreateSemaphore(NULL, N, 2, NULL);		// �ղۿ���
	full = CreateSemaphore(NULL, 0, 2, NULL);		// ���ۿ���

	// CREATE_SUSPENDED �����Ȳ�����
	p = CreateThread(NULL, 0, producer, NULL, 0, NULL);
	c = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

	Sleep(50);			// main �߳�˯��һ��
	CloseHandle(p);		// �ͷ�
	CloseHandle(c);
	CloseHandle(mutex);
	CloseHandle(empty);
	CloseHandle(full);
/*
	���������̲߳�������
	TerminateThread(handle,0); 
	ExitThread(0);
*/
	return 0;
}
