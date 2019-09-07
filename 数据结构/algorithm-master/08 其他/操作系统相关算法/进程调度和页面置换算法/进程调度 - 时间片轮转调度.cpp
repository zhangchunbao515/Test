#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// ����ʽϵͳ�еĵ���, ʱ��Ƭ��ת���� (��ռʽ����)

#define TS 80		// ʱ��Ƭ (time slice) 80 ms
// ����ʱ��Ƭ��С�ɹ۲��ܺ�ʱ, ��Ϊ�����л�Ҫ��ʱ��
// ʱ��Ƭ��С, �����Ժ�, ���� CPU �����ʵ�, 
// ʱ��Ƭ����, CPU �����ʸ�, ���ǽ����Բ�

typedef struct		// PCB ���̿��ƿ�
{
	char name[30];		// ������
	unsigned pid;		// ���� pid
	long int start_time;
	long int end_time;
	long int service_time;
	long int mission;		// ��ҵ��, ����һ����ҵҪ 1 ����
}PCB;


#define SIZE 20		// ������ز���
typedef struct
{
	PCB *base[SIZE];
	int rear;
	int front;
}queue;
queue q;		
void initialize(queue *q);
void enqueue(queue *q, PCB *data);
void dequeue(queue *q);
PCB *getfirst(queue *q);


// �������̲����
PCB *createprocess(char *name, int i, int m)
{
	PCB *p;

	p = (PCB *)malloc(sizeof(PCB));
	p->mission = m;
	strcpy(p->name, name);
	p->pid = i;
	p->start_time = clock();
	p->end_time = 0;
	p->service_time = 0;
	enqueue(&q, p);

	return p;
}

inline void run(PCB *tmp)		// ������, ÿ�η� TS ʱ��
{
	if (tmp->mission >= TS)
	{
		Sleep(TS);
		tmp->mission -= TS;
	}
	else		// ��ҵ��С��ʱ��Ƭ, �����������л�
	{
		Sleep(tmp->mission);
		tmp->mission = 0;
	}
}

void show(PCB *p[], int n)
{
	int i, t;		// ��תʱ��
	float avg;		// ƽ����ת
	int sum = 0;

	printf("\n������\t��ʼ\t����\t����\t��ת\tƽ����ת  (ʱ�䵥λ ms)\n");
	for (i=0; i<n; i++)
	{
		t = p[i]->end_time - p[i]->start_time;
		avg = (float)t / (p[i]->service_time);
		sum += p[i]->end_time;
		printf(" %s\t%d\t%d\t%d\t%d\t%.2f\n", 
			p[i]->name, p[i]->start_time, p[i]->end_time, 
			p[i]->service_time, t, avg);
	}
	printf("\nÿ������ƽ����ʱ %0.2f\n\n", (float)sum / n);
}

int main(void)
{
	PCB *p[10];
	int i, m, t;
	char name[2] = {'A'-1, '\0'};
	int flag;
	
	initialize(&q);
	srand(time(NULL));
	for (i=0; i<10; i++)	// ������� 10 ���������
	{
		name[0]++;
		m = rand() % 1000 + 500;
		p[i] = createprocess(name, i, m);
	}
	while (1)		// ��ͣ�ٵش�����̶���
	{				// ��������Ԫ��
		flag = 1;
		for (i=q.front; i!=q.rear; i=(i+1)%SIZE)
		{
			if (q.base[i]->mission > 0)		// ����ҵ������
			{
				printf("�л������� %s ����...\n", q.base[i]->name);
				t = clock();
				run(q.base[i]);			// ����
				q.base[i]->service_time += clock() - t;
				q.base[i]->end_time += clock();
				flag = 0;
			}
		}
		if (flag) break;		// ȫ�����̶���������
	}
	show(p, 10);
	for (i=0; i<10; i++) free(p[i]);	// ���ٽ���
	
	return 0;
}

// �����Ƕ�����غ���, ���Է���ͷ�ļ���, Ҳ���� STL �Ķ���
void initialize(queue *q)
{q->front = q->rear = 0;}
void enqueue(queue *q, PCB *data)
{
	q->base[q->rear] = data;
	q->rear = (q->rear + 1) % SIZE;
}
void dequeue(queue *q)
{q->front = (q->front + 1) % SIZE;}
PCB *getfirst(queue *q)
{
	if (q->front != q->rear) return q->base[q->front];
	else return NULL;
}