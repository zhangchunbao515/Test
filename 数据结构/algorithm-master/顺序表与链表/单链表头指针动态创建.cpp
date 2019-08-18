#include <malloc.h>
#include <stdio.h>

typedef int elemtype;
typedef int status;

#define OK 1
#define ERROR 0

typedef struct node
{
	elemtype data;
	node *next;
}node;

node *createlist(node *p, int n)
{
	node *newbase = NULL;

	p = (node *)malloc(sizeof(node));
	p->next = NULL;
	p->data = 0;
	// ͷ��㽨��
	if (!p) return ERROR;
	while (n--)
	{
		newbase = (node *)malloc(sizeof(node));
		if (!newbase) return ERROR;
		newbase->next = p->next;
		p->next = newbase;
		newbase = NULL;
	}
	return p; // p �����ŵ�ַ��Ҫ����ȥ��
}

status remove(node *p)
{
	node *cur;
	node *del;

	// cur -> [1] -> [2] -> [3]
	cur = p;
	while (cur->next)   // ��cur����һ����Ϊ��
	{
		del = cur->next;
		cur->next = del->next;
		free(del);
	}
	return OK;
}

void show(node *p)
{
	node *cur;

	cur = p->next;
	while (cur)
	{
		printf("%-4d", cur->data);
		cur = cur->next;
	}
}

int main(void)
{
	node *list = NULL;
	node *cur;
	elemtype num = 0;

	list = createlist(list, 6);
	cur = list->next;
	while (cur)
	{
		cur->data = num++;
		cur = cur->next;
	}
	show(list);
	remove(list);
	printf("\n");
	return 0;
}