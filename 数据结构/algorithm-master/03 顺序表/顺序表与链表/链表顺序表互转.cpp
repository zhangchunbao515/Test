// ˳���������ת
#include <iostream>
#include <stdlib.h>

typedef int status;
typedef int elemtype;

#define SIZE  10
#define INC   10
#define OK    1
#define ERROR 0

// ˳�����ṹ
typedef struct 
{
	elemtype *base;
	int length;
	int size;
}list;

// ��������ṹ
typedef struct node
{
	elemtype data;
	node *next;
}node;

// --------˳�����---------
status createlist(list *p)
{
	p->base = (elemtype *)malloc(SIZE*sizeof(elemtype));
	if (!(p->base)) return ERROR;
	p->size = SIZE;
	p->length = 0;

	return OK;
}

status destorylist(list *p)
{
	if (p->base != NULL) free(p->base);  // ������<-------
	else return ERROR;

	p->base = NULL;
	p->length = p->size = 0;

	return OK;
}

status insert(list *p, int pos, elemtype *data)
{
	elemtype *end;
	elemtype *now;
	elemtype *cur;
	elemtype *n;
	int newsize;

	// 1 2 3 , lenth==3
	if (pos >= 1 && pos <= p->length+1)
	{
		// ����û
		if (p->length == p->size)
		{
			newsize = p->size + SIZE;
			n = (elemtype *)malloc(newsize* sizeof(elemtype));
			if (!n) return ERROR;
			p->base = n;
			p->size = newsize;
		}
		// 1 2 3 , pos = 2
		end = p->base + p->length - 1;
		now = p->base + pos - 1;
		for (cur=end; cur>=now; cur--)
		{
			*(cur+1) = *cur;
		}
		*now = *data;
		p->length++;

		return OK;
	}
	else return ERROR;
}

status showlist(list *p)
{
	elemtype *cur;
	elemtype *end;

	if (p->length == 0) return ERROR;
	end = p->base + p->length - 1;
	for (cur=p->base; cur<=end; cur++)
	{
		printf("%d, ", *cur);
	}
	printf("\n");
	return OK;
}

// --------������-----------
// ��ʼ������
status initnode(node *p)
{
	p->next = NULL;
	p->data = 0;

	return OK;
}

status shownode(node *p)
{
	node *cur;

	if (p->next == NULL) return ERROR;
	cur = p->next;
	while (cur)
	{
		printf("%d, ", cur->data);
		cur = cur->next;
	}
	printf("\n");

	return OK;
}

status destorynode(node *p)
{
	node *del;
	
	if (p->next == NULL) return ERROR;
	while (p->next)
	{
		del = p->next;
		p->next = p->next->next;
		free(del);
	}
	p->next = NULL;
	p->data = 0;

	return OK;
}

// ׷�ӵ� cur �ĺ���
status append(node *p, elemtype *data)
{
	node *cur;
	node *n;

	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->data = *data;

	cur = p;
	while (cur->next) cur = cur->next;
	n->next = cur->next;
	cur->next = n;
	p->data++;

	return OK;
}

// --------ת������-----------
// listtonode ����˳�����Ԫ��
// Ȼ�󲻶�׷�ӵ� ������
status listtonode(list *a, node *b)
{
	elemtype *cur;
	elemtype *end;

	// �����״̬
	if (a->base == NULL) return ERROR;
	if (a->length == 0)  return ERROR;
	
	end = a->base + a->length - 1;
	for (cur=a->base; cur<=end; cur++)
	{
		// �� cur ׷�ӵ����� b ��
		if (append(b, cur) == ERROR) break;
	}
	// �����ǲ���ȫ��ת����
	if (cur > end) return OK;
	else return ERROR;
}

// nodetolist ����������Ԫ��
// Ȼ����뵽�� i++ ��λ��
status nodetolist(node *p, list *b)
{
	node *cur;
	int pos = 1;

	// �����ǲ��ǿձ�
	if (p->data == 0) return ERROR;
	// ˳����ڲ���ʱ���Զ���չ��С
	
	cur = p->next;
	while (cur)
	{
		if (insert(b, pos++, &(cur->data)))
		{
			cur = cur->next;
		}
		else break;
	}
	if (cur) return ERROR;
	else return OK;
}

// ---------main--------------
int main(void)
{
	list a;
	node b;
	elemtype data;
	int num = 5;
	int i;
	
	createlist(&a);
	initnode(&b);
	printf("--- ˳���ת����:\n");
	printf("--- ��˳��������� %d ��Ԫ��\n", num);
	for (i=1; i<=num; i++)
	{
		printf("�� %d ����", i);
		scanf("%d", &data);
		insert(&a, i, &data);
	}
	printf("����Ԫ�أ�");
	showlist(&a);
	if (listtonode(&a, &b)) 
	{
		printf("--- �ɹ�תΪ����\n");
		shownode(&b);
	}
	else printf("ת��ʧ�ܣ�\n");
	destorylist(&a);
	destorynode(&b);

	fflush(stdin);
	getchar();
	system("cls");

	//----------------------------------
	createlist(&a);
	initnode(&b);
	printf("--- ����ת˳���:\n");
	printf("������������ %d ��Ԫ��", num);
	for (i=1; i<=num; i++)
	{
		printf("�� %d ����", i);
		scanf("%d", &data);
		append(&b, &data);	// ĩβ׷��
	}
	printf("����Ԫ�أ�");
	shownode(&b);

	if (nodetolist(&b, &a)) 
	{
		printf("--- �ɹ�תΪ˳���\n");
		showlist(&a);
	}
	else printf("ת��ʧ�ܣ�\n");
	destorylist(&a);
	destorynode(&b);

	fflush(stdin);
	getchar();

	return 0;
}
