
// ˫�˶���
// push_front()		ǰ�����
// pop_front()		ǰ�˳���
// push_rear()		������
// pop_rear()		��˳���
// get_front()		��ö�ͷ
// get_rear()		��ö�β

#include <stdio.h>

typedef int elemtype;
#define NUM 50		// ���д�С
#define INC(a) ((a + 1) % NUM)
#define DEC(a) ((a - 1 + NUM) % NUM)

// ˫�˶��нṹ: 
//  ...... 0 1 2 3 4 5 ..........
//         |           |
//       front        rear

typedef struct
{
	elemtype base[NUM];
	int front;		// ��ͷ
	int rear;		// ��β
}queue;

void init(queue *q)
{
	q->front = q->rear = 0;
}

// ǰ��ѹ�� front--
int push_front(queue *q, elemtype data)
{
	if (DEC(q->front) == q->rear) return 0;	// ����
	q->front = DEC(q->front);
	q->base[q->front] = data;

	return 1;
}

// ǰ�˵��� front++
int pop_front(queue *q)
{
	if (q->front == q->rear) return 0;	// ��
	q->front = INC(q->front);

	return 1;
}

// ��ö�ͷ
elemtype get_front(queue *q)
{
	if (q->front == q->rear) return -1;
	return q->base[q->front];
}

// ������ rear++
int push_rear(queue *q, elemtype data)
{
	if (INC(q->rear) == q->front) return 0;
	q->base[q->rear] = data;
	q->rear = INC(q->rear);

	return 1;
}

// ��˳��� rear--
int pop_rear(queue *q)
{
	if (q->rear == q->front) return 0;
	q->rear = DEC(q->rear);

	return 1;
}

// ��ö�β 
elemtype get_rear(queue *q)
{
	if (q->rear == q->front) return -1;
	return q->base[DEC(q->rear)];
}

int main(void)
{
	queue q;
	int i, tmp;

	init(&q);
	printf("\n���ѹ��: ");
	for (i=0; i<55; i++)
	{
		if (push_rear(&q, i)) printf("%d, ", i);
		else printf("��, ");
	}
	printf("\n\nǰ�˵���: ");
	for (i=0; i<55; i++)
	{
		if ((tmp = get_front(&q)) != -1) 
		{
			pop_front(&q);
			printf("%d, ", tmp);
		}
		else printf("��, ");
	}
	printf("\n\nǰ��ѹ��: ");
	for (i=0; i<55; i++)
	{
		if (push_front(&q, i)) printf("%d, ", i);
		else printf("��, ");
	}
	printf("\n\n��˵���: ");
	for (i=0; i<55; i++)
	{
		if ((tmp = get_rear(&q)) != -1) 
		{
			pop_rear(&q);
			printf("%d, ", tmp);
		}
		else printf("��, ");
	}
	return 0;
}