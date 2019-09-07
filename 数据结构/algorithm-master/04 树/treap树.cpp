#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// treap ��, �����������һ��, ÿ����������ȼ�
// treap ����Ԫ�ؾ��в�����������, ���ȼ����д󶥶ѵ�����
// ���ȼ�Խ��, Խ������, Խ���ҵ�, �����ҵĴ�����

#define OK 1
#define ERROR 0
typedef int status;
typedef int elemtype;

// treap �����ṹ
typedef struct node
{
	int p;			// ���ȼ�
	elemtype data;	// ����
	node *lchild;
	node *rchild;
}node, treap;


// �� root Ϊ��, ������ת, �� AVL ������תһ��
inline void right(treap **root)
{
	node *lc = (*root)->lchild;;

	(*root)->lchild = lc->rchild;
	lc->rchild = *root;
	*root = lc;
}

// ������ת
inline void left(treap **root)
{
	node *rc = (*root)->rchild;

	(*root)->rchild = rc->lchild;
	rc->lchild = *root;
	*root = rc;
}

node *new_node(elemtype data, int p)	// ����һ���½��
{
	node *n;

	n = (node *)malloc(sizeof(node));
	n->data = data;
	n->p = p;
	n->lchild = n->rchild = NULL;
	return n;
}

// ����һ�������ڵĽ��, ������Ҳ���ظ�����, �����ﲻ�����ظ���
// ���ն����������ķ�������, �ڻ��ݵ�ʱ��, ������ת, �������ȼ�
status insert(treap **tree, elemtype data, int p)
{
	status s;
	if (!(*tree)) 
	{
		*tree = new_node(data, p);
		return OK;
	}
	else if ((*tree)->data == data) return ERROR;	// ����
	else if (data < (*tree)->data)
	{
		// ����������, ���ݵ�ʱ��������ȼ�
		// ����ʱ, �������ӵ����ȼ���, ��������ת
		s = insert(&((*tree)->lchild), data, p);
		if ((*tree)->lchild->p > (*tree)->p)  right(tree);
	}
	else 
	{
		// ����������. ����ʱ, �ǵõ���
		s = insert(&((*tree)->rchild), data, p);
		if ((*tree)->rchild->p > (*tree)->p) left(tree);
	}
	return s;
}

// ɾ��һ�����
// �����ò������ķ����ҵ�������
// Ȼ���ö��µ��ķ���, ���������µ���Ҷ��, ���ͷŵ�
status remove(treap **tree, elemtype data)
{
	node *del;

	if (!(*tree)) return ERROR;

	if ((*tree)->data == data)	// �ҵ� data �����µ�
	{	
		// һ������ķ���, �ж�������������״̬
		switch (!!((*tree)->lchild) + !!((*tree)->rchild) * 2)
		{
		case 0 :		// Ҷ��, ����ֱ���ͷ�
			free(*tree);   *tree = NULL;   break;
		case 1 :			// ֻ������
			del = *tree;
			*tree = (*tree)->lchild;
			free(del);   break;
		case 2 :			// ֻ���Һ���
			del = *tree;
			*tree = (*tree)->rchild;
			free(del);   break;
		case 3 :		// ��������, �����µ�, �����ȼ��ߵĺ��Ӹ�����
			if ((*tree)->lchild->p > (*tree)->rchild->p)
			{
				right(tree);	// ��ߴ�, ������ת, ����ߵ�ת��ȥ
				remove(&((*tree)->rchild), data);
			}
			else	// ͬʱ�ݹ鵽����, ����ɾ��
			{
				left(tree);
				remove(&((*tree)->lchild), data);
			}
		}
		return OK;
	}
	else if (data < (*tree)->data)
		return remove(&((*tree)->lchild), data);
	else return remove(&((*tree)->rchild), data);
}

// ������ȼ����������������
status check(treap *tree)
{
	int re = 1;

	if (!tree) return OK;
	if (tree->lchild)		// ������
	{
		if (tree->p < tree->lchild->p) return ERROR;
		if (!check(tree->lchild)) return ERROR;
		if (tree->rchild)		// ���Һ���
		{
			if (tree->p < tree->rchild->p) return ERROR;
			if (!check(tree->rchild)) return ERROR;
		}
	}
	else if (tree->rchild)		// ֻ���Һ���
	{
		if (tree->p < tree->rchild->p) return ERROR;
		if (!check(tree->rchild)) return ERROR;
	}
	return OK;
}

void destory(treap *tree)		// ����
{
	if (tree)
	{
		destory(tree->lchild);
		destory(tree->rchild);
		free(tree);
	}
}

void first_tra(treap *tree)		// �������
{
	if (tree)
	{
		printf("%d, ", tree->data);
		first_tra(tree->lchild);
		first_tra(tree->rchild);
	}
}

void mid_tra(treap *tree)		// �������
{
	if (tree)
	{
		mid_tra(tree->lchild);
		printf("%d, ", tree->data);
		mid_tra(tree->rchild);
	}
}

char display(treap *tree)	// ������ʾģ��
{
	char c;

	if (check(tree)) printf("\ntreap ����ȷ!");
	else printf("\ntreap ������!");
	printf("\n\n�������: ");   first_tra(tree);
	printf("\n�������: ");   mid_tra(tree);
	
	printf("\n\n�� c ������, ���س�����...\n");
	getchar();   c = getch();
	system("cls");

	return c;
}

int main(void)
{
	treap *tree = NULL;
	elemtype data;
	int p;

	while (1)		// �������
	{
		printf("������Ҫ�����Ԫ�ؼ����ȼ�: ");
		scanf("%d %d", &data, &p);
		if (insert(&tree, data, p))		// ����
			printf("\n��Ԫ�ز�����, �Ѳ���!\n");
		else printf("\n%d �Ѵ���!\n", data);

		if (display(tree) == 'c') break;
	}
	while (1)		// ɾ������
	{
		printf("������Ҫɾ����Ԫ��: ");
		scanf("%d", &data);
		if (!remove(&tree, data))		// ɾ��
			printf("\n��Ԫ�ز�����, ɾ��ʧ��!\n");
		else printf("\n��ɾ��!\n");

		if (display(tree) == 'c') break;
	}
	destory(tree);
	return 0;
}
/*		��������, ��� - Ȩֵ
1 10

2 8

3 6

4 11

5 0
*/