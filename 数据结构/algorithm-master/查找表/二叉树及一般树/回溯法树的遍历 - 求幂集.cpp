#include <stdio.h>
#include <stdlib.h>

// ���ݷ�, ����״̬��, �� n ��Ԫ�ص��ݼ�

typedef int status;
typedef char elemtype;
#define ERROR 0
#define OK 1

typedef struct		// ˳����ʾ����
{
	elemtype *base;
	int lenth;
	int size;
}sqlist;

status create(sqlist *list)
{
	list->base = (elemtype *)malloc(20 * sizeof(elemtype));
	if (!list->base) return ERROR;
	list->lenth = 0;
	list->size = 20;
	return 1;
}

status insert(sqlist *list, int pos, elemtype *data)
{
	elemtype *n;
	elemtype *end;
	elemtype *st;
	elemtype *cur;

	if (pos > list->lenth + 1) return ERROR;
	if (list->lenth == list->size)
	{
		n = (elemtype *)realloc(list->base, 
			(10 + list->size) * sizeof(elemtype));
		if (!n) return ERROR;
		list->base = n;
		list->size += 10;
	}
	end = list->base + list->lenth - 1;
	st = list->base + pos - 1;
	for (cur=end; cur>=st; cur--)
		*(cur + 1) = *cur;		// ���Ϻ���
	*st = *data;
	list->lenth++;
	return OK;
}

status del(sqlist *list, int pos)
{
	elemtype *end;
	elemtype *st;
	elemtype *cur;

	if (pos > list->lenth) return ERROR;
	end = list->base + list->lenth - 1;
	st = list->base + pos - 1;
	for (cur=st; cur<=end; cur++)
		*cur = *(cur + 1);		// ����ǰ��
	list->lenth--;
	return OK;
}

void destory(sqlist *list)
{
	if (list->base) free(list->base);
	list->base = NULL;
	list->lenth = 0;
	list->size = 0;
}

void show(sqlist *list)
{
	int i;

	if (list->lenth == 0) printf("{@}\n");   // �ռ��ı�ʾ
	else 
	{
		printf("{");
		for (i=0; i<list->lenth; i++)
		{
			printf("%c", list->base[i]);
			if (i+1 != list->lenth) printf(", ");
		}
		printf("}\n");
	}
}

void input(sqlist *list)
{
	int n, i;
	char ch;

	scanf("%d", &n);
	fflush(stdin);
	for (i=0; i<n; i++)
	{
		scanf("%c", &ch);
		insert(list, i+1, &ch);
	}
	fflush(stdin);
}

// ���ݼ��ĵݹ鲿��, i ��ʾ���
int set_s(sqlist *list, sqlist *b, int i)
{
	int num = 0;
	char ch;
	int len;

	if (i > list->lenth)	// ��������ײ�,�ҵ���
	{
		show(b);
		return 1;
	}
	ch = list->base[i - 1];   // ���һ��Ԫ��
	len = b->lenth + 1;		// ��ò����λ��

	// ���ƶ������ı���
	insert(b, len, &ch);	// ���� b ��
	num += set_s(list, b, i + 1);

	// ����ʱ, ɾȥch, ͬʱ�ֲ����µĵݹ�
	del(b, len);			// ������ b ��
	num += set_s(list, b, i + 1);

	return num;
}

// �������Ϊ n �� n ����
// Ҷ�ӽ�������ǽ�, 
int set(sqlist *list)
{
	sqlist tmp;	// ��ʱ����
	int num;

	create(&tmp);
	num = set_s(list, &tmp, 1);
	destory(&tmp);
	return num;
}


int main(void)
{
	sqlist list;
	sqlist b;
	int num;

	create(&list);   create(&b);
	printf("�������ַ�����: ");
	// ���뷽ʽ: ��ͷһ�� n, ��� n ���ַ���
	input(&list);
//	show(&list);

	num = set(&list);	// �� list ���ݼ�
	printf("\nlist ���ݼ��� %d ��\n", num);

	destory(&list);
	return 0;
}
