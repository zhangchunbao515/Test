// ������������ �� �������� �ָ�������
// ���ó���Ϊ 0 , ��������Ϊ \0 ���ؿ�
// ���������, �ָ�����
// �ָ���������,����ͼ
// pos = 3   ��:'A'
// ���� A BCD EFG
// ���� CBD A FEG
// ����������BCD, ������EFG, ���� f+1, f+pos+1, ���� pos
// ����������CBD, ������FEG, ���� m,   m+pos+1, ���� len-pos
// ������������,,�Һ�����������,,

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef char elemtype;

// ���������
typedef struct btnode
{
	elemtype data;
	btnode *lchild;
	btnode *rchild;
}btnode;


// �ݹ齨������
// ���ؽ��õ�����, ��������, ��������, ���ó���
btnode *createtree(elemtype *f, elemtype *m, int len)
{
	btnode *n;
	int i, pos;		// ��¼��λ��

	if (len <= 0 || *f == '\0') return NULL;  // ��������
	
	// ������: ����һ��������
	n = (btnode *)malloc(sizeof(btnode));
	if (!n) return NULL;
	n->data = *f;

	// ������ [0..len) ��*f
	for (i=0; i<len; i++)
		if (m[i] == *f) break;
	if (i == len) return NULL;	// i = len����û�ҵ�,���д���.
	else pos = i;

	// �ָ���������, ����������
	n->lchild = createtree(f + 1, m, pos);
	n->rchild = createtree(f + pos+1, m +pos+1, len-pos);

	return n;
}

// ��������,��������,�ָ�������, ���ظ��ڵ��ַ
btnode *create(elemtype *f, elemtype *m)
{
	int len1, len2;

	// �Ƚ��кϷ����
	if (!(f && m)) return NULL;
	len1 = strlen(f);
	len2 = strlen(m);
	if (len1 != len2) return NULL;
	
	// ������һ�㺯��,�ݹ齨��
	return createtree(f, m, len1);
}

// �������
void first_tra(btnode *tree)
{
	if (tree)
	{
		printf("%c, ", tree->data);
		first_tra(tree->lchild);
		first_tra(tree->rchild);
	}
}

int depth(btnode *tree)
{
	int a, b;
	
	if (!tree) return 0;
	a = depth(tree->lchild);
	b = depth(tree->rchild);
	return (a > b ? a : b) + 1;
}

// �ͷ�
void destory(btnode *tree)
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
	char first[70];		// ����
	char mid[70];		// ����
	btnode *head;		// ͷ���

	// ��������������
	printf("��������������: ");
	scanf("%s", first);
	printf("��������������: ");
	scanf("%s", mid);

	// �ָ�������
	head = create(first, mid);
	
	printf("\n�������: ");
	first_tra(head);
	printf("\n�������: %d\n", depth(head));

	destory(head);
	return 0;
}
