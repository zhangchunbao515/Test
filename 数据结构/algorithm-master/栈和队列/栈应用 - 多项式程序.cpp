#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;

#define OK 1
#define ERROR 0
#define EPS 1e-6

// ���ṹ
typedef struct node
{
	float p;		// ϵ��
	elemtype e;		// ָ��
	node *next;
}node;

// ͷ�ṹ
typedef struct list
{
	node *first;
	node *last;
	int lenth;
}list;

status create(list *p)
{
	node *n;

	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->next = NULL;
	p->first = p->last = n;
	p->lenth = 0;

	return OK;
}

status destory(list *p)
{
	node *del;

	while (p->first)
	{
		del = p->first;
		p->first = del->next;
		free(del);
	}
	p->first = p->last = NULL;
	p->lenth = 0;

	return 0;
}

status append(list *q, float *p, elemtype *e)
{
	node *n;

	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->p = *p;
	n->e = *e;
	n->next = q->last->next;
	q->last->next = n;
	q->last = n;		// �൱�� q->last++;
	q->lenth++;

	return OK;
}

status combine(list *p)
{
	node *cur;
	node *del;

	if (p->first == p->last) return ERROR;
	cur = p->first->next;
	while (cur->next)
	{
		if (cur->e == cur->next->e)
		{
			// �ϲ�, �������� cur->next
			// [cur] -> [del] -> []
			cur->p += cur->next->p;
			del = cur->next;
			cur->next = del->next;
			free(del);
			p->lenth--;
		}
		else cur = cur->next;
	}
	return OK;
}

// ���
status add(list *a, list *b, list *c)
{
	node *cura;
	node *curb;
	float pp;

	if (a->first == a->last 
		&& b->first == b->last) return ERROR;
	cura = a->first->next;
	curb = b->first->next;
	while (cura && curb)
	{
		// �Ƚ�ָ��
		if (cura->e < curb->e)
		{
			// cura ���Ƶ�c
			if (cura->p == 0) 
			{
				cura = cura->next;
				continue;
			}
			append(c, &cura->p, &cura->e);
			cura = cura->next;
		}
		else if (cura->e > curb->e)
		{
			if (curb->p == 0) 
			{
				curb = curb->next;
				continue;
			}
			append(c, &curb->p, &curb->e);
			curb = curb->next;
		}
		else 
		{
			pp = cura->p + curb->p;
			if (pp == 0) 
			{
				cura = cura->next;
				curb = curb->next;
				continue;
			}
			append(c, &pp, &cura->e);
			cura = cura->next;
			curb = curb->next;
		}
	}
	while (cura)
	{
		append(c, &cura->p, &cura->e);
		cura = cura->next;
	}
	while (curb)
	{
		append(c, &curb->p, &curb->e);
		curb = curb->next;
	}
	combine(c);
	return OK;
}

// ��� a - b
status jian(list *a, list *b, list *c)
{
	node *cura;
	node *curb;
	float pp;

	if (a->first == a->last 
		&& b->first == b->last) return ERROR;
	cura = a->first->next;
	curb = b->first->next;
	while (cura && curb)
	{
		// �Ƚ�ָ��
		if (cura->e < curb->e)
		{
			// cura ���Ƶ�c
			if (cura->p == 0) 
			{
				cura = cura->next;
				continue;
			}
			append(c, &cura->p, &cura->e);
			cura = cura->next;
		}
		else if (cura->e > curb->e)
		{
			if (curb->p == 0) 
			{
				curb = curb->next;
				continue;
			}
			pp = -curb->p;
			append(c, &pp, &curb->e);
			curb = curb->next;
		}
		else 
		{
			pp = cura->p - curb->p;
			if (pp == 0) 
			{			
				cura = cura->next;
				curb = curb->next;
				continue;
			}
			append(c, &pp, &cura->e);
			cura = cura->next;
			curb = curb->next;
		}
	}
	while (cura)
	{
		append(c, &cura->p, &cura->e);
		cura = cura->next;
	}
	while (curb)
	{
		pp = -curb->p;
		append(c, &pp, &curb->e);
		curb = curb->next;
	}
	combine(c);
	return OK;
}

void swap(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

void fswap(float *a, float *b)
{
	float t;

	t = *a;
	*a = *b;
	*b = t;
}

status listsort(list *p)
{
	int i;
	int flag;
	node *cur;

	if (p->first == p->last) return ERROR;
	for (i=0; i<p->lenth; i++)
	{
		flag = 1;
		cur = p->first->next;
		while (cur->next)
		{
			if (cur->e > cur->next->e)
			{
				swap(&cur->e, &(cur->next->e));
				fswap(&cur->p, &(cur->next->p));
				flag = 0;
			}
			cur = cur->next;
		}
		if (flag) break;
	}
	return OK;
}

// ���
status cheng(list *a, list *b, list *c)
{
	node *cura;
	node *curb;
	float pp;
	elemtype ee;

	if (a->first == a->last 
		|| b->first == b->last) return ERROR;
	cura = a->first->next;
	
	while (cura)
	{
		curb = b->first->next;
		while (curb)
		{
			// �������, ָ�����
			pp = cura->p * curb->p;
			ee = cura->e + curb->e;
			append(c, &pp, &ee);
			curb = curb->next;
		}
		cura = cura->next;
	}
	// ����һ�� c,����,�ϲ�ͬ����
	listsort(c);
	combine(c);

	return OK;
}

void input(list *q)
{
	static int t = 1;
	int c = 1;
	int check;
	elemtype e;
	float p;

	printf("������� %d ��ʽ��:\n", t++);
	while (1)
	{
		printf("������� %d ��:", c++);
		check = scanf("%f%d", &p, &e);
		if (check != 2) break;
		if (p < EPS && e == 0) break;
		if (!append(q, &p, &e)) break;
	}
}

inline float fabs(float n)
{
	return (n > 0 ? n : -n);
}

status show(list *q)
{
	node *cur;
	int f = 1;

	if (q->first == q->last) printf("0");
	else 
	{
		cur = q->first->next;
		while (cur)
		{
			// ���ж�����ķ���
			if (f && cur->p > 0) f = 0;
			else if (cur->p > 0) printf(" + ");
			else if (cur->p < 0) printf(" - ");
			f = 0;
			// ���ж�ָ��,
			if (cur->e == 0) printf("%g", fabs(cur->p));
			else if (cur->e == 1 && cur->p == 1) printf("X");
			else if (cur->e == 1 && cur->p != 1) printf("%gX", fabs(cur->p));
			else printf("%gX^%d", fabs(cur->p), cur->e);
			cur = cur->next;
		}
	}
	printf("\n");
	return OK;
}

int main()
{
	list a, b, c;

	create(&a);
	create(&b);
	printf("�����ʽ: ϵ�� ָ��... �� 0 0 ����\n");
	input(&a);
	input(&b);
	printf("\n��һ��ʽ��: ");
	show(&a);
	printf("�ڶ���ʽ��: ");
	show(&b);

	create(&c);
	add(&a, &b, &c);	// ��Ӻ�,�ŵ� c ����
	printf("\n��Ӻ�: ");
	show(&c);
	destory(&c);

	create(&c);
	jian(&a, &b, &c);	// a - b
	printf("\n�����: ");
	show(&c);
	destory(&c);

	create(&c);
	cheng(&a, &b, &c);	// a * b
	printf("\n��˺�: ");
	show(&c);
	destory(&c);

	destory(&a);
	destory(&b);

	return 0;
}

