// ѭ����������
#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;

#define OK 1
#define ERROR 0

typedef struct node
{
	elemtype data;
	node *next;
}node;  

status create(node *p, int num)
{
	node *n;

	p->next = p;
	num--;
	while (num--)
	{
		n = (node *)malloc(sizeof(node));
		if (!n) return ERROR;
		n->next = p->next;
		p->next = n;
	}
	return OK;
}

status input(node *p)
{
	node *cur;

	printf("Enter num:");
	scanf("%d", &p->data);
	cur = p->next;
	while (cur != p)
	{
		printf("Enter num:");
		scanf("%d", &cur->data);
		cur = cur->next;
	}
	return OK;
}

void sort(node *p)
{
	node *cur;
	int flag;
	elemtype t;

	while (1)
	{
		// ��һȦ��ð��
		flag = 1;
		cur = p;
		while (cur->next != p)
		{
			if (cur->data > cur->next->data)
			{
				t = cur->data;
				cur->data = cur->next->data;
				cur->next->data = t;
				flag = 0;
			}
			cur = cur->next;
		}
		if (flag) break; 
	}
}

void show(node *p)
{
	node *cur; 
	cur = p;
	
	while (cur->next != p)
	{
		printf("%d, ", cur->data);
		cur = cur->next;
	}
	printf("%d\n", cur->data);
}

// ������Զ�����
status insert(node *p, elemtype *data)
{
	node *cur;
	node *n;
	elemtype t;
	
	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->data = *data;
	cur = p;
	// �����ͷ��㻹С
	// �Ͳ���ͷ����λ��
	if (*data < cur->data && cur == p)
	{
		n->next = cur->next;
		cur->next = n;
		// [p] -> [n]
		// n ����Ӧ�ò��� p ��ǰ��
		// ���� p ��ͷ��㣬Ҫ��һ����Ȧ������p���� O(n)
		// ���ԣ��Ȳ��� P ���棬
		// Ȼ������������ O(1)
		t = p->data;
		p->data = n->data;
		n->data = t;
	}
	else
	{
		// 1 2 3  data == 10
		// �ܵ����û���ֱ��Ҵ�ģ�
		// �ͻ���ѭ��, ���ԣ�ֻ��һȦ
		while (*data > cur->data && cur->next!=p) cur = cur->next;
		// ���� cur ��
		n->next = cur->next;
		cur->next = n;
	}
	return OK;
}

int main(void)
{ 
	node list;
	int times = 5;
	elemtype data;
  
	// ����ͷ��
 	create(&list, 10);
	input(&list);
	show(&list);
	sort(&list);
	show(&list);
	while (times--)
	{
		scanf("%d", &data);
		insert(&list, &data);
		show(&list);
	}

	return 0;
}
