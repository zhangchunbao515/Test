
// ����б�ѵ����ȶ���
// б������ʽ�ѵ���������, б�Ѳ����� npl ��Ϣ
// б��һֱ���������ϲ�, �������������������
// Ϊ�˽���������, б���ڵݹ�ϲ���ʱ��, ����ÿһ����ʱ�Ľ��
// ������ת, ���������ǵ���������, �������޻��ǵ���ת

#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef int status;
#define OK 1
#define ERROR 0

// б����ʽ����
typedef struct node
{
	elemtype data;
	node *lchild;
	node *rchild;
}node, xie_heap;


xie_heap *merge(xie_heap *a, xie_heap *b);		// �ϲ���������
xie_heap *merge_s(xie_heap *a, xie_heap *b);	// ʵ�ʹ�������

// �ϲ� a, b ������, ��������, �ѶѶ������С�ĺϲ�
xie_heap *merge(xie_heap *a, xie_heap *b)
{
	if (a == NULL) return b;
	else if (b == NULL) return a;
	else if (a->data < b->data)
		return merge_s(a, b);
	else return merge_s(b, a);
}

// �� b �ϲ��� a, ��ʱ a �ĶѶ�С
xie_heap *merge_s(xie_heap *a, xie_heap *b)
{
	node *tmp;

	if (a->lchild == NULL) a->lchild = b;
	else 
	{
		a->rchild = merge(a->rchild, b);	// �ϲ��Һ���
		tmp = a->lchild;			// ����ʱ, ��ת���Һ���
		a->lchild = a->rchild;
		a->rchild = tmp;
	}
	return a;
}

// ������Կ������뵥���ϲ�������
status insert(xie_heap **h, elemtype data)
{
	node *n;

	n = (node *)malloc(sizeof(node));
	n->lchild = n->rchild = NULL;
	n->data = data;

	*h = merge(*h, n);
	return OK;
}

status deletetop(xie_heap **h)		// ɾ���Ѷ�
{
	node *del = *h;		// �Ѷ���ɾ��

	*h = merge((*h)->lchild, (*h)->rchild);
	free(del);
	return OK;
}

status gettop(xie_heap *h, elemtype *back)   // ��öѶ�
{
	if (!h) return ERROR;
	*back = h->data;
	return OK;
}

void destory(xie_heap *h)		// ���ٶ�
{
	if (h)
	{
		if (h->lchild) destory(h->lchild);
		if (h->rchild) destory(h->rchild);
		free(h);
	}
}

int lenth(xie_heap *h)		// �����
{
	int left, right;

	if (!h) return 0;
	left = lenth(h->lchild);
	right = lenth(h->rchild);

	return (left > right ? left : right) + 1;
}

void input(xie_heap **h, int n)	// ����ģ��
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
	xie_heap *h = NULL;
	xie_heap *h2 = NULL;
	int i, n;
	elemtype data;

	// ���� n ��Ԫ�غ�, ȫ������, �������ȶ�����
	printf("������1, ����� n ��Ԫ��: ");
	scanf("%d", &n);
	input(&h, n);
	printf("\n�����: %d\n", lenth(h));

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
