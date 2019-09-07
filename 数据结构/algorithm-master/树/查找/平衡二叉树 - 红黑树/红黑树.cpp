
// ������Ĳ�����ɾ���㷨, ���Һ������������һ��
// �㷨������ ����� - �㷨����.txt
// ��Ҫ����:
// insert();			������
// insert_fixup();		�����޸�
// remove();			ɾ�����
// remove_fixup();		ɾ���޸�
// check();				������ṹ���


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int status;
typedef int elemtype;
#define OK 1
#define ERROR 0
typedef enum {RED, BLACK} c_type;	// ��ɫ����


// ��������ṹ
typedef struct node
{
	elemtype data;		// ������
	node *lchild;
	node *rchild;
	node *parent;
	c_type color;		// �����ɫ
}node, rb_tree;

node *nullnode = NULL;		// �ƽ��, ���������


inline node *gradepa(node *tree)	// ���游
{
	return tree->parent->parent;
}

inline node *uncle(node *tree)		// ������
{
	node *g = gradepa(tree);

	if (tree->parent == g->lchild)
		return g->rchild;
	else return g->lchild;
}

inline node *brother(node *tree)	// ���ֵ�
{
	if (tree == tree->parent->lchild)
		return tree->parent->rchild;
	else return tree->parent->lchild;
}

void left(node *tree)		// ��������
{
	node *rc = tree->rchild;

	// rc Ҫ��Ϊ�¸�
	if (tree->parent != nullnode) 
	{
		if (tree == tree->parent->lchild) 
			tree->parent->lchild = rc;
		else tree->parent->rchild = rc;
	}
	// �ؽ�˫��
	if (rc->lchild != nullnode) 
		rc->lchild->parent = tree;
	rc->parent = tree->parent;
	tree->parent = rc;
	// �ؽӺ���
	tree->rchild = rc->lchild;
	rc->lchild = tree;
}

void right(node *tree)		// ��������
{
	node *lc = tree->lchild;
	
	if (tree->parent != nullnode) 
	{
		if (tree == tree->parent->lchild) 
			tree->parent->lchild = lc;
		else tree->parent->rchild = lc;
	}
	if (lc->rchild != nullnode)
		lc->rchild->parent = tree;
	lc->parent = tree->parent;
	tree->parent = lc;
	tree->lchild = lc->rchild;
	lc->rchild = tree;
}

// �����޸�, ��ϸ�㷨�� ������㷨����.txt
void insert_fixup(rb_tree *tree)
{
	node *g, *p;
	node *u = uncle(tree);

	if (tree->parent == nullnode)
		tree->color = BLACK;		// �¸�, ֱ��Ϳ��
	else if (tree->parent->color == BLACK)
		return ;	// ��ĸ�Ǻ�ɫ��, ��ʱ�����ɫ�����κ��޸�
	else if (u != nullnode
		&& u->color == RED)	// ��Ӧ��� 3
	{
		u->color = tree->parent->color = BLACK;
		g = gradepa(tree);
		g->color = RED;
		insert_fixup(tree->parent->parent);
		// ���游�ĳɺ�ɫ, �ֿ��ܻ�����µĳ�ͻ, ���µݹ��޸�
	}
	else	// ��Ӧ��� 4, ����Ԥ����, ȫ����Ϊһ����
	{
		g = gradepa(tree);
		p = tree->parent;		// ���ҵ�֮����, תΪһ��
		if (p == g->lchild && tree == p->rchild)
		{
			left(tree->parent);
			tree = tree->lchild;
		}
		else if (p == g->rchild && tree == p->lchild)
		{
			right(tree->parent);
			tree = tree->rchild;
		}
		// �����Ӧ��� 5
		tree->parent->color = BLACK;
		g = gradepa(tree);
		g->color = RED;
		if (tree == tree->parent->lchild 
			&& tree->parent == g->lchild)
			right(tree->parent->parent);
		else left(tree->parent->parent);
	}
}

// �ݹ���벿��
status insert_s(rb_tree **tree, elemtype data, node *f)
{
	node *n;

	if (*tree == nullnode)		// û����������, Ҫ����
	{
		n = (node *)malloc(sizeof(node));
		n->color = RED;			// �²��������ɫҪ�Ǻ��
		n->data = data;
		n->lchild = n->rchild = nullnode;
		n->parent = f;
		*tree = n;
		insert_fixup(n);	// �����, ���ܻ��ƻ�����, ���в����޸�
		// ����һ��Ҫ n �ĵ�ַ, �������� tree
		// ��Ϊ����� tree ���ϸ���㺢�ӵĵ�ַ, �����
		return OK;
	}
	else if ((*tree)->data == data) return ERROR;	// �Ѵ���
	else if (data < (*tree)->data)
		return insert_s( &((*tree)->lchild), data, *tree);
	else return insert_s( &((*tree)->rchild), data, *tree);
}

// �Ȱ��ն���������ķ�ʽ����, ֮���ٽ������ʻָ�
status insert(rb_tree **tree, elemtype data)
{
	status s;
	s = insert_s(tree, data, nullnode);
	while ((*tree)->parent != nullnode) 
		*tree = (*tree)->parent;
	return s;
}

// ɾ�� del ��˫�׹�ϵ
void del_p(rb_tree *del, char r)
{
	if (del == del->parent->lchild)
	{
		if (r == 'L')
			del->parent->lchild = del->lchild;
		else del->parent->lchild = del->rchild;
	}
	else 
	{
		if (r == 'L')
			del->parent->rchild = del->lchild;
		else del->parent->rchild = del->rchild;
	}
}

// ɾ���޸�, ��ϸ�㷨�� ������㷨����.txt
void remove_fixup(rb_tree *tree, node *replace)
{
	node *s = brother(tree);

	if (tree->color == RED) return ;	// ɾ����ɫ�Ĳ����޸�
	else 
	{	/// ��ʱ tree �Ǻ�ɫ��
		if (replace->color == RED)		// ������Ǻ�ɫ��
			replace->color = BLACK;		// ��Ϊ��ɫ
		else
		{	// ��ʱ tree �ʹ���㶼�Ǻ�ɫ��
			if (tree->parent == nullnode) return ;
			else 
			{	// ��Ӧ ���2, �Ѻ�ɫ�ֵܵĺ�ɫ�Ƶ��Լ���ͷ��
				if (s->color == RED)
				{
					s->color = BLACK;
					tree->parent->color = RED;
					if (tree == tree->parent->lchild) 
						left(tree->parent);
					else right(tree->parent);
				}
				// �����Ӧ ���3, ȫ�����Ǻڵ�
				s = brother(tree);
				if (tree->parent->color == BLACK 
					&& s->color == BLACK 
					&& s->lchild->color == BLACK 
					&& s->rchild->color == BLACK)
				{
					s->color = RED;		// ���ֵܼӸ���ɫ
					remove_fixup(tree->parent, tree);
				}
				else	// ��� 4, ��˫�׵ĺ�ɫ�Ƶ��ֵ���
				{
					if (tree->parent->color == RED 
						&& s->color == BLACK 
						&& s->lchild->color == BLACK 
						&& s->rchild->color == BLACK)
					{
						tree->parent->color = BLACK;
						s->color = RED;
					}
					else	// ���5, �ֵܵĺ������к�ɫ 
					{		// Ҫת��һ����
						if (s->color == BLACK)
						{
							if (tree == tree->parent->lchild
								&& s->lchild->color == RED 
								&& s->rchild->color == BLACK)
							{
								s->color = RED;
								s->lchild->color = BLACK;
								right(s);
							}
							else if (tree == tree->parent->rchild
								&& s->lchild->color == BLACK
								&& s->rchild->color == RED)
							{
								s->color = RED;
								s->rchild->color = BLACK;
								left(s);
							}
						}
						// ���6, �� tree ��ͷ������һ����ɫ
						s = brother(tree);
						s->color = tree->parent->color;
						tree->parent->color = BLACK;
						if (tree == tree->parent->lchild)
						{
							s->rchild->color = BLACK;
							left(tree->parent);
						}
						else 
						{
							s->lchild->color = BLACK;
							right(tree->parent);
						} // case 6
					} // case 5
				} // case 4
			} // case 3
		} // case 2
	} // csae 1
}

// �Ȱ��ն����������ķ�ʽ�ҵ��ý��
// ��ͨ���ý��ļ�·������һ����ɫ���, ���ͷŵ���
status remove_s(rb_tree **tree, elemtype data)
{
	node *pre;
	node *del;

	if ((*tree) == nullnode) return ERROR;	// û��������
	else if ((*tree)->data == data)		// �ҵ���
	{
		// ��ʱҪɾ�� *tree, ����ǰ���滻��ɾ��
		// ����ɾ���Ĳ��� *tree �Ŀռ�, ��������ǰ��
		// ɾȥһ�����ǰ, ����˫�׹�ϵ, �������ӹ�ϵ
		del = *tree;
		switch ((del->lchild != nullnode) + 
			2 * (del->rchild != nullnode))
		{
		case 0 :					// ���Һ��ӽԿ�
			remove_fixup(del, del->lchild);		// ɾ���޸�
			if (del->parent == nullnode) *tree = nullnode;
			else del_p(del, 'L');   break;
		case 1 :					// ֻ������
			remove_fixup(del, del->lchild);
			del->lchild->parent = del->parent;
			if (del->parent == nullnode) 
				*tree = del->lchild;
			else del_p(del, 'L');   break;
		case 2 :					// ֻ���Һ���
			remove_fixup(del, del->rchild);
			del->rchild->parent = del->parent;
			if (del->parent == nullnode)
				*tree = del->rchild;
			else del_p(del, 'R');   break;
		case 3 :					// ��������
			pre = del->lchild;
			while (pre->rchild != nullnode) pre = pre->rchild;
			del->data = pre->data;		// ǰ���滻
			remove_fixup(pre, pre->lchild);
			pre->lchild->parent = pre->parent;
			del = pre;
			del_p(pre, 'L');   break;
		}
		free(del);
		return OK;
	}
	else if (data < (*tree)->data)
		return remove_s( &((*tree)->lchild), data);
	else return remove_s( &((*tree)->rchild), data);
}

status remove(rb_tree **tree, elemtype data)
{
	status s;
	node *cur = *tree;

	s = remove_s(tree, data);
	if (*tree != nullnode 
		&& (*tree)->parent != nullnode) 
	{
		cur = *tree;
		while (cur->parent != nullnode)
			cur = cur->parent;
		*tree = cur;
	}
	// ����ָ������, ��ת��ʱ����ᱻ�滻, �������»ص���
	return s;
}

// �������·���ĺ�ɫ����ǲ���һ����
int check_path(rb_tree *tree)
{
	int left, right;

	if (tree == nullnode) return 1;		// Ҷ��Ҳ�Ǻ�ɫ��

	left = check_path(tree->lchild);
	right = check_path(tree->rchild);

	if (left == 0 || right == 0) return ERROR;
	if (left != right) return ERROR;	// ��ɫ�������һ����

	if (tree->color == BLACK) return left + 1;	// ��ɫ�Ĳż�һ��
	else return left;
}

status check_child(rb_tree *tree)	// �����û�к�ɫ�����Ľ��
{
	if (tree == nullnode) return OK;
	if (tree->color == RED)
	{
		// ���ü�����ĺ����ǲ��ǿյ�, ��Ϊ���ƽ��Ĵ���
		// ���ƽ�����ɫ�Ǻ�ɫ
		if (tree->lchild->color == RED) return ERROR;
		if (tree->rchild->color == RED) return ERROR;
	}
	if (!check_child(tree->lchild)) return ERROR;
	if (!check_child(tree->rchild)) return ERROR;
	return OK;
}

status check(rb_tree *tree)		// ��������ʼ��
{
	if (tree == nullnode) return OK;		// ����Ҳ�Ǻ����
	if (tree->color == RED) return ERROR;	// ���Ǻ��
	if (!check_child(tree)) return ERROR;	// �к�ɫ�����Ľ��
	if (!check_path(tree)) return ERROR;	// ����·����ɫ��㲻һ����
	return OK;
}

node *init()		// ��ʼ��
{
	if (!nullnode)
	{
		nullnode = (node *)malloc(sizeof(node));
		nullnode->color = BLACK;		// Ҷ�ӽ��Ҫ�Ǻ�ɫ��
		nullnode->lchild = nullnode->rchild = nullnode;
		nullnode->parent = nullnode;
		nullnode->data = -1;
	}
	return nullnode;
}

void destory(rb_tree *tree)		// ����
{
	if (tree != nullnode)
	{
		destory(tree->lchild);
		destory(tree->rchild);
		free(tree);
	}
}

void mid_tra(rb_tree *tree)		// �������
{
	if (tree != nullnode)
	{
		mid_tra(tree->lchild);
		printf("%d, ", tree->data);
		mid_tra(tree->rchild);
	}
}

void first(rb_tree *tree)		// �������
{
	if (tree != nullnode)
	{
		printf("\ndata = %d, parent = %d,  color = %s", 
			tree->data, tree->parent->data, 
			tree->color==RED ? "Red" : "Black");
		first(tree->lchild);
		first(tree->rchild);
	}
}

int depth(rb_tree *tree)	// �����
{
	int right, left;

	if (tree == nullnode) return 0;

	left = depth(tree->lchild);
	right = depth(tree->rchild);
	return (left > right ? left : right) + 1;
}

void ASL_s(rb_tree *tree, int *asl, int *cnt, int flood)
{
	if (tree != nullnode) 
	{
		*asl += flood;
		(*cnt)++;
		ASL_s(tree->lchild, asl, cnt, flood+1);
		ASL_s(tree->rchild, asl, cnt, flood+1);
	}
}

float ASL(rb_tree *tree)		// �� ASL
{
	int asl = 0;
	int cnt = 0;
	ASL_s(tree, &asl, &cnt, 1);
	if (cnt == 0) return 0.0;
	else return (float)asl / (float)cnt;
}

char display(rb_tree *tree)	// ������ʾģ��
{
	char c;

	printf("\n�������: ");   first(tree);
	printf("\n\n�������: ");   mid_tra(tree);
	printf("\n\n���: %d\t\t", depth(tree));
	printf("ƽ�� ASL = %0.3f\t", ASL(tree));
	if (check(tree)) printf("�������ȷ");
	else printf("�ṹ����");
	
	printf("\n\n�� c ������, ���س�����...\n");
	getchar();   c = getch();
	system("cls");

	return c;
}

int main(void)
{
	rb_tree *tree;
	elemtype data;

	tree = init();
	while (1)		// �������
	{
		printf("������Ҫ�����Ԫ��: ");
		scanf("%d", &data);

		if (insert(&tree, data))	// ����
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
	if (nullnode) free(nullnode);
	return 0;
}
