//
// �����ֵ����Ķ�ģʽƥ���㷨֮ AC �Զ���
//
// �㷨����:
// 1. ���ݶ��ģʽ������һ���ֵ���
// 2. �����ֵ�����ʧ��ָ��, ��������� AC �Զ���
// 3. ���������Զ����Ͻ���ƥ��, ����¼���
//
// ����˵����, ��һƪ�������Һܶ������
// ���ʹ�� KMP �㷨Ҳ����, ����̫����
// ���㷨���� KMP, ����������, KMP �����ԵĽṹ�Ͻ����Զ���
// �����㷨�����νṹ�Ͻ����Զ���
// �´���������״�ṹ�Ͻ����Զ������㷨Ҳͬ��
// 
// �ٸ�����, ������ģʽ�� aash, she, he
// ʧ��ָ������, ���������� kmp �� next[] ����, ��ṹ��������������
// a  a  s  h 
//       |  |
//       s  h  e 
//          |  |
//	        h  e     ������ṹתΪ�ֵ����ļ����Զ���


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	node *parent;		// ˫�׵�ַ
	node *fail;			// ʧ��ָ��
	int num;			// �ô����ֵĴ���
}trie_tree, node;

typedef struct		// ������¼��¼����
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
	(*tree)->fail = NULL;
	(*tree)->num = 0;
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
	n->parent = p;   n->tag = k;      n->data = data;
	n->num = 0;      n->fail = NULL;
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
		re.add = re.add->child[cur];	// ������һ��
		re.pos++;
	}
	if (re.add->tag == BRANCH) re.add->tag = L_B;
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
			if (tree->child[i]->tag != BRANCH)
			{
				stack[top] = '\0';
				printf("%s\t", stack);
				if (tree->child[i]->num)
					printf("���� %d ��\n", tree->child[i]->num);
				else printf("δ�ҵ�!\n");
			}
			show(tree->child[i]);
			top--;		// ���ݵ�ʱ��, ջָ��ҲҪ����һ��
		}
	}
}

void input(char *re[], int n)	// ����ģ��
{
	int i, len;
	char buf[100];

	fflush(stdin);
	for (i=0; i<n; i++)
	{
		scanf("%s", buf);   getchar();
		len = strlen(buf);
		re[i] = (char *)malloc((len+2) * sizeof(char));
		strcpy(re[i], buf);
	}
}

// ���в�α���, ��ÿ����㽨��ʧ��ָ��
// ����: ����һ����� k, ���� k ˫�׵�ʧ��ָ����
// ��Ϊ˫����ͬ�Ľ��Ų�����ƥ��˫����
// ������˫�׵ĺ�����Ҳ�� k ���, ��ʧ��ָ��ָ����
// ��ʾƥ��ʧ�ܺ�, ���������ƥ��
// ֱ��ʧ��ָ��������, �����һ�����ӽ��, ָ������
// ��ʾҪ���´Ӹ���ʼƥ��
void create_fail_point(trie_tree *tree)
{
	node *queue[100];		// ���в�α���
	int front = 0;
	int rear = 0;
	node *tmp;
	node *cur;		// ��ǰʧ��ָ��
	int i;

	tree->fail = NULL;		// ���û��ʧ��ָ��
	queue[rear] = tree;		// �����
	rear = (rear + 1) % 100;
	while (front != rear)
	{
		tmp = queue[front];
		front = (front + 1) % 100;
		for (i=0; i<MAX; i++)		// ��������, ���
		{
			if (tmp->child[i])
			{
				queue[rear] = tmp->child[i];	// ����Ӽ�¼
				rear = (rear + 1) % 100;
				cur = tmp;			// ȡ��˫��, �޸�ʧ��ָ��
				if (cur == tree) tmp->child[i]->fail = tree;
				else 
				{	// cur ��ʧ��ָ��ָ��Ľ��
					while (cur->fail)
					{
						cur = cur->fail;
						if (cur->child[i]) 
						{
							tmp->child[i]->fail = cur->child[i];
							break; 
						}
						// ֻ����һ������
					}
					if (tmp->child[i]->fail == NULL)
						tmp->child[i]->fail = tree;
				}
			}
		} // end for
	} // end while
}

// ����������ģʽƥ��, ����¼ num ��Ա
void find(trie_tree *tree, char *str)
{
	int i = 0;
	int pos;
	node *cur = tree;
	node *tmp;

	while (str[i] != '\0')
	{
		pos = str[i] - 'a';
		// û��������Ӿ���ʧ��ָ����, ֱ���ߵ���
		while (cur != tree && !(cur->child[pos])) cur = cur->fail;
		// ��������Ӿ�������һ��
		if (cur->child[pos]) cur = cur->child[pos];
		else cur = tree;		// û���������, �Ӹ�����ƥ��
		tmp = cur;
		while (tmp != tree)		// ȥ��ʧ�ܵĵط�, ƥ����ͬ��
		{
			if (tmp->tag != BRANCH) tmp->num++;   // �ߵ���Ҷ��
			tmp = tmp->fail;
		}
		i++;
	}
}

int main(void)
{
	trie_tree *tree;
	char *re[50];
	char main_str[1000];	 // ��������ʵ����Ҫ���Ը���
	int n;

	create(&tree);
	printf("���� n, �� n ��ģʽ��: ");
	scanf("%d", &n);
	input(re, n);
	printf("\n��������: ");
	scanf("%s", main_str);   getchar();
	while (n--)  insert(&tree, re[n]);   // �����ֵ���
	create_fail_point(tree);		// ����ʧ��ָ��
	find(tree, main_str);			// ����ƥ��
	printf("\n");
	show(tree);					// ������

	destory(&tree);
	return 0;
}
