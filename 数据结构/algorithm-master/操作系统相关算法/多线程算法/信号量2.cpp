#include <stdio.h>
#include <windows.h>

// �˴�ʵ������: ��һ���߳�������, main �̱߳�������������ܽ���
// ���ź�����֪ͨ main �̺߳�ʱ����
// ����ʹ�� Sleep() �����ƴ�Լʲôʱ�����

HANDLE mutex;		// �ź���
HANDLE quit;		// main �����ź�

DWORD WINAPI func1(void *id)
{
	int i;

	WaitForSingleObject(mutex, INFINITE);	// P ����
	printf("�߳�������, ���Ե�...\n");
	for (i=0; i<500000000; i++) ;		// �ղ���
	ReleaseSemaphore(quit, 1, NULL);	// �� quit ��һ, ����main�����˳�
	ReleaseSemaphore(mutex, 1, NULL);	// V ���� 

	return 0;
}

int main(void)
{
	HANDLE t;
	int i;

	mutex = CreateSemaphore(NULL, 1, 1, NULL);
	// quit ��ʼֵΪ 0, ��Ϊ main Ҫ�ȴ������̵߳��ź�
	quit = CreateSemaphore(NULL, 0, 1, NULL);
	if (mutex == NULL || quit == NULL) return 0;

	t = CreateThread(NULL, 0, func1, NULL, 0, NULL);

	CloseHandle(mutex);		// �ͷ���Դ
	CloseHandle(t);

	// ����ʹ�� Sleep() �����̳߳��ִ����
	// main �������߳���Ҫ����, ���Ǳ����������߳̽�����, ���ܽ���
	// �߳̽�����, �� quit ���ź�(V ����), ���� main ���߳̿��Խ���
	WaitForSingleObject(quit, INFINITE);
	CloseHandle(quit);
	return 0;
}
