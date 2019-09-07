#include <stdio.h>
#include <malloc.h>

#define NOT_FOUND -1
#define OK 1
#define ERROR 0
#define SIZE 30
typedef int status;


// �ؼ��ֽ��ṹ
typedef struct
{
	int key;
	char *info;
}keytype;

// keytype ˳���
typedef struct
{
	keytype *elem;
	int lenth;
	int size;
}table;

status create(table *t)
{
	t->lenth = 0;
	t->size = SIZE;
	t->elem = (keytype *)malloc(SIZE * sizeof(keytype));
	if (!t->elem) return ERROR;
	return OK;
}

status destory(table *t)
{
	if (t) free(t->elem);
	t->elem = NULL;
	t->lenth = t->size = 0;
	return OK;
}

status append(table *t, keytype *data)
{
	// ׷�ӿռ䲻���ص㣬���Բ�׷����
	if (t->lenth == t->size) return ERROR;

	t->elem[t->lenth].key = data->key;
	t->lenth++;
	return OK;
}

void show(table *t)
{
	int i;
	if (t)
		for (i=0; i<t->lenth; i++)
			printf("%d, ", t->elem[i].key);
}

// ���ֲ��Һ���, flag == 1 ����flag == 0 ����
status bin_search(table *t, keytype *data, short int flag)
{
	int left = 0;
	int right = t->lenth - 1;
	int mid;

	if (flag)   // ��������
	{
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (t->elem[mid].key == data->key)
				return mid;
			if (t->elem[mid].key < data->key)
				left = mid + 1;
			if (t->elem[mid].key > data->key)
				right = mid - 1;
		}
	}
	else    // ��������
	{
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (t->elem[mid].key == data->key)
				return mid;
			if (t->elem[mid].key < data->key)
				right = mid - 1;
			if (t->elem[mid].key > data->key)
				left = mid + 1;
		}
	}
	return NOT_FOUND;
}

int main(void)
{
	table t;
	keytype tmp;
	int pos;

	create(&t);
	printf("�밴��������ؼ��֣�");
	while (scanf("%d", &tmp.key))
		append(&t, &tmp);
	show(&t);
pre:
	printf("\n����������ҵ�Ԫ��: ");
	fflush(stdin);
	scanf("%d", &tmp.key);
	pos = bin_search(&t, &tmp, 1);		// ���ֲ��Һ���
	if (pos != NOT_FOUND)
		printf("�ҵ���λ��%d, �ؼ��֣�%d\n", pos+1, tmp.key);
	else printf("δ�ҵ�\n");
	goto pre;
	destory(&t);

	return 0;
}