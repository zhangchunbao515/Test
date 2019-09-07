// ջӦ�ã���ֵת����˳��ջ�洢
#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;

#define OK     1
#define ERROR  0
#define SIZE   10
#define INC    10

// ˳��ջ�洢�ṹ
typedef struct
{
	elemtype *base;		// base ָ��һ���ռ�
	elemtype *top;
	int size;
}stack;

status create(stack *p)
{
	p->base = (elemtype *)malloc(SIZE*sizeof(elemtype));
	if (!(p->base)) return ERROR;
	p->top = p->base;
	p->size = SIZE;

	return OK;
}

status destory(stack *p)
{
	if (!(p->base)) return ERROR;
	free(p->base);

	p->base = p->top = NULL;
	p->size = 0;

	return OK;
}

status push(stack *p, elemtype data)
{
	elemtype *n;
	int newsize;  //Ϊ��һ�в�д̫�����
	
	// ����ջ������û��
	if (!(p->base)) return ERROR;
	
	// �����ռ乻����
	if (p->top - p->base == p->size)
	{
		newsize = p->size + INC;
		n = (elemtype *)realloc(p->base, newsize* sizeof(elemtype));
		if (!n) return ERROR;
		p->base = n;
		p->size = newsize;
	}

	// ��ʼ��ջ
	*p->top = data;
	p->top++;

	return OK;
}

status pop(stack *p, elemtype *back)
{
	// �����ǲ��ǽ��õ�ջ
	if (p->base == NULL) return ERROR;
	// �����ǲ��ǿ�ջ
	if (p->top == p->base) return ERROR;

	p->top--;
	*back = *p->top;

	return OK;
}

char inttochar(int n)
{
	if (n>=0 && n<=9) return (n + '0');
	else return (n - 10 + 'A');
}

int main(void)
{
	stack s;
	elemtype n;
	int r;

	printf("ʮ����ת R ���ƣ�(2 <= R <= 16)\n");
	printf("������һ��ʮ����������");
	scanf("%d", &n);
	if (n<=0) return 0;
	printf("������ R��");
	scanf("%d", &r);
	if (r<2 || r>16) return 0;

	// ��ʼת��
	create(&s);
	while (n)
	{
		push(&s, n % r);
		n /= r;
	}
	// ȫ����ջ����ʾ
	while (pop(&s, &n))
	{
		printf("%c", inttochar(n));
	}
	printf("\n");
	destory(&s);
	
	return 0;
}
