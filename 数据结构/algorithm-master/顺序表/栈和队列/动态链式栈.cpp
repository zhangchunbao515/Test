#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;

#define OK 1
#define ERROR 0

// ���õ�������ṹ
typedef struct node
{
	elemtype data;
	node *next;
}node;

// ͷ�ṹ
typedef struct sqstack
{
	node *top;
	node *base;
	int lenth;
}sqstack;

status create(sqstack *p)
{
	node *n;

	// ��ʼ��ʱ��ͷ���һ����㣬
	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->next = NULL;

	p->base = p->top = n;
	p->lenth = 0;
	return OK;
}

// ��ջ���ȸ�ֵ��������һ���½�㣬����top��
status push(sqstack *p, elemtype *data)
{
	node *n;

	p->top->data = *data;	// ���� *p->top = *data

	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->next = p->top;		// ���� p->top++;
	p->top = n;
	p->lenth++;

	return OK;
}

// ��ջ��������top��㣬top--, ���ջ
status pop(sqstack *p, elemtype *back)
{
	node *del;

	// �����ǲ��ǿ�ջ
	if (p->top == p->base) return ERROR;
	del = p->top;			// ��ɾ���Ľ��
	p->top = p->top->next;	// �൱�� p->top--
	*back = p->top->data;   // �൱�� *back = *p->top;
	free(del);
	p->lenth--;
	
	return OK;
}

// ���鿴������ջ
status onlyshow(sqstack *p)
{
	node *cur;
	
	if (p->top == p->base) return ERROR; // ��ջ
	cur = p->top->next;
	while (cur)
	{
		printf("--- %d\n", cur->data);
		cur = cur->next;
	}
	return OK;
}

// ����ջ��Ԫ��,����ջ
status getelem(sqstack *p, elemtype *data)
{
	if (p->top == p->base) return ERROR;
	*data = p->top->next->data;
	
	return OK;
}

// �󳤶�
int lenth(sqstack *p)
{
	return p->lenth;
}

// �п�
status emptystack(sqstack *p)
{
	if (p->top == p->base) return ERROR;
	else return OK;
}

// ���ջ, ������д0��������
status clear(sqstack *p)
{
	node *cur;
	
	if (p->top == p->base) return ERROR;
	cur = p->top->next;
	while (cur)
	{
		cur->data = 0;
		cur = cur->next;
	}
	return OK;
}

// ��ͷ����
status destory(sqstack *p)
{
	node *del;

	if (p->base == NULL) return ERROR;
	while (p->top != p->base)
	{
		del = p->top;
		p->top = p->top->next;
		free(del);
	}
	free(p->base);
	return OK;
}

int main(void)
{
	sqstack s; 
	int i, num;
	elemtype data;

	create(&s);

	printf("������Ҫ��ջ��Ԫ�ظ�����");
	scanf("%d", &num);
	for (i=1; i<=num; i++)
	{
		printf("�� %d ����", i);
		scanf("%d", &data);
		push(&s, &data);
	}
	onlyshow(&s);
	i = pop(&s, &data);
	if (i) printf("��ջ��Ԫ�أ�%d\n", data);
	onlyshow(&s);

	printf("������һ����ջԪ�أ�");
	scanf("%d", &data);
	push(&s, &data);
	onlyshow(&s);

	getelem(&s, &data);
	printf("ջ����Ԫ�أ�%d\n", data);
	onlyshow(&s);

	printf("���ȣ�%d\n", lenth(&s));
	printf("���ջ��\n");
	clear(&s);
	onlyshow(&s);

	destory(&s);

	return 0;
}
