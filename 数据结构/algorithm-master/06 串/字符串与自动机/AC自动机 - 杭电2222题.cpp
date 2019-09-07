
#include <stdio.h>
#include <malloc.h>

#define NUM 26		// 26 ��Сд��ĸ
#define MAXN 100000

typedef struct node		// �ֵ����ṹ
{
	int count;			// �ַ����ĳ��ֵĴ���, ���ظ�
	node *fail;			// ʧ��ָ��
	node *next[NUM];	// ����ָ��
}node;

node *q[MAXN];
char str[1000010];		// ����

// ����һ���½��, ���ص�ַ
node *new_node()
{
	int i;
	node *tmp = (node *)malloc(sizeof(node));

	tmp->count = 0;
	tmp->fail = NULL;
	for (i=0; i<NUM; i++)
		tmp->next[i] = NULL;
	return tmp;
}

// �� str �ַ��������ֵ�����
void insert(node *tree, char *str)
{
	int i;
	int add;
	node *cur = tree;

	for (i=0; str[i]!='\0'; i++)
	{
		add = str[i] - 'a';
		if (cur->next[add] == NULL)
			cur->next[add] = new_node();
		cur = cur->next[add];
	}
	cur->count++;		// �õ��������� 1
}

// ����ʧ��ָ��
void build(node *tree)
{
	int f = 0;		// ��ͷ
	int r = 0;		// ��β
	node *cur;
	node *ptr;
	int i;

	q[r] = tree;
	r = (r + 1) % MAXN;
	while (f != r)
	{
		cur = q[f];
		f = (f + 1) % MAXN;
		for (i=0; i<NUM; i++)		// �����ӽ��
		{
			if (cur->next[i])
			{
				if (cur == tree) cur->next[i]->fail = tree;
				else
				{
					// ����ʧ��ָ��
					for (ptr=cur->fail; ptr!=NULL; ptr=ptr->fail)
					{
						// �������ͬǰ�����
						if (ptr->next[i])
						{
							cur->next[i]->fail = ptr->next[i];
							break;
						}
					}
					// û���ҵ�ǰ�������ͬ�Ĵ�
					if (ptr == NULL)
						cur->next[i]->fail = tree;
				}
				q[r] = cur->next[i];
				r = (r + 1) % MAXN;
			}
		}
	}
}

// ���������ж��ٸ��Ӵ�������, �Ӵ������ظ�
int search(node *root, char *str)
{
	int i;
	int add;
	node *cur = root;
	node *ptr;
	int total = 0;

	for (i=0; add=str[i]-'a', str[i]!='\0'; i++)
	{
		// ȥ��ʧ��ָ��ָ��Ľ�����ƥ��
		while (cur != root)
		{
			if (cur->next[add]) break;
			cur = cur->fail;
		}
		ptr = cur = cur->next[add];
		if (cur == NULL) ptr = cur = root;
		while (ptr != NULL)
		{
			if (ptr->count > 0)
			{
				total += ptr->count;
				ptr->count = 0;
			}
			ptr = ptr->fail;
		}
	}
	return total;
}

void destory(node *tree)
{
	int i;

	for (i=0; i<NUM; i++)
		if (tree->next[i])
			destory(tree->next[i]);
	free(tree);
}

int main(void)
{
	int t, n, i;
	char buf[70];
	node *tree;

	scanf("%d", &t);
	while (t--)
	{
		tree = new_node();		// �����
		scanf("%d", &n);
		for (i=0; i<n; i++)		// ����������Ӵ�
		{
			scanf("%s", buf);
			insert(tree, buf);
		}
		scanf("%s", str);		// ��������
		build(tree);			// ����ʧ��ָ��
		n = search(tree, str);	// ���Ҷ��ٸ��Ӵ�������
		printf("%d\n", n);
		destory(tree);
	}
	return 0;
}