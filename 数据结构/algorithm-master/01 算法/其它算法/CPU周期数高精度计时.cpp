
#include <stdio.h>
#include <windows.h> 

int main(void)
{
	// typedef __int64 LARGE_INTEGER
    LARGE_INTEGER start, end;             
    LARGE_INTEGER freq;   

	// �̶��߳��� CPU_0 �ϣ���ֹǨ��
	SetThreadAffinityMask(GetCurrentThread(), 0x1);

	// ÿ���� CPU ��������, ��ÿ����ִ�ж�����ָ��
	// һ�����Լִ�� 3 ��ָ��
	QueryPerformanceFrequency(&freq);
 	printf("CPU���� = %I64d\n", freq.QuadPart);

	// CPU ���е����ڵ���������
    QueryPerformanceCounter(&start);
    Sleep(1000);
    QueryPerformanceCounter(&end);

	printf("����ʱ��: %lf\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);

    return 0;   
}