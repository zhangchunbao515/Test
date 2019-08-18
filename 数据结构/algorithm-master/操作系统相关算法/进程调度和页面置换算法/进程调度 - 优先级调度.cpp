#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// ����ʽϵͳ�еĵ���,���ȼ����� (��ռʽ����)
// main ����ֻ�������ȼ���ߵĶ����еĽ���, �������, �����伶��
// adjust �����Ͱѵȴ����õĽ������һ�����ȼ�
// ����ÿ�ȴ� 80 ms �Ͱ����н������һ������
// �������ⲿ�����ȼ�����, ���ڲ�����ת����

// ���� main �� adjust ��Ҫ���ʶ���, ���Ƕ��г����ٽ���
// ͬʱ���ʻ��������, ���� main Ҫ���, ��û���ü��� rear ��һ
// �л��� adjust, ��ҲҪ���, ���ǰ� main �ĸ����ǵ���
// ���ź��� mutex ���Ʒ���

#define TS 80		// ʱ��Ƭ (time slice) 80 ms
HANDLE mutex;

typedef struct		// PCB ���̿��ƿ�
{
	char name[30];		// ������
	unsigned int pid;	// ���� pid
	unsigned int p;		// ���ȼ�
	long int start_time;
	long int end_time;
	long int service_time;
	long int mission;		// ��ҵ��, ����һ����ҵҪ 1 ����
}PCB;

#define JI 3		// �༶���еļ���
#define SIZE 20	
typedef struct
{
	PCB *base[SIZE];
	int rear;
	int front;
}queue;
queue q[JI];	// �༶����, q[0] ���ȼ����
void initialize(queue *q);
void enqueue(queue *q, PCB *data);
void dequeue(queue *q);
PCB *getfirst(queue *q);
int empty(queue *q);


// �������̲����
PCB *createprocess(char *name, int i, int m)
{
	PCB *p;

	p = (PCB *)malloc(sizeof(PCB));
	p->mission = m;
	p->p = rand() % JI;		// �������һ�����ȼ�
	strcpy(p->name, name);
	p->pid = i;
	p->start_time = clock();
	p->end_time = 0;
	p->service_time = 0;
	// �������ȼ����, q[0], q[1], q[2]
	enqueue(q + p->p, p);

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

// ÿ�� 50 ms, ��ߵȴ����õĶ��е����ȼ� 
DWORD WINAPI adjust(void *id)
{
	int i;

	Sleep(50);
	while (1)		// ���ϵİ���
	{
		WaitForSingleObject(mutex, INFINITE);
		for (i=1; i<JI; i++)
		{
			while (!empty(q + i))
			{
				// �� i ����Ԫ�ذᵽ 0 ��
//				printf("���ڰ��� %d �� %d ������...\n", i, i-1);
				enqueue(q + i - 1, getfirst(q + i));
				dequeue(q + i);
			}
		}
		ReleaseSemaphore(mutex, 1, NULL);
	}
	return 0;
}

int main(void)
{
	PCB *p[10];
	PCB *tmp;
	int i, m, t;
	char name[2] = {'A'-1, '\0'};
	int flag;
	HANDLE ad;
	
	mutex = CreateSemaphore(NULL, 1, 2, "queue");
	for (i=0; i<JI; i++)
		initialize(q + i);
	srand(time(NULL));
	for (i=0; i<10; i++)	// ������� 10 ���������
	{
		name[0]++;
		m = rand() % 1300 + 200;
		p[i] = createprocess(name, i, m);
	}
	ad = CreateThread(NULL, 0, adjust, NULL, 0, NULL);

	while (1)		// ��ͣ�ٵش�����̶��� q[0]
	{				// ��������Ԫ��
		WaitForSingleObject(mutex, INFINITE);	// ���Խ����ٽ���
		while (!empty(q + 0))
		{
			tmp = getfirst(q + 0);
			dequeue(q + 0);
			if (tmp->mission > 0)		// ����ҵ������
			{
				printf("�л������� %s ����...\n", tmp->name);
				t = clock();
				run(tmp);			// ����
				tmp->service_time += clock() - t;
				tmp->end_time += clock();
				enqueue(q + JI - 1, tmp);	// ��������, ����
			}
		}
		ReleaseSemaphore(mutex, 1, NULL);
		flag = 1;
		for (i=0; i<JI; i++)
			if (!empty(q + i)) flag = 0;
		if (flag) break;
	}
	show(p, 10);
	for (i=0; i<10; i++) free(p[i]);	// ���ٽ���
	CloseHandle(mutex);
	CloseHandle(ad);
	
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
int empty(queue *q)
{return !(q->rear - q->front);}
