
// ��ϣ�� - PASCAL�ؼ���
// ��������ַ��, �����ͻ

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef char keytype;	// ���÷���ֵ����
typedef int status;
#define OK 1
#define ERROR 0
#define FOUND -1
#define R 13		// ȡ������, ���Ե���һ��

typedef struct node		// ���ṹ
{
	keytype *str;	// �ַ�����ַ
	node *next;
}node;

typedef struct		// ��ϣ��ṹ
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
			if (del->str) free(del->str);
			free(del);
		}
	}
}

// ��λ�ַ� ASCLL �����,�ٶ� R ȡ��, �õ� hash ֵ
int hash(keytype *data)
{
	return (data[0] + data[strlen(data)-1]) % R;
}

// ����һ���ؼ���
status search(hashtable *t, keytype *data, int *pos)
{
	node *cur;
	
	*pos = hash(data);		// ���� hash ֵ
	cur = t->base[*pos];
	while (cur)			// ���Ʊ����ڽӵ�
	{
		if (cur->str && !strcmp(data, cur->str)) 
			return OK;
		cur = cur->next;
	}
	return ERROR;
}

// ����һ���ؼ���
status insert(hashtable *t, keytype *data)
{
	int len = strlen(data);
	int add;
	node *n;

	if (search(t, data, &add)) return ERROR;
	n = (node *)malloc(sizeof(node));
	n->str = (keytype *)malloc((len + 1) * sizeof(keytype));
	strcpy(n->str, data);

	n->next = t->base[add];		// �����½��, ������
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
			printf(" -> [%s]", cur->str);
			cur = cur->next;
		}
		printf("\n");
	}
}

int main(void)
{
	hashtable table;
	keytype data[50];

	create(&table);
	while (1)		// �������
	{
		printf("������Ҫ���ҵ�Ԫ��: ");
		scanf("%s", &data);
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
/* 
// ��������, ���� PASCAL ���Թؼ���, 
// �� C ����Ҳ�ǿ��Ե�, ���ַ�������
and

array

as

or

asm

begin

end

for

while

case

cdecl

const

dynamic

if

else

*/