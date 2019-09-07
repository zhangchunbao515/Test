#include <stdio.h>
#include <stdlib.h>
#include "mgraph.h"

/*
ͼ������
��һ���Ƕ���������� n ����������
���x���� a �� b Ȩֵ�� c
�� 0 0 0 ����
����ͼ���Բ�дȨֵ������Ҫд
ͼ
5
ABCDEF
a b
b c
0 0
��
5
12345
a b 3
c b 6
0 0 0
*/

// ����������
status showname(nametype *data)
{
	if (data) printf("%c, ", *data);
	else return ERROR;
	return OK;
}

int main(void)
{
	mgraph graph;
	int kind;
	int n, i;
	nametype vex[MAX_NUM];	// �㼯
	nametype back;
	nametype data;
	int pos;

	printf("������ͼ�����ͣ�(0.DG, 1.UDG, 2.DN, 3.UDN):");
	scanf("%d", &kind);
	printf("�����붥�����:");
	scanf("%d", &n);
	fflush(stdin);
	printf("�����붥������:");
	for (i=0; i<n; i++)
		scanf("%1c", vex + i);
	fflush(stdin);

	if (kind == DG || kind == UDG)
		printf("������ߣ�(�� a b, ��ʾ a �� b)\n");
	else printf("�����뻡��(�� a b c, ��ʾ a �� b ��ȨΪ c)\n");
	create(&graph, kind, n, vex);	// ����ͼ
	input(&graph);					// ����ͼ
	printf("����ڽӾ���:\n");
	show(&graph);

	printf("\nȡ��i�Ŷ�������ƣ�");
	scanf("%d", &pos);
	if (getvex(&graph, pos, &back))
		printf("�ҵ���%c\n", back);
	else printf("δ�ҵ�\n");

	printf("\n���¶�������, (��X A):");
	fflush(stdin);
	scanf("%c %c", &back, &data);
	if (putvex(&graph, &back, &data))
	{
		printf("���³ɹ�\n");
		show(&graph);
	}
	else
		printf("�Ҳ��� %c\n", back);

	printf("\n����X�ĵ�һ���ڽӵ㣺");
	fflush(stdin);
	scanf("%c", &data);
	pos = firstadjvex(&graph, &data);
	if (pos != NOT_FOUND) 
		printf("��һ���ڽӵ��ǣ�%c\n", graph.vexs[pos]);
	else printf("δ�ҵ�\n");

	printf("\n����X��Y����һ���ڽӵ㣺");
	fflush(stdin);
	scanf("%c %c", &back, &data);
	pos = nextadjvex(&graph, &back, &data);
	if (pos != NOT_FOUND) 
		printf("%c ����һ���ڽӵ��ǣ�%c\n", data, graph.vexs[pos]);
	else printf("δ�ҵ�\n");

	printf("\n����һ����㣺");
	fflush(stdin);
	scanf("%c", &data);
	if (insertvex(&graph, &data))
		show(&graph);
	else printf("\n�ڽӾ�������");

	printf("\nɾ��һ����㣺");
	fflush(stdin);
	scanf("%c", &data);
	if (deletevex(&graph, &data))
		show(&graph);
	else printf("�Ҳ��� %c\n", data);

	if (graph.kind == DG || graph.kind == UDG)
	{
		printf("\n����һ���ߣ�");
		fflush(stdin);
		scanf("%c %c", &back, &data);
		if (insertarc(&graph, &back, &data, 0)) 
			show(&graph);
		else printf("����ʧ��\n");
	}
	else
	{
		printf("\n����һ������");
		fflush(stdin);
		scanf("%c %c %d", &back, &data, &pos);
		if (insertarc(&graph, &back, &data, pos)) 
			show(&graph);
		else printf("����ʧ��\n");
	}

	printf("\nɾ��һ���ߣ�");
	fflush(stdin);
	scanf("%c %c", &back, &data);
	if (deletearc(&graph, &back, &data)) 
		show(&graph);
	else printf("ɾ��ʧ��\n");

	printf("\n�������������");
	graph_DFS(&graph, showname);
	printf("\n");

	printf("\n�����������(�ǵݹ�)��");
	graph_DFS_s(&graph, showname);
	printf("\n");

	printf("\n�������������");
	graph_BFS(&graph, showname);
	printf("\n\n");

	destory(&graph);
	return 0;
}
