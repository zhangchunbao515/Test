// ������ĵݹ����
#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;

#define OK 1
#define ERROR 0

typedef struct node
{
	elemtype data;
	node *next;
}node;

status create(node *p, int num)
{
	node *n;

	p->next = NULL;
	p->data = num;
	while (num--)
	{
		n = (node *)malloc(sizeof(node));
		if (!n) return ERROR;
		n->next = p->next;
		p->next = n;
	}
	return OK;
}

status assign(node *p, int pos, elemtype *data)
{
	int j;
	node *cur;
	
	if (pos > p->data+1) return ERROR;
	cur = p->next;
	j = 1;
	while (j < pos)
	{
		cur = cur->next;
		j++;
	}
	cur->data = *data;
	return OK;
}

void show(node *p)
{
	printf("%d, ", p->data);
}

// ��ͨ����
status tra(node *p, void (*visit)(node *p))
{
	node *cur = p->next;

	while (cur)
	{
		visit(cur);
		cur = cur->next;
	}
	return OK;
}

// �ݹ����
status tra_s(node *p, void (*visit)(node *p))
{
	// ������
	// ����ǿ�ָ�룬��������
	// ������ǿ�ָ�룬����visit����
	// ��һ�����Ҳ�����
	// �����ȷ�����һλ���ٽ���visit����
	if (p)
	{
	//	tra_s(p->next, show);  ������������
		visit(p);
		tra_s(p->next, show);
	}
	return OK;
}

status destory(node *p)
{
	node *cur = p->next;

	while (cur)
	{
		p->next = cur->next;
		free(cur);
		cur = p->next;
	}
	return OK;
}

int main(void)
{
	node n;
	int i;

	create(&n, 10);
	for (i=1; i<=10; i++)
		assign(&n, i, &i);
	tra(&n, show);
	printf("\n\n");

	tra_s(n.next, show);
	printf("\n\n");

	destory(&n);

	return 0;
}
