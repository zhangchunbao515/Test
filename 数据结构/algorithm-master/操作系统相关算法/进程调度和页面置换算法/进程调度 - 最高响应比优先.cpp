#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// ������ϵͳ�еĵ���, ����ռʽ����
// �����Ӧ������, �ý��̵ĵȴ�ʱ����Է���ʱ��, �õ���Ӧ��
// ÿ�δ���һ����Ӧ����ߵĽ���

// PCB ���̿��ƿ�
typedef struct 
{
	char name[30];		// ������
	unsigned pid;		// ���� pid
	long int start_time;
	long int end_time;
	long int service_time;
	long int mission;		// ������, ����һ������Ҫ 1 ����
}PCB;

// �������̲����
PCB *createprocess(char *name, int i, int m)
{
	PCB *p;

	p = (PCB *)malloc(sizeof(PCB));
	p->mission = m;
	strcpy(p->name, name);
	p->pid = i;
	p->start_time = clock();

	return p;
}

void run(PCB *tmp)	// ������
{
	Sleep(tmp->mission);
	tmp->mission = 0;
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
	int i, j, m, t;
	char name[2] = {'A'-1, '\0'};
	PCB *tmp;
	int pos = 0;
	float xiangying, max;	// ��Ӧ��
	long int wait_time;
	
	srand(time(NULL));
	for (i=0; i<10; i++)	// ������� 10 ���������
	{
		name[0]++;
		m = rand() % 1000 + 500;
		p[i] = createprocess(name, i, m);
		Sleep(1);
	}
	for (i=0; i<10; i++)		// �������
	{
		// ���������е�Ԫ��, �ҳ�һ�������Ӧ�ȵĽ���
		max = -1;
		for (j=0; j<10; j++)
		{
			if (p[j]->mission != 0)
			{	// ������Ӧ��, = �ȴ�ʱ�� / ����ʱ��
				wait_time = clock() - p[j]->start_time;
				xiangying = (float)wait_time / p[j]->service_time;
				if (xiangying > max) { max = xiangying;  pos = j; }
			}
		}
		tmp = p[pos];
		printf("���� %s ������...\n", tmp->name);
		t = clock();		// ��ʼ����ʱ��
		run(tmp);
		tmp->service_time = clock() - t;
		tmp->end_time = clock();
	}
	show(p, 10);
	for (i=0; i<10; i++) free(p[i]);	// ���ٽ���
	
	return 0;
}
