#include <stdio.h>
#include <malloc.h>

typedef char elemtype;
typedef int status;
#define ERROR 0
#define OK 1

// �������
typedef struct node
{
	elemtype data;
	node *next;
}node;

// ջ�Ĵ���ṹ
typedef struct sqstack
{
	node *top;
	node *base;
	int size;
}sqstack;

status create(sqstack *p)
{
	node *n;

	p->base = NULL;  // ��ȫ��
	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->next = NULL;

	p->base = p->top = n;
	p->size = 0;

	return OK;
}

status destory(sqstack *p)
{
	node *del;

	while (p->top)
	{
		del = p->top;
		p->top = p->top->next;
		free(del);
	}
	p->base = p->top = NULL;
	
	return OK;
}

status push(sqstack *p, elemtype *data)
{
	node *n;

	// �ȿ���ջ������û��
	if (p->base == NULL) return ERROR;

	// �ȸ�ֵ������һ���½�㣬����ȥ
	p->top->data = *data;

	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->next = p->top;
	p->top = n;
	p->size++;

	return OK;
}

status pop(sqstack *p, elemtype *back)
{
	node *del;

	// �ȿ����ǲ��ǿ�ջ
	if (p->top == p->base) return ERROR;
	
	// ����top��㣬�ٳ�ջ
	del = p->top;
	p->top = p->top->next;
	*back = p->top->data;
	free(del);
	p->size--;

	return OK;
}

elemtype gettop(sqstack *p)
{
	if (p->top == p->base) return ERROR;
	else return p->top->next->data;
}

status ok(elemtype *a, elemtype *b)
{
	if (*a == '(' && *b == ')') return OK;
	else if (*a == '[' && *b == ']') return OK;
	else if (*a == '{' && *b == '}') return OK;
	else return ERROR;
}

status left(elemtype c)
{
	switch (c)
	{
	case '(' :
	case '[' :
	case '{' : return OK;
	default: return ERROR;
	}
}

elemtype anther(elemtype *c)
{
	switch (*c)
	{
	case '(' : return ')';
	case '[' : return ']';
	case '{' : return '}';
	default : return ERROR;
	}
}

int main(void)
{
	sqstack s;
	elemtype c;
	elemtype top;

	create(&s);
	printf("���������ţ�");
	c = getchar();
	while (c != '\n')
	{
		if (left(c)) push(&s, &c);
		else
		{
			top = gettop(&s);
			if (ok(&top, &c)) pop(&s, &top);
			else break;
		}
		c = getchar();
	}
	// c �˳���ʱ���ǻس���������
	if (s.top == s.base && c=='\n') 
	{
		printf("����ƥ��ɹ���\n");
	}
	else if (s.top == s.base && c!='\n')
	{
		printf("���� %c\n", c);
	}
	else 
	{
		pop(&s, &top);
		printf("ȱ�� %c\n", anther(&top));
	}
	destory(&s);

	return 0;
}