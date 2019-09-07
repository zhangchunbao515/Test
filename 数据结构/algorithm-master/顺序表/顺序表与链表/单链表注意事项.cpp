#include <malloc.h>
#include <stdio.h>

typedef int elemtype;
typedef int status;

#define OK     1
#define ERROR  0

typedef struct node
{
	elemtype data;
	node *next;
}node;

status createlist(node *p, int lenth)
{
	node *newbase = NULL;
	int i;

	// ����ǵ�Ҫ��ʼ����
	p->next = NULL;
	for (i=0; i<lenth; i++)
	{
		newbase = (node *)malloc(sizeof(node));
		if (newbase)
		{
			// ֱ�ӽӵ�ͷ������һλ��
			// ���ӵ����һλ��
			newbase->next = p->next;
			p->next = newbase;
			newbase = NULL;
		}
		else return ERROR;
	}
	p->data = lenth;
	return OK;
}

int main(void)
{
	node list;
	int lenth;
	int i;
	node *cur, *del;

	scanf("%d", &lenth);

	// ����������ֿ���
	createlist(&list, lenth);
	
	// updata
	cur = list.next;
	while (cur)
	{
		scanf("%d", &cur->data);
		cur = cur->next;
	}
prv:
	// showlist
	cur = list.next;
	while (cur)
	{
		printf("%4d", cur->data);
		cur = cur->next;
	}
	printf("\n");

	// ɾ����n�����
	scanf("%d", &i);
	if (i>=1 && i<=list.data)
	{
		cur = &list;
		//  [prv] -> [del] -> [next]
		// ɾ�� [del],  ��ȥ�� prv,
		// ɾ���� i � ��ȥ�� i-1 ��

		i--;
		while (i--) cur = cur->next;
		del = cur->next;
		cur->next = del->next;
		free(del);
		list.data--;
	}

	goto prv;
	
	return 0;
}