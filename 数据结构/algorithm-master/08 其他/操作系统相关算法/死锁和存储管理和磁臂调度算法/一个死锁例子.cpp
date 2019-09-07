
// �����򽫲�������
// t1 ռ�� A ��Դ, ���� B ��Դ
// t2 ռ�� B ��Դ, ���� A ��Դ

#include <stdio.h>
#include <windows.h>

HANDLE A, B;

DWORD WINAPI fun1(void *id)		// ռ�� A ��Դ, ���� B ��Դ
{
	WaitForSingleObject(A, INFINITE);
	Sleep(500);
	WaitForSingleObject(B, INFINITE);
	printf("�þ仰�ò������\n");

	return 0;
}

DWORD WINAPI fun2(void *id)		// ռ�� B ��Դ, ���� A ��Դ
{
	WaitForSingleObject(B, INFINITE);
	Sleep(500);
	WaitForSingleObject(A, INFINITE);
	printf("�þ仰�ò������\n");

	return 0;
}

int main(void)
{
	HANDLE t1, t2;

	A = CreateSemaphore(NULL, 1, 2, NULL);
	B = CreateSemaphore(NULL, 1, 2, NULL);
	printf("������...\n");
	t1 = CreateThread(NULL, 0, fun1, NULL, NULL, 0);
	t2 = CreateThread(NULL, 0, fun2, NULL, NULL, 0);
	
	Sleep(5000);		// ���� 5 ��
	CloseHandle(t1);
	CloseHandle(t2);
	CloseHandle(A);
	CloseHandle(B);
	return 0;
}