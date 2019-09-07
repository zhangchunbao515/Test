#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// trie�� - ����, ������Ҷ�ӽ����Ϣ, ����·�������ַ���

typedef char keytype;
typedef int status;
#define ERROR 0
#define OK 1
#define MAX 26		// ֻʵ��Сд��ĸ, ������ 26

// ��֧, Ҷ��, ��֧��Ҷ��
typedef enum {BRANCH, LEAF, L_B} kind;

typedef struct node		// trie ������
{
	kind tag;			// ��־
	char data;			// ���һλ�ַ�
	node *child[MAX];	// ���ӵ�ַ
	int child_num;		// ������
	node *parent;		// ˫�׵�ַ
}trie_tree, node;

typedef struct		// ������Ϣ��¼����
{
	char tag;		// �ɹ���־
	node *add;
	int pos;
}result;

void create(trie_tree **tree)    // ���� trie ��
{
	int i;

	*tree = (trie_tree *)malloc(sizeof(node));
	// ͷ����Ƿ�֧, ���Ҳ�����κ�����
	(*tree)->tag = BRANCH;
	(*tree)->parent = NULL;
	(*tree)->child_num = 0;
	for (i=0; i<MAX; i++)
		(*tree)->child[i] = NULL;
}

void destory(trie_tree **tree)   // ���� trie ��
{
	int i;

	for (i=0; i<MAX; i++)		// ���ƶ��������ͷ�
		if ((*tree)->child[i])
			destory( &((*tree)->child[i]) );
	free(*tree);
}

node *new_node(char data, kind k, node *p)	// ����һ����֧���
{
	node *n;
	int i;

	n = (node *)malloc(sizeof(node));
	n->parent = p;
	n->tag = k;
	n->data = data;
	n->child_num = 0;
	for (i=0; i<MAX; i++) n->child[i] = NULL;
	return n;
}

// �����ϲ���һ�����
result search(trie_tree *tree, keytype *data)
{
	result re;
	int cur;

	re.pos = 0;   re.add = tree;
	if (tree)
	{
		while (data[re.pos] != '\0')
		{
			cur = data[re.pos] - 'a';
			if (tree->child[cur])
				tree = tree->child[cur];
			else break;
			re.add = tree;		// ��¼��ǰ��ַ
			re.pos++;
		}
		if (data[re.pos] == '\0' && tree->tag != BRANCH)
			re.tag = 1;
		else re.tag = 0;
	}
	return re;
}

// ����һ�������ڵĽ��
status insert(trie_tree **tree, keytype *data)
{
	result re;
	int cur;
	kind k;

	re = search(*tree, data);
	if (re.tag) return ERROR;	// �ҵ���

	// û�ҵ� data, ��ʣ�µ�Ԫ�ز��뵽����
	while (data[re.pos] != '\0')
	{
		cur = data[re.pos] - 'a';
		if (re.add->tag == LEAF) re.add->tag = L_B;

		if (!(re.add->child[cur]))
		{	// ��û��������, ��������ֵ data[n]
			if (data[re.pos + 1] != '\0') k = BRANCH;
			else k = LEAF;
			re.add->child[cur] = new_node(data[re.pos], k, re.add);
		}
		re.add->child_num++;
		re.add = re.add->child[cur];	// ������һ��
		re.pos++;
	}
	if (re.add->tag == BRANCH) re.add->tag = L_B;

	return OK;
}

// ɾ��һ�����
status remove(trie_tree **tree, keytype *data)
{
	result re;
	int i;
	node *del;

	re = search(*tree, data);
	if (!re.tag) return ERROR;	// û�ҵ�

	if (re.add->tag == L_B) re.add->tag = BRANCH;
	else if (re.add->tag == LEAF)
	{
		del = re.add;
		while (re.add->parent)	// �ͷ� re.add
		{
			re.add = re.add->parent;
			for (i=0; i<MAX; i++)
			{
				if (re.add->child[i])
				{
					if (re.add->child[i] == del)
					{
						re.add->child[i] = NULL;
						re.add->child_num--;
					}
					else if (re.add->child[i]->child_num == 0 
						&& re.add->child[i]->tag == BRANCH)
					{
						free(re.add->child[i]);
						re.add->child[i] = NULL;
					}
					// �ͷ�û�к��ӵĽ��
				}
			}	
		}
		free(del);
	}
	return OK;
}

// �ݹ�����, ������н��
void show(trie_tree *tree)
{
	int i;
	static char stack[60];	// ��¼�ַ���
	static int top = 0;

	for (i=0; i<MAX; i++)
	{
		if (tree->child[i])
		{
			stack[top++] = tree->child[i]->data;
			if (tree->child[i]->tag == LEAF 
				|| tree->child[i]->tag == L_B)
			{
				stack[top] = '\0';
				printf("%s\n", stack);
			}
			show(tree->child[i]);
			top--;		// ���ݵ�ʱ��, ջָ��ҲҪ����һ��
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
	destory(&tree);
	return 0;
}
