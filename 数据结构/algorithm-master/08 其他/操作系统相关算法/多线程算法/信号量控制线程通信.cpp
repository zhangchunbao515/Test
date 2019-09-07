
// �߳� A ��������������, ���������ֻ�ܷ�һ������
// �߳� B ȥ������ȡ����, �� A ����֮�����ȡ
// A �������ݺ�, B ����ȡ
// ���� A ������, Ȼ��֪ͨ B ȥȡ, ͬʱ A �߳�����, �ȴ� B ���ź�
// B ����ȡ����, ȡ���, ���� A, ͬʱ B ����

#include <stdio.h>
#include <windows.h>

int share;		// ������
HANDLE put;		// �����ݵ��ź���
HANDLE get;		// ȡ���ݵ��ź���

// ������, ѭ���� 0 - 9 ʮ������
DWORD WINAPI producter(void *id)
{
	int data = 0;

	while (1)
	{
		WaitForSingleObject(put, INFINITE);		// ���Է�����
		share = data;
		data = (data + 1) % 10;
		ReleaseSemaphore(get, 1, NULL);			// ֪ͨ B ȡ����
	}
	return 0;
}

DWORD WINAPI customer(void *id)		// ȡ����
{
	while (1)
	{
		WaitForSingleObject(get, INFINITE);		// ����ȡ����
		printf("%d, ", share);
		if (share == 9) printf("\n");
		ReleaseSemaphore(put, 1, NULL);		// ȡ��, ֪ͨ A ������
	}
	return 0;
}

int main(void)
{
	HANDLE a, b;

	put = CreateSemaphore(NULL, 1, 2, NULL);
	get = CreateSemaphore(NULL, 0, 2, NULL);
	a = CreateThread(NULL, 0, producter, NULL, 0, NULL);
	b = CreateThread(NULL, 0, customer, NULL, 0, NULL);

	Sleep(50);

	CloseHandle(a);
	CloseHandle(b);
	CloseHandle(put);
	CloseHandle(get);
	return 0;
}