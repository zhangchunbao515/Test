#include <stdio.h>
#include <windows.h>

// �˴�ʵ������: 
// ���ź�������, ����������̷߳��ʹ�������Դ
// ������뻥����������, ������ֻ����һ������

HANDLE mutex;		// �ź���
int share = 1234;	// ������Դ, �κ��̶߳����Է���

DWORD WINAPI func1(void *id)		// �ú���ȥ�ù���������Դ
{
	WaitForSingleObject(mutex, INFINITE);	// P ����
	printf("\n%d ���߳��ڷ��ʹ�����: %d\n", *(int *)id, share);
	ReleaseSemaphore(mutex, 1, NULL);	// V ���� 

	return 0;
}

int main(void)
{
	HANDLE t[4];
	int i;

	// ����һ���ź���, ��ʼֵ 2, ���ֵ 4, ͬʱ���������̷߳���
	mutex = CreateSemaphore(NULL, 2, 4, NULL);
	if (mutex == NULL) return 0;	// ����ʧ��

	for (i=0; i<4; i++)
		t[i] = CreateThread(NULL, 0, func1, (void *)(&i), 0, NULL);
	Sleep(200);

	CloseHandle(mutex);		// �ͷ���Դ
	for (i=0; i<4; i++) CloseHandle(t[i]);

	return 0;
}
