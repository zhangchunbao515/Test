// �������������� (haffman)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef short int status;
#define NO -1		// NO ��ʾû��

// ������������ṹ
// �����ϸ�Ķ���������˳�򴢴�
typedef struct
{
	int wight;		// Ȩֵ
	int lchild;		// ���� 0
	int rchild;		// �Һ��� 1
	int parent;		// ˫��
}htree;		// ��̬����ռ�


// ��ʼ��������Ա
inline void init_member(htree **tree, int i)
{
	(*tree)[i].parent = NO;
	(*tree)[i].lchild = NO;
	(*tree)[i].rchild = NO;
}

// ����ģ��, ����Ȩֵ
void input(char *str, int *w)
{
	int len, i;

	// ���뺺��Ҳ�ǿ��Ե�, ��Ϊһ������ռ�����ֽ�
	// �����ʱ��, �����ַ��ı����ʾһ������
	scanf("%s", str);
	len = strlen(str);
	for (i=0; i<len; i++)
	{
		// ȨֵԽ��ı���Խ��
		printf("������ %c ��Ȩֵ: ", str[i]);
		scanf("%d", w + i);
	}
	fflush(stdin);
	system("cls");
}

// ���ٹ������������
void destory(htree *tree, char **table, int n)
{
	int i;

	if (tree) free(tree);
	for (i=0; i<n; i++)		// ���ƶ�ά������ͷ�
		if (table[i]) free(table[i]);
	free(table);
}

// �ݹ鷨, �����Ĵ�Ȩ·������, size ���Ĵ�С, flood ����
// �����Ҷ��, ����·������
// �������, �����Һ��ӵĳ���
int WPL(htree *tree, int root, int flood)
{
	int len = 0;

	if (tree[root].lchild == NO 
		&& tree[root].rchild == NO)
			return flood * tree[root].wight;

	len += WPL(tree, tree[root].lchild, flood + 1);
	len += WPL(tree, tree[root].rchild, flood + 1);

	return len;
}

// �� buf ת�뵽 result ��, ��������������ַ�
// ������ str ���ҵ� *buf ��λ�� pos
// �� table �е� pos ���ַ������Ƶ� result ��
status encode(char **table, char *str, char *buf, char *result)
{
	int cur = 0;
	int pos;
	char *s = str;

	while (*buf != '\0')
	{
		// �� str ���ҵ�ǰ�ַ�
		pos = 0;
		while (s[pos] != '\0')
		{
			if (s[pos] == *buf) break;
			pos++;
		}
		if (s[pos] == '\0') return 0;	// û�ҵ��ַ�

		// �� table[pos] ���Ƶ� result ��
		strcpy(result + cur, table[pos]);
		while (result[cur] != '\0') cur++;   // �ƺ� cur
		buf++;
	}
	return 1;
}

// ������ result ͨ���������� tree(���� n) ��ԭ������ buf
status decode(htree *tree, char *str, char *result, char *buf)
{
	int n;
	int cur = 0;
	int pos = 0;
	int root;
	
	// n ���ַ��� (2n-1) �����, �±��� 1
	n = strlen(str);   root = 2 * n - 2;

	for (pos=0; result[pos] != '\0'; pos++)
	{
		if (result[pos] == '0')
			root = tree[root].lchild;	// ������
		else if (result[pos] == '1')
			root = tree[root].rchild;	// ������
		else return 0;   // ���Ĵ���

		// ������Һ���ͬʱΪ 0 ˵������Ҷ�ӽ��
		if (tree[root].lchild == NO 
			&& tree[root].rchild == NO)
		{
			buf[cur++] = str[root];
			root = 2 * n - 2;	// ���´Ӹ���ʼ��
		}
	}
	buf[cur] = '\0';
	return 1;
}

// --------------������������Ҫ����----------------
// ѡ��һ��Ȩֵ��С, ��û�з��ʹ��Ľ��
// ���˫��Ϊ NO �պ���û�з��ʹ���
inline int select(htree **tree, int n)
{
	int i;
	int wight = 0xFFFFFFF;
	int min;

	for (i=0; i<n; i++)
		if ((*tree)[i].parent == NO 
			&& (*tree)[i].wight < wight)
			{
				wight = (*tree)[i].wight;	// ��¼��С��Ȩֵ
				min = i;		// �Լ����ĵ�ַ
			}
	(*tree)[min].parent = -2;		// ��ֹ�´���ѡ��ͬ����
	return min;
}

// �Ӹ���Ҷ��, ��ù���������, ��ջ�ǵݹ�
// �㷨:
// ��ÿ�����, ����flag[i] ״̬���
// 0 ��ʾҪ��������, 1 ��ʾҪ�����Һ���, 2 ��ʾ�����ʹ���
status create_table2(htree **tree, char ***table, int n, int r)
{
	char *buf;
	int cur;
	short int *flag;	// ����״̬�������

	*table = (char **)malloc(n * sizeof(char *));	// ����ָ������
	buf = (char *)malloc((n+3) * sizeof(char));
	flag = (short int *)malloc((r+1) * sizeof(short int));
	if (!((*table) && buf && flag)) return 0;

	for (cur=0; cur<=r; cur++) flag[cur] = 0;
	cur = 0;   r--;		// r �Ǵ�С, ���±�� 1
	while (r != NO)
	{
		if (flag[r] == 0)   // 0 ��ʾ����û����
		{
			flag[r] = 1;
			if ((*tree)[r].lchild != NO)
			{
				r = (*tree)[r].lchild;
				buf[cur++] = '0';
			}
			else if ((*tree)[r].rchild == NO)
			{
				buf[cur] = '\0';
				(*table)[r] = (char *)malloc((cur+1) * sizeof(char));
				strcpy((*table)[r], buf);
			}
		}
		else if (flag[r] == 1)  // 1 ��ʾ�Һ���û����
		{
			flag[r] = 2;
			if ((*tree)[r].rchild != NO)
			{
				r = (*tree)[r].rchild;
				buf[cur++] = '1';
			}
		}
		else	// 2 ��ʾ���Һ��Ӷ�������, �˻�ȥ
		{
			r = (*tree)[r].parent;
			cur--;
		}
	}
	free(buf);   free(flag);
	return 1;
}

// ���ݹ������� tree, ������� table
// ����Ҷ�� n ��, ��Ҷ�� size - n ��
// ���ô�Ҷ���ߵ����ķ�����ñ���
status create_table(htree **tree, char ***table, int n, int size)
{
	int i;
	int son, p;
	char *buf;		// ��¼����
	int cur;

	// Ϊ�������ռ�
	(*table) = (char **)malloc(n * sizeof(char *));
	if (!(*table)) return 0;

	// n ���ַ��������볤�Ȳ����� n - 1
	buf = (char *)malloc(n * sizeof(char));
	buf[n - 1] = '\0';

	for (i=0; i<n; i++)		// ����ÿƬҶ��
	{
		cur = n - 1;
		son = i;
		p = (*tree)[son].parent;
		while (p != NO)
		{
			if ((*tree)[p].lchild == son) 
				buf[--cur] = '0';	// ����Ϊ 0
			else 
				buf[--cur] = '1';
			son = p;
			p = (*tree)[p].parent;
		}
		// ���һ���ַ��ı���, ��¼������, ����������ָ��
		(*table)[i] = (char *)malloc((size - cur) * sizeof(char));
		if (!(*table)[i]) return 0;
		strcpy((*table)[i], buf + cur);
	}
	free(buf);
	return 1;
}

// �ú�����ɶ�̬���ɹ�������, ���������
// �� tree �Ϲ����������, ���뱣�浽 table ��, w ��Ȩֵ
status haffman_code(htree **tree, char ***table, int *w, int n)
{
	int size;
	int i;
	int s1, s2;

	// ------����ռ�ͳ�ʼ����������
	size = 2 * n - 1;	// ���� n ���ַ�����, ��Ҫ 2n-1 �����
	*tree = (htree *)malloc(size * sizeof(htree));
	if (!(*tree)) return 0;

	// ���Ŀռ�˵��  [0..n-1], [n..size-1]
	// 0 �� n-1 ��Ҷ�ӽ���,  n �� size ������Ҷ�ӽ���
	for (i=0; i<n; i++)		// ��ʼ��Ҷ��[0..n-1]
	{
		(*tree)[i].wight = w[i];	// ��ʼ��Ȩֵ
		init_member(tree, i);
	}
	for (i=n; i<size; i++)   // ��ʼ����Ҷ�ӽ��[n..size-1]
	{
		(*tree)[i].wight = NO;
		init_member(tree, i);
	}

	// ------��̬����������� htree
	for (i=n; i<size; i++)	// ��Ҷ��[n..size-1]
	{
		// ��[0..i-1]��ѡ���� Ȩֵ��С��û�з��ʹ� �ĵĽ��
		s1 = select(tree, i);
		s2 = select(tree, i);

		(*tree)[i].lchild = s1;		// s1, s2 ��������
		(*tree)[i].rchild = s2;
		(*tree)[s1].parent = (*tree)[s2].parent = i;
		(*tree)[i].wight = (*tree)[s1].wight + (*tree)[s2].wight;
	}
	
	// ------���ɹ�������� �� table, �������������Կ�
	create_table(tree, table, n, size);
//	create_table2(tree, table, n, size);

//  create_table() �Ǵ�Ҷ�� �� �������
//  create_table2() �ǴӸ� �� Ҷ�������
	return 1;
}

int main(void)
{
	char str[60];	// ����Ҫ������ַ�
	int w[60];		// ��Ӧ��Ȩֵ
	htree *tree;	// ��������
	char **table;	// ����������� (��ά����)
	// str[i] ��Ӧ tree[i] �� �� table[i] �ı���

	int len, i;
	char buf[100];
	char result[200];

	printf("\n--- ����������\n\n--- ������Ҫ������ַ�: ");
	input(str, w);

	len = strlen(str);
	haffman_code(&tree, &table, w, len);	// ��ʼ����������
	i = WPL(tree, 2 * len - 2, 0);			// �� WPL
	printf("\n--- ���������� WPL = %d\n", i);
	printf("\n--- �������������:\n\n");
	for (i=0; i<len; i++)
		printf(" %c : %s\n", str[i], table[i]);

	printf("\n�����ַ��� ת���� ����������:");
	scanf("%s", buf);	fflush(stdin);
	if (encode(table, str, buf, result))	// ��ʼת��
		printf("\n��������: %s\n", result);
	else printf("\n���Ĵ���!\n");

	printf("\n������������� ת���� �ַ���:");
	scanf("%s", result);	fflush(stdin);
	if (decode(tree, str, result, buf))		// ��ʼ����
		printf("\n��������: %s\n\n", buf);
	else printf("\n���Ĵ���!\n\n");

	destory(tree, table, len);

	return 0;
}
