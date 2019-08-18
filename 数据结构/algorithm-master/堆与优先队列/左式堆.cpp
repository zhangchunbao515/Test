
// ������ʽ�ѵ����ȶ���
// ��ʽ�ѵ���������������, ����������ǳ,
// ���������������ϲ�����, ���ӶȽ�С O(log n)
// ����������������ȳ�����������, ��ִ����ת����, �����������

#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef int status;
#define OK 1
#define ERROR 0

// ��ʽ�����ڼ���ƽ��, ����ʽ����
typedef struct node
{
	elemtype data;
	node *lchild;
	node *rchild;
	int npl;
	// npl: �����·���� (null path length),���� AVL ����ƽ������
}node, left_heap;


left_heap *merge(left_heap *a, left_heap *b);	// �ϲ���������
left_heap *merge_s(left_heap *a, left_heap *b);	// ʵ�ʹ�������

// �ϲ� a, b ������, ��������, �ѶѶ������С�ĺϲ�
left_heap *merge(left_heap *a, left_heap *b)
{
	if (a == NULL) return b;
	else if (b == NULL) return a;
	else if (a->data < b->data)		// �Ѷ�С������
		return merge_s(a, b);
	else return merge_s(b, a);
}

// �� b �ϲ��� a, a ����������ǳ, һֱ���ұߺϲ�
left_heap *merge_s(left_heap *a, left_heap *b)
{
	node *tmp;

	// a ���С, �� a û����������, ��ȻҲû��������
	if (a->lchild == NULL) a->lchild = b;
	else 
	{
		a->rchild = merge(a->rchild, b);	// �������Һϲ�
		if (a->rchild->npl > a->lchild->npl)	// �Ƚ����� npl
		{
			tmp = a->rchild;
			a->rchild = a->lchild;
			a->lchild = tmp;
		}	// ����ʱ, �������������Ƚϳ�, ��Ҫ������ת
		a->npl = a->rchild->npl + 1;	// ת���, ����˫�׵� npl
	}
	return a;
}

// ������Կ������뵥���ϲ�������
status insert(left_heap **h, elemtype data)
{
	left_heap *tmp;		// �� h �� tmp ���кϲ�

	tmp = (node *)malloc(sizeof(node));
	tmp->data = data;
	tmp->lchild = tmp->rchild = NULL;
	tmp->npl = 0;

	*h = merge(*h, tmp);	// �ϲ�
	return OK;
}

status deletetop(left_heap **h)		// ɾ���Ѷ�
{
	node *del = *h;		// ��¼��ɾ�����

	if (!(*h)) return ERROR;

	*h = merge((*h)->lchild, (*h)->rchild);	// ���ºϲ�
	free(del);
	return OK;
}

status gettop(left_heap *h, elemtype *back)   // ��öѶ�
{
	if (!h) return ERROR;
	*back = h->data;
	return OK;
}

int check(left_heap *h)		// ���ѵ���ȷ��
{
	int a, b;

	if (!h) return OK;
	if (!h->rchild) return OK;
	if (!h->lchild) return OK;

	// ������һ�� npl ��������ʽ��, ��һֱ���� ERROR
	if (h->lchild->npl < h->rchild->npl) return ERROR;
	a = check(h->lchild);
	b = check(h->rchild);
	if (a == ERROR || b == ERROR) return ERROR;
	else return OK;
}

void destory(left_heap *h)		// ���ٶ�
{
	if (h)
	{
		if (h->lchild) destory(h->lchild);
		if (h->rchild) destory(h->rchild);
		free(h);
	}
}

void input(left_heap **h, int n)	// ����ģ��
{
	int data;

	while (n--)
	{
		scanf("%d", &data);
//		data = rand() % 1000;	// (������) �����ֶ�����, ���Զ���
		insert(h, data);		// �������
	}
}

int main(void)
{
	left_heap *h = NULL;
	left_heap *h2 = NULL;
	int i, n;
	elemtype data;

	// ���� n ��Ԫ�غ�, ȫ������, �������ȶ�����
	printf("������1, ����� n ��Ԫ��: ");
	scanf("%d", &n);
	input(&h, n);
	if (check(h)) printf("\n����ȷ!\n");
	else printf("\n�Ѵ���!\n");

	printf("\n���� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		if (gettop(h, &data))
		{
			printf("%d, ", data);
			deletetop(&h);		// ͬʱɾ���Ѷ�
		}
		else break;
	}
	printf("\n\n������2, ����� n ��Ԫ��: ");
	scanf("%d", &n);
	input(&h2, n);

	printf("\n�ϲ���1 ��2 ......\n");
	h = merge(h, h2);

	printf("��������ȫ����Ԫ��: ");
	while (gettop(h, &data))
	{
		printf("%d, ", data);
		deletetop(&h);
	}
	printf("\n\n");
	destory(h);
	return 0;
}
