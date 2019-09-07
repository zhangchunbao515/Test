#include <stdio.h>
#include <windows.h>

// æ�ȴ��Ļ���, Peterson�㷨
// enter_gion() ����, leave_gion() ����

// æ�ȴ����� �� �ź���������: 
// �ź��������æ�ȴ���� CPU �˷�

// CPU �ָ��˽��� 1 һ��ʱ��Ƭ, ���� 1 һֱ�ڿ��ٽ����ܲ��ܽ���
// ��ѭ���ȴ�, ֱ��ʱ��Ƭ����, CPU �л�����һ������

// ��������ź���, CPU �ָ����� 1 һ��ʱ��Ƭ,
// ���� 1 ͬ��ȥ���ٽ����ܲ��ܷ���, 
// ������ܸý������ϱ�����������������, CPU �����л�����Ľ���
// �� ʱ��Ƭû�б���ȫ����, ֻ�����˿���һ���ٽ�����ʱ�����

// ��æ�ȴ�Ҫ������ȫ��ʱ��Ƭ, �ź����ᱻ�����������ж���

#define NUM 10			// ����߳�����
int want_to_join;
int interests[NUM];

// �� pro ���̼߳���
void enter_gion(int pro)
{
	int other = 1 - pro;

	want_to_join = pro;
	interests[pro] = 1;		// �����
	while (pro == want_to_join && interests[other] == 1);
	// ����������, ����Ҳ�����, ���ȵȴ�, ����һ���߳̽���
	// ��ʱ want_to_join �Ѿ����ĳ�����, ������һ���߳̿��Դ�ѭ�����˳�
}

void leave_gion(int pos)
{
	interests[pos] = 0;
}

DWORD WINAPI func1(void *para)
{
	int i;

	enter_gion(0);		// ���Խ����ٽ���
						// �ٽ���
	for (i=0; i<50; i++) printf("t1 = %d\n", i);
	leave_gion(0);		// �뿪�ٽ���

	return 0;
}

DWORD WINAPI func2(void *para)
{
	int i;

	enter_gion(1);
	for (i=0; i<50; i++) printf("  t2 = %d\n", i);
	leave_gion(1);

	return 0;
}

int main(void)
{
	HANDLE t1, t2;

	t1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	t2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);
	Sleep(500);
	CloseHandle(t1);
	CloseHandle(t2);

	// Sleep(500) ��Ϊ����main���̲���������, ���߳���ʱ��������
	return 0;
}
