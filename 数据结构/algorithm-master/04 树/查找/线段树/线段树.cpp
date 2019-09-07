
// �߶����Ļ�������
// create()		�����߶���
// destory()	�����߶���
// insert()		��������
// remove()		ɾ������
// query()		��ѯ��㸲�Ǵ���
// sum()		��ѯ�������к�
// max()		��ѯ�������ֵ


// �ٸ��򵥵�����, ���ݵ��麣�������Ʊϵͳ
// ��ϵͳ������ [���� - �麣]
// ��������, ������Ʊ, ��������һ�� [�麣 - ��ɽ] ��Ʊ
// ɾ������, ������Ʊ, ǰ����Ҫ��������Ʊ, ������Ʊʧ��
// ��ѯ�������ֵ, �ĸ�վ�۵�Ʊ���
// ��ѯ�������к�, ���ĵ���һ�����˼���Ʊ
// ��ѯ��㸲�Ǵ���, �����ѯ��ɽվ, ��ʱ�г����м���Ʊ
// Ʊ�����ܳ����г�����λ��, ��λ��������Ʊ������ʣ��Ʊ��

// �㷨���ܷ���
// ������ n ��Ʊ, �� m ����վҪ��ѯʣ��Ʊ��
// ��ͨ�������ж� n �ų�Ʊ, �м��Ÿ����˵� k ����վ, ���Ӷ� O(m*n)
// �����Ϊ m ���߶���, ��Ȳ����� log m, һ�β�ѯ�� log m ��
// n ��Ʊ��ѯ, ���Ը��Ӷ��� O(n log m)


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int status;
#define OK 1
#define ERROR 0

// �߶����ö���������, ���һ��, ������Ҳ��, ��Ϊ����ȫ������
typedef struct node 
{
	int left, right;
	int num;		// ��¼����
	node *lchild;
	node *rchild;
}node, itree;


// �����߶���, [left..right]
void create(itree **tree, int left, int right)
{
	int mid;

	if (left > right) return ;
	
	*tree = (node *)malloc(sizeof(node));
	(*tree)->lchild = (*tree)->rchild = NULL;
	(*tree)->left = left;
	(*tree)->right = right;
	(*tree)->num = 0;

	if (left != right)		// ���������, ����һ�������
	{
		mid = (left + right) / 2;
		create( &((*tree)->lchild), left, mid);
		create( &((*tree)->rchild), mid+1, right);
	}
}

void destory(itree *tree)	// �����߶���
{
	if (tree)
	{
		destory(tree->lchild);
		destory(tree->rchild);
		free(tree);
	}
}

// �����ϲ���һ������, ��������� num
// ������ƥ��, ���¼�� +1
// ���������ָ�����, ֱ���ŵ����ʵĽ����
void insert(itree *tree, int left, int right, int num)
{
	int mid;

	if (tree->left == left && tree->right == right)
		tree->num += num;	// ƥ��ɹ�
	else 
	{	
		if (!(tree->lchild && tree->rchild)) return ;
		// ƥ��ʧ��, �����ָ�
		mid = (tree->left + tree->right) / 2;
		if (right <= mid)   // ������ȫ�����
		{
			insert(tree->lchild, left, right, num);
		}
		else if (left > mid)  // ������ȫ���ұ�
		{
			insert(tree->rchild, left, right, num);
		}
		else
		{	// ���Ҷ���, Ҫ�ָ� [left, mid], [mid+1, right]
			insert(tree->lchild, left, mid, num);
			insert(tree->rchild, mid+1, right, num);
		}
	}
}

// ɾ��һ�������㷨�Ͳ���ĺ�����, ������һ���������
void remove(itree *tree, int left, int right, int num)
{
	int mid;

	// ƥ�䵽�ɹ��������, �������κ�����
	if (tree->left == left && tree->right == right)
	{
		if (tree->num >= num) tree->num -= num;
		else
		{	// ��ʱ tree->num < num
			// ����ûд����, �������Ʊϵͳ��˵
			// �������Ʊ����������, ��ʾ��Ʊʧ��!
		}
	}
	else 
	{	// û������
		if (!(tree->lchild && tree->rchild)) return ;
		mid = (tree->left + tree->right) / 2;
		if (right <= mid)
			remove(tree->lchild, left, right, num);
		else if (left > mid)
			remove(tree->rchild, left, right, num);
		else 
		{	// �ָ�����
			remove(tree->lchild, left, mid, num);
			remove(tree->rchild, mid+1, right, num);
		}
	}
}

// ��ѯ n �ĸ�����, �Ӹ�������, ͳ�� num ��, O(log n)
int query(itree *tree, int n)
{
	int sum = 0;
	int mid;

	if (!tree) return 0;
	mid = (tree->left + tree->right) / 2;
	if (n <= mid)	// ������
		sum += query(tree->lchild, n);
	else		// �Һ�����
		sum += query(tree->rchild, n);

	return sum + tree->num;  // ���ϵ�ǰ���� num
}

// ͳ�� [left..right] ���и��Ǵ���, Ҳ����ͳ��Ʊ�� 
int sum(itree *tree, int left, int right)
{
	int re = 0;
	int i;

	for (i=left; i<=right; i++)
		re += query(tree, i);
	return re;
}

// pos, cnt ����λ�ú�������
void max(itree *tree, int left, int right, int *pos, int *cnt)
{
	int i;
	int tmp;

	*pos = 0;
	*cnt = -0xFFFFFF;
	for (i=left; i<=right; i++)
	{
		tmp = query(tree, i);
		if (tmp > *cnt) 
		{  *cnt = tmp;   *pos = i;  }
	}
}

void show(itree *root, itree *tree)	// �鿴���н��
{
	if (tree)
	{
		printf("[%d, %d] ", tree->left, tree->right);
		printf("��¼�� %d\n", tree->num);
		show(root, tree->lchild);
		show(root, tree->rchild);
	}
}

inline char display(itree *tree)	// ��ʾ
{
	char c;
	int i;

	getchar();
	show(tree, tree);
	for (i=tree->left; i<=tree->right; i++)
		printf("\n %d �ĸ��Ǵ��� %d", i, query(tree, i));
	printf("\n\n�� c �˳�, �س�����...\n");
	c = getch();   system("cls");
	return c;
}

int main(void)
{
	itree *tree = NULL;
	int left, right, n;
	int cnt, pos;

	printf("�������߶�������: ");
	scanf("%d %d", &left, &right);
	create(&tree, left, right);
	while (1)		// �������, ��Ʊ
	{
		printf("��������估�������: ");
		scanf("%d %d %d", &left, &right, &n);
		insert(tree, left, right, n);
		if (display(tree) == 'c') break;
	}
	while (1)		// ɾ������, ��Ʊ
	{
		printf("��Ҫɾ�����估ɾ������: ");
		scanf("%d %d %d", &left, &right, &n);
		remove(tree, left, right, n);
		if (display(tree) == 'c') break;
	}
	while (1)		// ��ѯ��㸲�Ǵ���, ����Ʊ��
	{	// ��һ���г�, �� 300 ����λ, ��ô��󸲸������� 300
		// ������������ 300, ����ʾƱ������!
		printf("������Ҫ��ѯ�Ľ��: ");
		scanf("%d", &n);
		printf("\n������: %d\n", query(tree, n));

		printf("\n�� c �˳�, �س�����...\n");
		if (getch() == 'c') {system("cls");   break;}
		system("cls");
	}
	printf("��ѯ�������к�, ����һ������: ");	// ͳ��Ʊ��
	scanf("%d %d", &left, &right);
	printf("\n�������к�: %d\n", sum(tree, left, right));

	// ��ѯ�������ֵ, ��СֵҲͬ��,
	printf("\n��ѯ�������ֵ, ����һ������: ");
	scanf("%d %d", &left, &right);
	max(tree, left, right, &pos, &cnt);
	printf("\n��󸲸ǵĽ��: %d    ������: %d\n\n", pos, cnt);

	destory(tree);
	return 0;
}
