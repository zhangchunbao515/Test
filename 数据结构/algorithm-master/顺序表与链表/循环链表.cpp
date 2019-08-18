#include <malloc.h>
#include <iostream>
using namespace std;

typedef int elemtype;
typedef int status;

#define OK    1
#define ERROR 0

typedef struct node
{
	elemtype data;
	node *next;
}node;

node *createlist(int n)
{
	node *p;
	node *b;

	p = (node *)malloc(sizeof(node));
	p->next = p;
	// ѭ������ָ���Լ�
	if (p)
	{
		while (n--)
		{
			b = (node *)malloc(sizeof(node));
			if (!b) return ERROR;
			b->next = p->next;
			p->next = b;
		}
	}
	return p;
}

void input(node *p)
{
	elemtype num = 0;
	node *cur;

	// p ��ͷ��㣬
	// p ����һ�����ſ�ʼ��������
	cur = p->next;
	while (cur != p)
	{
		cur->data = num++;
		cur = cur->next;
	}
}

void destory(node *p)
{
	node *del;
	node *cur;

	cur = p->next;
	// [p] -> [1] -> [2]
	while (cur != p)
	{
		del = cur->next;
		cur = del->next;
		free(del);
	}
	free(p);
}

int main(void)
{
	node *list;
	node *cur;
	
	list = createlist(6);
	input(list);
	cur = list->next;
	// [list] -> [1] -> [2]
	while (cur != list)
	{
		printf("%-4d", cur->data);
		cur = cur->next;
	}

	printf("\n");
	destory(list);

	return 0;
}