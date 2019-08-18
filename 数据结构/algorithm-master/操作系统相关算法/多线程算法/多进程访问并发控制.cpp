
// �������ж��������, �۲첢������
// ������ÿ��ֻ����һ��ʵ������, ����ж��ͬʱ���н�������
// ֱ����һ�������е��˳�, ������һ��ʵ���ֿ�������

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// ��ʾ�ȴ���Ϣ
DWORD WINAPI msg(void *id)
{
	int time = *(DWORD *)id;
	int i;

	system("cls");
	for (i=time/1000-1; i>=0; i--)
	{
		printf("\r�ȴ������� %02d ��", i);
		Sleep(1000);
	}
	return 0;
}

int main(void)
{
	HANDLE mutex;			// �ź���
	char name[] = "cpp1";	// �ź�������
	int num = 1;			// ��������������
	DWORD time = 30000;		// ���ȴ�ʱ��, 30 ��
	DWORD flag;
	HANDLE tip;

	// ���Դ�һ�� "cpp1" ���ź���
	mutex = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, name);
	if (mutex == NULL)		// ��һ������, ��ʧ��
	{
		mutex = CreateSemaphore(NULL, num, 1000, name);
		if (mutex == NULL) return 0;		// ����ʧ��
	}
	// ��ʾ��Ϣ���߳� tip
	tip = CreateThread(NULL, 0, msg, (void *)(&time), 0, NULL);
	Sleep(5);			// �������߳�һ��ʱ��
	flag = WaitForSingleObject(mutex, time);		// ���Խ���
	if (flag == WAIT_OBJECT_0)
	{
		// ����ɹ�, ɱ����Ϣ��ʾ�̲߳�����
		TerminateThread(tip, 0);
		CloseHandle(tip);
		system("cls");
		printf("\n����������ռ���ٽ���,,,\n");
		printf("\n��������˳�...\n");
		getchar();
		ReleaseSemaphore(mutex, 1, NULL);
	}
	else if (flag == WAIT_TIMEOUT)
	{
		printf("\n\n�ȴ���ʱ, ������...\n");
		CloseHandle(tip);
		getchar();
	}
	CloseHandle(mutex);

	return 0;
}
/*
OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, name)
����һ:
SEMAPHORE_ALL_ACCESS	���ź�����ȫ����, P, V �����Կ�
SEMAPHORE_MODIFY_STATE  ����ʹ��ReleaseSemaphore(), ֻ���� V ����
������:
true		�����ӽ��̼̳и��ź���
false		������̳�
������:
name		Ҫ���ź���������, ��ʧ�ܷ��� NULL


DWORD WaitForSingleObject() ����ֵ
WAIT_OBJECT_0		�õ��ź���
WAIT_TIMEOUT		�ȴ���ʱ
WAIT_FAILED			���ִ���
*/