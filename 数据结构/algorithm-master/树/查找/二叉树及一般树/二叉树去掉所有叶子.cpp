#include <stdio.h>
#include <malloc.h>

#define OK 1
#define ERROR 0
typedef int status;

typedef struct 
{
	char key;
	char *info;
}elemtype;

// ��������
typedef struct btnode
{
	elemtype data;
	btnode *lchild;
	btnode *rchild;
}btnode;

// ��������רһ�ԣ����Բ����ַ���飬
// �ַ���齻����������
char* create(btnode **tree, char *str)
{
	if (str[0] == '\0') return ERROR;
	if (*str == '#') *tree = NULL;
	else 
	{
		// �����½��
		*tree = (btnode *)malloc(sizeof(btnode));
		if (!(*tree)) return ERROR;
		(*tree)->data.key = *str;
		(*tree)->lchild = NULL;
		(*tree)->rchild = NULL;
	
		// ����
		str = create(&((*tree)->lchild), str + 1);
		str = create(&((*tree)->rchild), str + 1);
	}
	return str; 
}

// ����ݹ����
status first_tra(btnode *tree)
{
	if (tree)
	{
		printf("%c, ", tree->data.key);
		first_tra(tree->lchild);
		first_tra(tree->rchild);
		return OK;
	}
	return ERROR;
}

int lenth(btnode *tree)
{
	int left, right;

	// ����������� 0
	if (!tree) return 0;
	else 
	{
		left = lenth(tree->lchild);
		right = lenth(tree->rchild);
		left = left > right ? left : right;
	}
	return left + 1;
}

// ȥ��������Ҷ��
status cuttree(btnode **tree, btnode *parent)
{
	if (!(*tree)) return ERROR;
	else
	{
		// �����Ҷ�Ӿ��ͷŵ�
		if ((*tree)->lchild == NULL 
			&& (*tree)->rchild == NULL)
		{
			free(*tree);
			if (!parent) *tree = NULL;
			else if (parent->lchild == *tree)
				parent->lchild = NULL;
			else if (parent->rchild == *tree)
				parent->rchild = NULL;
		}
		else   // ����Ҷ�Ӿͼ�����������
		{
			cuttree(&((*tree)->lchild), *tree);
			cuttree(&((*tree)->rchild), *tree);
		}
	}
	return OK;
}

int main(void)
{
	btnode *tree;
	char str[100] = {0};

	// ABCH###D##EFJ###G#I##
	printf("��������");
	scanf("%s", str);
	create(&tree, str);
	printf("���������");
	first_tra(tree);
	printf("\n������ȣ�%d\n", lenth(tree));
	
	while (1)   // ����ȥ��Ҷ��
	{
		getchar();
		cuttree(&tree, NULL);
		printf("\nȥ��Ҷ�Ӻ�");
		first_tra(tree);
		printf("\n������ȣ�%d\n", lenth(tree));
	}

	return 0;
}
