
// trie ��, ���ֲ�������һ��, �ֳ��ֵ���
// ��Ҫ����, ����, ����, ɾ��, 
// trie ���ṹ�Ƚϸ���, ����㷨������������, �������

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef char keytype;
typedef int status;
#define SIZE 100
#define ERROR 0
#define OK 1
#define MAX 27		// ���Ķ�, 0 �ŵ�Ԫ����
// ����Ϊ 27 ����Ϊ, ����ֻʵ�� 26 ��СдӢ����ĸ
// ���Ҫʵ���д��ĸ, ���Խ� 27 �ĸ���, ʵ������Ҳͬ��

typedef enum {LEAF, BRANCH} kind;	// ��־Ҷ�����֧

// trie ���Ĵ���ṹ
typedef struct node
{
	kind tag;			// ��־
	union 
	{
		keytype data[MAX];	// �ؼ���
		struct 
		{
			node *add[MAX];		// ���ӵ�ַ
			int num;			// ��������
		}ptr;
	};
}node, trie_tree;

typedef struct		// ���������¼����
{
	int tag;		// �ɹ���־
	node *add;		// �ҵ��Ľ���ַ
	int pos;		// ���ƥ��λ��
}result;

void create(trie_tree **tree)	// ���� trie ��
{
	int i;

	*tree = (trie_tree *)malloc(sizeof(trie_tree));
	(*tree)->tag = BRANCH;		// ��֧
	for (i=0; i<MAX; i++) (*tree)->ptr.add[i] = NULL;
	(*tree)->ptr.num = 0;
}

void destory(trie_tree *tree)	// ���� trie ��
{
	int i;
	for (i=0; i<MAX; i++)
	{
		// �����Ҷ��, ֱ���ͷ�, ����Ҷ��, �ݹ��ͷ�
		if (tree->ptr.add[i])
		{
			if (tree->ptr.add[i]->tag == LEAF)
				free(tree->ptr.add[i]);
			else destory(tree->ptr.add[i]);
		}
	}
	free(tree);
}

node *new_node(kind k)		// ����һ���½��, ����ʼ��
{
	node *n;
	int i;

	n = (node *)malloc(sizeof(node));
	for (i=0; i<MAX; i++)
		n->ptr.add[i] = NULL;
	n->tag = k;
	n->ptr.num = 0;
	
	return n;
}

// �����ϲ���һ�����, �����������, stack ��¼����·��
// �����ʱ����Ҫ stack ��Ϣ, ����ɾ����ʱ���Ҫ��
result search(trie_tree *tree, keytype *data, node **stack)
{
	result tmp;
	int i = 0;
	int top = 0;

	tmp.tag = 0;   tmp.pos = 0;
	while (data[tmp.pos] != '\0')
	{	
		stack[top++] = tree;
		i = data[tmp.pos++] - 'a' + 1;	// �ؼ��ֵ�ַ
		// ����Ϊ��, ��ǰ�Ƿ�֧���, ���к���
		if (tree && tree->tag==BRANCH && tree->ptr.add[i])
			tree = tree->ptr.add[i];
		else break;
	}
	// �������, �����ĺ���, �Һ�����Ҷ��, �� data ���, �Ǿ��ҵ���
	// �������Ҷ��, �Ϳ���һ����֧�� 0 �ŵ�Ԫ
	if (tree)
	{
		if (tree->tag == LEAF)
		{
			if (!strcmp(tree->data, data))
				tmp.tag = 1;
		}
		else 
		{
			if (tree->ptr.add[0] && 
				!strcmp(tree->ptr.add[0]->data, data))
				tmp.tag = 1;
		}
	}
	tmp.add = stack[top - 1];
	stack[top] = NULL;		// �����ַ������
	tmp.pos--;
	return tmp;
}

// �����ϲ���һ�����, �㷨�� 245 ҳ, ͼ 9.21
status insert(trie_tree **tree, keytype *data)
{
	result r;
	int i, j;
	keytype buf[70];
	node *stack[SIZE];

	r = search(*tree, data, stack);
	if (r.tag) return ERROR;	// ������

	tree = &r.add;
	while (data[r.pos] != '\0')		// ������֧
	{
		i = data[r.pos] - 'a' + 1;	// ƥ��ʧ�ܵ����λ��
		if ((*tree))			// ����ʧ�ܺ��ԭ��
		{
			if ((*tree)->tag == LEAF)
			{
				// �����Ҷ��, �����ɷ�֧, Ҷ���ٽӵ���֧ 0 λ��
				strcpy(buf, (*tree)->data);		// buf��¼Ҷ��
				(*tree)->tag = BRANCH;
				(*tree)->ptr.num = 2;
				for (j=0; j<MAX; j++) (*tree)->ptr.add[i] = NULL;
				// ��Ϊ��Ҷ�Ӹ��������, ������union���Ҫ��ʼ��
				// �ؽ�Ҷ��
				(*tree)->ptr.add[0] = new_node(LEAF);
				strcpy((*tree)->ptr.add[0]->data, buf);
				tree = &((*tree)->ptr.add[i]);		// ������һ��
			}
			else 
			{
				(*tree)->ptr.num++;
				tree = &((*tree)->ptr.add[i]);	// �Ƿ�֧, ֱ��������
			}
		}
		else	// �������
		{
			*tree = new_node(BRANCH);
			(*tree)->ptr.num++;
			tree = &((*tree)->ptr.add[i]);
		}
		r.pos++;
	}
	// ����ٰ�Ҷ�ӽ�㽨��
	if (*tree) tree = &((*tree)->ptr.add[0]);
	*tree = new_node(LEAF);
	strcpy((*tree)->data, data);

	return OK;
}

// ������ɾ��һ��Ԫ��
status remove(trie_tree **tree, keytype *data)
{
	node *stack[SIZE];
	node *cur;
	node *del;
	int top, i;
	result r;

	r = search(*tree, data, stack);
	if (!r.tag) return ERROR;		// û�ҵ�Ԫ��

	for (top=0; stack[top]!=NULL; top++);	// ���ջ��ָ��
	while (top != 0)
	{
		cur = stack[--top];
		i = data[top] - 'a' + 1;
		// ��֧�Ľ�����, ��һ����� 0 �ŵ�Ԫ
		if (cur->ptr.add[i]->tag == LEAF)
		{
			free(cur->ptr.add[i]);
			cur->ptr.add[i] = NULL;
			cur->ptr.num--;
		}
		else	// ���ӽ��, ����Ҷ��, ���Ƕ�Ϊ 0 ��ҲҪ�ͷŵ�
		{		// ��Ϊ 1 ��, ������ 0 �ŵ�Ԫռ����
			if (cur->ptr.add[i]->ptr.num == 0)
			{
				free(cur->ptr.add[i]);
				cur->ptr.add[i] = NULL;
				cur->ptr.num--;
			}
			else if (cur->ptr.add[i]->ptr.num == 1)
			{
				if (cur->ptr.add[i]->ptr.add[0])	// 0 ��ռ����
				{
					// �� 0 �ŵ�Ҷ��������
					del = cur->ptr.add[i];
					cur->ptr.add[i] = cur->ptr.add[i]->ptr.add[0];
					free(del);
				}
			}
			else	// ֱ���ͷ� 0 ��
			{
				if (cur->ptr.add[i]->ptr.add[0])
				{
					free(cur->ptr.add[i]->ptr.add[0]);
					cur->ptr.add[i]->ptr.add[0] = NULL;
					cur->ptr.add[i]->ptr.num--;
				}
			}
		}
	}
	return OK;
}

void show(trie_tree *tree)		// ���ȫ�������
{
	int i;
	for (i=0; i<MAX; i++)
	{
		if (tree->ptr.add[i])	// ��Ҷ��ֱ�����, ��������ݹ�
		{
			if (tree->ptr.add[i]->tag == LEAF)
				printf("%s\n", tree->ptr.add[i]->data);
			else show(tree->ptr.add[i]);
		}
	}
}

char display(trie_tree *tree)	// ��ʾ
{
	char c;

	printf("\n\n����ȫ��Ԫ��: \n");
	show(tree);

	printf("\n�� c �˳�, ���س�����...");
	getchar();
	c = getch();
	system("cls");

	return c;
}

int main(void)
{
	trie_tree *tree;
	char data[50];

	create(&tree);
	while (1)		// �������
	{
		printf("������Ҫ���ҵ�Ԫ��: ");
		scanf("%s", &data);
		if (insert(&tree, data))		// ����
			printf("\n��Ԫ�ز�����, �Ѳ���!");
		else printf("\n���ҵ�!");

		if (display(tree) == 'c') break;
	}
	while (1)		// ɾ������
	{
		printf("������Ҫɾ����Ԫ��: ");
		scanf("%s", &data);
		if (remove(&tree, data))		// ɾ��
			printf("\n�ɹ�ɾ��!");
		else printf("\n���Ԫ�ز�����!");

		if (display(tree) == 'c') break;
	}
	destory(tree);
	return 0;
}
