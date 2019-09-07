#include <stdio.h>
#include <windows.h>

// �ź������˾�� - ��ƱԱ����
// ��ƱԱ�뿪��, �����˾����ͣ���ź�, stop_car
// ˾���뿪��, �������ƱԱ�����ź�, close_door
// ��ʼ: stop_car = 0, close_door = 0

HANDLE stop_car;
HANDLE close_door;

DWORD WINAPI driver(void *id)		// ˾��
{
	while (1)
	{
		printf("---> ˾��: ͣ��\n");
		ReleaseSemaphore(stop_car, 1, NULL);		// ����ͣ���ź�
		WaitForSingleObject(close_door, INFINITE);	// �ȴ������ź�
		printf("˾��: ����\n");
	}
	return 0;
}

DWORD WINAPI seller(void *id)		// ��ƱԱ
{
	while (1)
	{
		WaitForSingleObject(stop_car, INFINITE);	// �ȴ�ͣ���ź�
		printf("��ƱԱ: ����\n");
		printf("��ƱԱ: ��Ʊ\n");
		printf("��ƱԱ: ����\n");
		ReleaseSemaphore(close_door, 1, NULL);		// ���������ź�
	}
	return 0;
}

int main(void)
{
	HANDLE d, s;

	stop_car = CreateSemaphore(NULL, 0, 2, NULL);
	close_door = CreateSemaphore(NULL, 0, 2, NULL);
	d = CreateThread(NULL, 0, driver, NULL, 0, NULL);
	s = CreateThread(NULL, 0, seller, NULL, 0, NULL);

	Sleep(1000);
	CloseHandle(stop_car);
	CloseHandle(close_door);
	CloseHandle(d);
	CloseHandle(s);

	return 0;
}