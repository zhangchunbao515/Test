// ����������ʽ����

typedef int status;
typedef char elemtype;

#define OK 1
#define ERROR 0
#define SIZE 80

// ���������ṹ
typedef struct btnode
{
	elemtype data;
	btnode *lchild;   // ����
	btnode *rchild;   // �Һ���
	btnode *parent;   // ˫��
}btnode;

// ----------������������������-----------
status create(btnode **tree);		// ������
char   *create2(btnode **tree, char *str);	// ������,����str������
status destory(btnode *tree);		// ������
status clear(btnode *tree);			// �����
status empty(btnode *tree);			// �п�
int    depth(btnode *tree);			// ���������
int    leafnum(btnode *tree);		// ��Ҷ����
int    nodenum(btnode *tree);		// ���ؽ�����

// ������û��key�Ľ��, ���ص�ַ
btnode *find(btnode *tree, elemtype *key);
// ����key����ֵ��data
status update(btnode *tree, elemtype *key, elemtype *data);
// ����һ�����ӽ�� rl��ʾ 0�� 1��
status insert(btnode *tree, elemtype *key, elemtype *data, char rl);
// ɾ��һ�����ӽ�� �� ��֦
status remove(btnode *tree, elemtype *key, char rl);
// ����˫�׽���ַ
btnode *parent(btnode *tree, elemtype *data);
// ���ظ�����ַ
btnode *root(btnode *tree);
// ��ʼ��˫��ָ��
status init_parent(btnode *tree);

// ������� (�ݹ�), ִ�� visit ����
status first_tra(btnode *tree, status (*visit)(btnode *node));
// ������� (�ݹ�)
status mid_tra(btnode *tree, status (*visit)(btnode *node));
// ������� (�ݹ�)
status last_tra(btnode *tree, status (*visit)(btnode *node));
// ��α��� (���й���)
status wild_tra(btnode *tree, status (*visit)(btnode *node));
// ������� (�ǵݹ飬ջ)
status first_tra_s(btnode *tree, status (*visit)(btnode *node));
// ������� (�ǵݹ飬 ջ)
status mid_tra_s(btnode *tree, status (*visit)(btnode *node));
// ������� (�ǵݹ飬 ջ)
status last_tra_s(btnode *tree, status (*visit)(btnode *node));
