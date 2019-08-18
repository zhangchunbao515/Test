#include <stdio.h>
#include <stdlib.h>

// ��״���� - ���� + ����

typedef int elemtype;
typedef int status;
#define ERROR 0
#define OK 1
#define SIZE 5		// ÿ������ 5 ��Ԫ��
// �����ܶ� = (SIZE * sizeof(elemtype)) / (sizeof(node));

typedef struct node
{
	elemtype data[SIZE];
	node *next;
}node, array;

void create(array **a, int size)		// ����
{
	int n = size / SIZE + 1;
	node **cur = a;
	
	while (n--)
	{
		*cur = (node *)malloc(sizeof(node));
		cur = &((*cur)->next);
	}
	*cur = NULL;
}

void destory(array *a)		// ����
{
	node *del;
	while (a)
	{
		del = a;
		a = a->next;
		free(del);
	}
}

// �� pos ��, ���� data
status insert(array *a, int pos, int data)
{
	int n = pos / SIZE;
	int p = pos % SIZE;
	// �� n �Ž���, �� p ��λ��
	node *cur = a;

	while (n--) 
	{
		cur = cur->next;
		if (!cur) return ERROR;
	}
	cur->data[p] = data;
	return OK;
}

// ���һ�����
elemtype getelem(array *a, int pos)
{
	int n = pos / SIZE;
	int p = pos % SIZE;
	node *cur = a;

	while (n--)
	{
		cur = cur->next;
		if (!cur) return -0xFFFFFF;
	}
	return cur->data[p];
}

int main(void)
{
	array *arr = NULL;
	int i, n;
	elemtype data;
	
	printf("��������, ���� n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	create(&arr, n);
	for (i=0; i<n; i++)
	{
		scanf("%d", &data);
		insert(arr, i, data);
	}
	printf("\n��������: ");
	for (i=0; i<n; i++)
		printf("%d, ", getelem(arr, i));
	printf("\n");

	destory(arr);
	return 0;
}