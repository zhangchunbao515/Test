#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlist.h"

sqlist list;	// ˳���
head linklist;	// ������

const char *listpath = "C:\\list.dat";
const char *nodepath = "C:\\node.dat";

void display()
{
	static int f = 1;	// ��֤ f �����������в���

	system("color 0e");
	printf("\n---------���Ա�д��/��ȡ�ļ�\n\n");
	printf("--- 1. ˳���д���ļ�\n");
	printf("--- 2. ���ļ��ж�ȡ˳���\n\n");
	printf("--- 3. ����д���ļ�\n");
	printf("--- 4. ���ļ��ж�ȡ����\n\n");
	printf("--- ������ţ�ִ�в�����");
}

int getnum(char str[])
{
	int buf;
	char s[10] = "exit";

	if (str[0] >= '0' && str[0] <= '9')
	{
		sscanf(str, "%d", &buf);
		return buf;
	}
	else if (!strcmp(str, s)) return -2;
	else return -1;
}

void wait()
{
	char str[10];
	int op;
	
	while (1)
	{
		fflush(stdin);
		scanf("%9s", str);
		fflush(stdin);
		op = getnum(str);
		if (op >= 1 && op <= 4)
		{
			switch (op)
			{
			case 1 : exe_writefile();	break;
			case 2 : exe_readfile();	break;
			case 3 : exe_writefile2();	break;
			case 4 : exe_readfile2();	break;
			}
		}
		else if (op == -2) exit(0);
		else printf("XXX ����������������룺");
	}
}

void back()
{
	fflush(stdin);
	printf("\n\n--- ���»س�������������");
	getchar();
	system("cls");
	display();
}

void exe_writefile()	// ˳���д�ļ�
{
	int i = 1;
	unsigned char status = 0;
	char str[10];
	int num;

	system("cls");
	createlist(&list, SIZE);
	printf("\n--- ���������ݣ�����������ĸ����\n");
	while (1)
	{
		printf("--- ������� %d ����", i++);
		scanf("%9s", str);
		fflush(stdin);
		num = getnum(str);
		if (num == -1)
		{
			status = 0;
			break;
		}
		// �嵽 list �����
		if (!insertlist(&list, list.lenth+1, &num)) 
		{
			status = 1;
			break;
		}
	}
	if (!status) printf("\n--- ��������\n");
	else printf("--- ����ʧ�ܣ��������\n");
	
	// ��ʼд���ļ�...
	if (writefile(&list, listpath))
		printf("\n--- �ļ�����ɹ�!\nλ�ã�%s", listpath);
	else printf("\n--- д���ļ�ʧ��\n");
	destorylist(&list);
	back();
}

void exe_readfile()		// ���ļ���ȡ˳���
{
	system("cls");
	if (readfile(&list, listpath))
	{
		printf("\n--- ��ȡ�ɹ���\n\n");
		showlist(&list);
	}
	else printf("\n--- ��ȡʧ��, �ļ�������!\n");

	// ��list�༭���ִ���ļ���������...

	back();
}

void exe_writefile2()	// ����д�ļ�
{
	int i = 1;
	unsigned char status = 0;
	char str[10];
	int num;

	system("cls");
	createnode(&linklist);
	printf("\n--- ���������ݣ�����������ĸ����\n");
	while (1)
	{
		printf("--- ������� %d ����", i++);
		scanf("%9s", str);
		fflush(stdin);
		num = getnum(str);
		if (num == -1)
		{
			status = 0;
			break;
		}
		// �嵽 list �����
		if (!append(&linklist, &num)) 
		{
			status = 1;
			break;
		}
	}
	if (!status) printf("\n--- ��������\n");
	else printf("--- ����ʧ�ܣ��������\n");

	// ��ʼд���ļ���һ��һ������д��
	if (writefile2(&linklist, nodepath))
		printf("\n--- �ļ�����ɹ�!\nλ�ã�%s", nodepath);
	else printf("\n--- д���ļ�ʧ��\n");
	destorynode(&linklist);

	back();
}

void exe_readfile2()	// ���ļ���ȡ����
{
	system("cls");

	createnode(&linklist);
	if (readfile2(&linklist, nodepath))
	{
		printf("\n--- ��ȡ�ɹ���\n\n");
		shownode(&linklist);
	}
	else printf("\n--- ��ȡʧ��, �ļ�������!\n");
	destorynode(&linklist);

	back();
}
