
// ����ʽ�洢�����ʵ�� - ʹ��λͼ�Ĵ洢����
// ������ 320 KB ���ڴ�ռ�����ʵ��, 320 KB = 327680 B
// ʹ��һ���ֽ�������һ����Ԫ�Ƿ�ʹ��
// �赥Ԫ��С 512 B, ��ôλͼ��С�� 320 KB / 512 B = 640 ��λ

// �������ֵ���Ը���ʵ���Զ�
// ��Ԫ��СԽС, ��Ҫ��λͼԽ��, �ѿռ�
// ��Ԫ��СԽ��, ��Ҫ��λͼԽС, ͬʱ�������ڲ���Ƭ��, �˷ѿռ�

// �� main ����Ϊ�ֽ���, main ���µ��ǽ�����޹ؽ�Ҫ�Ĵ���
// ��Ҫ����:
// find_free_memory()		// ���ҿ����ڴ�
// free_memory()			// �ͷ��ڴ�
// collect_memory()			// �ڴ����

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM  640		// λ���� (number)
#define UNIT_SIZE 512	// ��Ԫ��С (unit size)
#define USING 1			// ռ��
#define FREE  0			// ����

char map[NUM];			// λͼ
int free_bit = NUM;

struct re		// ��¼��ʼ��ַ, �ڴ�����, �ͷ��ڴ�ʱ�õ�
{
	unsigned int addr;		// ��ʼ��ַ
	unsigned int number;	// ���䵥Ԫ����
	char name[21];			// ��������
}recond[100];
int top = 0;
// ������洢��������, ��������Ǽ�¼�ֽ�����
// λͼ�����Ǽ�¼��Ԫ����, ��¼λ�ε���ʼ��ַ


// ִ���ڴ����
// ȫ������ʼ��ַ��£, ��:
// ����ǰ: 0 0 1 1 0 1 0 1
// ������: 1 1 1 1 0 0 0 0
// ����ʱ, ͬʱҪ����������������ʼ��ַ, �Ȱ���ʼ��ַ����
// Ȼ��� 0 ��ַ��ʼ, �Ѻ������ǰ��
void collect_memory()
{
	void sort_addr();
	int i;
	int d = 0, s;	// d (destination),  s (start)
	int end;

	sort_addr();		// ��ʼ��ַ����
	for (i=0; i<top; i++)	// һ��һ����ǰ��
	{
		s = recond[i].addr;			// ��ʼ
		end = s + recond[i].number;	// ����
		if (s != d)
		{
			recond[i].addr = d;		// ͬʱ�޸��µ���ʼ��ַ
			while (s < end)			// �ƶ�
			{
				map[d++] = map[s];
				map[s++] = FREE;
			}
		}
		else d = end;		// ����Ҫ�ƶ�
	}
}

// ���ҿ��õ��ڴ�, �����״����䷨
// ���Ҳ������ʵĿռ�, ���� 0, ���򷵻� 1
// Ҳ���������ڴ������, ��Ѱ���ڴ�, ��ʵ���в���ô��, �ڴ�����ܺ�ʱ
int find_free_memory()		// ������Ϣ�� recond[top]
{
	int i, j;
	int size;
	
	for (i=0; i<NUM; i++)
	{
		if (map[i] == FREE)		// �״�����
		{
			// ���������Ŀռ��Ƿ�
			size = recond[top].number + i;
			if (size > NUM) return 0;
			for (j=i; j<size; j++)
			{
				if (map[j] == USING) break;
			}	// ��һ����ռ����, �� break, �� j ��������
			if (j == size)
			{	// j == size ˵���ҵ���
				recond[top].addr = i;
				for (j=i; j<size; j++) map[j] = USING;
				free_bit -= recond[top].number;
				return 1;
			}
			else i = j + 1;
		}
	}
	return 0;
}

// �ͷ���Ϊ str �Ŀռ�, ����ʼ��ַ��ʼȫ��д FREE
int free_memory(char *str)
{
	int i, j;
	int size;

	for (i=0; i<top; i++)
	{
		if (!strcmp(recond[i].name, str))	// �ҵ�
		{
			size = recond[i].number;
			j = recond[i].addr;
			while (size--) map[j++] = FREE;
			free_bit += recond[i].number;
			for (j=i; j<top; j++) recond[j] = recond[j + 1];
			top--;
			return 1;
		}
	}
	return 0;
}

char display();		// ��ʾ
void a();		// �����ڴ�
void b();		// �ͷ��ڴ�
void c();		// �ڴ����
void d();		// �鿴λͼ

int main(void)
{
	memset(map, FREE, sizeof(map));  // ��ʼ��λͼΪ FREE
	while (1)
	{
		switch (display())
		{
		case '1' : a();   break;		// �����ڴ�
		case '2' : b();   break;		// �ͷ��ڴ�
		case '3' : c();   break;		// �ڴ����
		case '4' : d();   break;		// �鿴λͼ
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
	printf("\n 1. �����ڴ�\n");
	printf("\n 2. �ͷ��ڴ�\n");
	printf("\n 3. �ڴ����\n");
	printf("\n 4. �鿴λͼ\n");
	printf("\n---������: ");
	fflush(stdin);
	scanf("%c", &c);

	return c;
}

void a()	// �����ڴ�
{
	unsigned int size;

	system("cls");
	printf("�ڴ��ܴ�С: %d �ֽ�, ���ô�С: %d �ֽ�\n", 
		NUM * UNIT_SIZE, free_bit * UNIT_SIZE);
	printf("\n�����ڴ�Ĵ�С(�ֽ�): ");
	scanf("%d", &size);
	getchar();
	// �����������Ƿ�������, ���Ҳ��Ǳ�ʵ���ص�
	// ������˳�����, ��ϣ����, �ֵ����ȵȲ�������, �жϼ������ظ�Ԫ��
	printf("\n�����ڴ�����ȡ������ (��� 20 ���ַ�): ");
	scanf("%s", recond[top].name);
	recond[top].number = (size / UNIT_SIZE) + !!(size % UNIT_SIZE);
	if (find_free_memory()) printf("\n����ɹ�", top++);
	else printf("\n����ʧ��, �ɳ����ڴ����");
	back();
}

void b()	// �ͷ��ڴ�
{
	char buf[21];
	int i;

	system("cls");
	if (top)
	{
		printf("\n������: \n");
		for (i=0; i<top; i++)
			printf("%s\n", recond[i].name);
	}
	printf("\n������ͷŵı�����: ");
	fflush(stdin);
	scanf("%s", buf);
	if (free_memory(buf)) printf("\n�ɹ��ͷ� %s", buf);
	else printf("\nδ�ҵ� %s", buf);
	back();
}

void c()	// �ڴ����
{
	system("cls");
	printf("\n�����ڴ����...\n");
	collect_memory();
	printf("\n�������, �ɲ鿴λͼ���\n");
	back();
}

void d()		// �鿴λͼ
{
	int i;

	system("cls");
	printf("0 ��ʾռ��, 1 ��ʾ����\n");
	for (i=0; i<NUM; i++)
	{
		if (i % 32 == 0) printf("\n");
		printf("%2d", map[i]);
	}
	back();
}

void sort_addr()	// ����
{
	int i, j;
	char flag;
	struct re tmp;

	for (i=0; i<top; i++)
	{
		flag = 1;
		for (j=0; j<top-1; j++)
		{
			if (recond[j].addr > recond[j+1].addr)
			{
				tmp = recond[j];
				recond[j] = recond[j+1];
				recond[j+1] = tmp;
				flag = 0;
			}
		}
		if (flag) break;
	}
}
