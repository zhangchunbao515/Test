// ����˫�ױ�ʾ��

#include <stdio.h>
#include <malloc.h>

typedef char elemtype;
typedef int status;

#define ERROR 0
#define OK 1
#define SIZE 50

typedef struct pnode
{
	elemtype data;
	int parent;
}pnode;

typedef struct ptree
{
	pnode *base;	// �����ַ
	int cur;
	int size;
}ptree;

status create(ptree *tree)
{
	int queue[SIZE] = {0};   // ��ʱ����
	int rear = 0; 
	int front = 0;
	int cur = 0;	// ��ν���ʱ��ָ�����ڽ����Ľ��
	char c;

	// ��ʼ�� tree
	tree->base = (pnode *)malloc(SIZE * sizeof(pnode));
	if (!tree->base) return ERROR;
	tree->size = SIZE;
	tree->cur = 0;
	printf("���������㣺");
	c = getchar();
	fflush(stdin);
	
	// ���������
	tree->base[0].data = c;
	tree->base[0].parent = -1;
	tree->cur = 1;
	// ��������
	queue[rear] = cur;
	rear = (rear + 1) % SIZE;

	while (rear != front)
	{
		cur = queue[front];		// �Ӷ������ó�Ҫ�����ӵĽ��
		front = (front + 1) % SIZE;
		printf("������ %c �ĺ��ӣ�", tree->base[cur].data);
		c = getchar();
		while (c != '\n')
		{
			tree->base[tree->cur].data = c;
			tree->base[tree->cur].parent = cur;
			// ����ȫ����Ӽ�¼
			if ((rear + 1) % SIZE != front)
			{
				queue[rear] = tree->cur;
				rear = (rear + 1) % SIZE;
			}
			else return ERROR;
			c = getchar();
			tree->cur++;
		}
		cur++;		// ��������
	}
	return OK;
}

status destory(ptree *tree)
{
	if (tree->base) free(tree->base);
	tree->base = NULL;
	return OK;
}

// Ѱ�� c ���ĵ�ַ
pnode *find(ptree *tree, elemtype c)
{
	int i;

	// ������� data ��
	for (i=0; i<tree->cur; i++)
		if (tree->base[i].data == c)
			return tree->base + i;
	return NULL;
}

// ���� c ��˫��
elemtype parents(ptree *tree, elemtype c)
{
	pnode *addr;
	int p;

	addr = find(tree, c);
	if (!addr) return '\0';
	// addr - tree->base ��ַ֮���λ��֮��
	p = tree->base[addr - tree->base].parent;
	return tree->base[p].data;
}

// ���� c �ĸ�
elemtype roots(ptree *tree, elemtype c)
{
	pnode *addr;
	int p;

	addr = find(tree, c);
	if (!addr) return '\0';
	p = tree->base[addr - tree->base].parent;
	while (p != -1)
	{
		// p = p��˫��, ��¼��ַ
		addr = tree->base + p;
		p = tree->base[p].parent;
	}
	return addr->data;
}

// ������
status insert(ptree *tree, elemtype c, elemtype data)
{
	pnode *addr;

	// ����������û
	if (tree->cur == tree->size)
	{
		tree->size += 10;
		tree->base = (pnode *)realloc(tree->base, 
			tree->size * sizeof(pnode));
		if (!tree->base) return ERROR;
	}
	addr = find(tree, c);
	if (!addr) return ERROR;
	tree->base[tree->cur].data = data;
	tree->base[tree->cur].parent = addr - tree->base;
	tree->cur++;

	return OK;
}

int main(void)
{
	ptree tree;
	pnode *addr = NULL;
	elemtype c;
	elemtype data;

	printf("���س�����ʾ�������\n");
	create(&tree);
	printf("������ϣ�\n");
	printf("���ҽ�㣺");
	c = getchar();
	addr = find(&tree, c);
	if (addr)
	{
		printf("\n�ҵ� %c����ַΪ��%x\n", addr->data, addr);
		printf("˫��Ϊ��%c\n", parents(&tree, c));
		printf("�����Ϊ��%c\n", roots(&tree, c));
	}
	else printf("û���ҵ�!\n");

	printf("��X�²���Z��㣺(��:X Z)");
	c = getchar();
	data = getchar();
	fflush(stdin);
	insert(&tree, c, data);

	destory(&tree);

	return 0;
}