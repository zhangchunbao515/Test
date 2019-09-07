
// ���ڶ����������ȶ���

#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef int status;
#define OK 1
#define ERROR 0
#define INF 0x5FFFFFFF
#define MAX 30					// ��������
#define capacity 1073741824		// �������


// �����ֵܴ��������
typedef struct node
{
	elemtype data;
	node *fchild;		// �׺���
	node *nbrother;		// �ֵ�
}node;

// ������
typedef struct bqueue
{
	node *base[MAX];		// ��������
	int cap;		// �������
}bqueue;


bqueue *init(void)		// ����һ���������
{
	bqueue *q;
	int i;

	q = (bqueue *)malloc(sizeof(bqueue));
	for (i=0; i<MAX; i++)
		q->base[i] = NULL;
	q->cap = 0;
	return q;
}

node *new_node(elemtype data)	// �½����
{
	node *n;

	n = (node *)malloc(sizeof(node));
	n->data = data;
	n->fchild = n->nbrother = NULL;
	return n;
}

void del(node *n)		// ����һ������
{
	if (n)
	{
		del(n->fchild);
		del(n->nbrother);
		free(n);
	}
}

void destory(bqueue *q)		// ���ٶ������
{
	int i;

	if (!q) return ;
	for (i=0; i<MAX; i++)
		if (q->base[i]) del(q->base[i]);
	free(q);
}

// �ϲ�������ͬ������, ���浽 n1
node *combine(node *n1, node *n2)
{
	if (n1->data < n2->data)
	{
		n2->nbrother = n1->fchild;
		n1->fchild = n2;
		return n1;
	}
	else 
	{
		n1->nbrother = n2->fchild;
		n2->fchild = n1;
		return n2;
	}
}

// �ϲ� h1, h2, ͬʱ���� h2
bqueue *merge(bqueue **h1, bqueue **h2)
{
	node *t1, *t2, *carry;
	int i, j;

	if (*h1 == NULL) return *h2;
	if (*h2 == NULL) return *h1;
	// ��������
	if ((*h1)->cap + (*h2)->cap > capacity) return NULL;
	carry = NULL;
	(*h1)->cap += (*h2)->cap;
	for (i=0, j=1; j<=(*h1)->cap; i++, j*=2)	// j ���ƴ�С
	{
		t1 = (*h1)->base[i];   t2 = (*h2)->base[i];
		// 421 ���ж� t1, t2, carry ״̬
		// �κ�һ����ֵ���� !! ������ 0,1
		switch (!!t1 + !!t2 * 2 + !!carry * 4)
		{
		case 0 : break;		// û����
		case 1 : break;		// ֻ�� t1
		case 2 :			// ֻ�� t2
			(*h1)->base[i] = t2;
			(*h2)->base[i] = NULL;  break;
		case 3 :
			carry = combine(t1, t2);	// t1, t2
			(*h1)->base[i] = NULL;
			(*h2)->base[i] = NULL;  break;
		case 4 :	// ֻ�� carry
			(*h1)->base[i] = carry;
			carry = NULL;  break;		// �ǵ�Ҫ��ʱ���carry
		case 5 :	// t1, carry
			carry = combine(carry, t1);
			(*h1)->base[i] = NULL;  break;
		case 6 :	// t2, carry
			carry = combine(carry, t2);
			(*h2)->base[i] = NULL;  break;
		case 7 :	// t1, t2, carry
			(*h1)->base[i] = carry;
			carry = combine(t1, t2);
			(*h2)->base[i] = NULL;  break;
		}
	}
	return *h1;
}

status insert(bqueue **q, elemtype data)		// �� q �в���һ��Ԫ��
{
	bqueue *tmp;

	tmp = init();
	tmp->base[0] = new_node(data);
	tmp->cap = 1;

	*q = merge(q, &tmp);
	destory(tmp);
	if (*q == NULL) return ERROR;
	else return OK;
}

// ������Сֵ, ͬʱɾȥ��
elemtype deletetop(bqueue **h)
{
	elemtype mindata = INF;
	int minpos = -1;
	int i, j;
	node *tree, *del;
	bqueue *tmp;


	// �ҵ���СԪ mindata, ��λ�� minpos
	for (i=0, j=1; *h && j<=(*h)->cap; i++, j*=2)
	{
		if ((*h)->base[i] && (*h)->base[i]->data < mindata)
		{
			mindata = (*h)->base[i]->data;
			minpos = i;
		}
	}
	if (minpos == -1) return INF;
	// ���� minpos �������ó���, ��ɢ����ʱ������, �ٺϲ��� h ��
	del = (*h)->base[minpos];
	(*h)->base[minpos] = NULL;
	tree = del->fchild;
	free(del);
	tmp = init();
	tmp->cap = 1 << minpos;
	for (i=minpos-1; i>=0 && tree; i--)
	{
		tmp->base[i] = tree;
		tree = tree->nbrother;
		tmp->base[i]->nbrother = NULL;
	}
	(*h)->cap -= tmp->cap;
	*h = merge(h, &tmp);
	return mindata;
}

void input(bqueue **q, int n)
{
	elemtype data;

	while (n--)
	{
		scanf("%d", &data);
//		data = rand() % 1000;	// (������) �����ֶ�����, ���Զ���
		insert(q, data);		// �������
	}
}

int main(void)
{
	bqueue *h = NULL;
	bqueue *h2 = NULL;
	int i, n;
	elemtype data;

	// ���� n ��Ԫ�غ�, ȫ������, �������ȶ�����
	h = init();
	printf("�������ȶ���1, ����� n ��Ԫ��: ");
	scanf("%d", &n);
	input(&h, n);

	printf("\n���� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		data = deletetop(&h);
		if (data != INF)
			printf("%d, ", data);
	}
	h2 = init();
	printf("\n\n�������ȶ���2, ����� n ��Ԫ��: ");
	scanf("%d", &n);
	input(&h2, n);

	printf("\n�ϲ����ȶ���1, 2\n");
	h = merge(&h, &h2);

	printf("��������ȫ����Ԫ��: ");
	while (1)
	{
		data = deletetop(&h);
		if (data != INF)
			printf("%d, ", data);
		else break;
	}
	printf("\n\n");
	destory(h);
	destory(h2);
	return 0;
}
