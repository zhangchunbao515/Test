#include <stdio.h>
#include <stdlib.h>

// ������, ���ö���ѽ�������

#define SIZE 102	// �Ѵ�С
#define MIN -0XFFFFFFF
#define MAX 0XFFFFFFF

typedef struct		// ����Ѵ���
{
	int *base;
	int lenth;
}heap;

void create(heap *h, int flag)		// ������
{
	h->base = (int *)malloc(SIZE * sizeof(int));
	if (flag) h->base[0] = MAX;
	else h->base[0] = MIN;
	h->lenth = 0;
}

void destory(heap *h)		// ���ٶ�
{
	if (h && h->base) free(h->base);
	h->lenth = 0;
}

void node_up_s(heap *h, int p)	// �ϵ�С����
{
	int key = h->base[p];	// ��¼�������

	while (key < h->base[p / 2])
	{
		h->base[p] = h->base[p / 2];
		p /= 2;
	}
	h->base[p] = key;
}

void node_up_l(heap *h, int p)	// �ϵ��󶥶�
{
	int key = h->base[p];	// ��¼�������

	while (key > h->base[p / 2])
	{
		h->base[p] = h->base[p / 2];
		p /= 2;
	}
	h->base[p] = key;
}

void node_down_s(heap *h, int p)	// �µ�С����
{
	int lc, rc;
	int key = h->base[p];

	while (1)
	{
		lc = 2 * p;   rc = lc + 1;
		if (lc > h->lenth) break;
		if (rc > h->lenth)
		{
			// ֻ������
			if (h->base[lc] < key)
			{
				h->base[p] = h->base[lc];
				p = lc;
			}
			else break;		// ���ý�����, Ҫ��ʱ�˳�
		}
		else	// ���Ҷ���
		{
			if (h->base[lc] < h->base[rc])
			{
				if (h->base[lc] < key)
				{
					h->base[p] = h->base[lc];
					p = lc;
				}
				else break;
			}
			else 
			{
				if (h->base[rc] < key)
				{
					h->base[p] = h->base[rc];
					p = rc;
				}
				else break;
			}
		}
	}
	h->base[p] = key;	// �����ǲ��ȥ
}

void node_down_l(heap *h, int p)	// �µ��󶥶�
{
	int lc, rc;
	int key = h->base[p];

	while (1)
	{
		lc = 2 * p;   rc = lc + 1;
		if (lc > h->lenth) break;
		if (rc > h->lenth)
		{
			if (h->base[lc] > key)
			{
				h->base[p] = h->base[lc];
				p = lc;
			}
			else break;
		}
		else 
		{	// ��С�����෴, �����������ϸ�
			if (h->base[lc] > h->base[rc])
			{
				if (h->base[lc] > key)
				{
					h->base[p] = h->base[lc];
					p = lc;
				}
				else break;
			}
			else 
			{
				if (h->base[rc] > key)
				{
					h->base[p] = h->base[rc];
					p = rc;
				}
				else break;
			}
		}
	}
	h->base[p] = key;	// �����ǲ��ȥ
}

// ���Ѷ�����, ����ɾ���Ѷ�
int pop_del(heap *h, int flag)
{
	int result = h->base[1];		// ��¼�Ѷ�

	// �����һ��Ԫ��, �ŵ��Ѷ�, Ȼ���ٵ����Ѷ�
	h->base[1] = h->base[h->lenth];
	h->lenth--;
	if (flag) node_down_l(h, 1);	// ���󶥶�����
	else node_down_s(h, 1);

	return result;
}

// �����
void insert(heap *h, int data, int flag)
{
	h->lenth++;
	h->base[h->lenth] = data;
	if (flag) node_up_l(h, h->lenth);	// ���󶥶�����
	else node_up_s(h, h->lenth);		// ��С��������
}

// С����, ��������
void heap_sort_up(int *data, int n)
{
	heap h;
	int i;

	create(&h, 0);		// 0 �ǽ���С����
	for (i=0; i<n; i++) insert(&h, data[i], 0);
	for (i=0; i<n; i++) data[i] = pop_del(&h, 0);
	destory(&h);
}

// �󶥶�, ��������, ȫ��Ԫ�ؽ���� (���ȶ���) ��
// ��ȫ�����������������
void heap_sort_down(int *data, int n)
{
	heap h;
	int i;

	create(&h, 1);		// 1 �ǽ����󶥶�
	for (i=0; i<n; i++) insert(&h, data[i], 1);
	for (i=0; i<n; i++) data[i] = pop_del(&h, 1);
	destory(&h);
}

int main(void)
{
	int i, n;
	int data[100];
	int data2[100];

	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		scanf("%d", data + i);
//		data[i] = rand() % 100;	// (������)
		data2[i] = data[i];		// �ٸ��ƶ�һ��
	}
	heap_sort_up(data, n);
	printf("����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	
	heap_sort_down(data2, n);
	printf("����: ");
	for (i=0; i<n; i++) printf("%d, ", data2[i]);
	printf("\n\n");

	return 0;
}
