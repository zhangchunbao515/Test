#include <stdio.h>
#include <windows.h>

DWORD WINAPI func(LPVOID para)
{
	printf("func ���� %d\n", para);
	return 0;
}

int main(void)
{
	HANDLE thread1;

	thread1 = CreateThread(NULL, 0, func, NULL, 0, NULL);
	Sleep(100);
	// main ������˯�� 100 ms, �� thread1 �л���õ�ʱ��Ƭ����
	// ������� Sleep ��õ���ֵĽ��, �����������̶�������
	CloseHandle(thread1);		// �ر��߳�
	printf("main ����\n");

	return 0;
}