// ����������ʽ���漰��ز���

#include <stdio.h>
#include "Btree.h"

// �Զ������
status show(btnode *tree)
{
	if (!tree) return ERROR;
	printf("%-2c", tree->data);
	return OK;
}

int main(void)
{
	btnode *tree = NULL;   // ��������ĵ�ַ
	char buf[100] = {0};
	char c, n, d;
	btnode *addr;

	printf("��������(# �ű�ʾ��)");
	create(&tree);      // ֱ�������ַ���
//	gets(buf);			// ���� buf ������
//	create2(&tree, buf);  //ABC##DE#G##F###
	init_parent(tree);	// ��ʼ��˫��, Ӧ����create��������
	
	printf("\n���������");
	first_tra(tree, show);
	printf("\n�ǵݹ鷨��");
 	first_tra_s(tree, show);

	printf("\n\n���������");
	mid_tra(tree, show);
	printf("\n�ǵݹ鷨��");
	mid_tra_s(tree, show);

	printf("\n\n���������");
	last_tra(tree, show);
	printf("\n�ǵݹ鷨��");
	last_tra_s(tree, show);
	
	printf("\n\n��α�����");
	wild_tra(tree, show);

	printf("\n\n������ȣ�%d\n", depth(tree));
	printf("�������%d\n", nodenum(tree));
	printf("Ҷ������%d\n\n", leafnum(tree));

	printf("������Ҫ���ҵĽ�㣺");
	fflush(stdin);
	scanf("%c", &c);
	addr = find(tree, &c);
	if (addr) 
	{
		printf("�ҵ�, ��ַΪ: %x\n", addr);
		if (addr->parent)
			printf("��˫��Ϊ %c\n", addr->parent->data);
		addr = root(addr);
		printf("�����Ϊ��%c\n", addr->data);
	}
	else 
		printf("û���ҵ�!\n");

	printf("\n����Ҫ�޸ĵĽ�����ֵ:(��A T) ");
	fflush(stdin);
	scanf("%c %c", &c, &n);
	if (update(tree, &c, &n))
	{
		printf("�޸ĳɹ�!\n");
		printf("�޸ĺ�");
		wild_tra(tree, show);
	}
	else printf("�Ҳ��� %c ���", c);
	printf("\n");

	printf("\n��X����²�������ֵ��λ��(�� X A 0)");
	fflush(stdin);
	scanf("%c %c %c", &c, &n, &d);
	if (insert(tree, &c, &n, d))
	{
		printf("����ɹ�!\n");
		printf("�����");
		wild_tra(tree, show);
		printf("\n�����������ȣ�%d", depth(tree));
	}
	else printf("��ǰλ�ò��ɲ���!");
	printf("\n");

	printf("\n������Ҫɾ�����ĺ���(�� A 1)");
	fflush(stdin);
	scanf("%c %c", &c, &d);
	if (remove(tree, &c, d))
	{
		printf("ɾ����");
		wild_tra(tree, show);
		printf("\nɾ����������ȣ�%d\n", depth(tree));
	}
	else printf("ɾ����λ�ò���ȷ!\n");

	destory(tree);

	return 0;
}
