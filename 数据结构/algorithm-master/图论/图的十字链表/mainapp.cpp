#include <stdio.h>
#include "olist.h"

int main(void)
{
	olgraph graph;		// ʮ������
	elemtype vexs[NUM];
	int n, i;
	char a, b;

	printf("ͼ��ʮ������\n");
	printf("�����붥�㼯: ");
	scanf("%d", &n);   fflush(stdin);
	for (i=0; i<n; i++) scanf("%1c", vexs + i);

	create(&graph, vexs, n);		// ����ͼ
	printf("������߼�: ");
	input(&graph);		// ��������
	printf("ʮ�������ֹ�ϵ����: \n");
	show(&graph);		// �鿴ʮ������

	printf("\n����һ����: ");
	fflush(stdin);   scanf("%c %c", &a, &b);
	insert_arc(&graph, &a, &b);
	show(&graph);
	printf("\nɾ��һ����: ");
	fflush(stdin);   scanf("%c %c", &a, &b);
	remove_arc(&graph, &a, &b);
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

	destory(&graph);
	return 0;
}
