
// �������������ز���

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int elemtype;
typedef int status;
#define OK 1
#define ERROR 0

// ����������
typedef struct bnode
{
	elemtype data;
	bnode *lchild;
	bnode *rchild;
}btree, bnode;


// ����һ��Ԫ�� data, �� back ���ص�ַ, p �� tree ��˫��
status search(btree **tree, btree *p, elemtype data, bnode **back)
{
	if (!(*tree)) 
	{
		*back = p;		// �Ҳ����ͷ��������˫��
		return ERROR;	// ����������
	}
	else if ((*tree)->data == data) return OK;
	else if (data < (*tree)->data) 
		return search( &((*tree)->lchild), *tree, data, back);
	else 
		return search( &((*tree)->rchild), *tree, data, back);
	// ����ֱ�ӷ���������ֵ
}

// ����һ�������ڵ�Ԫ��, �����ڷ��� OK
status insert(btree **tree, elemtype data)
{
	bnode *add;		// ��������˫��
	bnode *n;

	if (!search(tree, NULL, data, &add))
	{
		// �����������Ԫ�ؾͲ��� 
		n = (bnode *)malloc(sizeof(bnode));
		n->data = data;
		n->lchild = n->rchild = NULL;

		// add �Ǵ����������һ�����  add -> new_node
		if (!add) *tree = n;
		else
		{
			if (data < add->data)
				add->lchild = n;
			else add->rchild = n;
		}
		return ERROR;
	}
	else return OK;
}

// ɾ��һ�����, �㷨1: �ؽ�������
// ɾ��һ����� cur, ���Ҷ�����ʱ
// ɾ�� cur ʱ,  cur �������� f �̳�
//  cur ���Һ���, �ӵ����ӵ����ұ�
status del(bnode *f, bnode **node)
{
	bnode *cur = *node;		// cur ��ɾ���Ľ��

	if (!cur->rchild)	// ��������
	{
		// (!f) û��˫�׵Ľ����Ǹ�
		if (!f) *node = cur->lchild;
		else if (f->lchild == cur)  f->lchild = cur->lchild;
		else f->rchild = cur->lchild;
	}
	else if (!cur->lchild)	// ��������
	{
		if (!f) *node = cur->rchild;
		else if (f->lchild == cur)  f->lchild = cur->rchild;
		else f->rchild = cur->rchild;
	}
	else	// ���Ҷ�����, �㷨����
	{
		// �����������������������ұ� (��������)
		cur = (*node)->lchild;
		while (cur->rchild)  cur = cur->rchild;
		cur->rchild = (*node)->rchild;		// �ؽ�������

		cur = *node;
		if (!f) *node = cur->lchild;	// ɾ���Ǹ�, ֱ���ڸ����ؽ�
		else if (f->lchild == cur) 
			f->lchild = cur->lchild;	// f ���Ӽ̳�������
		else 
			f->rchild = cur->lchild;	// f �Һ��Ӽ̳�������
	}
	free(cur);		// �ͷŵ� cur
	return OK;
}

// ɾ��һ�����, �㷨2: ǰ���滻��
// ��ǰ�����Լ���λ��, �ͷ�ǰ�����
// ���Ҷ���Ϊ��ʱ, ǰ�����ض�û�������� (��������)
status del2(bnode *f, bnode **node)
{
	bnode *pre;		// ǰ�����
	bnode *fpre;	// ǰ����˫��
	bnode *cur = *node;

	if (!cur->lchild)		// ��������
	{
		if (!f) *node = cur->rchild;
		else if (f->lchild == cur) f->lchild = cur->rchild;
		else f->rchild = cur->rchild;
	}
	else if (!cur->rchild)	// ��������
	{
		if (!f) *node = cur->lchild;
		else if (f->lchild == cur) f->lchild = cur->lchild;
		else f->rchild = cur->lchild;
	}
	else	// ���Ҷ�����
	{
		pre = cur->lchild;		// pre ��ǰ��
		while (pre->rchild)  
		{
			fpre = pre;		// ��¼˫�׽��, �����ͷ� pre
			pre = pre->rchild;
		}
		cur->data = pre->data;		// ǰ���滻�� node
		if (pre == cur->lchild)  
			cur->lchild = pre->lchild;	// �����������յ��ؽ�
		else fpre->rchild = pre->lchild;
		// ��ʱ pre û��������, ֻ���ؽ�������
		cur = pre;   // pre �Ǵ��ͷŵĽ��, �������ͷ�
	}
	free(cur);
	return OK;
}

// ����һ����ɾ�����, f ��˫��ָ��
// ��ΪҪֱ��������ɾ��, Ҫô��ָ���ָ��, Ҫô��ָ�������
status remove(btree *f, btree **tree, elemtype data)
{
	if (!(*tree)) return ERROR;
	else if ((*tree)->data == data)
	{
		return del(f, tree);
//		return del2(f, tree);
//		del() �� del2() ������ɾ���㷨, ����ʹ��
	}
	else if (data < (*tree)->data)
		return remove(*tree, &((*tree)->lchild), data);
	else
		return remove(*tree, &((*tree)->rchild), data);
}

// �ݹ��� ASL, num ������, len �ܳ���, flood �ݹ����
void ASL_s(btree *tree, int *num, double *len, int flood)
{
	if (!tree) return ;

	(*num)++;   (*len) += flood;
	// �ۼ��굱ǰ���, �������µݹ�
	ASL_s(tree->lchild, num, len, flood + 1);
	ASL_s(tree->rchild, num, len, flood + 1);
}

double ASL(btree *tree)		// ����ƽ�����ҳ��� ASL
{
	int num = 0;
	double len = 0.0;

	ASL_s(tree, &num, &len, 1);
	if (num == 0) return 0;
	else return len / num;
}

int depth(btree *tree)		// �����
{
	int a, b;

	if (!tree) return 0;

	a = depth(tree->lchild);
	b = depth(tree->rchild);

	return (a > b ? a : b) + 1;
}

void mid_tra(btree *tree)	// �������
{
	if (tree)
	{
		mid_tra(tree->lchild);
		printf("%d, ", tree->data);
		mid_tra(tree->rchild);
	}
}

void destory(btree *tree)	// ������
{
	if (tree)
	{
		destory(tree->lchild);
		destory(tree->rchild);
		free(tree);
	}
}

char display(btree *tree)	// ������ʾģ��
{
	char c;

	printf("\n�������: ");
	mid_tra(tree);
	printf("\n\nƽ�����ҳ���: %.4lf\t\t", ASL(tree));
	printf("�������: %d\n", depth(tree));
	
	printf("\n�� c ������, ���س�����...\n");
	getchar();    c = getch();
	system("cls");

	return c;
}

int main(void)
{
	btree *tree = NULL;
	int data;

	while (1)		// �������
	{
		printf("������Ҫ���ҵ�Ԫ��: ");
		scanf("%d", &data);
		if (!insert(&tree, data))		// ����
			printf("\n��Ԫ�ز�����, �Ѳ���!\n");
		else printf("\n�ҵ�!\n");

		if (display(tree) == 'c') break;
	}
	while (1)		// ɾ������
	{
		printf("������Ҫɾ����Ԫ��: ");
		scanf("%d", &data);
		if (!remove(NULL ,&tree, data))		// ɾ��
			printf("\n��Ԫ�ز�����, ɾ��ʧ��!\n");
		else printf("\n��ɾ��!\n");

		if (display(tree) == 'c') break;
	}
	destory(tree);
	return 0;
}
