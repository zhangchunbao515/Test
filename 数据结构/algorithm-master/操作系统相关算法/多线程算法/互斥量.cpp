#include <stdio.h>
#include <windows.h>

// ������ʵ��:
// ���������ź����ļ򻯰�, ���ֻ������һ����������
// ����ͨ������������̷���

HANDLE mutex = NULL;	// ������
int share[10];			// ������Դ


// 1 ���߳�������д 0
DWORD WINAPI func1(void *id)
{
	int i;

	// �ȴ� mutex �ź�
	WaitForSingleObject(mutex, INFINITE);
	printf("\n %d ���߳��ڷ��ʹ�����\n");
	for (i=0; i<10; i++) share[i] = 0;
	for (i=0; i<10; i++) printf("%d, ", share[i]);
	printf("\n");
	ReleaseMutex(mutex);		// �ͷ� mutex 

	return 0;
}

// 2 ���߳�������д 1
DWORD WINAPI func2(void *id)
{
	int i;

	WaitForSingleObject(mutex, INFINITE);
	printf("\n %d ���߳��ڷ��ʹ�����\n");
	for (i=0; i<10; i++) share[i] = 1;
	for (i=0; i<10; i++) printf("%d, ", share[i]);
	printf("\n");
	ReleaseMutex(mutex);

	return 0;
}

int main(void)
{
	HANDLE t1, t2;

	mutex = CreateMutex(NULL, false, NULL);
	// ����˵�� CreateMutex(��ȫ����, ����˭, ������������)
	// NULL ��ȫ����
	// FALSE ��ʾ���������˭��������, Ҳ��������˭������ռ����
	// FALSE ��ʾ�û��������ڼ���̬, �൱���ź����� 1 ֵ
	// NULL ��ʾ���������û������, ��Ϊ���ÿ���̷���, ȡ��ȡ��������ν
	if (mutex == NULL) return 0;

	t1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	t2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	Sleep(400);		// main �߳���Ϣһ��
	CloseHandle(mutex);
	CloseHandle(t1);
	CloseHandle(t2);

	return 0;
}
