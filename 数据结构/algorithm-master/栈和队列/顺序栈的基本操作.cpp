#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;

#define OK     1
#define ERROR  0
#define INC   10   // ����
#define SIZE  10   // ��ʼ��С

typedef struct stack
{
	elemtype *base;
	elemtype *top;
	int size;
}stack;

// ����һ����ջ
status create(stack *p, int size)
{
	p->base = (elemtype *)malloc(size*sizeof(elemtype));
	if (!p->base) return ERROR;
	p->top = p->base;
	p->size = size;
	return OK;
}

// ��ջ
status push(stack *p, elemtype *data)
{
	elemtype *n;
	int s;	// size

	// ����ջ����û��
	if (p->top - p->base == p->size)
	{
		s = p->size + INC;
		n = (elemtype *)realloc(p->base, s * sizeof(elemtype));
		if (!n) return ERROR;
		p->base = n;
		p->top = p->base + p->size;
		p->size += INC;
		// ��ȫ������� p->top, ���¸�ֵ
	}
	*p->top++ = *data;
	// ����Ļ��ȼ���  *(p->top) = data; *p->top++;
	// ����һ������ ++ 
	return OK;
}

// ��ջ
status pop(stack *p, elemtype *back)
{
	if (p->base == p->top) return ERROR;
	*back = *--p->top;
	// ��--���ڳ�ջ��Ԫ��
	return OK;
}

// ����ջ��Ԫ��,����ջ
status gettop(const stack *p, elemtype *back)
{
	if (p->top == p->base) return ERROR;
	*back = *(p->top-1);
	return OK;
}

// �󳤶�
int lenth(stack *p)
{
	// ������û�д���ջ��NULLû��
	if (p->base == NULL) return ERROR;
	else return (p->top - p->base);
}

// �п�
status empty(stack *p)
{
	if (p->top == p->base) return OK;
	else return ERROR;
}

// ��ʾջ��ȫ��Ԫ�أ�����ջ
status onlyshow(const stack *p)
{
	elemtype *cur;

	if (p->top == p->base) return ERROR;
	cur = p->top-1;
	while (cur >= p->base)
	{
		printf("%d\n", *cur);
		cur--;
	}
	return OK;
}

// ���ջ
status clear(stack *p)
{
	if (p->base == NULL) return ERROR;
	p->top = p->base;
	return OK;
}

// ����
status destory(stack *p)
{
	if (p->base == NULL) return ERROR;
	free(p->base);
	p->top = p->base = NULL;
	p->size = 0;
	return OK;
}

int main(void)
{
	int i;
	elemtype data;
	stack s;	// �洢λ�ò���̬�� ����̬
				// stack *s; s->base=malloc
	if (!create(&s, SIZE))
	{
		printf("��ʼʧ��!\n");
		return 0;
	}

	printf("����5�����ݿ�ʼ��ջ��\n");
	for (i=1; i<=20; i++)
	{
		printf("������� %d �����ݣ�", i); 
		scanf("%d", &data);
		push(&s, &data);
	}
	pop(&s, &data);
	printf("ִ�г�ջ������%d\n", data);

	gettop(&s, &data);
	printf("ջ��Ԫ�أ�%d\n", data);

	onlyshow(&s);	// ���鿴������ջ
	
	printf("ջ�ĳ��ȣ�%d\n", lenth(&s));
	clear(&s);
	printf("ջ�ĳ��ȣ�%d\n", lenth(&s));

	destory(&s);

	return 0;
}
