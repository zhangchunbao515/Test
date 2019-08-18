#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;
typedef int keytype;

#define OK 1
#define ERROR 0

// ��������ṹ
typedef struct node
{
	elemtype data;
	node *next;
}node;

// ͷ�ṹ
typedef struct
{
	node *first;
	node *last;
	int lenth;
}linklist;


// �����ĩβ���ڱ�����ÿ�β�������ĵ����ڶ�λ
status init(linklist *t)
{
	// ����һ���ռ���ڱ�
	t->first = (node *)malloc(sizeof(node));
	if (!t->first) return ERROR;
	t->first->next = NULL;
	t->last = t->first;
	t->lenth = 1;
	return OK;
}

status destory(linklist *t)
{
	node *cur;
	if (!t) return ERROR;
	
	cur = t->first;
	while (cur != NULL)
	{
		t->first = cur->next;
		free(cur);
		cur = t->first;
	}
	t->first = NULL;
	t->last  = NULL;
	t->lenth = 0;
	return OK;
}

void show(linklist *t)
{
	node *cur;
	if (t)
	{
		cur = t->first;
		while (cur != t->last)
		{
			printf("%d, ", cur->data);
			cur = cur->next;
		}
	}
}

// ÿ��׷�ӵ�����ĵ����ڶ�λ
// ��Ϊ���һλ���ڱ�
status append(linklist *t, elemtype *data)
{
	node *n;

	if (!t) return ERROR;

	// ���ý������룬���ں��棬ǰ�󽻻�
	// �����½��, ������
	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	// n β�巨
	n->next = NULL;
	t->last->data = *data;
	t->last->next = n;
	t->last = n;
	t->lenth++;

	return OK;
}

// ˳����Һ���
// �ҵ�����λ���Ҳ������� 0
int search(linklist *t, elemtype *data)
{
	node *cur;
	int pos = 0;

	if (!t) return ERROR;
	// �����ڱ�
	t->last->data = *data;
	cur = t->first;
	while (cur)
	{
		pos++;
		if (cur->data == *data) return pos;
		cur = cur->next;
	}
	return t->lenth;
}

int main(void)
{
	linklist list;
	elemtype tmp;
	int pos;

	init(&list);
	printf("��������");
	while (scanf("%d", &tmp) != 0)
		append(&list, &tmp);	// ׷�ӵ�ĩβ
	show(&list);
	printf("\n����������ҵ�Ԫ�أ�");
	fflush(stdin);
	scanf("%d", &tmp);
	pos = search(&list, &tmp);		// ˳����Һ���
	if (pos != list.lenth) 
		printf("�ҵ���λ�ã�%d, ���ݣ�%d\n", pos, tmp);
	else printf("δ�ҵ�\n");

	destory(&list);
	return 0;
}
