// ��������������������

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int status;
typedef char elemtype;

#define ERROR 0
#define OK 1

typedef enum {link, thread} tag;
// link �Ǻ��ӣ�thread ������

// ��������������ṹ
typedef struct btnode
{
	elemtype data;
	btnode *lchild;
	btnode *rchild;
	tag ltag;
	tag rtag;
}btnode;

// ����str�������������ص�ַ
char *create(btnode **tree, char *str)
{
	if (*str != '\0')
	{
		if (*str == '#') *tree = NULL;
		else
		{
			*tree = (btnode *)malloc(sizeof(btnode));
			if (!(*tree)) exit(0);
			(*tree)->data = *str;
			(*tree)->lchild = NULL;
			(*tree)->rchild = NULL;
			str = create(&((*tree)->lchild), str + 1);
			str = create(&((*tree)->rchild), str + 1);
		}
	}
	return str;
}

status destory(btnode *tree)
{
	if (tree->ltag == link || tree->ltag == link)
	{
		destory(tree->lchild);
		destory(tree->rchild);
		free(tree);
	}
	return OK;
}

// ----------��������������---------------

// �ǵݹ飬���������
status mid_tra_s(btnode *tree)
{
	btnode *stack[150] = {0};
	int top = 0;
	btnode *back;
	
	while (top || tree)
	{
		// һֱ�����ߵ���ͷ
		while (tree)
		{
			stack[top++] = tree;
			tree = tree->lchild;
		}
		// ÿ��������һ����������û���Һ���
		if (top)
		{
			back = stack[--top];
			printf("%c ", back->data);
			tree = back->rchild;
		}
	}
	return OK;
}

// ����������
// �����������ݹ鲿��
btnode *threading(btnode *tree, btnode *pre)
{
	if (tree)
	{
		pre = threading(tree->lchild, pre);
		// ������
		// ����������У���������ǰ����Ϣ
		if (!tree->lchild)
		{
			tree->lchild = pre;
			tree->ltag = thread;
		}
		else tree->ltag = link;
		// ���˫�׵��Һ��ӿ��У��򱣴�����Ϣ��
		if (!pre->rchild)
		{
			pre->rchild = tree;
			pre->rtag = thread;
		}
		else pre->rtag = link;
		pre = tree;		// �൱�� pre ������һ��
		pre = threading(tree->rchild, pre);
	}
	return pre;
}

// ����������
status threadtree(btnode *th, btnode *tree)
{
	btnode *pre;	// ��¼��һ�����ʵĽ��

	if (!tree) return ERROR;
	th->ltag = link;
	th->lchild = tree;
	th->rtag = thread;
	th->rchild = th;	// ��ָ���ָ
	
	pre = th;
	pre = threading(tree, pre);
	// ���һ���������
	pre->rchild = th;
	pre->rtag = thread;
	th->rchild = pre;

	return OK;
}

// ������������
status mid_tra_th(btnode *th)
{
	btnode *cur;

	cur = th->lchild;
	// ����ѭ������Ľ�����־��cur != head
	while (cur && cur != th)
	{
		// ��������������
		while (cur->ltag == link) 
			cur = cur->lchild;
		printf("%c ", cur->data);
		// ���ݺ�����������ϻ�ȥ��
		while (cur->rtag == thread && cur->rchild != th)
		{
			cur = cur->rchild;
			printf("%c ", cur->data);
		}
		cur = cur->rchild;
	}
	return OK;
}

// ------------�ǵݹ��������--------------
// �������
status first_tra_s(btnode *tree)
{
	btnode *stack[150] = {0};
	int top = 0;
	btnode *back;

	while (top != 0 || tree)
	{
		while (tree)
		{
			printf("%c ", tree->data);
			stack[top++] = tree;
			tree = tree->lchild;
		}
		if (top != 0)
		{
			back = stack[--top];
			tree = back->rchild;
		}
	}
	return OK;
}

// �����ǵݹ����
status last_tra_s(btnode *tree)
{
	btnode *stack[150] = {0};
	int top = 0;
	btnode *pre;

	stack[top++] = tree;	// ����ջ
	tree = tree->lchild;
	while (top != 0)
	{
		// ��ջ��������ȫ����ջ
		tree = stack[top-1];
		while (tree->lchild)
		{
			stack[top++] = tree->lchild;
			tree = tree->lchild;
		}
		// �ҵ�һ�����������ߵĽ����ջ
		pre = stack[top-1];
		while (top != 0)
		{
			tree = stack[top-1];
			if (tree->rchild==NULL || tree->rchild == pre) 
			{
				printf("%c ", tree->data);
				top--;
				pre = tree;
			}
			else 
			{
				stack[top++] = tree->rchild;
				break;
			}
		}
	}
	return OK;
}

// �����������ݹ鴦����
btnode *fthreading(btnode *tree, btnode *pre)
{
	if (tree)
	{
		// ����ǰ����Ϣ
		if (!tree->lchild)
		{
			tree->lchild = pre;
			tree->ltag = thread;
		}
		else tree->ltag = link;

		// ��������Ϣ
		if (!pre->rchild)
		{
			pre->rchild = tree;
			pre->rtag = thread;
		}
		pre = tree;
		if (tree->ltag != thread)
			pre = fthreading(tree->lchild, pre);
		if (tree->rtag != thread)
			pre = fthreading(tree->rchild, pre);
	}
	return pre;
}

// ������������
status fthreadtree(btnode *th, btnode *tree)
{
	btnode *pre;

	if (!tree) return ERROR;

	// ��ʼ������ͷ
	th->lchild = tree;
	th->ltag = link;
	th->rchild = th;
	th->rtag = thread;
	pre = th;

	pre = fthreading(tree, pre);
	pre->rchild = th;
	pre->rtag = thread;
	th->rchild = pre;
	return OK;
}

// ��������������
// ������Ӳ���������һֱ����ȥ
// Ȼ������������һ��
status first_tra_th(btnode *th)
{
	btnode *cur;

	if (!th->lchild) return ERROR;
	cur = th->lchild;
	while (cur && cur != th)
	{
		// ����ָ���������
		while (cur && cur->ltag == link)
		{
			printf("%c ", cur->data);
			cur = cur->lchild;
		}
		// ����������ȥ������ th ����
		while (cur && cur->rtag == thread && cur != th)
		{
			printf("%c ", cur->data);
			cur = cur->rchild;
		}
	}

	return OK;
}

int main(void)
{
	btnode *tree;
	btnode th;		// ��������ͷ
	btnode fth;		// ��������ͷ
	char buf[200] = {0};

	// -+a##*b##-c##d##/e##f##
	printf("����������������");
	gets(buf);
	create(&tree, buf);
	
	printf("\n��ͨ���������");
	last_tra_s(tree);

	printf("\n\n��ͨ���������");
	first_tra_s(tree);
	printf("\n");
	fthreadtree(&fth, tree);	// ����������
	printf("�������������");
	first_tra_th(&fth);			// ��������
	printf("\n");
	destory(tree);
	tree = NULL;

	create(&tree, buf);
	printf("\n��ͨ���������");
	mid_tra_s(tree);
	printf("\n");
	threadtree(&th, tree);		// ����������
	printf("�������������");
	mid_tra_th(&th);			// ��������
	printf("\n\n");
	destory(tree);
	tree = NULL;

	return 0;
}

