#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;
typedef int keytype;	// �ؼ�������

#define ERROR 0
#define OK 1

typedef struct
{
	elemtype *base;
	int lenth;
}table;

status init(table *t)
{
	// ���� 0 �ŵ�Ԫ���ڱ�
	t->lenth = 1;
	t->base = (elemtype *)malloc(sizeof(elemtype));
	if (!t->base) return ERROR;
	return OK;
}

// ��ĩβ׷��һ������
status append(table *t, elemtype *data)
{
	elemtype *n;

	if (!t || !t->base || !t->lenth) return ERROR;
	
	t->lenth += 1;
	n = (elemtype *)realloc(t->base, t->lenth * sizeof(elemtype));
	if (!n) return ERROR;
	t->base = n;
	t->base[t->lenth - 1] = *data;
	
	return OK;
}

void show(table *t)
{
	int i;
	if (t && t->base)
		for (i=1; i<t->lenth; i++)
			printf("%d, ", t->base[i]);
}

// ˳����Һ���
// ����ҵ����ظ�Ԫ��λ��, �Ҳ������� 0 
int search(table *t, elemtype *data)
{
	int i;

	if (!t || !t->base) return 0;
	// �����ڱ�
	t->base[0] = *data;
	for (i=t->lenth-1; i>=0; i--)
		if (t->base[i] == *data) return i;
	return 0;
}

int main(void)
{
	table t;
	keytype tmp;
	int pos;

	init(&t);
	printf("�����뾲̬���ұ�: ");
	while (scanf("%d", &tmp) != 0)
		append(&t, &tmp);

	show(&t);
	printf("\n�����������Ԫ�أ�");
	fflush(stdin);
	scanf("%d", &tmp);
	pos = search(&t, &tmp);		// ˳����Һ���
	if (pos) 
		printf("�ҵ���λ�ã�%d�� ���ݣ�%d\n", pos, t.base[pos]);
	else printf("δ�ҵ�\n");

	return 0;
}