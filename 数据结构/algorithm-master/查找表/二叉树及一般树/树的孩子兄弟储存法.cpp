// ���ĺ����ֵܴ���

#include <stdio.h>
#include <malloc.h>

typedef char elemtype;
typedef int status;

#define OK 1
#define ERROR 0
#define SIZE 100	// ���д�С

/*
 /  ���׺���
 -> ���ֵ�

      R
     /
    A -> B -> C
   /	     /
  D -> E    F
           /
          G -> H -> K
*/

// ���ӽ��ṹ�����ƶ�������
typedef struct node
{
	elemtype data;		// ���ֵ
	node *firstchild;	// �����ϴ�
	node *nextbrother;	// �����ֵ�
	node *parent;		// ˫��
}node, cstree;


// ��ν���
status create(cstree *tree)
{
	elemtype c;
	node *queue[50];	// �򵥶���
	node *back;			// ���ӵ�Ԫ��
	node *n;			// �½��
	node *cur;			// ������
	int rear = 0;
	int front = 0;

	// ��ʼ�������
	printf("���������㣺");
	c = getchar();
	fflush(stdin);
	tree->data = c;
	tree->parent = NULL;		// �������˫��
	tree->nextbrother = NULL;	// ��ֻ��һ��
	tree->firstchild = NULL;
	// ���м�¼�¸����
	queue[rear] = tree;
	rear = (rear + 1) % 100;

	while (rear != front)
	{
		// ��ʱ back ��˫��
		back = queue[front];
		front = (front + 1) % 50;
		printf("������ %c �ĺ��ӣ�", back->data);
		c = getchar();
		while (c != '\n')
		{
			// ����c�������ӽ��
			n = (node *)malloc(sizeof(node));
			if (!n) return ERROR;
			n->data = c;
			n->firstchild = NULL;
			n->nextbrother = NULL;
			n->parent = back;

			// n ��Ӽ�¼
			if ((rear + 1) % 50 == front) return ERROR;
			queue[rear] = n;
			rear = (rear + 1) % 50;

			// ��firstchild�ߵ����һ�����ӵ�ĩβ������
			cur = back->firstchild;
			if (cur)
			{
				// �����ֵ��ҵ����
				while (cur->nextbrother)
					cur = cur->nextbrother;
				cur->nextbrother = n;
			}
			else back->firstchild = n;
			c = getchar();
		}
	}
	return OK;
}

// �ͷ���
// ���ƶ��������ͷ�
// firstchild ���� lchild
// nextbrother ���� rchild
// �����Ǻ����ͷţ���Ȼ���Ҳ���������
status destory(cstree *tree)
{
	if (tree)
	{
		destory(tree->firstchild);
		destory(tree->nextbrother);
		free(tree);
		return OK;
	}
	return ERROR;
}

// ������� (�ǵݹ�)
// ��ջ��¼·��
status first_tra_s(cstree *tree, status (*visit)(node *n))
{
	node *stack[SIZE];
	int top = 0;

	while (top || tree)
	{
		// ���׺���ȫ����ջ
		while (tree)
		{
			visit(tree);
			stack[top++] = tree;
			tree = tree->firstchild;
		}
		// ��ʱ�ߵ����Ӿ�ͷ
		// Ȼ��������һ��
		if (top)
		{
			tree = stack[--top];
			// ���ֵ���һ��
			tree = tree->nextbrother;
		}
	}

	return OK;
}

// ������� (�ݹ�)
// �ȷ������ӣ������ҷ����ֵ�
// �������򣬺���ֻ���������˳�򼴿�
status first_tra(cstree *tree, status (*visit)(node *n))
{
	if (tree)
	{
		visit(tree);
		first_tra(tree->firstchild, visit);
		first_tra(tree->nextbrother, visit);
		return OK;
	}
	return ERROR;
}

// ��α���
// �ö��м�¼ÿ������׺���
status BFS_tree(cstree *tree, status (*visit)(node *n))
{
	node *queue[SIZE];
	node *back;
	int rear = 0;
	int front = 0;

	// ���ȸ�������
	queue[rear] = tree;
	rear = (rear + 1) % SIZE;
	while (rear != front)
	{
		// ����һ�����,�������ֵ�,��¼ÿ���ֵܵ��׺���
		back = queue[front];
		front = (front + 1) % SIZE;

		while (back)
		{
			visit(back);
			// ����к��ӣ����¼
			if (back->firstchild)
			{
				queue[rear] = back->firstchild;
				rear = (rear + 1) % SIZE;
			}
			back = back->nextbrother;
		}
	}
	return OK;
}

status show(node *tree)
{
	if (tree)
		printf("%c, ", tree->data);
	return OK;
}

// ������û��key�Ľ��, ���ص�ַ
// �����ù��Ѳ��ң����Ѳ���
// �����
// ����ǿ��� ���� NULL
// ����� key ֵ������ tree
// ������ ������������
// ��󷵻� NULL
node *DFS_find(cstree *tree, elemtype *key)
{
	node *addr = NULL;

	if (!tree) return NULL;
	if (tree->data == *key) return tree;

	// �����׺���, ���ƶ�����������
	addr = DFS_find(tree->firstchild, key);
	if (addr) return addr;

	// �����ֵ�
	addr = DFS_find(tree->nextbrother, key);
	if (addr) return addr;

	// ������涼û���ҵ�
	return addr;
}

// ���Ѳ��ҽ��
// ÿ�δӶ������ó�һ���������ǲ���key
node *BFS_find(cstree *tree, elemtype *key)
{
	node *queue[100];
	int rear = 0;
	int front = 0;
	node *back;

	// �����
	queue[rear] = tree;
	rear = (rear + 1) % 100;

	while (rear != front)
	{
		back = queue[front];
		front = (front + 1) % 100;
		// ���г�����ֻ���׺���
		// �����׺��ӵĽ�㲻�������
		// �������ﲻ��ȫ������

		// ���� back ���ֵܣ���¼���ֵܵ��׺���
		while (back)
		{
			// �����ǲ��� key
			if (back->data == *key) return back;

			// ��¼�׺���
			if (back->firstchild) 
			{
				if ((rear + 1) % 100 == front) return NULL;
				queue[rear] = back->firstchild;
				rear = (rear + 1) % 100;
			}
			// ���������ֵ�
			back = back->nextbrother;
		}
	}
	return NULL;
}

// ����key����ֵ,Ϊdata
status update(cstree *tree, elemtype *key, elemtype *data)
{
	node *addr = NULL;

	addr = DFS_find(tree, key);
	if (!addr) return ERROR;
	addr->data = *data;
	return OK;
};

// ��pos�������һ��data���
status insert(cstree *tree, elemtype *key, elemtype *data, int flag)
{
	node *addr;
	node *n;
	node *cur;

	// ���� key
	addr = DFS_find(tree, key);
	if (!addr) return ERROR;

	// �����½��
	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->data = *data;
	n->parent = addr;
	n->firstchild = NULL;
	n->nextbrother = NULL;

	// ׼������
	if (flag)
	{
		// ����ĩβ
		cur = addr->firstchild;
		if (cur)
		{
			while (cur->nextbrother)
				cur = cur->nextbrother;
			cur->nextbrother = n;
			// n->nextbrether �Ѿ��� NULL
		}
		else addr->firstchild = n;
	}
	else 
	{
		// ������λ, �㷨�����ϵ�ͼ
		// �Ȱ�ԭ�����׺��Ӽ�¼
		n->nextbrother = addr->firstchild;
		// ��ʱ�׺����� n
		addr->firstchild = n;
		// ������ֵ�
		if (n->nextbrother)
		{
			// �� n �̳� a ���׺���
			n->firstchild = n->nextbrother->firstchild;
			// Ĩ�� a ���׺���
			n->nextbrother->firstchild = NULL;
		}
	}
	return OK;
}

// ����X����ַ, ���ظ�����ַ
node *root(node *n)
{
	if (!n) return NULL;
	while (n->parent) n = n->parent;
	return n;
}

// ɾ��һ��Ҷ�ӻ���֦
status remove(cstree *tree, elemtype *data)
{
	node *addr;
	node *cur;
	
	addr = DFS_find(tree, data);
	if (addr)
	{
		// ����Ǹ���
		if (addr == root(addr)) 
		{
			destory(tree->firstchild);
			tree->firstchild = NULL;
			tree->data = '\0';
		}
		else 
		{
			// �ҵ� addr ��ǰһ��, �ÿ�ָ��
			if (addr->parent->firstchild == addr)
				addr->parent->firstchild = addr->nextbrother;
			else 
			{
				cur = addr->parent->firstchild;
				while (cur->nextbrother != addr)
					cur = cur->nextbrother;
				// ��ʱ cur ����һ���� addr
				cur->nextbrother = addr->nextbrother;
			}
			destory(addr->firstchild);
			free(addr);
		}
		return OK;
	}
	else return ERROR;
}

status create2(cstree *tree, char *str)
{
	node *queue[50];
	int rear = 0;
	int front = 0;
	node *back;
	node *n;
	node *last;		// βָ��

	if (str[0] == '#' || str[0] == '\0') return ERROR;
	// ����ͷ��㣬�����
	tree->data = *str++;
	tree->parent = NULL;
	tree->firstchild = NULL;
	tree->nextbrother = NULL;
	queue[rear] = tree;
	rear = (rear + 1) % 50;

	while (rear != front)
	{
		back = queue[front];
		front = (front + 1) % 50;

		while (str[0] != '#' && str[0] != '\0')
		{
			n = (node *)malloc(sizeof(node));
			if (!n) return ERROR;
			n->data = *str++;
			n->parent = back;
			n->firstchild = NULL;
			n->nextbrother = NULL;
			// ���� back
			if (back->firstchild)
				last->nextbrother = n;
			else 
				back->firstchild = n;
			last = n;
			// ��Ӽ�¼
			if ((rear + 1) % 50 == front) return ERROR;
			queue[rear] = n;
			rear = rear + 1;
		}
		if (str[0] == '\0') break;
		else str++;
	}
	return OK;
}

int main(void)
{
	cstree tree;
	elemtype data;
	elemtype key;
	node *addr;
	node *r;
	int flag;
	char str[100] = {0};

	create(&tree);
//  RABC#DE##F###GHK###
//	scanf("%s", &str);
//	getchar();
//	create2(&tree, str);   // �����ַ�������
	printf("\n���������");
	first_tra(&tree, show);

	printf("\n\n");
	printf("��α�����");
	BFS_tree(&tree, show);	

	printf("\n\n������Ҫ���ҵĽ��ֵ: ");
	scanf("%c", &data);
	addr = DFS_find(&tree, &data);   // ����
//	addr = BFS_find(&tree, &data);   // ����Ҳ��
	if (addr)
	{
		printf("�ҵ�����ַΪ: %x\n", addr);
		printf("���Ϊ��%c\n", addr->data);
		if (addr->parent)
			printf("˫��Ϊ��%c\n", addr->parent->data);
		r = root(addr);
		printf("����Ϊ��%c\n", r->data);
	}
	else printf("�Ҳ��� %c\n", data);

	printf("\nɾ��һ������Ҷ�ӣ�");
	fflush(stdin);
	scanf("%c", &key);
	if (remove(&tree, &key))
	{
		printf("ɾ���ɹ�\n");
		printf("����--ջ��");
		first_tra_s(&tree, show);
		printf("\n\n");
	}
	else printf("ɾ��ʧ�ܣ��Ҳ��� %c\n", key);

	// A �²��� X, 0��ʾ������λ, 1��ĩβ
	printf("\n������Ҫ����Ľ��:(�� A X 1) ");
	fflush(stdin);
	scanf("%c %c %d", &key, &data, &flag);
	if (insert(&tree, &key, &data, flag))
	{
		printf("����ɹ�\n");
		printf("\n����--ջ��");
		first_tra_s(&tree, show);
		printf("\n");
	}
	else printf("����ʧ��\n");
	destory(tree.firstchild);
	tree.firstchild = NULL;

	return 0;
}