#include <stdio.h>
#include "adjlist.h"

// ����� n �����
void print(algraph *graph, int addr)
{
	printf("%c, ", graph->vex[addr].data);
}

int main(void)
{
	algraph graph;		// �ڽӱ�
	elemtype vexs[NUM];
	short int kind;
	int n, i;
	char a, b;

	printf("ͼ���ڽӱ�\n");
	printf("������ͼ������ (0.DG, 1.UDG, 2.DN, 3.UDN): ");
	scanf("%d", &kind);
	printf("�����붥�㼯: ");
	scanf("%d", &n);   fflush(stdin);
	for (i=0; i<n; i++)
		scanf("%1c", vexs + i);

	create(&graph, kind, vexs, n);		// ����ͼ
	printf("������߼�: ");
	input(&graph);		// ��������
	printf("�ڽӱ�����: \n");
	show(&graph);		// �鿴�ڽӱ�

	printf("\n����һ����: ");
	fflush(stdin);   scanf("%c %c", &a, &b);
	if (graph.kind == DN || graph.kind == UDN)	// �����Ȩ
		scanf("%d", &n);
	else n = 0;
	insert_arc(&graph, &a, &b, n);
	show(&graph);
	printf("\nɾ��һ����: ");
	fflush(stdin);   scanf("%c %c", &a, &b);
	remove_arc(&graph, &a, &b);
	show(&graph);
	printf("\n����һ����: ");
	fflush(stdin);   scanf("%c", &a);
	insert_vex(&graph, &a);
	show(&graph);
	printf("\nɾ��һ����: ");
	fflush(stdin);   scanf("%c", &a);
	remove_vex(&graph, &a);
	show(&graph);
	printf("\nX �ĵ�һ���ڽӵ�: (X): ");
	fflush(stdin);   scanf("%c", &a);
	n = first_vex(&graph, &a);
	if (n != NO)
		printf("%c �ĵ�һ���ڽӵ�: %c\n", a, graph.vex[n].data);
	else printf("δ�ҵ�\n");
	printf("\nX ����һ���ڽӵ�: (X A): ");
	fflush(stdin);   scanf("%c %c", &a, &b);
	n = next_vex(&graph, &a, &b);
	if (n != NO)
		printf("%c ����һ���ڽӵ�: %c\n", a, graph.vex[n].data);
	else printf("δ�ҵ�\n");

	printf("\n�����������: ");
	BFS(&graph, print);
	printf("\n�����������: ");
	DFS(&graph, print);
	printf("\n����(�ǵݹ�): ");
	DFS2(&graph, print);
	printf("\n\n");

	destory(&graph);
	return 0;
}
