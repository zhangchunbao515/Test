/* ---------------------------------
// ���ĵȼ����� - ���鼯
// ��Ҫ����: 
// init()		ÿ���˶����ϴ�
// find_set()	�������ϴ���˭
// merge()		�ϲ���������
// ʵ�ֲ����ϴ���������
// find_set()    �ݹ�ѹ��
// find_set_s()  �ǵݹ�, ����ջ
// find_set_y()  �ǵݹ�, ���Ӷ���С
-----------------------------------*/

#include <stdio.h>
#include <malloc.h>

typedef char elemtype;
#define SIZE 10		// �̶���С

// ������˫�׷���ʾ
typedef struct
{
	int parent;		// ָ��˫��
	int depth;		// ���
	elemtype data;
}node;

// �̶���СΪ 10
typedef struct
{
	node table[SIZE];
//	int cur;   ���Լ�һ����ʾʹ����
}forest;

forest f;		// ����һ��ȫ�ֵ�ɭ��, ��Ϊ�������Ҫ�õ�

// ��ʼ�����, ÿ����㶼�Ǹ�, û��˫��
// ��: ÿ������Լ���һ����, ����һ������
// ˫�ױ�ʾ���� -1 ��ʾû��˫��
// Ҳ��ָ���Լ� (x.parent == x) ��ʾû��˫��
void init(forest *t)
{
	int i;

	// �� {A}{B}{C}{D}{E}{F}{G}{H}{J}{I} ��ô����
	for (i=0; i<SIZE; i++)
	{
		t->table[i].data = 'A' + i;
		t->table[i].parent = i;
		t->table[i].depth = 0;
	}
}

// ���Ҽ��ϵ�ʱ��, ˳��ݹ�ѹ��·��
// ��� addr��parent == addr �򷵻� addr
// ���� �ѵ�ǰ����˫�� ��Ϊ ˫�����ڵĸ�
// �ݹ����ɿ��� 
// temp = find_set(...parent);
// parent = temp   �������ڻ���ʱ, �޸�˫�׵�
int find_set(int addr)
{
	if (f.table[addr].parent != addr)
	{
		f.table[addr].parent = find_set( f.table[addr].parent );
		f.table[addr].depth = 1;	// ѹ�������Ҳ����
	}
	return f.table[addr].parent;
	// ���ﲻ�ܷ���addr, ��Ϊ addr û�б��޸�
}

// �ǵݹ�ѹ��·��
// Ҳ�����Լ���ջ��¼, ���ڴ�������Ӧ���÷ǵݹ��
int find_set_s(int addr)
{
	int stack[11];		// �����ռ� 11
	int top = 0;
	int tmp;

	while (f.table[addr].parent != addr)
	{
		stack[top++] = addr;
		addr = f.table[addr].parent;	// ���� p = p->next;
	}
	while (top)		// ȫ����ջ, ѹ��·��
	{
		tmp = stack[--top];
		f.table[tmp].parent = addr;  // ֱ�����ӵ����ڵ���
		f.table[tmp].depth = 1;
	}
	return addr;
}

// �ǵݹ�ѹ��·��, ���㷨�ռ临�Ӷȸ���
int find_set_y(const int addr)
{
	int i = addr;
	int tmp = addr;

	while (f.table[i].parent != i)	
		i = f.table[i].parent;

	// ��ʱ i �Ǹ���, ��ѹ��һ��·��
	while (f.table[tmp].parent != i)
	{
		f.table[tmp].parent = i;
		f.table[tmp].depth = 1;
	}
	return i;
}

// �ϲ� {a}, {b} ��������
void merge(int a, int b)
{
	int a_root, b_root;

	a_root = find_set_y(a);		// �������ڵĸ�
	b_root = find_set_y(b);		// find_set_s() Ҳ����ͨ��
	
	if (a_root != b_root)		// ��� a, b ����ͬһ������
	{
		// a �����������С, ʹ�������С
		if (f.table[a].depth < f.table[b].depth)
		{
			f.table[a_root].parent = b_root;   // ��a�ĸ�����ȥ
		}
		else if (f.table[a].depth > f.table[b].depth)
		{
			f.table[b_root].parent = a_root;
		}
		else 
		{
			f.table[b_root].parent = a_root;
			f.table[a_root].depth++;
		}
	}
}

void show_root(forest *f)		// �鿴˫�׽��
{
	int i;
	printf("�����: ");
	for (i=0; i<10; i++)
		printf("%d, ", find_set_y(i));
	printf("\n");
}

int main(void)
{
	int i;

	init(&f);	// ��ʼ��ɭ��

	// һ��ʼ�� {A}{B}{C}{D}{E}{F}{G}{H}{J}{I} ��ô�༯��
	show_root(&f);
	
	// �����ϲ��� {A,B} {C,D} {E,F} {G,H} {J,I}
	for (i=0; i<10; i+=2) merge(i, i + 1);
	show_root(&f);

	// �����ϲ� {A,B,C,D} {E,F,G,H} {J,I}
	merge(0, 2);   merge(4, 6);
	show_root(&f);

	// �����ϲ� {A,B,C,D,E,F,G,H,J,I} һ��������
	merge(3, 7);   merge(7, 9);
	show_root(&f);

	return 0;
}
