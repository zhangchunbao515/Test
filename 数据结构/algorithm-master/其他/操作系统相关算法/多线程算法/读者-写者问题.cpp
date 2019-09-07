#include <stdio.h>
#include <windows.h>

// �ź����������, д������
// ����������������ͬʱ��ȡ����
// ��ֻ����һ��д���߳�д����
// �ж����ڵ�ʱ��д�߲���д��

HANDLE mutex;		// ���Ƹ������߷����ٽ���
HANDLE m2;			// ����д�߷����ٽ���
int num = 0;		// ��ǰ�����ٽ����Ķ�������
int share = 0;		// �ٽ�����Դ
CRITICAL_SECTION cs;

inline void read_data(int i, int data)
{
	// ����������Ļ�� printf û�б�����, ��ô������ʱ�����
	// �����������Ļ���ܳ�������, 
	EnterCriticalSection(&cs);
	printf(" %d �Ŷ��߶�ȡ�� %d\n", i, data);
	LeaveCriticalSection(&cs);
}

// ��д���϶�ȡ�ٽ�����Դ
DWORD WINAPI reader(void *id)
{
	int i = *(int *)id;
	while (1)
	{
		// ���Խ����ٽ���, ����ǵ�һ������, ����д��
		WaitForSingleObject(mutex, INFINITE);
		num++;
		if (num == 1) WaitForSingleObject(m2, INFINITE);
		// ��һ������, ���� m2, д�߲���д
		ReleaseSemaphore(mutex, 1, NULL);
		// ��ʱд�߲���д��, ��ʼ��ȡ����
		read_data(i, share);

		// �����뿪�ٽ���, ��������һ���뿪, ����д��
		WaitForSingleObject(mutex, INFINITE);
		num--;
		if (num == 0) ReleaseSemaphore(m2, 1, NULL);
		ReleaseSemaphore(mutex, 1, NULL);
		Sleep(5);
	}
	return 0;
}

// д�߲��ϸ�д�ٽ�����Դ
DWORD WINAPI writer(void *id)
{
	int data = 1;

	while (1)
	{
		WaitForSingleObject(m2, INFINITE);
		share = data++;			// д�� data
		printf("д��д���� %d\n", data-1);
		ReleaseSemaphore(m2, 1, NULL);
	}
	return 0;
}

int main(void)
{
	HANDLE r[10];		// 10 ������
	HANDLE w;			// һ��д��
	int i;
	int id[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	// ��ʼ�������ٽ�������, �ź���
	InitializeCriticalSection(&cs);
	mutex = CreateSemaphore(NULL, 1, 10, NULL);
	m2 = CreateSemaphore(NULL, 1, 10, NULL);

	// ��ʼ����
	w = CreateThread(NULL, 0, writer, NULL, 0, NULL);
	for (i=0; i<10; i++)
		r[i] = CreateThread(NULL, 0, reader, id + i, 0, NULL);

	Sleep(100);		// main ��Ϣһ��
	// �ͷž����Դ
	CloseHandle(w);
	for (i=0; i<10; i++) CloseHandle(r[i]);
	CloseHandle(mutex);
	CloseHandle(m2);
	DeleteCriticalSection(&cs);

	return 0;
}
