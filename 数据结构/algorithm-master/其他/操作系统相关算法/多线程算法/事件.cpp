#include <stdio.h>
#include <windows.h>

// ʹ���¼���ͬ���߳�
// �¼�����ͬ���ڲ�ͬ�����е��߳�
// ԭ�����
// CreateEvent()			// ����һ���¼�
// WaitForSingleObject()	// �ȴ�һ���ź�
// SetEvent()				// ����Ϊ���ź�
// ResetEvent()				// ����Ϊ���ź�

// ���ź�ʱ, WaitForSingleObject() ���ܷ���, ���ҹر�����ź�

HANDLE mutex;		// ���ƹ���������
int share[10];		// ������

DWORD WINAPI func1(void *id)		// func1 д 0
{
	int i;

	// �ȴ�һ���ź�, ���źŲŷ���
	WaitForSingleObject(mutex, INFINITE);
	printf("\nfunc1 ���ڷ��ʹ�����...\n");
	for (i=0; i<10; i++) share[i] = 0;
	for (i=0; i<10; i++) printf("%d, ", share[i]);
	printf("\n");
	SetEvent(mutex);
	// �źű� WaitForSingleObject ������
	// �� SetEvent ����ʹ�� mutex ���ź�, �൱�� V ����

	return 0;
}

DWORD WINAPI func2(void *id)		// func2 д 1
{
	int i;
	
	WaitForSingleObject(mutex, INFINITE);
	printf("\nfunc2 ���ڷ��ʹ�����...\n");
	for (i=0; i<10; i++) share[i] = 1;
	for (i=0; i<10; i++) printf("%d, ", share[i]);
	printf("\n");
	SetEvent(mutex);

	return 0;
}

int main(void)
{
	HANDLE t1, t2;

	mutex = CreateEvent(NULL, false, true, NULL);
	// CreateEvent ��������������

	t1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	t2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	Sleep(100);
	CloseHandle(t1);
	CloseHandle(t2);
	CloseHandle(mutex);
	return 0;
}

/*  CreateEvent(NULL, true, false, NULL)
��һ�� NULL, �ǰ�ȫ����
�ڶ��� false 
�����false, ��ô������ SetEvent() �����¼��ָ������ź�״̬
�����true, ���¼���һ���ȴ��߳��ͷ��Ժ�ϵͳ�Զ����¼�״̬�ָ������ź�״̬
������ true, ��ʾ��ʼʱ���ź�, ˭������ռ����, false �����ź�
���ĸ� NULL, ���¼�������, Ҳ������������ NULL, �������̾�Ҫ�����������
*/
