#include <stdio.h>
#include <malloc.h>

typedef int elemtype;
typedef int status;

#define OK 1
#define ERROR 0
#define SIZE 20		// ��С�ѹ̶�

// ѭ������ ˳��ṹ����
typedef struct 
{
	elemtype *base;
	int front;
	int rear;
}queue;

status create(queue *p)
{
	p->base = (elemtype *)malloc(SIZE*sizeof(elemtype));
	if (!p->base) return ERROR;
	p->front = p->rear = 0;

	return OK;
}

status destory(queue *p)
{
	if (p->base)
	{
		free(p->base);
		p->front = p->rear = 0;

		return OK;
	}
	else return ERROR;
}

status clear(queue *p)
{
	p->front = p->rear = 0;
	return OK;
}

status enqueue(queue *p, elemtype *data)
{
	// û���õĶ��в�����
	if (!p->base) return ERROR;

	// ������������û��
	if ((p->rear+1) % SIZE == p->front) return ERROR;

	p->base[p->rear] = *data;
	p->rear = (p->rear + 1) % SIZE;

	return OK;
}

status dequeue(queue *p, elemtype *back)
{
	// û���õĶ��в��ܴ�����
	if (!p->base) return ERROR;

	// �����ǲ��ǿն���
	if (p->rear == p->front) return ERROR;

	*back = p->base[p->front];
	p->front = (p->front + 1) % SIZE;

	return OK;
}

int lenth(queue *p)
{
	if (!p->base) return 0;
	return (p->rear - p->front + SIZE) % SIZE;
	//  0 1 2 3 4 5 
	//  rear  front 
}

// ���⿼��ѭ����ϸ�ڣ�
// inc ��front rear ����һλ
void inc(int *pos)
{
	*pos = (*pos + 1) % SIZE;
}

status onlyshow(queue *p)
{
	int i;

	if (!p->base) return ERROR;
	if (p->rear == p->front) return ERROR;
	
	// 0 1 2 3 
	i = p->front;
	while ( i % SIZE != p->rear )
	{
		printf("%d, ", p->base[i]);
		inc(&i);
	}
	// ��ʱ i % SIZE == p->rear

	return OK;
}

status gethead(queue *p, elemtype *back)
{
	if (!p->base) return ERROR;
	if (p->rear == p->front) return ERROR;

	*back = p->base[ p->front ];

	return OK;
}

int main(void)
{
	queue q;
	elemtype data;
	int i;
	int times = 10;

	create(&q);
	// 5 �����
	for (i=1; i<=times; i++)
	{
		if (!enqueue(&q, &i)) break;
		printf("���Ԫ�أ�%d\n", i);
	}

	printf("\n�ӳ���%d\n", lenth(&q));
	gethead(&q, &data);
	printf("��ͷԪ��: %d\n", data);
	printf("�������У�");
//	clear(&q);
	onlyshow(&q);
	getchar();

	// ����
	for (i=1; i<=times; i++)
	{
		if (!dequeue(&q, &data)) break;
		printf("����Ԫ�أ�%d\n", data);
	}
	destory(&q);

	return 0;
}
