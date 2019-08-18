#include <stdio.h>
#include <malloc.h>
#include "Btree.h"

// �����
// ����ǿո�,��ʾ������
// ������ǿո񣬴���һ�������
// �����
// ���� ���� Ҳ�����
// ���� �Һ��� Ҳ�����
status create(btnode **tree)
{
	char c;

	c = getchar();
	// ������
	if (c == '#') *tree = NULL;
	else if (c != '\n')
	{
		// ֱ���� tree �Ļ����Ͻ���
		(*tree) = (btnode *)malloc(sizeof(btnode));
		if (!(*tree)) return ERROR;
		(*tree)->data = c;
		(*tree)->lchild = NULL;
		(*tree)->rchild = NULL;

		// ������:
		create(&( (*tree)->lchild ));
		create(&( (*tree)->rchild ));
	}
	return OK;
}
// ˵����
// ��Ϊ���ܽ���ָ�������
// ����ֻ�а�treeָ���ָ�봫����
// ��ô *tree ����mian���������ָ���ˣ����ḳ����ֵ
// ���� (*tree)->lchild ���Ǻ���ָ��
// ��ô &( (*tree)->lchild ) ���Ǻ���ָ��ĵ�ַ��


// ����str������
char *create2(btnode **tree, char *str)
{
	if (*str != '\0')
	{
		if (*str == '#') *tree = NULL;
		else 
		{
			(*tree) = (btnode *)malloc(sizeof(btnode));
			if (!(*tree)) return ERROR;
			(*tree)->data = *str;
			(*tree)->lchild = NULL;
			(*tree)->rchild = NULL;

			// ������
			str = create2(&( (*tree)->lchild ), str + 1);
			// ������������ str, �� 1 ���ٴ�������
			str = create2(&( (*tree)->rchild ), str + 1);
			// ������������ str, �ٷ���ȥ
		}
	}
	return str;
}


// ������
// ������ǿ�ָ�룬���������ӣ��������Һ���
// ����������Լ���
// ���Ҫ�������Լ�����Ҫ��¼�º��ӵĵ�ַ
// ��Ȼ���Ҳ���������
status destory(btnode *tree)
{
	if (tree)
	{
		destory(tree->lchild);
		destory(tree->rchild);
		free(tree);
		tree = NULL;   // ��ȫ��
		return OK;
	}
	return ERROR;
}


// ������� (�ݹ�), ִ�� visit ����
// ������
// ������ǿգ���ִ��visit����
// �����������
// �����Һ���Ҳ���
status first_tra(btnode *tree, status (*visit)(btnode *node))
{
	if (tree)  // �������,�Ż�ִ��visit��,����visit�в����ж�
	{
		visit(tree);
		first_tra(tree->lchild, visit);
		first_tra(tree->rchild, visit);
	}
	else return ERROR;
	return OK;
}
// ���ϵ��㷨�������
// �������� if (visit(tree))


// ������� (�ݹ�)
// �������ȷ������ӣ��ٸ���㣬�������Һ���
status mid_tra(btnode *tree, status (*visit)(btnode *node))
{
	if (tree)
	{
		mid_tra(tree->lchild, visit);
		visit(tree);
		mid_tra(tree->rchild, visit);
	}
	else return ERROR;
	return OK;
}

// ������� (�ݹ�)
// �ȷ������ӣ�Ȼ���Һ��ӣ������Ǹ�
status last_tra(btnode *tree, status (*visit)(btnode *node))
{
	if (tree)
	{
		last_tra(tree->lchild, visit);
		last_tra(tree->rchild, visit);
		visit(tree);
	}
	else return ERROR;
	return OK;
}

// ------------���к���--------------
// �ѽ��ĵ�ַ��ӣ�����������������
static int front;
static int rear;

status enqueue(btnode *q[SIZE], btnode *data)
{
	if ((rear+1)%SIZE == front) return ERROR;
	q[rear] = data;
	rear = (rear + 1) % SIZE;
	return OK;
}

status dequeue(btnode *q[SIZE], btnode **back)
{
	if (rear == front) return ERROR;
	*back = q[front];
	front = (front + 1) % SIZE;

	return OK;
}

// ��α��� (���й���)
status wild_tra(btnode *tree, status (*visit)(btnode *node))
{
	btnode *back;
	btnode *q[SIZE];	// ����

	front = rear = 0;
	if (tree)
	{
		// ��������
		// ���������й�ϵ��Ҳ���
		enqueue(q, tree);
		while (rear != front)
		{
			// ���ӣ�����visit����
			// �йصĽ�㣬���
			dequeue(q, &back);	// back�нӽ��ֵ��
			visit(back);
			if (back->lchild) enqueue(q, back->lchild);
			if (back->rchild) enqueue(q, back->rchild);
		}
	}
	return OK;
}

// ���������
// ������:
// ��� tree==NULL ���Ϊ 0
// ���� ���Ϊ 1
// ������:
// ��� = max(����, �Һ���);
int depth(btnode *tree)
{
	int max;
	int left, right;

	if (!tree) return 0;
	else
	{
		left = depth(tree->lchild);
		right = depth(tree->rchild);
		if (left > right) max = left;
		else max = right;

		return max + 1;
	}
}

// ���ؽ�����
int nodenum(btnode *tree)
{
	int num = 0;

	if (tree)
	{
		num += nodenum(tree->lchild);
		num += nodenum(tree->rchild);
		return num + 1;
		// ��Ϊ�Լ�Ҳ��һ���������� num+1
	}
	return 0;
}

// ������û��key�Ľ��, ���ص�ַ
// �����
// ��� tree==NULL ����NULL
// ��� key==data  ����tree
// �����
// �������ӣ��Һ���ͬ��
// ����ҵ�һ���ͷ���
// ������Ҳ����ͷ��� NULL
btnode *find(btnode *tree, elemtype *key)
{
	btnode *addr = NULL;

	// ������:
	if (!tree) return NULL;
	if (tree->data == *key)
		return tree;

	// ������:
	addr = find(tree->lchild, key);
	if (addr) return addr;   // �вŷ���

	addr = find(tree->rchild, key);
	if (addr) return addr;

	return addr;
}

// ����key����ֵ��data
status update(btnode *tree, elemtype *key, elemtype *data)
{
	btnode *addr;

	addr = find(tree, key);
	if (!addr) return ERROR;
	addr->data = *data;

	return OK;
}

// ��key�µ�rlλ�ò���һ�����ӽ��data, rl��ʾ����
status insert(btnode *tree, 
			  elemtype *key, 
			  elemtype *data, 
			  char rl)
{
	btnode *addr;

	addr = find(tree, key);
	if (!addr) return ERROR;
	if (rl == '0')
	{
		if (addr->lchild) return ERROR;
		addr->lchild = (btnode *)malloc(sizeof(btnode));
		if (!addr->lchild) return ERROR;
		addr->lchild->lchild = NULL;
		addr->lchild->rchild = NULL;
		addr->lchild->data = *data;
		return OK;
	}
	if (rl == '1')
	{
		if (addr->rchild) return ERROR;
		addr->rchild = (btnode *)malloc(sizeof(btnode));
		if (!addr->rchild) return ERROR;
		addr->rchild->lchild = NULL;
		addr->rchild->rchild = NULL;
		addr->rchild->data = *data;
		return OK;
	}
	return ERROR;
}

// ɾ��key�µ�rl���
status remove(btnode *tree, elemtype *key, char rl)
{
	btnode *addr;

	addr = find(tree, key);
	if (!addr) return ERROR;
	if (rl == '0')
	{
		destory(addr->lchild);
		addr->lchild = NULL;	// ��ȫ��
	}
	else 
	{
		destory(addr->rchild);
		addr->rchild = NULL;
	}
	return OK;
}

// ��Ҷ����
// ����������ҵ���Ϊ 0 �Ľ��
// ֱ�ӵ����ϵı�������Ҳ��
// ����������дһ��
int leafnum(btnode *tree)
{
//	static int sum = 0;	// ����Ҳ��
	int sum = 0;

	if (tree)
	{
		if (!(tree->lchild || tree->rchild)) sum++;
		sum += leafnum(tree->lchild);
		sum += leafnum(tree->rchild);
	}

	return sum;
}

// �����
status clear(btnode *tree)
{
	if (tree) destory(tree);
	tree = NULL;
	return OK;
}

// �п�
status empty(btnode *tree)
{
	if (tree) return OK;
	return ERROR;
}

// ��ʼ��˫��ָ��
// ������ָ���Լ�
// ���Һ���ָ���Լ�
// �����ӣ��Һ���Ҳ���
status init_parent(btnode *tree)
{
	static int f = 1;
	
	// �����û��˫��, ֻ��ִ��һ��
	if (tree)
	{
		if (f) {f=0; tree->parent = NULL;}
		if (tree->lchild)
			tree->lchild->parent = tree;
		if (tree->rchild)
			tree->rchild->parent = tree;
		init_parent(tree->lchild);
		init_parent(tree->rchild);
	}
	return OK;
}

// ����˫�׵�ַ
btnode *parent(btnode *tree, elemtype *data)
{
	btnode *addr;

	addr = find(tree, data);
	if (!addr) return NULL;
	return addr->parent;
}

// ���ظ�����ַ
btnode *root(btnode *tree)
{
	if (!tree) return NULL;
	while (tree->parent)
		tree = tree->parent;

	return tree;
}


// -----------˳��ջ����-------------
// ��������������� rear front
// ����Ϊ�����֣���������������
static int top;
static int base;
#define STACK_SIZE 150

status push(btnode *s[STACK_SIZE], btnode *data)
{
	if (top == base + STACK_SIZE) return ERROR;
	s[top++] = data;
	return OK;
}

btnode *pop(btnode *s[STACK_SIZE])
{
	if (top == base) return NULL;
	return s[--top];
}

btnode *gettop(btnode *s[STACK_SIZE])
{
	if (top == base) return NULL;
	return s[top - 1];
}

// ������� (�ǵݹ飬ջ)
// ִ��visit���������ջ
// ֱ��û�ý�ջ�ˣ��ͳ�ջ��ֱ������������
// ֱ��ջΪ�գ���������
status first_tra_s(btnode *tree, status (*visit)(btnode *node))
{
	btnode *stack[STACK_SIZE];
	btnode *temp;

	if (!tree) return ERROR;
	top = base = 0;
	visit(tree);
	push(stack, tree);
	while (top != base)
	{
		temp = gettop(stack);  // ��ջ���ó�һ��
		if (!temp) break;      // ��ȫ��
		while (temp->lchild)   // һֱ������
		{
			visit(temp->lchild);
			push(stack, temp->lchild);
			temp = temp->lchild;
		}
		while (1)
		{
			temp = pop(stack);
			if (temp->rchild) break; // ֱ�� temp �����Һ���
			if (top == base)         // ����ջ����
			{
				temp = NULL;
				break;
			}
		}
		if (temp)
		{
			visit(temp->rchild);   // ������һ��
			push(stack, temp->rchild);
		}
	}
	return OK;
}

// ������� (�ǵݹ飬 ջ)
// һֱ�����ߣ�����һ��ֱ������������
status mid_tra_s(btnode *tree, status (*visit)(btnode *node))
{
	btnode *s[STACK_SIZE];
	btnode *t;

	top = base = 0;
	if (!tree) return 0;
	push(s, tree);		// �������ջ
	while (top != base)
	{
		t = gettop(s);
		if (!t) break;
		while (t->lchild)	// һֱ������
		{
			push(s, t->lchild);
			t = t->lchild;
		}
		while (1)		// �ҵ�һ�����������ߵĽ��
		{
			t = pop(s);
			if (t) visit(t);
			if (t->rchild) break;
			if (top == base) break;
		}
		if (t) push(s, t->rchild);	// ������
	}

	return OK;
}

// ������� (�ǵݹ飬 ջ)
status last_tra_s(btnode *tree, status (*visit)(btnode *node))
{
	btnode *s[STACK_SIZE];
	btnode *t;
	btnode *right;
	// ��¼ t �Ǵ��ĸ��Һ��ӻ�����
	// ��� t->rchild == right
	// ˵���Ǵ��һص����Ĺ���

	top = base = 0;
	if (!tree) return 0;
	push(s, tree);		// �������ջ
	while (top != base)
	{
		t = gettop(s);
		if (!t) break;
		while (t->lchild)	// һֱ������
		{
			push(s, t->lchild);
			t = t->lchild;
		}
		while (1)	// һֱ�ҵ�һ�����������ߵ�
		{
			right = t;
			t = gettop(s);
			// û���Һ��ӻ���Һ��ӻ���ʱ�ŷ���
			if (!t->rchild || t->rchild == right)
			{
				visit(t);
				pop(s);
			}
			else break;
			if (top == base) break;
		}
		if (t && t->rchild != right)
			push(s, t->rchild);
	}
	return OK;
}

