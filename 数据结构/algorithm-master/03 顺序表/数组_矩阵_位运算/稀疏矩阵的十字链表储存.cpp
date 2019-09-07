#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;

#define OK 1
#define ERROR 0

int size;   // ͳ��ѹ����Ĵ�С

// ʮ��������
typedef struct node
{
	int x, y;		// ��¼����
	elemtype data;	// ֵ
	node *right;
	node *down;
}node;

// ����ר�õĽ�㣬ʡ�ռ�
typedef struct hnode
{
	node *first;	// ָ������Ľ��
}hnode;

// ͷ�ṹ
typedef struct head
{
	hnode **row;   // ��̬������
	hnode **col;   // ��̬������
	int r, c, all;   // �������������������
}head;

// ��ʼ��ʮ������
status create(head *p, int x, int y)
{
	int i;

	if (!p) return ERROR;
	
	// ��ʼ�����У��е�ָ������
	p->row = (hnode **)malloc(x * sizeof(hnode));
	if (!p->row) return ERROR;
	p->col = (hnode **)malloc(y * sizeof(hnode));
	if (!p->col) return ERROR;
	p->r = x;
	p->c = y;

	// ��ʼ���У���ָ�����ռ�, ����ʼ��
	for (i=0; i<x; i++)
	{
		p->row[i] = (hnode *)malloc(sizeof(node));
		if (!p->col[i]) return ERROR;
		p->row[i]->first = NULL;
	}
	for (i=0; i<y; i++)
	{
		p->col[i] = (hnode *)malloc(sizeof(node));
		if (!p->col[i]) return ERROR;
		p->col[i]->first = NULL;
	}
	p->all = 0;

	size += (x + y) * (sizeof(hnode) + sizeof(node));
	return OK;
}

// �ͷ�ʮ������
status destory(head *p, int x, int y)
{
	int i;
	node *cur;

	// �ͷ�ȫ�����
	for (i=0; i<x; i++)
	{
		cur = p->row[i]->first;
		while (cur)
		{
			p->row[i]->first = cur->right;
			free(cur);
			cur = p->row[i]->first;
		}
	}
	// �ͷ�����ָ������
	if (!p->col) free(p->col);
	if (!p->row) free(p->row);
	
	return OK;
}

// ������������ֵ��
status swap(node *a, node *b)
{
	node temp;

	temp.data = a->data;
	temp.x = a->x;
	temp.y = a->y;
	a->data = b->data;
	a->x = b->x;
	a->y = b->y;
	b->data = temp.data;
	b->x = temp.x;
	b->y = temp.y;
	return OK;
}

// �� map ѹ����ʮ������ p ��
status encode(head *p, int map[][7], int x, int y)
{
	int i, j;
	hnode *hang;
	hnode *lie;
	node *cur;
	node *n;

	if (!(p->col && p->row)) return ERROR;
	for (i=0; i<x; i++)
	{
		for (j=0; j<y; j++)
		{
			if (map[i][j])
			{
				n = (node *)malloc(sizeof(node));
				if (!n) return ERROR;
				size += sizeof(node);
				n->x = i;
				n->y = j;
				n->data = map[i][j];
				n->right = n->down = NULL;

				// ����ʮ������
				// Ѱ����, �ǾͱȽ��еĴ�С
				hang = p->row[i];
				cur = hang->first;
				if (!cur) hang->first = n;
				else 
				{
					while (cur->right)
					{
						if (j >= cur->y)
							break;
						cur = cur->right;
					}
					n->right = cur->right;
					cur->right = n;
					swap(cur, n);	// ���ں��棬������ֵ
				}
	
				// Ѱ���У��ǾͱȽ��еĴ�С
				lie = p->col[j];
				cur = lie->first;
				if (!cur) lie->first = n;
				else 
				{
					while (cur->down)
					{
						if (i >= cur->x)
							break;
						cur = cur->down;
					}
					n->down = cur->down;
					cur->down = n;
					swap(cur, n);
				}
				p->all++;
			}
		}
	}
	return OK;
}

// ��ʮ������ԭ�� map ��
status decode(head *p, int map[][7], int x, int y)
{
	node *cur;
	int i;

	if (!(p->col && p->row)) return ERROR;

	// ��ʵ��ԭ���Ǳ���ʮ������
	for (i=0; i<p->r; i++)
	{
		cur = p->row[i]->first;
		while (cur)
		{
			map[ cur->x ][ cur->y ] = cur->data;
			cur = cur->right;
		}
	}
	return OK;
}

void show(int m[][7])
{
	int i, j;

	for (i=0; i<6; i++)
	{
		for (j=0; j<7; j++)
			printf("%4d", m[i][j]);
		printf("\n");
	}
}

int main(void)
{
	int map[6][7] = 
	{
		0, 12, 39,  0, 0,  0,  0,
		0,  0,  0,  0, 0,  0,  0,
		11, 0,  0,  0, 0, 14,  0,
		0,  0, 24,  0, 0,  0,  0,
		0, 18,  0,  0, 0,  0,  0,
		15, 0,  0, 15, 0,  0,  0,
	};				// �ֹ�����
	head list;
	int buf[6][7] = {0};
	int resize;

	size = 0;
	resize = sizeof(map);
	printf("ԭ����\n");
	show(map);
	printf("\nʮ������ѹ����ԭ��\n\n");
	create(&list, 6, 7);

	encode(&list, map, 6, 7);   // map ѹ���� list ��
	decode(&list, buf, 6, 7);   // list ��ԭ�� buf ��
	show(buf);
	printf("\nԭ��С��%d �ֽ�, ѹ�����С��%d �ֽ�\nѹ���ʣ�%.2f%%\n",
		resize, size, 100*(size / (float)resize));
	destory(&list, 6, 7);

	// ���ԽѹԽ����Ϊ����ֵ��̫С(��4���ֽ�)
	// ��߽���ֵ����Դﵽѹ����Ч��
	// ��ʮ�������ʺ�ֵ��ϴ������ѹ������

	return 0;
}
