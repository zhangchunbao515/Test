
// ��·������ - B-tree
// ��Ҫ����: ���� search(),  ���� insert(),  ɾ�� remove()

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define OK     1
#define ERROR  0
#define TRUE   1
#define FALSE  0
typedef int status;
typedef int keytype;
typedef char FILE_ADD;	// �����ļ���ַ����

#define M 3		// ����һ�� 3 �� B ��

// B ������ṹ
typedef struct btree
{
	int num;				// �ֵ�����
	btree *child[M+1];		// ����ָ��
	btree *parent;			// ˫��ָ��
	keytype key[M+1];		// �ؼ���
	FILE_ADD *addr[M+1];	// �������ļ��ĵ�ַ
}btree, node;

typedef struct		// ���������¼����
{
	char tag;		// �ɹ���־
	btree *add;		// ����ַ
	int pos;		// �� pos ��Ԫ��
}result;


// ����һ��Ԫ�� data
result search(btree *tree, keytype data)
{
	result tmp;
	int i;

	tmp.tag = FALSE;   tmp.add = NULL;
	while (tree && !tmp.tag)		// ������, ��û�ҵ�ʱ
	{
		// Ѱ�� pos, �˲���Ҫ�������ϵ��ļ���ȡ���ڴ���
		// Ҳ���Ǵ� tree->addr[] ��¼���ļ���ַ
		// Ȼ�����ڴ��в���, ���㷨û������, ֱ�Ӳ��ҹؼ���
		// ����һ�� pos, ʹ�� key[pos] <= data < key[pos+1]
		tmp.add = tree;    tmp.pos = -1;
		if (tree->num == 1)
		{
			if (data <= tree->key[0]) tmp.pos = 0;
			else tmp.pos = 1;
		}
		else 
		{
			if (data <= tree->key[0])	// �ж���
			{
				if (data == tree->key[0]) tmp.pos = 0;
				else tmp.pos = 0;
			}
			else if (data >= tree->key[tree->num - 1])	// �ж�β
			{
				if (data == tree->key[tree->num - 1]) tmp.pos = tree->num-1;
				else tmp.pos = tree->num;
			}
			else 
				for (i=0; i<tree->num; i++)		// ��ô��Ԫ�ؿ϶����м�
				{
					if (tree->key[i] <= data 
						&& data < tree->key[i + 1])
					{
						tmp.pos = i + 1;   break;
					}
				}
		}
		if (tmp.pos == -1) break;	// û�ҵ�
		else 
		{
			if (tmp.pos < tree->num 
				&& tree->key[tmp.pos] == data) tmp.tag = TRUE;
			else 
			{	// ��������һ��, ����û�ҵ�
				tree = tree->child[tmp.pos];
				tmp.tag = FALSE;
			}
		}
	}
	return tmp;		// ����ʧ�ܷ���˫��
}

// �� t ����ϲ��� data, �����ؼ���������
// �Ӻ�����ǰ��, ���Ʋ�������ķ���
void in(btree *t, keytype data)
{
	int i;
	for (i=t->num; i>0; i--)
	{
		if (data < t->key[i-1])	// ������ǰ�ƶ�
		{
			t->key[i] = t->key[i-1];
			t->child[i+1] = t->child[i];
			t->child[i] = t->child[i-1];
			t->addr[i+1] = t->addr[i];
			t->addr[i] = t->addr[i-1];
		}
		else	// ���� i λ��
		{
			t->key[i] = data;
			t->child[i+1] = NULL;
			break;
		}
	}
	if (i == 0)		// ���ڵ�һλ
	{
		t->key[0] = data;
		t->child[0] = NULL;
	}
	t->num++;
}

// ���� tree ���, ���� [mid+1..num-1] ���ѵ� n ��
void split(btree *tree, btree *n, int mid)
{
	int i, j;

	for (j=0, i=mid+1; i<tree->num; i++, j++)
	{
		// ͬʱҪ�ƶ�����
		in(n, tree->key[i]);
		n->child[j] = tree->child[i];
		if (tree->child[i])
			tree->child[i]->parent = n;
	}
	n->child[j] = tree->child[i];
	if (tree->child[i])
		tree->child[i]->parent = n;
	tree->num = mid;			// ɾ�����ѳ�ȥ��Ԫ��
}

btree *new_node()	// ��������ʼ��һ�����
{
	btree *n;
	int i;

	n = (btree *)malloc(sizeof(btree));
	for (i=0; i<=M; i++)
	{
		n->addr[i] = NULL;
		n->child[i] = NULL;
		n->key[i] = NULL;
	}
	n->parent = NULL;
	n->num = 0;
	return n;
}

inline int ceil(int n)		// �� n/2 ������
{
	if (n % 2)
		return n / 2;
	else return n / 2 - 1;
}

// �� B ���в���һ�������ڵĽ��
// ���㷨�Ѿ�����������������, ���<���ݽṹ> 242 ҳ
status insert(btree **tree, keytype data)
{
	result tmp;
	btree *n, *r;
	char flag = FALSE;		// ָʾ�Ƿ�������
	int mid;
	
	tmp = search(*tree, data);	// ���ҵ�������
	if (!tmp.add)
	{
		*tree = new_node();		// ���������
		in(*tree, data);   return OK;
	}
	else 
	{	
		if (tmp.tag != TRUE)	// û�ҵ��øý��
		{
			in(tmp.add, data);		// �ҵ����ʵ�λ�ò���
			while (tmp.add && !flag)		// û������, Ҫ����ִ��
			{
				if (tmp.add->num > M-1)
				{
					// ������� m-1 Ҫ���ѽ��
					// ����Ƿ��Ѹ����, Ҫ�����¿ռ�
					if (tmp.add->parent)
					{
						// [0..mid-1], [mid], [mid+1..num-1]
						// �� key[mid] ���뵽˫����
						mid = ceil(tmp.add->num);
						in(tmp.add->parent, tmp.add->key[mid]);
						
						// [mid+1..num-1] ���ѳ�ȥ
						n = new_node();
						split(tmp.add, n, mid);		// ����
						
						if (tmp.add->parent->key[0] == tmp.add->key[mid])
						{
							// �����˵�һ��λ��, ��������ָ��
							tmp.add->parent->child[0] = tmp.add->parent->child[1];
							tmp.add->parent->child[1] = n;
						}
						else	// ���������һλ
						{
							tmp.add->parent->child[tmp.add->parent->num] = n;
						}
						n->parent = tmp.add->parent;
					}
					else	// ��������
					{
						r = new_node();		// �����¸�
						mid = ceil(tmp.add->num);
						in(r, tmp.add->key[mid]);
						n = new_node();		// �������ֵܽ��
						
						split(tmp.add, n, mid);
						n->parent = tmp.add->parent = r;
						r->child[0] = tmp.add;		// �ؽӺ���
						r->child[1] = n;
						*tree = r;		// �����¸�
					}
					tmp.add = tmp.add->parent;	// ����˫��Ҫ��Ҫ����
					tmp.tag = FALSE;
				}
				else flag = TRUE;
			} // end while
		}
		else return ERROR;
	}
	return OK;
}

void del_pos(btree *tree, int pos)	// ����˳���ɾ��
{
	int i;

	for (i=pos; i<tree->num; i++)
	{
		tree->addr[i] = tree->addr[i+1];
		tree->addr[i+1] = NULL;
		tree->child[i] = tree->child[i+1];
		tree->child[i+1] = NULL;
		tree->key[i] = tree->key[i+1];
	}
	tree->child[i] = tree->child[i+1];
	tree->num--;
}

int find_pos(btree *f, btree *child)	// Ѱ��λ��
{
	int i;
	for (i=0; i<=f->num; i++)
	{
		if (f->child[i]->key[0] == child->key[0])
			break;
	}
	return i;
}

void del_child(btree *cur)
{
	int i;

	for (i=0; i<cur->num; i++)
	{
		if (cur->child[i])
		{
			free(cur->child[i]);
			cur->child[i] = NULL;
		}
	}
}

void left(btree *cur, int pos)		// B ������
{
	cur->child[pos]->key[0] = cur->key[pos];
	cur->key[pos] = cur->child[pos+1]->key[0];
	del_pos(cur->child[pos+1], 0);
}

void right(btree *cur, int pos)		// B ������
{
	cur->child[pos]->key[0] = cur->key[pos-1];
	cur->key[pos-1] = cur->child[pos-1]->key[1];
	del_pos(cur->child[pos-1], 1);
}

// �� cur ���ͷ� child[del], �ٽ�����Ӧ�ĺϲ�
void combine_p(btree *cur, int del)
{
	int i;

	free(cur->child[del]);
	cur->child[del] = NULL;
	if (del == 0)		// ������
	{
		in(cur->child[1], cur->key[0]);
		for (i=del; i<cur->num; i++)
		{
			cur->child[i] = cur->child[i+1];
			cur->key[i] = cur->key[i+1];
		}
	}
	else	// ������
	{
		in(cur->child[del-1], cur->key[del-1]);
		if (del == 1) 
		{
			cur->key[0] = cur->key[1];
			cur->child[1] = cur->child[2];
		}
	}
	cur->num--;
}

// �ϲ�˫���뺢��, �߶Ƚ�һ
void combine_child(btree *f, int del)
{
	if (del == 0) f->key[1] = f->child[1]->key[0];
	else
	{
		f->key[1] = f->key[0];
		f->key[0] = f->child[0]->key[0];
	}
	f->num = 2;
	del_child(f);
}

// ƽ���޸����1: ˫��һ��, ����һ��
void fixup_1(btree *fcur, btree *u, btree *cur, int i)
{
	if (i == 0)
	{
		fcur->key[1] = u->key[0];
		fcur->child[1] = u->child[0];
		fcur->child[2] = u->child[1];
	}
	else 
	{
		fcur->child[2] = fcur->child[1];
		fcur->key[1] = fcur->key[0];
		fcur->key[0] = u->key[0];
		fcur->child[1] = u->child[1];
		fcur->child[0] = u->child[0];
	}
	fcur->num = 2;
	u->child[0]->parent = u->child[1]->parent = fcur;
	free(u);
}

// ƽ���޸����2: ˫�׶��, ����һ��
void fixup_2(btree *fcur, btree *u, btree *cur, int i)
{
	if (i == 0)
	{
		in(u, fcur->key[0]);
		u->child[0] = fcur->child[0];
		fcur->child[0]->parent = u;
		del_pos(fcur, 0);
	}
	else if (i == 1)
	{
		in(u, fcur->key[0]);
		u->child[2] = fcur->child[1];
		fcur->child[1]->parent = u;
		fcur->key[0] = fcur->key[1];
		fcur->child[1] = fcur->child[2];
		fcur->child[2] = NULL;
		fcur->num--;
	}
	else
	{
		in(u, fcur->key[1]);
		u->child[2] = fcur->child[2];
		fcur->child[2]->parent = u;
		fcur->child[2] = NULL;
		fcur->num--;
	}
}

// ƽ���޸����3: ˫��һ��, ������
void fixup_3(btree *fcur, btree *u, btree *cur, int i)
{
	node *n = new_node();

	n->num = 1;
	n->parent = fcur;
	if (i == 0)
	{
		n->key[0] = fcur->key[0];
		fcur->key[0] = u->key[0];
		n->child[0] = fcur->child[0];
		n->child[1] = u->child[0];
		fcur->child[0] = u->child[0]->parent = n;
		u->child[0] = NULL;
		fcur->child[0] = n;
		del_pos(u, 0);
	}
	else 
	{
		n->key[0] = fcur->key[0];
		fcur->key[0] = u->key[1];
		n->child[0] = u->child[2];
		u->child[2]->parent = n;
		n->child[1] = fcur->child[1];
		fcur->child[1]->parent = n;
		u->child[2] = NULL;
		fcur->child[1] = n;
		n->parent = fcur;
		u->num--;
	}
}

// ƽ���޸����4: ˫�׶��, ������
void fixup_4(btree *fcur, btree *u, btree *cur, int i)
{
	node *n = new_node();

	n->num = 1;
	n->parent = fcur;
	if (i == 0)
	{
		n->key[0] = fcur->key[0];	// ����ͨ��
		fcur->key[0] = u->key[0];
		n->child[0] = fcur->child[0];
		n->child[1] = u->child[0];
		fcur->child[0]->parent = u->child[0]->parent = n;
		u->child[0] = NULL;
		fcur->child[0] = n;
		del_pos(u, 0);
	}
	else if (i == 1)
	{
		n->key[0] = fcur->key[0];	// ����ͨ��
		fcur->key[0] = u->key[1];
		n->child[0] = u->child[2];
		n->child[1] = fcur->child[1];
		u->child[2]->parent = fcur->child[1]->parent = n;
		u->child[2] = NULL;
		fcur->child[1] = n;
		u->num--;
	}
	else if (i == 2)
	{
		n->key[0] = fcur->key[1];	// ����ͨ��
		fcur->key[1] = u->key[1];
		n->child[0] = u->child[2];
		n->child[1] = fcur->child[2];
		u->child[2]->parent = fcur->child[2]->parent = n;
		u->child[2] = NULL;
		fcur->child[2] = n;
		u->num--;
	}
}

// �� B ����ɾ��һ���ؼ���
status remove(btree **tree, keytype data)
{
	result tmp;
	node *cur;		// ˫��
	node *fcur;		// �游
	node *u;		// ����
	int i;
	char flag = 0;
	int min = ceil(M);	// ��С�����
	int lower;
	int del, re;

	tmp = search(*tree, data);
	if (!tmp.tag) return ERROR;		// û�ҵ�
	if (tmp.add->child[0] == NULL)	// �����Ҷ��
	{
		if (tmp.add->num > min || !(tmp.add->parent))
		{
			del_pos(tmp.add, tmp.pos);
			if (tmp.add->num == 0)
			{
				free(*tree);
				*tree = NULL;	// ɾ����
			}
		}
		else	// ���������ֵ���û��"����"�Ľ��
		{
			flag = 0;		// flag ��־��û�ж���Ľ��
			cur = tmp.add->parent;
			i = find_pos(cur, tmp.add);
			switch (i)
			{
			case 0 :	// ������
				if (cur->child[1]->num > min)
				{
					left(cur, 0);   flag = 1;
				}
				break;
			case 1 :	// �������
				if (cur->child[0]->num > min)
				{
					right(cur, 1);   flag = 1;
				}
				else if (cur->child[2] 
					&& cur->child[2]->num > min)
				{
					left(cur, 1);   flag = 1;
				}
				break;
			case 2 :	// ������
				if (cur->child[1]->num > min)
				{
					right(cur, 2);   flag = 1;
				}
				break;
			}
			if (!flag)		// �ֵ�û�ж���Ľ��
			{				// ˫���ж����, ��һ�����Լ��ϲ�
				if (cur->num > min) combine_p(cur, i);
				else 
				{
					combine_child(cur, i);
					lower = 1;			// �߶Ƚ�һ
					while (lower)		// ѭ������, ����ƽ��
					{
						fcur = cur->parent;
						lower = 0;
						if (fcur)
						{
							i =  find_pos(fcur, cur);
							if (i == 0) u = fcur->child[1];
							else u = fcur->child[i-1];
							switch ((fcur->num==1) + (u->num==1) * 2)
							{
							case 0 :		// F ���, U ���
								fixup_4(fcur, u, cur, i);   break;
							case 1 :		// F һ��, U ���
								fixup_3(fcur, u, cur, i);   break;
							case 2 :		// F ���, U һ��
								fixup_2(fcur, u, cur, i);   break;
							case 3 :		// F һ��, U һ��
								fixup_1(fcur, u, cur, i);
								lower = 1;		// �߶Ƚ�һ 
								cur = fcur;		// ������һ��, ����ƽ�⵽��
								break;		
							}
						}
					} // end while
				}
			}
		}
	}
	else	// ����Ҷ��, �ú���滻��, ǰ���滻Ҳ��
	{
		del = tmp.add->key[tmp.pos];
		cur = tmp.add->child[tmp.pos + 1];
		while (cur->child[0] != NULL) cur = cur->child[0];
		re = cur->key[0];
		remove(tree, cur->key[0]);
		// �˴� remove ����ִ��һ������, ���Ż�
		tmp = search(*tree, del);
		tmp.add->key[tmp.pos] = re;
	}
	return OK;
}


void show(btree *tree)		// �����Ԫ��, ��� B ��
{
	int i;
	if (tree)
	{
		printf("{");
		for (i=0; i<tree->num; i++)
		{
			printf("%d", tree->key[i]);
			if (i != tree->num - 1) printf(", ");
		}
		printf("}, ");
		if (tree->num == 1) printf("\t\t");
		else printf("\t");
		// ��Ϊ���νṹ�������ڿ���̨�¹ۿ�
		// �������˫��, �������� B ���ṹ�Ƿ���ȷ
		if (tree->parent) 
		{
			printf("parent = {");
			for (i=0; i<tree->parent->num; i++)
			{
				printf("%d", tree->parent->key[i]);
				if (i != tree->parent->num - 1) printf(", ");
			}
			printf("}, ");
		}
		else printf("parent = NULL");
		printf("\n");

		for (i=0; i<=tree->num; i++)	// �ݹ�鿴���ӽ��
			if (tree->child[i]) show(tree->child[i]);
			else break;
	}
}

char display(btree *tree)	// ��ʾģ��
{
	char c;

	printf("�������:\n");
	show(tree);   printf("\n\n�� c �˳�, ���س�����\n");
	getchar();
	c = getch();
	system("cls");
	return c;
}

int main(void)
{
	btree *tree = NULL;
	keytype data = 0;

	while (1)		// �������
	{
		printf("������Ҫ���ҵ�Ԫ��: ");
		scanf("%d", &data);
		if (insert(&tree, data))		// ����
			printf("\n��Ԫ�ز�����, �Ѳ���!\n\n");
		else printf("\n�ҵ�!\n\n");
	
		if (display(tree) == 'c') break;
	}
	while (1)		// ɾ������
	{
		printf("������Ҫɾ����Ԫ��: ");
		scanf("%d", &data);
		if (!remove(&tree, data))		// ɾ��
			printf("\n��Ԫ�ز�����, ɾ��ʧ��!\n");
		else printf("\n��ɾ��!\n\n");

		if (display(tree) == 'c') break;
	}
	return 0;
}
