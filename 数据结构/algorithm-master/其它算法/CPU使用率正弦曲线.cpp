
// �� CPU ʹ���ʳ���������
// ע���ڶ�˻�����, Ҫ�趨һ�� CPU ���иó���

// sin() ����ʹ��˵��, ������ѧ��������� sin ֵ sin(PI/6) = 1/2, sin(PI/2) = 1
// sin(x), x ��Χ�� [0, 2 * PI]
// �� [0, 2 * PI] ��������и�� 200 ��, ÿ�ݶ�Ӧһ����
// ÿ 250 MS ����һ����, 1 �����û� 4 ����
// ��������� CPU ���� 1 ��ˢ��һ��, ���� 200 ���� 50 ��

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <time.h>

const double P = 3.1514926536;
const int    NUM = 200;			// 200 ����
const int    TIMES = 250;		// ʱ��Ƭ 250 ms
const int    F = TIMES / 2;		// ���
const double inc = 2.0 / NUM;	// sin(x) �� x ����

int main(void)
{
	DWORD st;		// ��ʼʱ��
	DWORD busytime[NUM];	// ��æʱ��
	int i;
	double rad;

	// �����߳������ڵ�һ�� CPU ��
	// 0x0001 �������е� 1 ��ʾʹ���ĸ�CPU
	SetThreadAffinityMask(GetCurrentThread(), 0x0001);

	// �����������ߵ� busytime
	for (rad=i=0; i<NUM; i++)
	{
		busytime[i] = (DWORD)(sin(P * rad) * F + F);
		// sin(P * rad) ���� [-1.0, 1.0] �ĸ�����
		// sin(P * rad) * F �����������
		// ������ F �Ͱ� [-1.0, 1.0] �任�� [0, 250] ����
		rad += inc;
	}
	// ѭ����ͼ
	for (i=0; ; i = (i + 1) % NUM)
	{
		st = clock();
		// æʱ
		while (clock() - st <= busytime[i]);
		// ��ʱ, ���������� TIMES
		Sleep(TIMES - busytime[i]);
	}
	return 0;
}