#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ��ʽ��������, ���ƶ��ʹ��Ͱ����

#define NO -1
#define MAX_KEY 10		// �ؼ�����󳤶�
#define SIZE 100		// ������
#define MAX 10			// ���Ĵ�С
// ����ֻʵ��ʮ��������, ������ 10, Ӣ�����Ϊ 26

// �������
typedef struct
{
	char data[MAX_KEY];		// �ؼ���
	int len;		// ����
	int next;		// ��һ�����
}node;

// ������̬����
typedef struct
{
	node link[SIZE];
	int max_len;		// ���
	int size;
}linklist;


// ��ʼ������
void init(linklist *list, int *data, int n)
{
	int i, j = 1;

	list->size = SIZE;   list->max_len = -1;
	for (i=0; i<n; i++)
	{	// ����תΪ�ַ�����
		itoa(data[i], list->link[i].data, 10);
		list->link[i].next = i + 1;
		list->link[i].len = strlen(list->link[i].data);
		if (list->link[i].len > list->max_len) 
			list->max_len = list->link[i].len;
		// max_key ��ȷ�����ж��ٴλ�������
	}
	list->link[i-1].next = NO;
}

// ��������, ��ÿһλ�ַ���������Ͱ����İ취
void base_sort(int *data, int n)
{
	int head = 0;
	linklist list;		// 0 ��Ϊͷ��ַ
	int base[MAX];		// ��
	int rear[MAX];		// β
	int i, j, p;
	int add, f = 1, last;

	init(&list, data, n);	// �� data �����ݸ��Ƶ�����
	for (j=0; j<list.max_len; j++)		// ���� n �η�̯����
	{
		// ��̯
		for (i=0; i<MAX; i++) base[i] = rear[i] = NO;
		p = head;
		while (p != NO)
		{
			if (list.link[p].len != 0) 
			{
				list.link[p].len--;
				add = list.link[p].data[ list.link[p].len ] - '0';
			}
			else add = 0;

			if (base[add] != NO)   // ��������Ĳ���
			{
				list.link[rear[add]].next = p;
				rear[add] = p;
			}
			else base[add] = rear[add] = p;
			p = list.link[p].next;
		}
		// ����, �ǵ� f ÿ�ζ�Ҫ��Ϊ 1
		for (f=1, i=0; i<MAX; i++)
		{
			if (base[i] != NO)
			{
				// ��һ��, ��¼ͷ����ַ base[i]
				// ���ǵ�һ��, �����һ�ε�ĩβ, ������ε�ͷ base[i]
				if (f) {head = base[i];   f = 0;}
				else list.link[last].next = base[i];
				last = rear[i];
			}
		}
		list.link[last].next = NO;
	}
	// �����������д�� data ��
	i = 0;
	while (head != NO)
	{
		data[i++] = atoi(list.link[head].data);
		head = list.link[head].next;
	}
}

int main(void)
{
	int i, n;
	int data[100];

	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", data + i);

	base_sort(data, n);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	return 0;
}
