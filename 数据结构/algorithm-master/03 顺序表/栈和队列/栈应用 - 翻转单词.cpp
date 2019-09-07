// ջӦ��, ���ʷ�ת
#include <stdio.h>
#include <malloc.h>

typedef int status;

#define OK 1
#define ERROR 0
#define SIZE 20
#define INC 10

// ˳��ջ
typedef struct stack
{
	char *base;
	char *top;
	int size;
}stack;

status create(stack *p)
{
	p->base = (char *)malloc(SIZE * sizeof(char));
	if (!p->base) return ERROR;
	p->top = p->base;
	p->size = SIZE;

	return OK;
}

status destory(stack *p)
{
	if (!p->base) return ERROR;
	free(p->base);
	p->top = p->base = NULL;
	p->size = 0;

	return OK;
}

status push(stack *p, char *data)
{
	char *n;

	if (!p->base) return ERROR;
	if (p->top - p->base == p->size)
	{
		n = (char *)realloc(p->base, 
			(p->size + INC) * sizeof(char));
		if (!n) return ERROR;
		p->base = n;
		p->size += INC;
	}
	*p->top = *data;
	p->top++;

	return OK;
}

status pop(stack *p, char *back)
{
	if (p->top == p->base) return ERROR;
	p->top--;
	*back = *p->top;

	return OK;
}

char *strstv(char *buf)
{
	stack s;
	int i;

	create(&s);
	for (i=0; buf[i]!='\0'; i++)
	{
		push(&s, buf + i);
	}
	i=0;
	while (pop(&s, buf + i)) i++;
	buf[i] = '\0';		// ���
	destory(&s);

	return buf;
}

// ȫ����ջ����ʾ
status showall(stack *p)
{
	char data;

	if (p->top == p->base) return ERROR;
	while (pop(p, &data)) printf("%c", data);
	return OK;
}

void output(char *buf)
{
	int i;
	stack s;

	// �����ո��ȫ����ջ, �����ջ
	create(&s);
	for (i=0; buf[i]!='\0'; i++)
	{
		if (buf[i] == ' ')
		{
			showall(&s);
			printf(" ");
		}
		else push(&s, buf + i);
	}
	showall(&s);	// ������Կո��β
	destory(&s);
}

int main(void)
{
	char buf[100] = {0};

	printf("��������: l love you\n");
	printf("�������: you love l\n");
	printf("������һ��Ӣ�ľ���: ");
	gets(buf);
	strstv(buf);	// ��ת�ַ���
	printf("��ת��: ");
	output(buf);	// ������
	printf("\n");

	return 0;
}
