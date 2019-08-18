#include <stdio.h>
#include <stdlib.h>

// ������, ������, ֱ���� data �������, ֱ�����϶�����
// ��������һ������, ����Ϊ��

#define MIN -0XFFFFFFF
#define MAX 0XFFFFFFF

void node_up_s(int *data, int p)	// �ϵ�С����
{
	int key = data[p];	// ��¼�������

	while (key < data[p / 2])
	{
		data[p] = data[p / 2];
		p /= 2;
	}
	data[p] = key;
}

void node_up_l(int *data, int p)	// �ϵ��󶥶�
{
	int key = data[p];	// ��¼�������

	while (key > data[p / 2])
	{
		data[p] = data[p / 2];
		p /= 2;
	}
	data[p] = key;
}

void node_down_s(int *data, int *len, int p)	// �µ�С����
{
	int lc, rc;
	int key = data[p];

	while (1)
	{
		lc = 2 * p;   rc = lc + 1;
		if (lc > *len) break;
		if (rc > *len)
		{
			// ֻ������
			if (data[lc] < key)
			{
				data[p] = data[lc];
				p = lc;
			}
			else break;		// ���ý�����, Ҫ��ʱ�˳�
		}
		else	// ���Ҷ���
		{
			if (data[lc] < data[rc])
			{
				if (data[lc] < key)
				{
					data[p] = data[lc];
					p = lc;
				}
				else break;
			}
			else 
			{
				if (data[rc] < key)
				{
					data[p] = data[rc];
					p = rc;
				}
				else break;
			}
		}
	}
	data[p] = key;	// �����ǲ��ȥ
}

void node_down_l(int *data, int *len, int p)	// �µ��󶥶�
{
	int lc, rc;
	int key = data[p];

	while (1)
	{
		lc = 2 * p;   rc = lc + 1;
		if (lc > *len) break;
		if (rc > *len)
		{
			if (data[lc] > key)
			{
				data[p] = data[lc];
				p = lc;
			}
			else break;
		}
		else 
		{	// ��С�����෴, �����������ϸ�
			if (data[lc] > data[rc])
			{
				if (data[lc] > key)
				{
					data[p] = data[lc];
					p = lc;
				}
				else break;
			}
			else 
			{
				if (data[rc] > key)
				{
					data[p] = data[rc];
					p = rc;
				}
				else break;
			}
		}
	}
	data[p] = key;	// �����ǲ��ȥ
}

// ���Ѷ�����, ����ɾ���Ѷ�
int pop_del(int *data, int *len, int flag)
{
	int result = data[1];		// ��¼�Ѷ�

	// �����һ��Ԫ��, �ŵ��Ѷ�, Ȼ���ٵ����Ѷ�
	data[1] = data[*len];
	(*len)--;
	if (flag) node_down_l(data, len, 1);	// ���󶥶�����
	else node_down_s(data, len, 1);

	return result;
}

// С����, ��������
// ���ϵ��µİ�СԪ���ϸ�
// ������һ�����������, ���ÿ�������������������ӵ�Ԫ��, 
// ��Ϊ���Ӻ�, data[ĩβ] �ǿ��е�, ����, ֱ�ӷŵ�����漴��
void heap_sort_up(int *data, int n)
{
	int i, len = n;
	for (i=1; i<=n; i++) node_up_s(data, i);
	for (i=n; i>0; i--) data[i] = pop_del(data, &len, 0);
}

// �󶥶�, ��������
void heap_sort_down(int *data, int n)
{
	int i, len = n;
	for (i=1; i<=n; i++) node_up_l(data, i);
	for (i=n; i>0; i--) data[i] = pop_del(data, &len, 1);
}

int main(void)
{
	int i, n;
	int data[100];
	int data2[100];

	data[0] = MIN;   data2[0] = MAX;
	// data[] 0 �ŵ�Ԫ������, �������� [1..n]
	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=1; i<=n; i++)
	{
		scanf("%d", data + i);
//		data[i] = rand() % 100;	// (������)
		data2[i] = data[i];		// �ٸ��ƶ�һ��
	}
	heap_sort_down(data2, n);
	printf("����: ");
	for (i=1; i<=n; i++) printf("%d, ", data2[i]);
	printf("\n\n");

	heap_sort_up(data, n);
	printf("����: ");
	for (i=1; i<=n; i++) printf("%d, ", data[i]);
	printf("\n\n");

	return 0;
}
