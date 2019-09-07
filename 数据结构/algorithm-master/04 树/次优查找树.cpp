
// ���Ų�����, �ö���������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char keytype;	// �� char ���� keytype
typedef int status;
#define OK 1
#define ERROR 0


// ���Ų������Ĵ���ṹ
typedef struct sostree
{
	keytype data;
	sostree *lchild;
	sostree *rchild;
}sostree, snode;


// �����ĵݹ鲿��, sw[] ����Ȩֵ��, low �� high
status create_tree(sostree **tree, keytype *str, 
				   int *sw, int low, int high)
{
	int dw = sw[high] + sw[low - 1];	// ��Ҳ�Ƕ�̬�滮��˼��
	int i, p;		// p ��ƽ������
	int min, pos;

	// ����С��ƽ������ pos
	pos = low;							// ��ֹ�Ҳ��������
	min = abs(sw[high] - sw[low]);		// min = INT_MAX Ҳ�ǿ��Ե�
	for (i=low + 1; i<=high; i++)		// �������� [low+1..high]
	{
		// p ������������ƽ��ƽ������
		// p ���������� - �������ľ��Բ�ֵ
		// ��ֵ��С�� p ������������Ȩֵ�Ͳ��һ�������
		// ֻ�Ǵ��Ų�����, ��������
		p = abs(dw - sw[i] - sw[i-1]);
		if (p < min) { min = p;   pos = i; }
	}
	*tree = (snode *)malloc(sizeof(snode));
	(*tree)->data = str[pos - 1];

	// ��������, ���� [low..pos-1], �Һ��� [pos+1..high]
	if (pos == low) (*tree)->lchild = NULL;
	else create_tree( &((*tree)->lchild), str, sw, low, pos - 1 );
	if (pos == high) (*tree)->rchild = NULL;
	else create_tree( &((*tree)->rchild), str, sw, pos + 1, high );

	return OK;
}

// ����Ԫ�غ�Ȩֵ, �� tree �Ͻ������Ų�����
status create(sostree **tree, keytype *str, int *wight)
{
	int len = strlen(str);
	int *sw;	// sw[i + 1] ����ǰ i ���, sw[0] ����
	int i;

	if (!len) return ERROR;

	sw = (int *)malloc((len + 5) * sizeof(int));
	sw[0] = 0;
	for (i=1; i<=len; i++)		// ��ǰ n ��Ȩֵ, ��̬�滮��˼��
		sw[i] = sw[i-1] + wight[i-1];
	
	create_tree(tree, str, sw, 1, len);
	free(sw);
	return OK;
}

// ���� ch Ԫ��
status search(sostree *tree, keytype ch)
{
	if (!tree) return ERROR;

	if (tree->data == ch) return OK;
	else if (ch < tree->data)
		return search(tree->lchild, ch);
	else 
		return search(tree->rchild, ch);
	return ERROR;
}

void input(keytype *str, int *wight)	// ����ģ��, �� 0 0 ����
{
	int i;

	for (i=0; i<100; i++)
	{
		scanf("%c %d", str + i, wight + i);
		getchar();
		if (str[i] == '0' && wight[i] == 0) 
		{
			str[i] = '\0';    wight[i] = -1;	// �������
			break;
		}
	}
	fflush(stdin);
}

void destory(sostree *tree)		// ������
{
	if (tree)
	{
		destory(tree->lchild);
		destory(tree->rchild);
		free(tree);
	}
}

int main(void)
{
	sostree *tree;		// ����
	keytype str[100];	// ��¼���
	int wight[100];		// ����Ӧ��Ȩֵ
	char c;

	printf("������Ų�����\n������Ԫ�ؼ�Ȩֵ:\n");
	input(str, wight);
	create(&tree, str, wight);	// ���ݽ��Ȩֵ����

	while (1)
	{
		printf("\n�����������: ");
		scanf("%c", &c);   getchar();
		if (c == '\n') break;
		if (search(tree, c)) printf("�ҵ�!\n");
		else printf("����: δ�ҵ�!\n");
	}
	destory(tree);
	return 0;
}
/*		�����������
A 1
B 1
C 2
D 5
E 3
F 4
G 4
H 3
I 5
0 0


A 1
B 30
C 2
D 29
E 3
0 0
*/