#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// ������ϵͳ�еĵ���, ����ռʽ����
// �����ҵ����, �Ȱ�����������, ÿ������̵���ҵ

// PCB ���̿��ƿ�
typedef struct 
{
	char name[30];		// ������
	unsigned int pid;
	long int start_time;
	long int end_time;
	long int service_time;
	long int mission;		// ��ҵ��, ����һ����ҵҪ 1 ����
}PCB;

// ��������
PCB *createprocess(char *name, int i, int m)
{
	PCB *p;

	p = (PCB *)malloc(sizeof(PCB));
	p->mission = m;
	strcpy(p->name, name);
	p->pid = i;
	p->start_time = 0;
	// �����ҵҪ����ҵͬʱ����

	return p;
}

void sort(PCB **p, int n);		// ����

void run(PCB *t)	// ������
{
	Sleep(t->mission);
	t->mission = 0;
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
	
	srand(time(NULL));
	for (i=0; i<10; i++)	// ������� 10 ���������
	{
		name[0]++;
		m = rand() % 1000 + 500;
		p[i] = createprocess(name, i, m);
		Sleep(1);
	}
	sort(p, 10);		// ��С��������ҵ������
	for (i=0; i<10; i++)
	{
		printf("���� %s ������...\n", p[i]->name);
		t = clock();		// ��ʼ����ʱ��
		run(p[i]);
		p[i]->service_time = clock() - t;
		p[i]->end_time = clock();
	}
	show(p, 10);
	for (i=0; i<10; i++) free(p[i]);	// ���ٽ���
	
	return 0;
}

void sort(PCB **p, int n)
{
	int i, j;
	int flag;
	PCB *tmp;

	for (i=0; i<n; i++)
	{
		flag = 1;
		for (j=0; j<n-1; j++)
		{
			if (p[j]->mission > p[j+1]->mission)
			{
				tmp = p[j];
				p[j] = p[j+1];
				p[j+1] = tmp;
				flag = 0;
			}
		}
		if (flag) break;
	}
}