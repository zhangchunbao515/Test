// ���˳������غ���
#include <stdio.h>
#include "sqlist.h"
#include <malloc.h>

void init(sqlist *p)	// ��ʼ����
{
	p->elem = NULL;
	p->length = 0;
	p->size = 0;
}

status createlist(sqlist *p)	// ����˳���
{
	elemtype *newbase = NULL;
	
	if (p->elem) return ERROR;	// �Ѿ�������
	newbase = (elemtype *)malloc(SIZE*sizeof(elemtype));
	if (newbase)
	{
		p->elem = newbase;
		p->length = 0;
		p->size = SIZE;
		return OK;
	}
	else return ERROR;
}

status destorylist(sqlist *p)	// �������Ա�
{
	if (p->elem)
	{
		free(p->elem);
		p->length = 0;
		p->size = 0;
		p->elem = NULL;
		return OK;
	}
	else return ERROR;
}

status insert(sqlist *p, int pos, elemtype *data) // ��������
{
	elemtype *end;
	elemtype *cur;
	elemtype *now;
	elemtype *newbase = NULL;
	int newsize = 0;

	if (p->elem == NULL) return ERROR; 
	// posλ���Ƿ���ȷ
	// �±�� 0 ��ʼ����λ��� 1 ��ʼ������pos--
	pos--;
	if (pos>=0 && pos<=p->length)
	{
		// ������Ĵ�С������
		if (p->length == p->size)
		{
			newsize = (p->size + INC) * sizeof(elemtype);
			newbase = (elemtype *)realloc(p->elem, newsize);
			if (newbase)
			{
				p->elem = newbase;
				p->size += INC;
			}
			else return ERROR;
		}

		// ��ʼ����
		end = p->elem + p->length - 1; 
		now = p->elem + pos;
		for (cur=end; cur>=now; cur--)
		{
			*(cur+1) = *cur;
		}
		*now = *data;
		p->length++;
		return OK;
	}
	else return ERROR;
}

status update(sqlist *p, int pos, elemtype *data) // �޸�����
{
	elemtype *cur;

	if (p->elem == NULL) return ERROR; 
	pos--;	// ͳһ�±���λ��
	if (pos>=0 && pos<p->length)
	{
		cur = p->elem + pos;
		*cur = *data;
		return OK;
	}
	else return ERROR;
}

status remove(sqlist *p, int pos) // ɾ������
{
	elemtype *cur;
	elemtype *end;

	if (p->elem == NULL) return ERROR; 
	pos--;	// ͳһ�±���λ��
	if (pos>=0 && pos<p->length)
	{	
		end = p->elem + p->length - 1;
		for (cur=p->elem + pos; cur<end; cur++)
		{
			*cur = *(cur + 1);
		}
		p->length--;
		return OK;
	}
	else return ERROR;
}

status showlist(sqlist *p) // ��ʾ��������Ԫ��
{
	elemtype *cur;
	int i;

	if (p->length)
	{
		// ÿһ����ʾ10��
		cur = p->elem;
		for (i=0; i<p->length; i++)
		{
			if (i%10 == 0) printf("\n\n");
			printf("%d, ", *cur);
			cur++;
		}
		return OK;
	}
	else return ERROR;
}

status clearlist(sqlist *p) // ��ձ���Ԫ��
{
	elemtype *cur;
	elemtype *end;

	if (p->length)
	{
		// 1 2 3  lenth = 3
		end = p->elem + p->length;
		for (cur=p->elem; cur<end; cur++)
		{
			*cur = 0;
		}
		return OK;
	}
	else return ERROR;
}

status getelem(sqlist *p, int pos, elemtype *back) // ���ʵ�N��Ԫ��
{
	elemtype *cur;

	if (p->elem == NULL) return ERROR; 
	pos--;
	if (pos>=0 && pos<p->length)
	{	
		cur = p->elem + pos;
		*back = *cur;
		return OK;
	}
	else return ERROR;
}

status listlen(sqlist *p, int *back) // ��ñ�
{
	if (p->elem == NULL) return ERROR; 
	*back = p->length;
	return OK;
}

