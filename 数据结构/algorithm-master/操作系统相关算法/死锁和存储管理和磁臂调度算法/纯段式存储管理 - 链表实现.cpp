
// ����ʽ�洢�����ʵ�� - ʹ������Ĵ洢����
// �� 512 kB �ռ�����ʵ��, 512 kB = 524288 B
// �ͷſռ�ʱҪ�鿴�����������, ���Բ���˫������ṹ

// ��Ҫ����:
// find_free_memory()		// ���ҿ����ڴ�
// free_memory()			// �ͷ��ڴ�
// collect_memory()			// �ڴ����
// find_free_memory()		// �������
// find_free_memory_bad()	// �������

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FREE  0
#define USING 1
int total_size = 524288;	// 512 KB

// ˫��������
typedef struct node
{
	int add;			// �ռ���ʼ��ַ
	int size;			// �ռ��С
	char flag;			// ����/ռ��λ
	char name[21];		// ����
	node *next;
	node *pre;
}node;
node *head;			// ��ͷ
node *nullnode;		// �ƽ��, �����ж�, �򻯳���

// �����½��
node *new_node(int add, char flag, char *name, int size)
{
	node *n;

	n = (node *)malloc(sizeof(node));
	n->add = add;
	n->flag = flag;
	n->size = size;
	strcpy(n->name, name);
	n->pre = n->next = nullnode;
	return n;
}

// �ڴ����
// ������, ͬʱҪ�޸ĸ��������ʼ��ַ
// �������н��, �����ռ��, ����ʼ��ַ��Ϊ add
// ����ǿ���, ���¿��д�С size, Ȼ���ͷ�
void collect_memory()
{
	node *cur = head;
	node *del;
	int add = 0;		// add ��ʼΪ 0, ��һ������
	int size = 0;
	int f = 1;
	node *pre;

	while (cur != nullnode)
	{
		if (cur->flag == USING)		// ռ�õĽ��
		{
			cur->add = add;
			add += cur->size;
			if (f)		// ��һ��Ҫ����ͷ���
			{
				f = 0;
				head = cur;
				head->pre = nullnode;
				pre = head;
			}
			else	// pre �൱��֯ë�µ���, ������һ�����
			{
				pre->next = cur;
				cur->pre = pre;
				pre = cur;
			}
			del = NULL;
		}
		else	// ���еĽ��, ��¼��С���ͷ�
		{
			size += cur->size;
			del = cur;
		}
		cur = cur->next;
		if (del) free(del);
	}
	pre->next = new_node(add, FREE, "null", size);
	pre->next->pre = pre;
	pre->next->next = nullnode;
}

// Ѱ�ҿ����ڴ�, �����״����䷨
node *find_free_memory(int size, char *name)
{
	node *cur = head;
	node *n;

	while (cur != nullnode)
	{
		if (cur->flag == FREE && size <= cur->size)
		{	// �ҵ�, ���� [cur] -> [n]
			n = new_node(cur->size-size, USING, name, size);
			cur->size -= size;
			cur->next->pre = n;			// �����ж� cur-next �Ƿ��
			n->next = cur->next;		// ���ƽ�����
			cur->next = n;
			n->pre = cur;
			return n;
		}
		cur = cur->next;
	}
	return NULL;
}

// Ѱ�ҿ����ڴ�, ����������䷨
node *find_free_memory_bad(int size, char *name)
{
	node *cur = head;
	int max_size = -1;
	node *pos = NULL;

	while (cur != nullnode)		// �Ҵ�һ�������н��
	{
		if (cur->flag == FREE 
			&& cur->size > max_size 
			&& size <= cur->size)
		{
			max_size = cur->size;
			pos = cur;
		}
		cur = cur->next;
	}
	if (pos)		// ���� [pos] -> [cur]
	{
		cur = new_node(pos->size-size, USING, name, size);
		pos->size -= size;
		pos->next->pre = cur;
		cur->next = pos->next;
		pos->next = cur;
		cur->pre = pos;
		return cur;
	}
	return NULL;
}

// �ϲ��ұߵĽ��
// �ϲ�ǰ [cur] -> [del] -> [x]
// �ϲ��� [cur] -> [x]
// ���� cur ��Ϊ ����
void right_combine(node *cur)
{
	node *del = cur->next;

	cur->size += del->size;
	cur->flag = FREE;
	del->next->pre = cur;
	cur->next = del->next;
	free(del);
}

// �ͷ�һ���ڴ�����, �ͷź�, Ҫ�����ҿ��еĽ��ϲ�
// �������, ���Ҷ���, ������, ������, ���Ҷ�����
int free_memory(char *str)
{
	node *cur = head;
	char left, right;

	while (cur != nullnode)
	{
		if (!strcmp(str, cur->name))
		{
			// �ҵ�, �����ͷ�, �ж����ҽ���״̬, �ǿ���, ����ռ��
			// ����ǿ���, Ҫ����ϲ�, �ƽ�㲻�����
			left = cur->pre->flag;
			right = cur->next->flag;
			switch (left + right * 2)
			{
			case 0 :	// �ϲ�����, ����ϲ�
				// [a] -> [cur] -> [cur->next] -> [b]
				right_combine(cur);			// �ϲ� [cur] �� [cur->next]
				// [a] -> [cur] -> [b]
				cur = cur->pre;				// cur ȥ�� a ��
				// [a] -> [cur->next] -> [b]
				right_combine(cur);			// �ϲ� [a] �� [cur->next]
				// [a] -> [b]
				break;
			case 1 :	// ���Һϲ�, [cur] -> [n] -> [x],  [cur] -> [x]
				right_combine(cur);
				break;
			case 2 :	// ����ϲ�, [a] -> [cur] -> [x],  [a] -> [x]
				cur = cur->pre;
				right_combine(cur);
				break;
			case 3 :	// ����ϲ�
				cur->flag = FREE;
				break;
			}
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

// ͳ�ƿ��ô�С, Ҳ����һ����������, ������, �ͷ�ʱ�޸�
int free_size()
{
	int size = 0;
	node *cur = head;

	while (cur != nullnode)
	{
		if (cur->flag == FREE) size += cur->size;
		cur = cur->next;
	}
	return size;
}

char display();		// ��ʾ
void a();		// �����ڴ�
void b();		// �ͷ��ڴ�
void c();		// �ڴ����
void d();		// �鿴����

int main(void)
{
	// ��ʼ����ͷ, �ƽ��
	nullnode = new_node(0, USING, "null", 0);
	head = new_node(0, FREE, "system", total_size);
	head->next = head->pre = nullnode;
	while (1)
	{
		switch (display())
		{
		case '1' : a();   break;		// �����ڴ�
		case '2' : b();   break;		// �ͷ��ڴ�
		case '3' : c();   break;		// �ڴ����
		case '4' : d();   break;		// �鿴����
		default : return 0;				// �˳�
		}
	}
	node *del;		// �ͷ�����
	while (head != nullnode)
	{
		del = head;
		head = head->next;
		free(del);
	}
	free(nullnode);
	return 0;
}

// ------------------------------------------------------------
// ------------------�����ǹ��ڽ�������ô���------------------
// ------------------------------------------------------------
void back()
{
	printf("\n\n�س�����...\n");
	fflush(stdin);
	getchar();
}

char display()		// ��ʾ
{
	char c;

	system("cls");
	printf("\n 1. �����ڴ�\n");
	printf("\n 2. �ͷ��ڴ�\n");
	printf("\n 3. �ڴ����\n");
	printf("\n 4. �鿴�ڴ�����\n");
	printf("\n---������: ");
	fflush(stdin);
	scanf("%c", &c);

	return c;
}

void a()	// �����ڴ�
{
	int size;
	char buf[21];
	node *n;

	system("cls");
	printf("�ڴ��ܴ�С: %d �ֽ�, ���ô�С: %d �ֽ�\n", 
		total_size, free_size());
	printf("\n�����ڴ�Ĵ�С(�ֽ�): ");
	scanf("%d", &size);
	getchar();
	printf("\n�����ڴ�����ȡ������ (��� 20 ���ַ�): ");
	scanf("%s", buf);
	n = find_free_memory(size, buf);
//	n = find_free_memory_bad(size, buf);
	if (n != NULL) printf("\n����ɹ�");
	else printf("\n����ʧ��, �ɳ����ڴ����");
	back();
}

void b()	// �ͷ��ڴ�
{
	char buf[21];
	node *cur = head;

	system("cls");
	printf("\n������: \n");
	while (cur != nullnode)
	{
		if (cur->flag == USING) printf("%s\n", cur->name);
		cur = cur->next;
	}
	printf("\n������ͷŵı�����: ");
	fflush(stdin);
	scanf("%s", buf);
	if (free_memory(buf)) printf("\n�ɹ��ͷ�");
	else printf("\nδ�ҵ� %s", buf);
	back();
}

void c()	// �ڴ����
{
	system("cls");
	printf("\n�����ڴ����...\n");
	collect_memory();
	printf("\n�������\n");
	back();
}

void d()		// �鿴����
{
	node *cur = head;

	system("cls");
	printf("\n��ʼ��ַ\t�����С\t״̬\t\t����\n\n");
	while (cur != nullnode)
	{
		if (cur->flag == USING)
			printf("%d\t\t%d\t\t%s\t\t%s\n", 
				cur->add, cur->size, "using", cur->name);
		else 
			printf("%d\t\t%d\t\t%s\t\t%s\n", 
				cur->add, cur->size, "free", " ");
		cur = cur->next;
	}
	back();
}
