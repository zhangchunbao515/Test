
// ���� CPU ��ʹ������ 50%, ��˻���Ҫָ��һ�������иó���

// GetTickCount()		// ϵͳ���������ڵĺ�����
// clock()				// �����̵����ڵĺ�����

#include <stdio.h>
#include <time.h>
#include <windows.h>

int main(void)
{
	DWORD st;
	while (1)
	{
		st = clock();
		// ���� 10 ms
		while (clock() - st <= 10);
		// ��Ϣ 10 ms
		Sleep(10);
	}
	return 0;
}