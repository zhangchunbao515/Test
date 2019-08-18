
// ���� A ����һ������, ���� B ����һ������, ���е�����
// ��������е�Ԫ�ز�������, ������ȡ"��Ϣָ��", �������ֻ�
// ����, ������ַ����ļ��Ͽ��Խ����ϣ��һ������, �ٴ����ϣ��

// �ⷨ1: ������ A �����ϣ��, ���� B ��ÿ��Ԫ�ؽ���ÿ��Ͱ�н��бȶ�
// �ⷨ2: ���ݷ�Χ�� 1000 ��, ���� map[] ���

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	int data;
	node *next;
}node;

node *table[10];		// ��ϣ��

inline int hash(int data)		// ��ϣ����
{
	return data % 10;
}

void insert(int data)
{
	int add = hash(data);
	node *cur = (node *)malloc(sizeof(node));
	
	cur->data = data;
	cur->next = table[add];
	table[add] = cur;
}

int main(void)
{
	int a[100];
	int b[100];
	int i, add;
	node *tmp;

	// ��ʼ����ϣ��
	for (i=0; i<10; i++) table[i] = NULL;

	// ��ʼ������
	srand(time(NULL));
	for (i=0; i<100; i++)
	{
		a[i] = rand() % 1000;
		b[i] = rand() % 1000;
	}
	printf("\nA ��Ԫ��: ");
	for (i=0; i<100; i++) printf("%d, ", a[i]);
	printf("\nB ��Ԫ��: ");
	for (i=0; i<100; i++) printf("%d, ", b[i]);
	printf("\n\n��ͬ��Ԫ��: ");
	for (i=0; i<100; i++)		// �� a �����ϣ��
		insert(a[i]);
	for (i=0; i<100; i++)		// ���� b �����ж�
	{
		add = hash(b[i]);
		tmp = table[add];
		while (tmp != NULL)
		{
			if (tmp->data == b[i])
			{
				printf("%d, ", b[i]);
				break;
			}
			else tmp = tmp->next;
		}
	}
	putchar('\n');
	for (i=0; i<10; i++)		// ���ٹ�ϣ��
	{
		while (table[i] != NULL)
		{
			tmp = table[i];
			table[i] = table[i]->next;
			free(tmp);
		}
	}
	return 0;
}
