/* ----------------------------------
// ��Ⱥ͹������������
// ���� �ڽӱ�   ����ͼ
// ���� �ֵ����� ������
//
// ��Ҫ����:
// DFS(ͼ, ��)   ���й���, ������
// BFS(ͼ, ��)   �ݹ�����, ������
// BFS2(ͼ, ��)  �ǵݹ�����, ������
// DFS_node()    ��ؽڵ�
----------------------------------- */

#include "adjlist.h"	// �ڽӱ��ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>

// �����������
void first_tra(tree *t)
{
	if (t)
	{
		printf("%c, ", t->data);
		first_tra(t->child);
		first_tra(t->brother);
	}
}

// �ͷ���
void del(tree **t)
{
	if (*t)
	{
		del(&(*t)->child);
		del(&(*t)->brother);
		free(*t);
	}
}

// ���Ĳ�α���
// ��Ϊ��û�л�·, ���Բ��ñ�Ƿ���
void BFS_tree(tree *t)
{
	tree *queue[60];	// ����ռ��㹻
	tree *tmp;
	int rear = 0;
	int front = 0;

	//   t  ->  a ->  b -> ...
	//  /      /
	// c ->.. d -> ...    
	queue[rear] = t;		// ��������
	rear = (rear + 1) % 60;
	while (rear != front)
	{
		tmp = queue[front];
		front = (front + 1) % 60;
		while (tmp)		// �����ֵ�, �к��ӵ�ȫ�����
		{
			printf("%c, ", tmp->data);
			if (tmp->child)		// �׺�����Ӽ�¼
			{
				queue[rear] = tmp->child;
				rear = (rear + 1) % 60;
			}
			tmp = tmp->brother;
		}
	}
}

int main(void)
{
	tree *t = NULL;		// ����������
	algraph graph;		// �ڽӱ�
	char str[50] = {'\0'};	// ��¼�ؽڵ�
	elemtype vexs[NUM];
	short int kind;
	int n, i;

	printf("ͼ���ڽӱ�\n");
	printf("������ͼ������ (0.����ͼ, 1.����ͼ): ");
	scanf("%d", &kind);
	printf("�����붥�㼯: ");
	scanf("%d", &n);   fflush(stdin);
	for (i=0; i<n; i++)
		scanf("%1c", vexs + i);

	create(&graph, kind, vexs, n);		// ����ͼ
	printf("������߼�: ");
	input(&graph);		// ��������

	DFS(&graph, &t);
	printf("\n�������������: ");
	first_tra(t);
	del(&t);	t = NULL;

	DFS2(&graph, &t);
	printf("\n�������������: ");
	first_tra(t);
	del(&t);	t = NULL;
	printf("   <- �ǵݹ�����");

	BFS(&graph, &t);
	printf("\n��α���������: ");
	BFS_tree(t);
	del(&t);	t = NULL;

	printf("\n\n��ͼ�Ĺؽڵ�: ");
	DFS_node(&graph, str);
	if (*str == '\0') printf("ǿ��ͨͼ, û�йؽڵ�!\n");
	else 
		for (i=0; str[i]!='\0'; i++)
		{
			// ��Ϊ����������ϵ�����, �����ظ���¼Ϊ�ؽڵ�
			// ������ȥ���ַ������ظ���Ԫ��
			// ����������С, ֱ���� O(n^2) ���㷨��
			// ���ں�������, �ù�ϣ��ȥ���ظ��Ŀ� O(n)
			for (n=i+1; str[n]!='\0'; n++)
				if (str[n] == str[i]) break;
			if (str[n] == '\0') printf("%c, ", str[i]);
		}
	printf("\n");

	destory(&graph);
	return 0;
}
