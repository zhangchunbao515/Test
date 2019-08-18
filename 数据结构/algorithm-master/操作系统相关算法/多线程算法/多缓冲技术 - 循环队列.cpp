
// �໺��, ��������豸������豸֮������ݴ�������
// ���������ݽṹ: ѭ������

// ʵ��1 :
// һ���߳� A ���ٵ��򻺳���ѭ������ 0 - 9 ʮ������
// һ���߳� B �����شӻ�����ȡ����

// ʵ��2 :
// һ���߳� A ���������� 0 - 9 
// һ���߳� B ���ٵض�ȡ����

// ���� TerminateThread(A, 0), ExitThread(0) �÷�

#include <stdio.h>
#include <windows.h>

#define SIZE 50
int queue[SIZE];	// ѭ�����л�����
int front = 0;		// ��ͷ
int rear = 0;		// ��β
// ��������Ȼ���ٽ���Դ, �����ﲻ��Ҫ����
// ��Ϊ�����߳��޸� rear, ��ȡ�߳��޸� front

// ��Ļ���ٽ���Դ, ��Ҫ����, ��ֹ printf ���������ʱ�򱻴��, ���ǲ�������
CRITICAL_SECTION mutex;

// ���ٵ��򻺳������� 0 - 9
DWORD WINAPI high_put(void *id)
{
	int data = 0;
	while (1)
	{
		while ((rear + 1) % SIZE == front);
		// �������������, ѭ���ȴ�
		// ʵ����, I/Oͨ�������л�ȥ�����豸����I/O
		queue[rear] = data;
		rear = (rear + 1) % SIZE;
		data = (data + 1) % 10;		// ѭ���� 0 - 9 ����
	}
	return 0;
}

// �����ض�ȡ����
DWORD WINAPI low_get(void *id)
{
	while (1)
	{
		Sleep(200);		// �����ٶ�
		while (front == rear);
		EnterCriticalSection(&mutex);		// ���� printf
		printf("%d, ", queue[front]);
		if (queue[front] == 9) putchar('\n');
		LeaveCriticalSection(&mutex);
		front = (front + 1) % SIZE;
	}
	return 0;
}

// ���������� 0 - 9
DWORD WINAPI low_put(void *id)
{
	int data = 0;
	while (1)
	{
		Sleep(250);		// �����ٶ�
		while ((rear + 1) % SIZE == front);
		queue[rear] = data;
		rear = (rear + 1) % SIZE;
		data = (data + 1) % 10;		// ѭ���� 0 - 9 ����
	}
	return 0;
}

// ���ٵض�ȡ
DWORD WINAPI high_get(void *id)
{
	while (1)
	{
		while (front == rear);			// ����
		EnterCriticalSection(&mutex);	// ���� printf
		printf("%d, ", queue[front]);
		if (queue[front] == 9) putchar('\n');
		LeaveCriticalSection(&mutex);
		front = (front + 1) % SIZE;
//		ExitThread(0);			// �߳������˳�
	}
	return 0;
}

int main(void)
{
	HANDLE A;		// �����߳�
	HANDLE B;		// �����߳�

	InitializeCriticalSection(&mutex);		// ��ʼ���ٽ���
	front = rear = 0;
	printf("ʵ��һ:\n");
	A = CreateThread(NULL, 0, high_put, NULL, 0, NULL);
	B = CreateThread(NULL, 0, low_get, NULL, 0, NULL);
	Sleep(10000);			// ���� 10 ��
	TerminateThread(A, 0);		// �����߳�ɱ�� A �߳�
	TerminateThread(B, 0);		// �ͷ� A �߳�ռ�õĻ�������Դ(queue)
	CloseHandle(A);
	CloseHandle(B);
	DeleteCriticalSection(&mutex);		// �ͷ��ٽ���

	// ʵ��һ���� TerminateThread() ��ɱ���߳�, �ͷ���Դ
	// �����п������ٽ��������ϵ�ʱ��, �̱߳�ɱ��, �����ٽ������˵ر�����
	// �����߳�Ҫ�����ٽ�����ʱ��, ��������!
	// �������³�ʼ���ٽ���, �����������������

	// TerminateThread() ��Σ����
	// ��һ: �� new, delete �Ȳ����ڴ�ʱ, ϵͳ����һ����, �������ڴ�����
	// ��� A �߳����� new �����ڴ�, ������������, ��û���ü�����
	// B �߳��� TerminateThread(A, 0) �� A ɱ��
	// ��������ĳ����޷����� new, delete �����ڴ�, ��������

	// ����: A �߳��������˶���, �� TerminateThread() ǿ�ƽ�����ʱ��
	// ����Ķ����������ͷ�, ����ڴ�й©

	InitializeCriticalSection(&mutex);		// �ٴγ�ʼ���ٽ���
	front = rear = 0;
	printf("\n\nʵ���:\n");
	A = CreateThread(NULL, 0, low_put, NULL, 0, NULL);
	B = CreateThread(NULL, 0, high_get, NULL, 0, NULL);
	Sleep(10000);			// ���� 10 ��
	TerminateThread(A, 0);
	TerminateThread(B, 0);
	CloseHandle(A);
	CloseHandle(B);
	DeleteCriticalSection(&mutex);

	return 0;
}