// ��� main ��ĺ���
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlist.h"

void display()
{
	system("color 0e");
	printf("\n---------˳���Ĵ洢��������\n\n");

	printf("--- ״̬��%s\n\n", 
		list.elem==0?"˳���δ����":"˳����Ѵ���");
	printf("--- 1. �������Ա�\n");
	printf("--- 2. ������������\n");
	printf("--- 3. �������Ա�\n\n");

	printf("--- 4. ��ʾ˳���\n");
	printf("--- 5. ��ʾ��\n\n");

	printf("--- 6. ����Ԫ��\n");
	printf("--- 7. �޸�Ԫ��\n");
	printf("--- 8. ɾ��Ԫ��\n\n");

	printf("--- 9. ����ȫ��Ԫ��\n");
	printf("--- 10. ɾ��ȫ������\n");
	printf("--- 11. ���ʵ�N��Ԫ��\n\n");

	printf("--- ������ţ�ִ�в���\n");
	printf("--- ����exit���˳�����");
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
		memset(str, 0, 10*sizeof(char));
		scanf("%8s", str);
		fflush(stdin);
		op = getnum(str);
		if (op>=1 && op<=11)
		{
			switch (op)
			{
			case 1 : exe_createlist();	break;
			case 2 : exe_input();		break;
			case 3 : exe_destorylist();	break;
			case 4 : exe_showlist();	break;
			case 5 : exe_listlen();		break;
			case 6 : exe_insert();		break;
			case 7 : exe_update();		break;
			case 8 : exe_remove();		break;
			case 9 : exe_clearlist();	break;
			case 10: exe_delall();		break;
			case 11: exe_getelem();		break;
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

void exe_createlist()
{
	system("cls");
	if (createlist(&list)) printf("\n--- �����ɹ���\n");
	else printf("\n--- Error:����ʧ�ܣ�\n\n--- ���Ѿ������ˣ�\n");
	back();
}

void exe_input()
{
	int i = 0;
	char buf[10];
	elemtype data;

	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX ����ʧ��! ��û�д���!\n");
	else 
	{
		printf("\n--- ����������ĸ����ʾ��������\n\n");
		while (1)
		{
			i++;
			printf(">>> ������� %d �����ݣ�", i);
			memset(buf, 0, 10*sizeof(char));
			scanf("%8s", buf);
			if (buf[0]>='0' && buf[0]<='9')
			{
				sscanf(buf, "%d", &data);
				if (insert(&list, i, &data) == ERROR) 
				{
					printf("\nXXX ERROR������д��ʧ��!\n");
					break;
				}
			}
			else 
			{
				printf("\n--- �������!\n");
				break;
			}
		}
	}
	back();
}

void exe_destorylist()
{
	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX ����ʧ��! ��û�б�����!\n");
	else 
	{
		if (destorylist(&list)) 
			printf("\n--- ���ٳɹ�!\n");
		else printf("\n-- ����ʧ��!\n");
	}
	back();
}
void exe_insert()
{	
	int i;
	elemtype data;

	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX ����ʧ��! ��û�б�����!\n");
	else 
	{
		printf("\n--- ��ǰ����Ԫ�أ�");
		if (!showlist(&list)) printf("�ձ�!\n");
		printf("\n\n--- ������Ҫ�����λ�ã�");
		scanf("%d", &i);
		printf("\n--- ������Ҫ��������ݣ�");
		scanf("%d", &data);
		if (insert(&list, i, &data))
		{
			printf("\n--- ����ɹ���\n\n--- ��ǰ��");
			showlist(&list);
		}
		else 
		{
			printf("\n--- ����ʧ�ܣ�λ�ò���ȷ��\n\n--- ��ǰ��:");
			showlist(&list);
		}
	}
	back();
}
void exe_update()
{
	int pos;
	elemtype data;

	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX �޸�ʧ��! ��û�б�����!\n");
	else 
	{
		printf("\n--- ��ǰ����Ԫ�أ�");
		if (!showlist(&list)) printf("�ձ�!\n");
		printf("\n\n--- ������Ҫ�޸ĵ�λ�ã�");
		scanf("%d", &pos);
		printf("\n--- �������µ����ݣ�");
		scanf("%d", &data);
		if (update(&list, pos, &data))
		{
			printf("\n--- �޸ĳɹ���\n\n--- ��ǰ��");
			showlist(&list);
		}
		else 
		{
			printf("\n--- �޸�ʧ�ܣ�λ�ò���ȷ��\n\n--- ��ǰ��:");
			showlist(&list);
		}
	}
	back();
}

void exe_remove()
{
	int pos;

	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX ɾ��ʧ��! ��û�б�����!\n");
	else 
	{
		printf("\n--- ��ǰ����Ԫ�أ�");
		if (!showlist(&list)) printf("�ձ�!\n");
		printf("\n\n--- ������Ҫɾ����λ�ã�");
		scanf("%d", &pos);
		if (remove(&list, pos))
		{
			printf("\n--- ɾ���ɹ���\n\n--- ��ǰ��");
			showlist(&list);
		}
		else 
		{
			printf("\n--- ɾ��ʧ�ܣ�λ�ò���ȷ��\n\n--- ��ǰ��:");
			showlist(&list);
		}
	}
	back();
}

void exe_showlist()
{
	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX ��ʾʧ��! ��û�б�����!\n");
	else 
	{
		printf("\n--- ��ǰ����Ԫ�أ�");
		if (!showlist(&list)) printf("�ձ�!\n");
	}
	back();
}

void exe_clearlist()
{
	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX ���ʧ��! ��û�б�����!\n");
	else 
	{
		if (clearlist(&list))
		{
			printf("\n--- ��ճɹ���\n\n");
			printf("\n--- ��ǰ����Ԫ�أ�");
		}
		if (!showlist(&list)) printf("�ձ�!\n");
	}
	back();
}
void exe_getelem()
{
	int pos;
	elemtype data;

	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX ����ʧ��! ��û�б�����!\n");
	else 
	{
		listlen(&list, &pos);
		printf("\n--- ��ǰ����%d\n\n", pos);
		printf("\n--- ������Ҫ���ʵ�λ�ã�");
		scanf("%d", &pos);
		if (getelem(&list, pos, &data))
			printf("\n--- ������Ϊ��%d\n\n", data);
		else 
			printf("\n--- ����ʧ�ܣ�λ�ò���ȷ��\n\n");
	}
	back();
}
void exe_listlen()
{
	int pos;

	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX ����ʧ��! ��û�б�����!\n");
	else 
	{
		listlen(&list, &pos);
		printf("\n--- ��ǰ����%d\n\n", pos);
	}
	back();
}

void exe_delall()
{
	int pos;
	int i;

	system("cls");
	if (list.elem == NULL) 
		printf("\nXXX ɾ��ʧ��! ��û�б�����!\n");
	else 
	{
		listlen(&list, &pos);
		// �Ӻ�����ǰ��ɾ�����Ӷ�С
		for (i=pos; i>=1; i--)
		{
			remove(&list, i);
		}
		listlen(&list, &pos);
		printf("\n--- ɾ����ɣ���ǰ����%d\n", pos);
	}
	back();
}

