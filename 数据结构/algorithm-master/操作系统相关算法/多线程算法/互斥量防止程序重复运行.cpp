#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main(void)
{
	HANDLE mutex;

	// ����һ����Ϊ cpp1 ������
	// ����Ѿ����� cpp1 �Ļ�����, �򴴽�ʧ��
	mutex = CreateMutex(NULL, false, "cpp1");
	if (GetLastError() ==  ERROR_ALREADY_EXISTS)
	{
		printf("\n�����Ѿ���������...\n");
		getch();
		CloseHandle(mutex);
		return 0;
	}
	printf("\n����������...\n");
	getch();
	CloseHandle(mutex);
	return 0;
}
