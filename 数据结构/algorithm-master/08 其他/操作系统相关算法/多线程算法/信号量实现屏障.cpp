#include <stdio.h>
#include <windows.h>

// �� 10 ���߳�������, ÿ���߳�һ���ź���
// ֻ������ȫ������, main �̲߳��ܽ���

HANDLE mutex[10];
HANDLE m;			// ���ƹ���������

DWORD WINAPI func(void *id)
{
	int i, p;

	WaitForSingleObject(m, INFINITE);
	p = *((int *)id);
	printf(" %d ���߳���������...\n", p);
	for (i=0; i<100; i++);
	ReleaseSemaphore(mutex[p], 1, NULL);
	ReleaseSemaphore(m, 1, NULL);

	return 0;
}

int main(void)
{
	HANDLE t[10];
	int i;

	m = CreateSemaphore(NULL, 1, 11, NULL);
	for (i=0; i<10; i++)
		mutex[i] = CreateSemaphore(NULL, 0, 1, NULL);
	// 10 ���ź����ĳ�ֵȫ����Ϊ 0, ��ʾ��û������ (û�ź�)
	// ��10 ���߳������Ժ�, �� 10 ���ź�����Ϊ 1 (���ź�)
	// ֻ�� 10 �źŶ�Ϊ 1 ��, ���ܽ��� main �߳�
	// WaitForMultipleObjects() ���ȴ�����ź�

	for (i=0; i<10; i++) 
	{
		t[i] = CreateThread(NULL, 0, func, (void *)(&i), 0, NULL);
		Sleep(2);		// �� CreateThread() ����һ��ʱ��
	}
	// �ȴ� 10 ���ź�, �ռ����˲ŷ���
	WaitForMultipleObjects(10, mutex, true, INFINITE);
	for (i=0; i<10; i++) 
	{
		CloseHandle(t[i]);
		CloseHandle(mutex[i]);
	}
	CloseHandle(m);

	return 0;
}
/*		WaitForMultipleObjects() ˵��
DWORD WaitForMultipleObjects(
DWORD nCount,				// ����Ҫ�ȼ��������
CONST HANDLE *lpHandles,	// ������飬��Ҫ�ȵľ�������������������
BOOL bWaitAll,				// ����� true ���еľ�����ź�ʱ, ������
							// ����� false �κ�һ��������ź�, ������
DWORD dwMilliseconds		// ���õȴ�ʱ��, ��λ ms, ���޵ȴ� INFINITE 
)
*/
