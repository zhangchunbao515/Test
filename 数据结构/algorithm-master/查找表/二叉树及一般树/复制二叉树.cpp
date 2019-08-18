/* --------------------------------------
// �������ĸ���
// ����һ�� A ��, �� A �����Ƶ� B ��
// ���ֱ�����ʽ, �����Է��ʵ�ȫ�����
// �������������������и���
//
// ����������ַǵݹ�����ļ�����
----------------------------------------*/

#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef char elemtype;

// �������洢�ṹ
typedef struct btnode
{
	elemtype data;
	btnode *lchild;
	btnode *rchild;
}btnode;

// �����ַ�������
char *create(btnode **t, char *str)
{
	if (*str == '#') (*t) = NULL;
	else if (*str != '\0')
	{
		(*t) = (btnode *)malloc(sizeof(btnode));
		if (!(*t)) return NULL;
		(*t)->data = *str;
		(*t)->lchild = NULL;
		(*t)->rchild = NULL;
		// �ݹ齨��
		str = create(&((*t)->lchild), str + 1);
		str = create(&((*t)->rchild), str + 1);
	}
	return str;
}

// ������� (�ǵݹ�)
void first_tra_s(btnode *t)
{
	btnode *stack[100];
	int top = 0;

	while (t || top)
	{
		while (t)
		{
			stack[top++] = t;
			printf("%c, ", t->data);
			t = t->lchild;
		}
		// ��̽��ȥһ��
		if (top) t = stack[--top]->rchild;
	}
}

// ������� (�ǵݹ�)
void mid_tra_s(btnode *t)
{
	btnode *stack[100];
	int top = 0;

	while (t || top)
	{
		// �����ߵ���
		while (t)
		{
			stack[top++] = t;
			t = t->lchild;
		}
		// ��ʱ���ߵ���, ��ջһ������
		if (top != 0)
		{
			t = stack[--top];
			printf("%c, ", t->data);
		}
		// ������Һ���, ���ҿ�һ��
		// û�о�Ҫ��ʱ�� t �ÿ�, ��ֹ�������while�߻�ȥ
		if (t->rchild) t = t->rchild;
		else t = NULL;
	}
}

// ������� (�ǵݹ�)
void last_tra_s(btnode *t)
{
	btnode *stack[100];
	int top = 0;
	btnode *right;		// ��¼ǰ�����

	do	// ��ִ��, ֱ��ջΪ��
	{
		while (t)	// �ߵ����
		{
			stack[top++] = t;
			t = t->lchild;
		}
		while (top)
		{
			right = t;
			t = stack[top - 1];		// ȡջ��
			if (t->rchild == NULL || t->rchild == right)
			{
				printf("%c, ", t->data);
				top--;		// ȷ���Ժ���ܳ�ջ
			}
			else	// ���ֿ��������ߵ���
			{
				t = t->rchild;
				break;
			}
		}
	} while (top);
}

// ������� t ��, ���Ƶ� n ��
// ���ƴ������������㷨
void copytree(btnode *t, btnode **n)
{
	if (!t) (*n) = NULL;
	else 
	{
		(*n) = (btnode *)malloc(sizeof(btnode));
		if (!(*n)) return ;
		(*n)->data = t->data;

		// ֱ���� n �����Һ����Ͻ����½��
		copytree(t->lchild, &((*n)->lchild));
		copytree(t->rchild, &((*n)->rchild));
	}
}

int main(void)
{
	btnode *tree;
	btnode *tree2;
	char str[100];

	// ABCH###D##EFJ###G#I##
	printf("�����������: ");
	scanf("%s", str);
	create(&tree, str);

	printf("tree����: ");
	mid_tra_s(tree);
	printf("\n");

	copytree(tree, &tree2);   // ���ƶ�������tree2
	printf("tree2 :\n");
	printf("�������: ");
	first_tra_s(tree2);
	printf("\n");
	printf("�������: ");
	mid_tra_s(tree2);
	printf("\n");
	printf("�������: ");
	last_tra_s(tree2);
	printf("\n");

	return 0;
}