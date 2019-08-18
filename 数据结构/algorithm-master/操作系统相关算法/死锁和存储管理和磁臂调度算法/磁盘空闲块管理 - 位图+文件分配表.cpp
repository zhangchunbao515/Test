
// ���̿��п����, λͼ��
// �ļ�����ռ䲻����, ���ļ���������ÿ���ļ��Ŀ��
// �������˷ֿ�, ���Բ�������ⲿ��Ƭ, ������Ҫ�ڴ����
// ���̿��С 1 KB, ������ 256 KB ���̿ռ�
// ����Ҫ 256 ��λͼ����ʾ

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NUM  256		// λ���� (number)
#define UNIT_SIZE 1024	// ��Ԫ��С (unit size)
#define USING 1			// ռ��
#define FREE  0			// ����
#define NO -1

char map[NUM];			// λͼ
int free_bit = NUM;		// ���ÿ���

struct			// Ŀ¼
{
	char name[100];		// �ļ���
	int start;			// �ļ���������ʼ��ַ
}recond[100];
int top = 0;

int next[NUM + 10];		// �ļ������, ��ʵ���Ǿ�̬����
// ����ʽ�е�λͼ����, Ҫ��ռ���������
// ���ļ��ڴ����ϵĴ�����Բ�����, ������Ҫ�ļ������������
// �ļ���������ڴ���


// ����һ����СΪ size �ֽڵ��ļ�
// �����ļ��������׵�ַ
int find_free_memory(int size)
{
	int count = size / UNIT_SIZE + !!(size % UNIT_SIZE);
	// ���� count �����̿�
	int i;
	int start = 0;
	int pre;
	int f = 1;

	if (count > free_bit) return NO;	// �ռ䲻����
	else free_bit -= count;		// ��ȥ����Ŀ���
	for (i=0; i<NUM; i++)
	{
		if (map[i] == FREE)
		{
			if (f)		// ������״�
			{
				f = 0;
				start = i;		// ��ʼ���
				pre = i;
			}
			else
			{
				next[pre] = i;		// ���ӷ����
				pre = i;		// pre ȥ����һ�����
			}
			map[i] = USING;
			if (count - 1 != 0) count--;
			else
			{
				next[pre] = NO;
				break;
			}
		}
	}
	return start;
}

// ɾ����Ϊ str ���ļ�
int free_memory(char *str)
{
	int i;
	int pre;
	int cur;

	for (i=0; i<top; i++)
	{
		if (!strcmp(str, recond[i].name))
		{
			cur = recond[i].start;
			while (cur != NO)
			{
				map[cur] = FREE;		// λͼ�ͷ�
				free_bit++;
				pre = cur;
				cur = next[cur];
				next[pre] = NO;		// �������������
			}
			recond[i] = recond[top - 1];	// �滻ɾ��
			top--;
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	char display();		// ��ʾ
	void a();		// �����ļ�
	void b();		// ɾ���ļ�
	void c();		// �鿴�ļ������
	void d();		// �鿴λͼ

	memset(next, -1, sizeof(next));		// ��ʼ�������
	memset(map, FREE, sizeof(map));		// ��ʼ��λͼΪ
	while (1)
	{
		switch (display())
		{
		case '1' : a();   break;
		case '2' : b();   break;
		case '3' : c();   break;
		case '4' : d();   break;
		default : return 0;				// �˳�
		}
	}
	return 0;
}

// ------------------------------------------------------------
// ------------------�����ǹ��ڽ�������ô���------------------
// ------------------------------------------------------------
void back()
{
	printf("\n\n�س�����...\n");
	fflush(stdin);
	getchar();
}

char display()		// ��ʾ
{
	char c;

	system("cls");
	printf("\n 1. �����ļ�\n");
	printf("\n 2. ɾ���ļ�\n");
	printf("\n 3. �鿴�ļ������\n");
	printf("\n 4. �鿴λͼ\n");
	printf("\n---������: ");
	fflush(stdin);
	scanf("%c", &c);

	return c;
}

void a()	// �����ļ�
{
	int size;

	system("cls");
	printf("�����ܴ�С: %d �ֽ�, ���ô�С: %d �ֽ�\n", 
		NUM * UNIT_SIZE, free_bit * UNIT_SIZE);
	printf("\n�����ļ���: ");
	scanf("%s", recond[top].name);
	printf("\n�ļ���С(�ֽ�): ");
	scanf("%d", &size);
	recond[top].start = find_free_memory(size);
	if (recond[top].start != NO) printf("\n�����ɹ�");
	else printf("\n����ʧ��, ���̿ռ䲻��");
	top++;
	back();
}

void b()	// ɾ���ļ�
{
	char buf[100];
	int i;

	system("cls");
	if (top)
	{
		printf("\n�ļ�: \n");
		for (i=0; i<top; i++)
			printf("%s\n", recond[i].name);
	}
	printf("\n�����ɾ�����ļ���: ");
	fflush(stdin);
	scanf("%s", buf);
	if (free_memory(buf)) printf("\n�ɹ�ɾ�� %s", buf);
	else printf("\nδ�ҵ� %s", buf);
	back();
}

void c()	// �鿴�ļ������
{
	int i;
	int cur;

	system("cls");
	printf("\n%-16s%-10s%-10s\n", "�ļ���", "��ʼ���", "ռ�п��");
	for (i=0; i<top; i++)
	{
		printf("%-16s ", recond[i].name, recond[i].start);
		cur = recond[i].start;
		while (cur != NO)
		{
			printf("%d, ", cur);
			cur = next[cur];
		}
		putchar('\n');
	}
	back();
}

void d()		// �鿴λͼ
{
	int i;

	system("cls");
	printf("0 ��ʾռ��, 1 ��ʾ����\n");
	for (i=0; i<NUM; i++)
	{
		if (i % 16 == 0) printf("\n");
		printf("%3d", map[i]);
	}
	back();
}
