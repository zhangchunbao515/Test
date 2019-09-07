#include <stdio.h>
#include <stdlib.h>

// ����������, �����޸�, ���������ͬ��Ԫ��

typedef struct node		// �������ṹ
{
	int data;
	node *lc;
	node *rc;
}btree, node;


// �����ϲ���һ������λ��, ֱ��ʧ�ܷ���˫��
// ��������ͬ�Ľ��, ���ҹ涨, ������ <= �� < ������
void search(btree *tree, node *f, int data, node **p)
{
	if (!tree) *p = f;
	else if (data <= tree->data)
		search(tree->lc, tree, data, p);
	else search(tree->rc, tree, data, p);
}

// ����һ���Ľ��, ���������ͬ�Ľ��
void insert(btree **tree, int data)
{
	node *p = NULL;
	node *n;

	search(*tree, NULL, data, &p);
	n = (node *)malloc(sizeof(node));
	n->lc = n->rc = NULL;
	n->data = data;
	if (!p) *tree = n;
	else if (data <= p->data) p->lc = n;
	else p->rc = n;
}

// �������, ���ҽ�������浽, data ��
void mid_tra(btree *tree, int *data, int *pos)
{
	if (tree)
	{
		mid_tra(tree->lc, data, pos);
		data[ (*pos)++ ] = tree->data;
		mid_tra(tree->rc, data, pos);
	}
}

void destory(btree *tree)	// ������
{
	if (tree)
	{
		destory(tree->lc);
		destory(tree->rc);
		free(tree);
	}
}

void btree_sort(int *data, int n)	// ����������
{
	btree *tree = NULL;
	int i, pos = 0;		// pos ָʾ data ����λ��

	for (i=0; i<n; i++) insert(&tree, data[i]);
	mid_tra(tree, data, &pos);	
	destory(tree);
}

int main(void)
{
	int i, n;
	int data[100];

	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", data + i);

	btree_sort(data, n);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	return 0;
}
