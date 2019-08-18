#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;

#define OK         1
#define ERROR      0
#define OVERFLOW  -2

typedef struct node
{
	elemtype data;
	node *next;
}node;

// ����������,����ֵ
status createlist(node *p, int num)
{	
	node *newbase = NULL;
	int i;

	// ��ʼ������
	p->next = NULL;

	// ��ʼ�������
	for (i=0; i<num; i++)
	{
		newbase = (node *)malloc(sizeof(node));
		if (newbase)
		{
			newbase->next = p->next;
			p->next = newbase;
			p->data++;
			newbase = NULL;
		}
		else return ERROR;
	}
	return OK;
}

// �ͷŵ�����
status destorylist(node *p)
{
	node *cur;
	node *pos;

	// [head]   [delete]    [3 th] 
	// cur      cur->next   cur->next->next
	while (p->next)
	{
		cur = p;
		pos = cur->next;  // ��ɾ���Ľ��
		cur = pos->next;  // cur->next->next Ҳ��
		p->next = cur;
		free(pos);
	}
	p->data = 0;
	return OK;
}

// �޸ĵ�N���������� 
status update(node *p, int i, elemtype *data)
{
	node *cur;
	int j = 0;

	// i �����Ǹ���
	if (i>=1)
	{
		cur = p;
		// ��� ��һ������ NULL
		// ��û�� i ��
		while (cur->next && j<i)
		{
			cur = cur->next;
			j++;
			// �� j++ ����� i �� j<i �Ͳ�������
		}
		// ���� i ��
		if (j == i)
		{
			cur->data = *data;
			return OK;
		}
		else return ERROR;
	}
	else return ERROR;
}

// ������
status insert(node *p, int i, elemtype *data)
{
	node *newbase;
	node *cur;
	int j = 0;
	
	// [1] -> [2] -> [3]...
	// �� i ��������,��Ҫ�� i-1 ��
	cur = p;
	while (cur->next && j<i-1)
	{
		cur = cur->next;
		j++;
	}
	
	if (j == i-1)
	{
		newbase = (node *)malloc(sizeof(node));
		if (newbase)
		{
			newbase->next = cur->next;
			cur->next = newbase;
			newbase->data = *data;
			return OK;
		}
		else return ERROR;
	}
	else return ERROR;
}

// ɾ��һ�����
status remove(node *p, int i)
{
	node *del;
	node *cur;
	int j = 0;
	
	//��ȥ�� i-1 �Ľ��
	cur = p;
	while (cur->next && j<i-1)
	{
		cur = cur->next;
		j++;
	}
	if (j == i-1)
	{
		del = cur->next;  // ��ɾ���Ľ��
		cur->next = del->next;
		free(del);
		return OK;
	}
	else return ERROR;
}

// ���һ����������
status getnode(node *p, int i, elemtype *back)
{
	node *cur = p;
	int j = 0;

	cur = p;
	while (cur->next && j<i)
	{
		cur = cur->next;
		j++;
	}

	if (j == i)
	{
		*back = cur->data;
		return OK;
	}
	else return ERROR;
}

// �������ĳ���
int listlenth(node *p)
{
	node *cur;
	int i = 0;

	// ������Ϣ�г��ȵĻ�
	// ֱ�� return p->data
	// ��������û�е����
	cur = p;
	while (cur->next) i++;
	return i;
}

void shownode(node *p)
{
	node *cur;
	
	cur = p;
	cur = cur->next;
	while (cur)
	{
		printf("%-4d", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

int main(void)
{
	node list;
	int i;
	int lenth;
	elemtype data;

	printf("�������½�����ĳ��ȣ�");
	scanf("%d", &lenth);
	createlist(&list, lenth);

	for (i=0; i<lenth; i++)
	{
		printf("������� %d �����ݣ�",i+1);
		scanf("%d",&data);
		update(&list, i+1, &data);
	}
	shownode(&list);

	printf("����������[λ��]��[����]:");
	scanf("%d%d", &i, &data);

	if (insert(&list, i, &data) == ERROR) 
		printf("����ʧ�ܣ�\n");
	shownode(&list);

	printf("������ɾ������λ��:");
	scanf("%d", &i);
	if (remove(&list, i) == ERROR)
		printf("ɾ��ʧ�ܣ�\n");
	shownode(&list);

	printf("��������ʽ���λ�ã�");
	scanf("%d", &i);
	if (getnode(&list, i, &data)) printf("����Ϊ��%d\n",data);
	else printf("����ʧ��!\n");

	destorylist(&list);

	return 0;
}