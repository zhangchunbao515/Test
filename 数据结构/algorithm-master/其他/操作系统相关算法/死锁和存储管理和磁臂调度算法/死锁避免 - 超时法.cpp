
// t1 ���� A, A �����ռ��
// ���� 4 ��, δ�õ�����Դ, �����, ���߼����ȴ���һ�� 4 ��

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HANDLE A, quit;
DWORD times = 4000;
// DWORD �� unsigned long

DWORD WINAPI msg(void *id)		// ��Ϣ��ʾ�߳�
{
	int n = *(int *)id;
	int i;
	
	for (i=n/1000; i>=0; i--)
	{
		printf("\r�ȴ������� %d ��... ", i);
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI fun1(void *id)		// t1 �߳�
{
	DWORD flag;
	HANDLE m;
	
	m = CreateThread(NULL, 0, msg, (void *)&times, 0, NULL);
	Sleep(5);
	flag = WaitForSingleObject(A, times);
	TerminateThread(m, 0);		// ɱ����Ϣ�߳�
	if (flag == WAIT_OBJECT_0)		// �ɹ��õ��ź�
	{
		system("cls");
		printf("\nt1 �õ��ź�\n");
	}
	else if (flag == WAIT_TIMEOUT)
	{
		printf("\n\nt1 �ȴ���ʱ\n");
	}
	CloseHandle(m);			// �ͷ���Ϣ�߳̾��
	ReleaseSemaphore(quit, 1, NULL);	// ���˳��ź�
	return 0;
}

int main(void)
{
	HANDLE t1;
	
	// A ���ź�����ʼΪ 0, ������� 1 ��Ч��
	A = CreateSemaphore(NULL, 0, 2, NULL);
	quit = CreateSemaphore(NULL, 0, 2, NULL);
	t1 = CreateThread(NULL, 0, fun1, NULL, 0, NULL);

	WaitForSingleObject(quit, INFINITE);		// �ȴ��˳��ź�
	CloseHandle(t1);
	CloseHandle(A);

	return 0;
}