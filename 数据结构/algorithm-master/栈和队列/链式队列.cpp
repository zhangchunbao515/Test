// ��ʽ����
#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elemtype;

#define OK 1
#define ERROR 0

// ���ṹ
typedef struct node 
{
	elemtype data;
	node *next;
}node;

// ����ͷ�ṹ
typedef struct queue
{
	node *front;
	node *rear;
	int lenth;
}queue;

// ������ṹ  [front] -> [] -> [] -> [rear]

// ����ʱ����һ���ս��,����־�ն���
// if front == rear ��ʾ�ն���
status create(queue *p)
{
	p->rear = (node *)malloc(sizeof(node));
	if (!p->rear) return ERROR;
	p->rear->next = NULL;		// ��ȫ��
	p->front = p->rear;
	p->lenth = 0;

	return OK;
}

status destory(queue *p)
{
	node *del;

	while (p->front)
	{
		del = p->front;
		p->front = del->next;
		free(del);
	}
	p->rear = p->front = NULL;
	p->lenth = 0;

	return OK;
}

status in(queue *p, elemtype *data)
{
	node *n;

	// �������,��ֵ,����ȥ,rear++,������++
	if (!p->rear) return ERROR;
	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;

	p->rear->data = *data;		// ����Ԫ��
	n->next = p->rear->next;	// ������
	p->rear->next = n;
	p->rear = n;		// �� rear �Ƶ� n ��λ��,rear++
	p->lenth++;

	return OK;
}

// �ڶ�����ӷ���,����һ������
status in2(queue *p, elemtype *data)
{
	if (!p->rear) return ERROR;

	p->rear->data = *data;		// ��ֵ, �������, ������һλ
	p->rear->next = (node *)malloc(sizeof(node));
	if (!p->rear->next) return ERROR;

	p->rear = p->rear->next;	// �൱�� rear++
	p->rear->next = NULL;		// ��ȫ��,���Բ�Ҫ
	p->lenth++;

	return OK;
}

status out(queue *p, elemtype *back)
{
	node *del;

	if (!p->rear) return ERROR;
	// �ն���
	if (p->rear == p->front) return ERROR;

	// ������һλ,ȡ������,�ͷŽ��,front++,������--
	del = p->front;
	p->front = del->next;
	*back = del->data;
	free(del);
	p->lenth--;

	return OK;
}

int lenth(queue *p)
{
	return p->lenth;
}

status onlyshow(queue *p)
{
	node *cur;

	if (!p->rear) return ERROR;
	// �ն���
	if (p->rear == p->front) return ERROR;

	cur = p->front;
	while (cur != p->rear)
	{
		printf("%d, ", cur->data);
		cur = cur->next;
	}
	printf("\n");

	return OK;
}

status gethead(queue *p, elemtype *back)
{
	if (!p->rear) return ERROR;
	if (p->rear == p->front) return ERROR;

	*back = p->front->data;

	return OK;
}

int main(void)
{
	queue q;
	elemtype data;
	int i;
	int times = 10;

	create(&q);
	// ���
	for (i=1; i<=times; i++)
	{
		if (!in2(&q, &i)) break;
		printf("���Ԫ��: %d\n", i);
	}

	// ��ʾ�ӳ�
	printf("\n�ӳ�: %d\n", lenth(&q));
	gethead(&q, &data);
	printf("��ͷԪ��: %d\n", data);
	printf("��������: ");
	onlyshow(&q);
	printf("\n");

	// ����
	for (i=1; i<=times; i++)
	{
		if (!out(&q, &data)) break;
		printf("����Ԫ��: %d\n", data);
	}

	destory(&q);

	return 0;
}