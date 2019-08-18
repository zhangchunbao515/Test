
// ƽ�����������ز��� (AVL ��)
// ��Ҫ����, ���� insertAVL(), ɾ�� deleteAVL()
// ���������Ѿ������������㷨��, �� 235 ҳ���ķ�ͼ

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int elemtype;
typedef int status;
#define OK 1
#define ERROR 0

// LH, EH, RH, �ֱ��ʾ��������, ƽ��, ��������
#define LH +1
#define EH  0
#define RH -1

// ƽ�����������ṹ
typedef struct bnode
{
	short int bf;			// ƽ������
	elemtype data;
	bnode *lchild;
	bnode *rchild;
}AVLtree, bnode;

// -----------------ƽ�����������ת�㷨-------------------
// ����һ������, ���㷨���Կ���ͼʾ��д
void left(AVLtree **tree)
{
	bnode *rc = (*tree)->rchild;
	if (rc)
	{
		(*tree)->rchild = rc->lchild;
		rc->lchild = *tree;
		*tree = rc;		// �Һ��ӳ�Ϊ�¸�
	}
}

void right(AVLtree **tree)		// ����һ������
{
	bnode *lc = (*tree)->lchild;
	if (lc)
	{
		(*tree)->lchild = lc->rchild;
		lc->rchild = *tree;
		*tree = lc;		// ���ӳ�Ϊ�¸�
	}
}

// ��ƽ���ͨ�׽���: �Ѷ��������ұ߳�
void rightbalence(AVLtree **tree)	// ������ƽ��
{
	bnode *lc = (*tree)->lchild;

	// �㷨�� 235 ҳͼ (a)
	if (lc->bf == LH)	// ͨ��ƽ������, �������뵽���ı�
	{
		(*tree)->bf = lc->bf = EH;
		right(tree);
	}
	else	// lc->bf == RH, ���뵽�� lc �ұ�
	{
		// �ȵ�����ת���ƽ������, �㷨��ͼ (b)
		switch (lc->rchild->bf)
		{
		case LH : 
			lc->bf = EH;   (*tree)->bf = RH;   break;
		case EH : 
			lc->bf = (*tree)->bf = EH;   break;
			// ��������� lc->rchild ��Ҷ�ӽ������
			// �������, ȫ��ƽ��, ������ EH
		case RH : 
			lc->bf = LH;   (*tree)->bf = EH;   break;
		}
		lc->rchild->bf = EH;
		// �ȵ���������, �ڵ������
		right( &((*tree)->lchild) );
		left(tree);
	}
}

void leftbalence(AVLtree **tree)	// ������ƽ��
{
	bnode *rc = (*tree)->rchild;

	if (rc->bf == RH)		// �㷨��ͼ (c)
	{
		rc->bf = (*tree)->bf = EH;
		left(tree);
	}
	else 
	{
		switch (rc->lchild->bf)	// �㷨��ͼ (d)
		{
		case LH : 
			(*tree)->bf = EH;   rc->bf = RH;   break;
		case EH : 
			(*tree)->bf = rc->bf = EH;   break;
		case RH : 
			(*tree)->bf = LH;   rc->bf = EH;   break;
		}
		rc->lchild->bf = EH;
		right( &((*tree)->rchild) );
		left(tree);
	}
}

// ---------------------ƽ��������Ĳ����㷨-----------------------
// taller ����ʾ���Ƿ�����, �������, Ҫ����ƽ������
// ������ƽ�����Ӻ�, ���־���ֵ������ 2, Ҫ������ת����
status insertAVL(AVLtree **tree, elemtype data, short int *taller)
{
	if (!(*tree))		// û��������Ͳ���
	{
		*tree = (bnode *)malloc(sizeof(bnode));
		(*tree)->bf = EH;
		(*tree)->lchild = (*tree)->rchild = NULL;
		(*tree)->data = data;
		*taller = 1;	// ������һ�㺯��, �߶ȷ����ı仯, Ҫ�������ӵ���
	}
	else if ((*tree)->data == data)	// ������
	{
		*taller = 0;
		return ERROR;
	}
	else if (data < (*tree)->data)
	{
		if (!insertAVL( &((*tree)->lchild), data, taller))
			return ERROR;

		// ��ʱ�Ѳ���������, ����ʱ, �����߶ȱ仯û
		if (*taller)		// ����߶ȱ仯, Ҫ�����Ӹ���ƽ������
		{
			switch ((*tree)->bf)
			{
			case LH :	// ������߸ߵ�, ��������ֶ�һ��, Ҫ������������ƽ��
				rightbalence(tree);
				*taller = 0;
				break;
			case EH :			// ����ƽ���, ������߶���һ��
				(*tree)->bf = LH;
				*taller = 1;		// �߶�����, ����µĲ�ƽ��
				break;
			case RH :			// �����ұ߸ߵ�, ��������ֶ�һ��, ����ƽ��
				(*tree)->bf = EH;
				*taller = 0;		// �߶�û�仯
				break;
			}
		}
	}
	else	// ������������
	{
		if (!insertAVL( &((*tree)->rchild), data, taller))
			return ERROR;
		if(*taller)
		{
			// ���뵽����������, �Ҹ߶ȱ仯��, ��������ͬ��
			switch ((*tree)->bf)
			{
			case LH : 
				(*tree)->bf = EH;   *taller = 0;   break;
			case EH : 
				(*tree)->bf = RH;   *taller = 1;   break;
			case RH : 
				leftbalence(tree);  *taller = 0;   break;
				// �ұ߸�����, ��������
			}
		}
	}
	return OK;
}

// ------------------ƽ�������ɾ���㷨-------------------
// ���ҵ��ý��, ����ɾ��, ɾ����, �ٽ��е�����ƽ��
status delete_s(bnode *p, bnode **tree)
{
	bnode *del = *tree;		// ��ɾ�����
	bnode *pre = NULL;		// del ǰ��
	bnode *fpre = NULL;		// del ǰ����˫��

	if (!del) return ERROR;
	if (!del->lchild)			// ���ӿ�
	{
		if (!p) *tree = del->rchild;
		else if (p->lchild == del) p->lchild = del->rchild;
		else p->rchild = del->rchild;
	}
	else if (!(*tree)->rchild)		// �Һ��ӿ�
	{
		if (!p) *tree = del->lchild;
		else if (p->lchild == del) p->lchild = del->lchild;
		else p->rchild = del->lchild;
		
	}
	else	// ���Ҷ�����
	{
		pre = del->lchild;
		while (pre->rchild) 
		{
			fpre = pre;
			pre = pre->rchild;
		}
		del->data = pre->data;		// ǰ���滻
		if (!fpre) del->lchild = pre->lchild;
		else fpre->rchild = pre->lchild;
		del = pre;		// ɾ��ǰ��
	}
	free(del);
	return OK;
}

// �ҵ���ɾ��, p ��˫�׽��, tree ����, data ��ɾ��
status find_and_del(AVLtree *p, AVLtree **tree, elemtype data)
{
	if (!(*tree)) return ERROR;
	else if ((*tree)->data == data) return delete_s(p, tree);
	else if (data < (*tree)->data)
		return find_and_del(*tree, &( (*tree)->lchild ), data);
	else return find_and_del(*tree, &( (*tree)->rchild ), data);
}

// ��һ��������, ����Ϊƽ�������
int adjust(AVLtree **tree)
{
	int left, right;	// ��¼�������

	if (!(*tree)) return 0;
	left = adjust( &((*tree)->lchild) );
	right = adjust( &((*tree)->rchild) );

	// ���ݵ�ʱ��, ���ϵ���
	(*tree)->bf = left - right;
	if ((*tree)->bf > 1)		// ��߸���
		rightbalence(tree);
	else if ((*tree)->bf < -1)	// �ұ߸���
		leftbalence(tree);

	// �������
	return (left > right ? left : right) + 1;
}

// ɾ������������
status deleteAVL(AVLtree *p, AVLtree **tree, elemtype data)
{
	if (find_and_del(p, tree, data))
	{
		adjust(tree);		// ����������ƽ��
		return OK;
	}
	return ERROR;
}

// �ݹ��� ASL, num ������, len �ܳ���, flood �ݹ����
void ASL_s(AVLtree *tree, int *num, double *len, int flood)
{
	if (!tree) return ;

	(*num)++;   (*len) += flood;
	// �ۼ��굱ǰ���, �������µݹ�
	ASL_s(tree->lchild, num, len, flood + 1);
	ASL_s(tree->rchild, num, len, flood + 1);
}

double ASL(AVLtree *tree)		// ����ƽ�����ҳ��� ASL
{
	int num = 0;
	double len = 0.0;

	ASL_s(tree, &num, &len, 1);
	if (num == 0) return 0;
	else return len / num;
}

int balence(AVLtree *tree)		// �ж��Ƿ�ƽ��
{
	int a, b;

	if (!tree) return 0;

	a = balence(tree->lchild);
	b = balence(tree->rchild);

	// ����һ����ƽ��ͷ��� -1, ���򷵻����
	if (a == -1 || b == -1 || abs(a - b) > 1) return -1;
	else return (a > b ? a : b) + 1;
}

int depth(AVLtree *tree)	// �����
{
	int a, b;

	if (!tree) return 0;
	a = depth(tree->lchild);
	b = depth(tree->rchild);
	return (a > b ? a : b) + 1;
}

void mid_tra(AVLtree *tree)	// �������
{
	if (tree)
	{
		mid_tra(tree->lchild);
		printf("%d, ", tree->data);
		mid_tra(tree->rchild);
	}
}

void first(AVLtree *tree)	// �������
{
	if (tree)
	{
		printf("%d, ", tree->data);
		first(tree->lchild);
		first(tree->rchild);
	}
}

void destory(AVLtree *tree)	// ������
{
	if (tree)
	{
		destory(tree->lchild);
		destory(tree->rchild);
		free(tree);
	}
}

char display(AVLtree *tree)	// ������ʾģ��
{
	char c;

	printf("\n�������: ");
	first(tree);
	printf("\n�������: ");
	mid_tra(tree);
	printf("\n\nƽ�����ҳ���: %.4lf         ", ASL(tree));
	printf("���: %d     ", depth(tree));
	if (balence(tree) == -1) printf("����ƽ��!\n");
	else printf("ƽ��!\n");
	
	printf("\n�� c ������, ���س�����...\n");
	getchar();    c = getch();
	system("cls");
	return c;
}

int main(void)
{
	AVLtree *tree = NULL;
	short int taller;
	int data;
	short int times = 2;

	while (times--)
	{
		while (1)		// �������
		{
			printf("������Ҫ���ҵ�Ԫ��: ");
			scanf("%d", &data);
			if (insertAVL(&tree, data, &taller))	// ����
				printf("\n��Ԫ�ز�����, �Ѳ���!\n");
			else printf("\n�ҵ�!\n");
			
			if (display(tree) == 'c') break;
		}
		while (1)		// ɾ������
		{
			printf("������Ҫɾ����Ԫ��: ");
			scanf("%d", &data);
			if (deleteAVL(NULL, &tree, data))	// ɾ��
				printf("\n�ɹ�ɾ��!\n");
			else printf("\n��Ԫ�ز�����!\n");
			
			if (display(tree) == 'c') break;
		}
	}
	// �ٴβ���...
	destory(tree);
	return 0;
}
