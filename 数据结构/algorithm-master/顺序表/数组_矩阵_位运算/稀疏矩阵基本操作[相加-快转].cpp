// ��������Ԫ�鴢�棬������ӣ�����ת�õȵ�

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef int elemtype;
typedef int status;

#define ERROR 0
#define OK 1

// ��Ԫ����ṹ
typedef struct
{
	int x;
	int y;
	elemtype data;
}unit;

// ��Ԫ��ͷ�ṹ
typedef struct
{
	unit *base;	// ��ַ
	int lenth;	// ����
}array;

// ��ʼ����
status init(array *s, int x, int y)
{
	s->base = (unit *)malloc(sizeof(unit));
	if (!s->base) return ERROR;
	// 0 �ű���������¼���������
	s->base->x = x;		// ����
	s->base->y = y;		// ����
	s->base->data = 0;	// ����Ԫ��
	s->lenth = 1;

	return OK;
}

status destory(array *s)
{
	if (s->base) free(s->base);
	s->base = NULL;
	s->lenth = 0;

	return OK;
}

// �������
void show(int map[][7], int x, int y)
{
	int i, j;

	for (i=0; i<x; i++)
	{
		for (j=0; j<y; j++)
		{
			printf("%4d", map[i][j]);
		}
		printf("\n");
	}
	return ;
}

// ׷��data����
status append(array *s, int x, int y, elemtype data)
{
	// ��� s ��
	if (!s->base) return ERROR;
	s->base = (unit *)realloc(s->base, 
		(s->lenth + 1) * sizeof(unit));
	if (!s->base) return ERROR;
	s->base[s->lenth].x = x;
	s->base[s->lenth].y = y;
	s->base[s->lenth].data = data;
	s->lenth++;

	return OK;
}

// ѹ������
void encode(array *s, int x, int y, int map[][7])
{
	int i, j;

	// map ����ѹ���� list ��..
	for (i=0; i<x; i++)
		for (j=0; j<y; j++)
			// ������� 0 ��׷�ӵ�����
			if (map[i][j]) append(s, i, j, map[i][j]);
}

// ��ԭ����
void decode(array *s, int x, int y, int buf[][7])
{
	int i;
	for (i=1; i<s->lenth; i++)
	{
		buf[ s->base[i].x ][ s->base[i].y ]
			= s->base[i].data;
	}
}

// �������
status add(array *a, array *b, array *c)
{
	int ia = 1;
	int ib = 1;
	int ax, bx, ay, by;
	elemtype data;

	// �Ƚ� a b ��ĳ���, ��Сһ���ſ����
	if (!(a->base && b->base)) return ERROR;
	if (a->base[0].x != b->base[0].x 
		|| a->base[0].y != b->base[0].y) return ERROR;
	while (ia < a->lenth && ib < b->lenth)
	{
		ax = a->base[ia].x;
		bx = b->base[ib].x;
		ay = a->base[ia].y;
		by = b->base[ib].y;
		if (ax == bx)
		{
			if (ay == by)
			{
				// ��Ӻ�׷�ӵ� c ��
				data = a->base[ia].data + b->base[ib].data;
				append(c, ax, ay, data);
				ia++;
				ib++;
			}
			else 
			{
				if (ay < by) 
					append(c, ax, ay, a->base[ia++].data);
				else
					append(c, bx, by, b->base[ib++].data);
			}
		}
		else
		{
			if (ax < bx)
				append(c, ax, ay, a->base[ia++].data);
			else
				append(c, bx, by, b->base[ib++].data);
		}
	}
	return OK;
}

// ����ת��
status transpose(array *a, array *b)
{
	int *num;	// ��x�з�0Ԫ����
	int *pos;	// ��b���е��ʺ�λ��
	int i;
	int posb;

	// a  x  y  data
	//    1  2   12
	//    1  3   39
	//    3  1   11
	// ͳ�Ʒ� 0 Ԫ����
	num = (int *)malloc(a->lenth * sizeof(int));
	if (!num) return ERROR;
	memset(num, 0, (a->lenth+1)*sizeof(int));
	for (i=1; i<a->lenth; i++)
	{
		num[a->base[i].y]++;	// ͳ��ÿһ�з�0Ԫ
	}

	pos = (int *)malloc(a->lenth * sizeof(int));
	if (!pos) return ERROR;
	pos[0] = 1;
	for (i=0; i<a->lenth; i++)
	{
		// ����λ��
		pos[i+1] = pos[i] + num[i];
	}

	for (i=1; i<a->lenth; i++)
	{
		// a�е�i��Ԫ��, ��b�е�pos[i]λ����
		// x y λ��Ҫ�Ե�
		posb = pos[ a->base[i].y ];
		b->base[posb].x = a->base[i].y;
		b->base[posb].y = a->base[i].x;
		b->base[posb].data = a->base[i].data;
		b->lenth++;
		pos[ a->base[i].y ]++;	// �����н���
	}
	b->base[0].x = a->base[0].y;
	b->base[0].y = a->base[0].x;

	return OK;
}

int main(void)
{
	int map[6][7] = 
	{
		0, 12, 39,  0, 0,  0,  0,
		0,  0,  0,  0, 0,  0,  0,
		11, 0,  0,  0, 0, 14,  0,
		0,  0, 24,  0, 0,  0,  0,
		0, 18,  0,  0, 0,  0,  0,
		15, 0,  0, 15, 0,  0,  0,
	};				// �ֹ�����
	int map2[6][7] = 
	{
		12, 0, 39,  1, 2,  3,  4,
		0,  0,  0,  0, 0,  0,  0,
		11, 0,  0,  0, 0, 14,  0,
		0,  24, 0,  0, 0,  0,  0,
		18, 2,  0,  0, 0,  0,  0,
		15, 0,  0, 15, 0,  0,  0,
	};				// �ֹ�����
	array list;		// ��Ԫ˳���
	array listbuf;
	array list3;
	array listmap;
	int buf[10][7] = {0};
	int buf3[6][7] = {0};
	float resize;	// ԭ��С
	float newsize;	// ѹ�����С
	
	init(&list, 6, 7);	// ��ʼ 6 �� 7 ��
	init(&listbuf, 6, 7);
	init(&list3, 6, 7);
	init(&listmap, 6, 7);
	printf("ԭ����\n");
	show(map, 6, 7);
	encode(&list, 6, 7, map);

	resize = (float)sizeof(map);
	newsize = (float)sizeof(list) + list.lenth * sizeof(unit);
	printf("ѹ���ʣ�%.2f%%\n\n", 100*(1 - newsize / resize));

	// �� list ��ԭ�� buf ��
	decode(&list, 6, 7, buf);
	printf("��ԭ��\n");
	show(buf, 6, 7);
	encode(&listbuf, 6, 7, buf);

	// �������
	encode(&listmap, 6, 7, map2);
	add(&listmap, &listbuf, &list3);
	decode(&list3, 6, 7, buf3);
	printf("\n��Ӻ�\n");
	show(buf3, 6, 7);

	// ����ת��
	destory(&listbuf);
	init(&listbuf, 7, 6);
	memset(buf, 0, sizeof(buf));
	printf("ת�ú�\n");
	transpose(&list, &listbuf);
	decode(&listbuf, 7, 6, buf);
	show(buf, 7, 6);
	
	destory(&list);
//	destory(&listbuf);
	destory(&list3);
//	destory(&listmap);
	
	return 0;
}
