
// ���ⴢ�漼���е�ҳ���û��㷨 - ���δʹ�� (NRU)
// ���㷨����ҳʽ�Ĵ������, ����ʵ�������ַת���������ַ

// ����һ��ҳ�� 1 KB, �ڴ��С 5 KB, ������ռ�ֻ�ܴ�� 5 ��ҳ��
// ����ҳ���ֻ�� 0 - 4 ���, �����ַ�ռ�: 0000 ~ 5119
// ����ĳ������ 10 ��ҳ��, ��Ȼ����һ��ȫ��װ���ڴ�
// �ó�������ҳ�� 0 - 9, �����ַ�ռ� 00000 ~ 10239

// �������Լ��ĵ�ַ�ռ��������, ģ��ȱҳ�����
// ��������������кܶ���תָ��, ��һ��˳��ִ��
// ��������, �������һ�������ַ, ����ҳ��ת�������ַ
// �����ҳ���з����ڴ���û����һҳ, ���û��㷨�����ҳ
// ��������ַ�����Լ��ĵ�ַ�ռ�, ������ʾһ�� "0XFFFFF ���ڴ治��Ϊ read"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SIZE 10240		// �����ַ�ռ��С, 10 KB
#define PSIZE  1024		// ҳ��С 1 KB

// ҳ��, 10 ��ҳ����Ҫ 10 ��ҳ����
// ҳ����Ҳ���ڴ���, �ڽ��̴���ʱ, �ɲ���ϵͳΪ�ý��̴���
struct
{
	unsigned visit  : 1;	// ����λ
	unsigned modify : 1;	// �޸�λ
	unsigned exist  : 1;	// �ڲ���λ
	unsigned num    : 5;	// ҳ���, 5 ��λ��ʾ
}page[10];			// 10 ��ҳ��
int kuang = 5;		// 5  ��ҳ��

HANDLE mutex;		// ����ҳ�����
int nopage = 0;		// ȱҳ����

// ��̭���δʹ��ҳ��, ���ؿ��õ�ҳ���
int NRU()
{
	int i;
	int value;
	int pos, min = 0XFFFFFF;
	
	// ��̭˳��: 0 - 3
	// 0. �޷���, ���޸�, 1. �޷���, ���޸�
	// 2. �з���, ���޸�, 3. �з���, ���޸�
	// value = ����λ * 2 + �޸�λ,  ��Ȩֵ�Ƚ�
	// value ��С����̭
	for (i=0; i<10; i++)
	{
		if (page[i].exist)
		{
			value = page[i].visit * 2 + page[i].modify;
			if (value < min)
			{
				min = value;
				pos = i;
			}
		}
	}
	// ��̭ pos ��ҳ��, ������޸���, ��Ҫд�ش���
	printf("��̭ҳ�� %d, ", pos);
	page[pos].exist = 0;
	return page[pos].num;
}

// �������ַת���������ַ, ������ȱҳ, ��Ҫ�����ҳ
int visit(int vir_add)
{
	int vir_num;	// ҳ���
	int phy_add;	// �����ַ

	if (vir_add < 0 || vir_add > SIZE-1) return -1;	// ��ַԽ��
	// ��ҳ���в�ѯ�����ַ
	vir_num = vir_add / PSIZE;	   // ҳ���, ҳ��ƫ���� vir_add % SIZE
	printf("ҳ�� %d, ", vir_num);
	if (page[vir_num].exist == 0)
	{
		printf("δ����, ");
		// �����ڴ�, ����ȱҳ�ж�, ȥҳ������һ�����õĿռ�
		// ���Ҳ���, ���û������δʹ��ҳ��
		if (kuang) {page[vir_num].num = kuang--;  printf("            ");}
		else   page[vir_num].num = NRU();	// �õ�һ������ҳ��
		page[vir_num].exist = 1;
		nopage++;
	}
	else printf("����  ,             ");
	printf("ҳ�� %d, ", page[vir_num].num);
	page[vir_num].visit = 1;
	phy_add = page[vir_num].num;	// ȡ��ҳ���
	phy_add *= PSIZE;				// ����ҳ���С
	phy_add += vir_add % PSIZE;		// ����ҳ��ƫ��
	return phy_add;
}

// ÿ��һ��ʱ�ӵδ�, ������з���λ
DWORD WINAPI clear(void *id)
{
	int i;
	while (1)
	{
		Sleep(5);		// ÿ�� 5 ms, ���һ�η���λ
		WaitForSingleObject(mutex, INFINITE);
		printf("����λ�������㱻����...\n");
		for (i=0; i<10; i++) page[i].visit = 0;
		ReleaseSemaphore(mutex, 1, NULL);
	}
	return 0;
}

int main(void)
{
	int times = 20;		// ���ʴ���
	int vir_add;		// �����ַ
	int phy_add;		// �����ַ
	int i;
	HANDLE t;

	mutex = CreateSemaphore(NULL, 1, 2, NULL);
	srand(time(NULL));
	for (i=0; i<10; i++)		// ��ʼ��ҳ��
	{
		page[i].visit = 0;
		page[i].modify = 0;
		page[i].exist = 0;
		page[i].num = 0;
	}
	t = CreateThread(NULL, 0, clear, NULL, 0, NULL);
	for (i=0; i<times; i++)
	{
		vir_add = rand() % SIZE;	// �������һ����ַ
		WaitForSingleObject(mutex, INFINITE);
		printf("���� %05d, ", vir_add);
		phy_add = visit(vir_add);
		printf("�����ַ: %04d\n", phy_add);
		ReleaseSemaphore(mutex, 1, NULL);
	}
	SuspendThread(t);		// �Ͻ������߳�
	CloseHandle(t);
	CloseHandle(mutex);
	printf("\n���ʴ��� %d, ȱҳ���� %d\n", times, nopage);
	return 0;
}