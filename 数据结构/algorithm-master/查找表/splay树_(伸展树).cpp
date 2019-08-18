
// ��չ���Ļ�������
// search()		����
// insert()		����
// remove()		ɾ��
// splay()		��չ

// ��չ���ĺ��Ĳ���, splay(tree, x) ��չ x ���, 
// Ҳ���ǰ� x ����ᵽ����λ��, ͬʱ���ƻ����������������
// ���û�� x ���, �Ǿ���չ x ��ǰ�����ߺ�̽��, Ҳ����ʲô������չ

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define OK 1
#define ERROR 0
typedef int status;
typedef int elemtype;

// ��չ���ö���������
typedef struct node
{
	elemtype data;
	node *lchild;
	node *rchild;
}node, splay_tree;

static node *nullnode = NULL;	// �ƽ��, ���������

node *init(void)	// ��ʼ����չ��, ����һ���ƽ��
{
	if (!nullnode)		// �� nullnode ���� NULL, �򻯳���
	{
		nullnode = (node *)malloc(sizeof(node));
		nullnode->lchild = nullnode->rchild = nullnode;
	}
	return nullnode;
}

// ��չ data ���, ���û�о���չ data ��ǰ��
// Ҳ���ǰ� data �ᵽ����
// ���¶��ϵ���չ��ʽ�����ڱ��, ����������϶��µķ���
node *splay(splay_tree **tree, elemtype data)
{
	node tmp;
	node *left_min, *right_max;		// ��ʱ����������, BST����, ���С, �ұߴ�
	node *cur;

	tmp.lchild = tmp.rchild = nullnode;
	left_min = right_max = &tmp;
	nullnode->data = data;		// data �ݴ����ƽ����

	if (*tree == nullnode) return *tree;		// ����
	
	while ((*tree)->data != data)		// ��ʼ��չ data
	{
		if (data < (*tree)->data)		// ������������
		{
			// �򻯵�֮����
			// ���� tree->left һ������ NULL, ��Ϊ���ƽ�� nullnode
			// ����������ƽ���Ŀ��, ��������������ж�, �򻯳���
			if (data < (*tree)->lchild->data)
			{
				// ����һ����, ������ת, �� AVL ������תһ��
				cur = (*tree)->lchild;
				(*tree)->lchild = cur->rchild;
				cur->rchild = *tree;
				*tree = cur;
			}
			if ((*tree)->lchild == nullnode) break;
			right_max->lchild = *tree;		// ���뵽��ʱ������
			right_max = right_max->lchild;		// ����ߵ�����С��, ���Խ�����߲��ƻ� BST ����
			*tree = (*tree)->lchild;
		}
		else if (data > (*tree)->data)	// ������������
		{
			if (data > (*tree)->rchild->data)
			{
				// ����һ����, ������ת
				cur = (*tree)->rchild;
				(*tree)->rchild = cur->lchild;
				cur->lchild = *tree;
				*tree = cur;
			}
			if ((*tree)->rchild == nullnode) break;
			left_min->rchild = *tree;		// ���ұ�������
			left_min = left_min->rchild;
			*tree = (*tree)->rchild;
		}
	}
	// ������������ʱ���ӻ���
	left_min->rchild = (*tree)->lchild;
	right_max->lchild = (*tree)->rchild;
	(*tree)->lchild = tmp.rchild;
	(*tree)->rchild = tmp.lchild;

	return *tree;
}

// �����в���һ�� data
// ���� data ������Ľ��(ǰ��)��չ������, 
// �ڰ� data ���뵽����, ������˾Ͳ��ظ�������, ��ʵҲ�����ظ�����
status insert(splay_tree **tree, elemtype data)
{
	node *new_node;		// �½��, ������

	new_node = (node *)malloc(sizeof(node));
	new_node->lchild = new_node->rchild = nullnode;
	new_node->data = data;

	*tree = splay(tree, data);		// ��չ
	if (*tree == nullnode)  *tree = new_node;		// ����
	else if (data == (*tree)->data) {free(new_node);  return ERROR;}
	else if (data < (*tree)->data)		// ������ new_node �����ı�
	{
		new_node->lchild = (*tree)->lchild;
		new_node->rchild = *tree;
		(*tree)->lchild = nullnode;
	}
	else 
	{
		new_node->lchild = *tree;
		new_node->rchild = (*tree)->rchild;
		(*tree)->rchild = nullnode;
	}
	*tree = new_node;
	return OK;
}

// ����һ��Ԫ��, ͬʱ��չ��
// ����Ҳ�������չ����ǰ��
status search(splay_tree **tree, elemtype data)
{
	*tree = splay(tree, data);
	if (data == (*tree)->data) return OK;
	else return ERROR;
}

// ɾ��һ��Ԫ��
// ���Խ���Ԫ����չ����, �����, ���ͷ���
status remove(splay_tree **tree, elemtype data)
{
	node *del;

	if (*tree == nullnode) return ERROR;

	*tree = splay(tree, data);
	if ((*tree)->data == data)		// �ҵ�
	{
		del = *tree;
		if ((*tree)->lchild == nullnode)
		{
			if ((*tree)->rchild == nullnode)
				*tree = nullnode;
			else *tree = (*tree)->rchild;
		}
		else if ((*tree)->rchild == nullnode)
			*tree = (*tree)->lchild;
		else		// ���Ҷ�����, ������������չһ�����ĵ���
		{			// ���� BST ����, �����Ǹ�, ��û����������
			*tree = splay(&((*tree)->lchild), data);
			(*tree)->rchild = del->rchild;
		}
		free(del);
		return OK;
	}
	return ERROR;
}

void destory(splay_tree *tree)		// ����
{
	if (tree != nullnode)
	{
		destory(tree->lchild);
		destory(tree->rchild);
		free(tree);
	}
}

void first_tra(splay_tree *tree)	// �������
{
	if (tree != nullnode)
	{
		printf("%d, ", tree->data);
		first_tra(tree->lchild);
		first_tra(tree->rchild);
	}
}

void mid_tra(splay_tree *tree)		// �������
{
	if (tree != nullnode)
	{
		mid_tra(tree->lchild);
		printf("%d, ", tree->data);
		mid_tra(tree->rchild);
	}
}

char display(splay_tree *tree)	// ������ʾģ��
{
	char c;

	printf("\n�������: ");   first_tra(tree);
	printf("\n\n�������: ");   mid_tra(tree);
	
	printf("\n\n�� c ������, ���س�����...\n");
	getchar();   c = getch();
	system("cls");

	return c;
}

int main(void)
{
	splay_tree *tree;
	int data;

	tree = init();		// ��ʼ��
	while (1)		// �������
	{
		printf("������Ҫ�����Ԫ��: ");
		scanf("%d", &data);
		if (insert(&tree, data))		// ����
			printf("\n��Ԫ�ز�����, �Ѳ���!\n");
		else printf("\n%d �Ѵ���!\n", data);

		if (display(tree) == 'c') break;
	}
	while (1)		// ���Ҳ���
	{
		printf("������Ҫ���ҵ�Ԫ��: ");
		scanf("%d", &data);
		if (search(&tree, data))
			printf("\n�ҵ�!\n");
		else printf("\nδ�ҵ�! %d\n", data);

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
