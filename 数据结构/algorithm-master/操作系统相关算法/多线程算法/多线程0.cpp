#include <stdio.h>
#include <windows.h>

// ���� 10 ���̲߳��˳�

DWORD WINAPI func(void *i)
{
	printf("�߳� %d\n", *(int *)i);
	return 0;
}

int main(void)
{
	HANDLE t[10];
	int i;

	for (i=0; i<10; i++)
	{
		t[i] = CreateThread(NULL, 0, func, (void *)(&i), 0, NULL);
		Sleep(20);			// ���߳���ʱ��ִ����
	}
	for (i=0; i<10; i++)
		CloseHandle(t[i]);
	return 0;
}