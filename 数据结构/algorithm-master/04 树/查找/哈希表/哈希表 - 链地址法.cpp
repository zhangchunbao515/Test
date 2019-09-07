
// ��ϣ������ͻ = ����ַ��

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int status;
typedef int keytype;
#define OK 1
#define ERROR 0
#define FOUND -1
#define R 11		// ȡ������

// ����ַ���Ĺ�ϣ��Ľṹ�����ڽӱ�
// ���ṹ  [data | next]
typedef struct node
{
	keytype data;
	node *next;
}node;

typedef struct	// ͷ�ṹ [�±�][first]
{
	node *base[R];
}hashtable;

status create(hashtable *t)		// ������ϣ��
{
	int i;
	if (!t) return ERROR;
	for (i=0; i<R; i++) t->base[i] = NULL;
	return OK;
}

void destory(hashtable *t)		// ���ٹ�ϣ��
{
	int i;
	node *del;

	if (!t) return ;
	for (i=0; i<R; i++)
	{
		while (t->base[i])
		{
			del = t->base[i];
			t->base[i] = del->next;
			free(del);
		}
	}
}

int hash(keytype n)		// ��ϣ���������й���
{ return n % R; }

// ����һ��Ԫ��
int search(hashtable *t, keytype data)
{
	int add;
	node *cur;

	add = hash(data);		// �� data �Ĺ�ϣֵ
	cur = t->base[add];
	while (cur)
	{
		if (cur->data == data) return FOUND;
		cur = cur->next;
	}
	return add;
}

status insert(hashtable *t, keytype data)
{
	node *n;
	int add;

	add = search(t, data);

	if (add == FOUND) return ERROR;	// ������
	
	n = (node *)malloc(sizeof(node));
	n->data = data;
	// �������, �嵽����
	n->next = t->base[add];
	t->base[add] = n;
	return OK;
}

float ASL(hashtable *t)
{
	node *cur;
	int len = 0, num = 0, i, c;

	for (i=0; i<R; i++)
	{
		cur = t->base[i];
		c = 0;		// c �ǲ��Ҵ���
		while (cur)
		{
			c++;   num++;   len += c;
			cur = cur->next;
		}
	}
	return (float)len / num;
}

void show(hashtable *t)
{
	int i;
	node *cur;
	for (i=0; i<R; i++)
	{
		printf("[%d]", i);
		cur = t->base[i];
		while (cur)
		{
			printf(" -> [%d]", cur->data);
			cur = cur->next;
		}
		printf("\n");
	}
}

int main(void)
{
	hashtable table;
	keytype data;

	create(&table);
	while (1)		// �������
	{
		printf("������Ҫ���ҵ�Ԫ��: ");
		scanf("%d", &data);

		if (insert(&table, data))	// ����
			printf("\n��Ԫ�ز�����, �Ѳ���!");
		else printf("\n���ҵ�!");

		printf("\n\n��ϣ��: \n");   show(&table);
		printf("\nASL = %.3f", ASL(&table));
		printf("\n\n�� c �˳�, ���س�����...\n");
		getchar();
		if (getch() == 'c') break;
		system("cls");
	}
	destory(&table);
	return 0;
}
