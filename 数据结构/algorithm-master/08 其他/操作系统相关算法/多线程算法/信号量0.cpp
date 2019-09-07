#include <stdio.h>
#include <windows.h>

// ���ź���ʵ���߳�ͬ��
// �뻥����������: �ź�������ͬʱ�������� n ���߳�����
// ����ֻ����һ���߳�����

// ��Ҫ����:
// CreateSemaphore()			����һ���ź������
// CloseHandle()				�ͷ�һ���ź������
// WaitForSingleObject()		�൱�� P ����, ��������
// ReleaseSemaphore()			�൱�� V ����, �˳�������

HANDLE mutex;		// �ź���
int share[10];		// ������Դ, �κ��̶߳����Է���

DWORD WINAPI func1(void *id)		// �ú����� share ��д 0
{
	int i;

	// WaitForSingleObject() �൱�� P ����, ���Է���
	// INFINITE ��ʾ�ȴ����޳���ʱ��, ��λ�Ǻ���, д����Ҳ��
	// ���������ʱ�仹û�ź�, �߳̾��˳�, �����ȴ�
	// ����������û�б����ʵ�
	WaitForSingleObject(mutex, INFINITE);
	printf("\nfunc1 �ڷ��ʹ�����: \n");
	for (i=0; i<10; i++) share[i] = 0;
	for (i=0; i<10; i++) printf("%d, ", share[i]);
	printf("\n");
	ReleaseSemaphore(mutex, 1, NULL);
	// ReleaseSemaphore() �൱�� V ����, 
	// 1 ��ʾ���ź����� 1, ͬʱ����һ���ڵȴ����߳�

	return 0;
}

DWORD WINAPI func2(void *id)		// �ú����� share ��д 1
{
	int i;

	WaitForSingleObject(mutex, INFINITE);		// P ����
	printf("\nfunc2 �ڷ��ʹ�����: \n");
	for (i=0; i<10; i++) share[i] = 1;
	for (i=0; i<10; i++) printf("%d, ", share[i]);
	printf("\n");
	ReleaseSemaphore(mutex, 1, NULL);		// V ����

	return 0;
}

int main(void)
{
	HANDLE t1, t2;

	// ����һ���ź���,��ȫֵ NULL ��ʼֵ 1, ����߳�ֵ 1, �ź�����: NULL
	mutex = CreateSemaphore(NULL, 1, 1, NULL);
	if (mutex == NULL) return 0;	// ����ʧ��

	t1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	t2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);
	Sleep(100);

	CloseHandle(mutex);		// �ͷ���Դ
	CloseHandle(t1);
	CloseHandle(t2);
	return 0;
}
