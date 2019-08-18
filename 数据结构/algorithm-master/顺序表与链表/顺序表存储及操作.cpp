#include <stdio.h>
#include <stdlib.h>

typedef int status;
typedef int ElemType;

#define OK         1
#define ERROR      0
#define OVERFLOW  -2
#define SIZE      50  // ԭ��С
#define INS       10  // ����

typedef struct
{
	ElemType *elem;
	int length;
	int size;
}sqlist;

// elemָ��һ��ռ䣬��������Ҫ������
// *p.elem �Ϳ���ȡ���ҵ�����

status init_sq(sqlist *p)  // ����sqlist��
{
	p->elem = (ElemType *)malloc(SIZE * sizeof(ElemType));
	// ��100���洢�ռ�
	if (p)
	{
		p->length = 0;
		p->size = SIZE;
		return OK;
	}
	else return ERROR;
}

status destory_sq(sqlist *p)  // ����
{
	if (p->size)
	{
		free(p->elem);
		//���ܰ� p ���ͷŵ��ˣ�p��auto�ͣ��ɱ������ͷ�
		// p->elem ���ǿ����ͷŵ�
		return OK;
	}
	else return ERROR;
}

// ��������
status listinsert(sqlist *p, int i, ElemType data)
{
	ElemType *newbase;
	ElemType *pos;
	ElemType *cur;

	// i ��λ���Ƿ���ȷ
	if (i>=0 && i<=(p->length))
	{
		// ���ǲ�������
		if (p->length == p->size)
		{
			newbase = (ElemType *)realloc(p->elem, (p->size + INS)*sizeof(ElemType));
			if (newbase)
			{
				p->elem = newbase;
				p->size += INS;
			}
			else return OVERFLOW;
		}
		// ��ʼ����
		pos = p->elem + i; // �������λ��
		for (cur = p->elem + p->length; cur>=pos; cur--)
		{
			// cur ָ�� p.elem[length] ���һ��Ԫ�صĵ�ַ
			// *cur ����ȡp.elem[length] ָ��һ��ռ������
			*(cur+1) = *cur;
		}
		*pos = data;
		p->length++;
		return OK;
	}
	else return ERROR;
}


// ɾ������
status listdelete(sqlist *p, int i)
{
	ElemType *pos;
	ElemType *cur;
	ElemType *end;

	if (i>=0 && i<(p->length))
	{
		// a[i]  []��Ѱַ+ȡֵ������
		// �� *(a + i) Ҳ�ǿ��Ե�
		pos = &(p->elem[i]);  // ��ɾ��������
		end = p->elem + p->length;   // β��ַ
		for (cur=pos; cur<=end; cur++)
		{
			*cur = *(cur+1);
		}
		p->length--;
		return OK;
	}
	else return ERROR;
}


// ��ձ�
status listclear(sqlist *p)
{
	ElemType *cur;
	ElemType *end;

	if (p->length > 0)
	{
		end = p->elem + p->length;
		for (cur=p->elem; cur<end; cur++)
		{
			*cur = 0;
		}
		return OK;
	}
	else return ERROR;
}

sqlist *show(sqlist *p)  // ������������Ԫ�أ�
{
	ElemType *cur;
	ElemType *end;
	int i = 0;

	printf("����Ԫ�أ�");
	end = p->elem + p->length;
	for (cur=p->elem; cur<end; cur++)
	{
		if (i%15 == 0) printf("\n");
		i++;
		printf("%4d", *cur);
	}
	printf("\n");

	return p;
}

// ��õ� i ��Ԫ�ص�ֵ
status getelem(sqlist *p, int i, ElemType *back)
{
	if (i>=0 && i<=(p->length))
	{
		*back = *(p->elem + i);
		return OK;
	}
	else return ERROR;
}

// ��ñ�
status listlength(sqlist *p)
{
	return p->length;
}

int main(void)
{
	sqlist list;
	int i;
	ElemType data;

	init_sq(&list);
	for (i=0; i<10; i++)
	{
		listinsert(&list, i, i);
	}		
	show(&list);
	printf("�� %d\n", listlength(&list));

	printf("������Ҫ�������ݣ���λ�ã�");
	scanf("%d %d", &data, &i);
	if (listinsert(&list, i-1, data)) printf("����ɹ�!\n\n");
	else printf("����ʧ��!\n\n");
	show(&list);

	printf("������Ҫɾ�����ݵ�λ�ã�");
	scanf("%d",&i);
	if (listdelete(&list, i-1)) printf("ɾ���ɹ�!\n\n");
	else printf("ɾ��ʧ��!\n\n");
	show(&list);

	printf("�������Ԫ�ص�λ�ã�");
	scanf("%d",&i);
	if (getelem(&list, i-1, &data)) 
	{
		printf("�ҵ�����Ԫ��Ϊ %d\n", data);
	}
	else printf("û���ҵ���\n");

	printf("\n��������Ϊ 0\n");
	if (listclear(&list)) printf("���óɹ���\n");
	else printf("����ʧ��!\n");
	show(&list);

	destory_sq(&list);

	return 0;
}
