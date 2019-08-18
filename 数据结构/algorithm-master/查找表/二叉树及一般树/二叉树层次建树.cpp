// ��������ν�����

#include <stdio.h>
#include <malloc.h>

typedef char elemtype;
typedef int status;

#define OK 1
#define ERROR 0

// ����������ṹ
typedef struct node
{
	elemtype data;
	node *lchild;
	node *rchild;
}node, btree;

// ��ν���
status create(btree **tree, char *str)
{
	node *queue[100];
	int rear = 0;
	int front = 0;
	node *back;

	if (str[0] == '\0' || str[0] == '#') return ERROR;
	
	// ���������, ��Ӽ�¼
	(*tree) = (node *)malloc(sizeof(node));
	if (!(*tree)) return ERROR;
	(*tree)->data = *str++;
	(*tree)->lchild = NULL;
	(*tree)->rchild = NULL;
	queue[rear] = *tree;
	rear = (rear + 1) % 100;

	while (rear != front)
	{
		back = queue[front];
		front = (front + 1) % 100;

		// �����ַ���ʱ�򣬼�������
		if (*str != '\0')
		{
			// ��Ϊ�ڴ�����ʱ�򣬾��Ѿ������ӵ�
			// ָ���ʼ���� NULL ��
			// ���� str == '#' ��������Բ��ٸ�ֵ�� 
			if (*str != '#')
			{
				// ��������
				back->lchild = (node *)malloc(sizeof(node));
				if (!back->lchild) return ERROR;

				back->lchild->data = *str;
				back->lchild->lchild = NULL;
				back->lchild->rchild = NULL;
				// �����ǣ���Ӽ�¼
				queue[rear] = back->lchild;
				rear = (rear + 1) % 100;
			}
			str++;

			if (*str != '#')
			{
				// �����Һ���
				back->rchild = (node *)malloc(sizeof(node));
				if (!back->rchild) return ERROR;

				back->rchild->data = *str;
				back->rchild->lchild = NULL;
				back->rchild->rchild = NULL;
				queue[rear] = back->rchild;
				rear = (rear + 1) % 100;
			}
			str++;
		}
	}
	return OK;
}

// �������
status first_tra(btree *tree)
{
	printf("%c, ", tree->data);
	if (tree->lchild)
		first_tra(tree->lchild);
	if (tree->rchild)
		first_tra(tree->rchild);
	return OK;
}

int main(void)
{
	btree *tree;
	char buffer[100] = {0};

	// �����������
	// ABECDFGH###J##I######
	// AB#CD##EF#G##
	printf("��ν���������: ");
	scanf("%s", buffer);
	create(&tree, buffer);
	printf("\n�������: ");
	first_tra(tree);
	printf("\n");

	return 0;
}