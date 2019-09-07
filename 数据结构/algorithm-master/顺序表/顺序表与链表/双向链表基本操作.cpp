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
	node *prior;
}node;

// ����˫����
status createlist(node *p, int size)
{
	node *n;
	int i;

	p->next = p;
	p->prior = p;
	p->data = 0;	// ��¼����
	for (i=0; i<size; i++)
	{
		n = (node *)malloc(sizeof(node));
		if (!n) return ERROR;

		//  [][p][]   [][2][]
		//       [][n][]
		n->next = p->next;
		n->prior = p;
		p->next->prior = n;
		p->next = n;

		p->data++;
	}
	return OK;
}

// ���µ�I������
status update(node *p, int pos, elemtype *data)
{
	int j;
	node *cur;

	// 1 2 3  lenth == 3
	if (pos>=1 && pos<=p->data)
	{
		cur = p->next;
		j = 1;
		while (j < pos)
		{
			cur = cur->next;
			j++;
		}
		// ��ʱ j == pos
		cur->data = *data;

		return OK;
	}
	else return ERROR;
}

void show(node *p)
{
	node *cur;

	cur = p->next;
	while (cur != p)
	{
		printf(" %d, ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

int lenth(node *p)
{
	node *cur;
	int count = 0;

	cur = p->next;
	while (cur != p)
	{
		count++;
		cur = cur->next;
	}

	return count;
}

status insert(node *p, int pos, elemtype *data)
{
	node *n;
	node *cur;
	int j;

	// 1 2 3  data = 3
	if (pos>=1 && pos<=p->data+1)
	{
		n = (node *)malloc(sizeof(node));
		if (!n) return ERROR;
		cur = p->next;
		j = 1;
		while (j < pos)
		{
			cur = cur->next;
			j++;
		}
		// ���뵽 cur��ǰ��
		n->next = cur;
		n->prior = cur->prior;
		cur->prior->next = n;
		cur->prior = n;

		n->data = *data;
		p->data++;
		return OK;
	}
	else return ERROR;
}

status remove(node *p, int pos)
{
	node *cur;
	int j;

	if (pos>=1 && pos<=p->data)
	{
		cur = p->next;
		j = 1;
		while (j < pos)
		{
			cur = cur->next;
			j++;
		}
		cur->prior->next = cur->next;
		cur->next->prior = cur->prior;
		free(cur);
		p->data--;
		return OK;
	}
	else return ERROR;
}

status getelem(node *p, int pos, elemtype *back)
{
	node *cur;
	int j;

	if (pos>=1 && pos<=p->data)
	{
		cur = p->next;
		j = 1;
		while (j < pos)
		{
			cur = cur->next;
			j++;
		}
		*back = cur->data;
		return OK;
	}
	else return ERROR;
}

status clearlist(node *p)
{
	node *cur;
	
	if (p->data == 0) return ERROR;
	cur = p->next;
	while (cur != p)
	{
		cur->data = 0;
		cur = cur->next;
	}
	return OK;
}

void destory(node *p)
{
	node *cur;

	cur = p->next;
	// [][p][]  [][cur][]  [][2][]
	while (cur != p)
	{
		cur->next->prior = cur->prior;
		cur->prior->next = cur->next;
		free(cur);
		cur = p->next;
	}
}

int main(void)
{
	node list;
	elemtype data;
	int num, i;

	printf("������˫������ĳ�ʼ����:");
	scanf("%d", &num);
	createlist(&list, num);
	for (i=1; i<=num; i++)
	{
		printf("������� %d ��ֵ��", i);
		scanf("%d", &data);
		update(&list, i, &data);
	}
	show(&list);
	printf("�������������ݺ�λ��:");
	scanf("%d%d", &data, &i);
	if (!insert(&list, i, &data)) 
		printf("����ʧ�ܣ�λ�ô���\n");
	show(&list);

	printf("������Ҫɾ����λ��:");
	scanf("%d", &i);
	if (!remove(&list, i)) 
		printf("ɾ��ʧ�ܣ�λ�ô���\n");
	show(&list);

	printf("������Ҫ���ʵ�λ��:");
	scanf("%d", &i);
	if (!getelem(&list, i, &data)) 
		printf("����ʧ�ܣ�λ�ô���\n");
	printf("��Ԫ�أ�%d\n", data);
	
	printf("��������Ԫ�أ�");
	clearlist(&list);
	show(&list);

	destory(&list);

	return 0;
}
