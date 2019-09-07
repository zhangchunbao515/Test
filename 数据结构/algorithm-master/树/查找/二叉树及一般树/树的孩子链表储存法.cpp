// ���ĺ���������

#include <stdio.h>
#include <malloc.h>

typedef char elemtype;
typedef int status;

#define ERROR 0
#define OK 1
#define SIZE 30

// ����������
typedef struct node
{
	int childaddr;	// ���ӵĵ�ַ
	node *next;
}node;

// ͷָ������
typedef struct head
{
	elemtype data;	// �����ֵ
	node *next;		// ͷָ��
}head;

// ͷ�ṹ��ַ����, Ĭ��base[0]�Ǹ����
typedef struct ctree
{
	head *base;		// ��ַ
	int cur;		// ʹ����
	int size;		// �ܴ�С
}ctree;

// ����
status create(ctree *tree)
{
	int i;

	// ����ͷ�ṹ�ռ�
	tree->base = (head *)malloc(SIZE * sizeof(head));
	if (!tree->base) return ERROR;
	tree->size = SIZE;
	tree->cur = 0;

	// ��ʼ������ͷָ��
	for (i=0; i<SIZE; i++)
		tree->base[i].next = NULL;

	return OK;
}

// Ѱ�� c ���ĵ�ַ
head *find(ctree *tree, elemtype c)
{
	int i;

	if (!tree->base) return ERROR;
	for (i=0; i<tree->cur; i++)
		if (tree->base[i].data == c)
			return tree->base + i;
	return NULL;
}

// ��ֵ
status input(ctree *tree)
{
	int cur = 0;
	elemtype c;
	head *addr;		// ��i�е�ͷ�ṹָ��
	node *n;		// �º���ָ��
	node *j;		// βָ��

	if (!tree) return ERROR;
	// ����ͷ�ṹ
	c = getchar();
	while (c != '\n')
	{
		// ��������û
		if (tree->cur == tree->size)
		{
			tree->size += 10;
			tree->base = (head *)realloc(tree->base, 
				tree->size * sizeof(head));
			if (!tree->base) return ERROR;
		}
		tree->base[tree->cur++].data = c;
		c = getchar();
	}

	// �������鴴��ÿ����㺢��
	fflush(stdin);
	while (cur < tree->cur)
	{
		printf("������ %c �ĺ��ӣ�", tree->base[cur].data);
		// ������ǰ���ĺ���
		c = getchar();
		while (c != '\n')
		{
			addr = find(tree, c);
			if (addr)
			{
				// ��ʱ addr ���������ͷ�ṹ
				n = (node *)malloc(sizeof(node));
				if (!n) return ERROR;
				n->childaddr = addr - tree->base;
				
				// β�巨��βָ�� j
				if (tree->base[cur].next)
				{
					j = tree->base[cur].next;
					while (j->next)
						j = j->next;
					n->next = j->next;
					j->next = n;
				}
				else 
				{
					n->next = tree->base[cur].next;
					tree->base[cur].next = n;
				}
			}
			c = getchar();
		}
		cur++;
	}
	return OK;
}

// ���
status show(ctree *tree, int addr)
{
	if (!tree->base) return ERROR;
	printf("%c, ", tree->base[addr].data);
	return OK;
}

// ������� (�ݹ鷨)
status first_tra(ctree *tree, int pos,
				 status (*visit)(ctree *tree, int addr))
{
	node *cur;
	static char f = 1;
	// ���һ�θ����
	if (f) {visit(tree, 0); f = 0;}

	// ���ͷָ�벻�ǿ�
	if (tree->base[pos].next)
	{
		// ������������
		cur = tree->base[pos].next;
		while (cur)
		{
			visit(tree, cur->childaddr);
			// �ݹ�������һ������
			first_tra(tree, cur->childaddr, visit);
			cur = cur->next;	// ����ʱ���Ѹò��cur�²�һλ
		}
	}
	else return ERROR;
	return OK;
}

// ���������
// ������
// ����ǿձ����� 1
// ������ǿձ����� ��������+1 
int lenth(ctree *tree, int pos)
{
	node *cur;
	int deep;
	int max = -1;

	// Ϊʲô�ձ��� 1 ?
	// ��ǰ���ǿձ������ 0 
	// �����˻ص���һ����� 1 ��
	// �൱���Ҹ�����һ�㣬����������� 1
	if (!tree->base[pos].next) return 1;
	
	// �������������ҵ���������
	cur = tree->base[pos].next;
	while (cur)
	{
		deep = lenth(tree, cur->childaddr);
		if (deep > max) max = deep;
		cur = cur->next;
	}
	// ��ǰ������� max, ���˻�һ����� max + 1
	return max + 1;
}

int main(void)
{
	ctree tree;

	if (!create(&tree)) return 0;
	printf("˵��������������㣬�Իس�������\n");
	printf("������ȫ����㣺");
	input(&tree);
	printf("\n���������");
	first_tra(&tree, 0, show);
	printf("\n������ȣ�%d\n", lenth(&tree, 0));

	return 0;
}
