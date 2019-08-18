#include <stdio.h>
#include <windows.h>

// �ٽ���ֻ��һ���̷߳���
// �ٽ���ֻ������ͬ���������ڵ��̣߳���������ͬ����������е��߳�
// ԭ�����:
// InitializeCriticalSection();	// �����ٽ���
// DeleteCriticalSection();		// �����ٽ���
// EnterCriticalSection();		// �����ٽ���
// LeaveCriticalSection();		// �뿪�ٽ���
// CRITICAL_SECTION mutex		// ����һ���ٽ�������

int share[10];				// �ٽ�����Դ
CRITICAL_SECTION mutex;		// �ٽ���������Ʒ���

DWORD WINAPI func1(void *id)	// �� share ��д 0
{
	int i;

	EnterCriticalSection(&mutex);		// ���Խ����ٽ���
	printf("\nfunc1 ��д�� 0\n");
	for (i=0; i<10; i++) share[i] = 0;
	for (i=0; i<10; i++) printf("%d, ", share[i]);
	printf("\n");
	LeaveCriticalSection(&mutex);		// �뿪

	return 0;
}

DWORD WINAPI func2(void *id)	// �� share ��д 1
{
	int i;

	EnterCriticalSection(&mutex);
	printf("\nfunc2 ��д�� 1\n");
	for (i=0; i<10; i++) share[i] = 1;
	for (i=0; i<10; i++) printf("%d, ", share[i]);
	printf("\n");
	LeaveCriticalSection(&mutex);

	return 0;
}

int main(void)
{
	HANDLE t1, t2;

	InitializeCriticalSection(&mutex);		// ��ʼ���ٽ����
	t1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	t2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	Sleep(100);		// �����߳�����ʱ��
	// Ҳ���� WaitForMultipleObjects();  �ȴ�����߳��˳����˳�
	
	CloseHandle(t1);
	CloseHandle(t2);
	DeleteCriticalSection(&mutex);		// ɾ���ٽ����

	return 0;
}
