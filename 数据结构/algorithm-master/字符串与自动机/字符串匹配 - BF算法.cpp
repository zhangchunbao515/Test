
// BF �㷨, ��������һλһλ�Ƚ�, ƥ��ʧ��ʱ, ģʽ������һλ

#include <stdio.h>
#include <string.h>

// �� r ���� d, �����ҵ���λ��
int find(char *r, char *d)
{
	int lenr = strlen(r);
	int lend = strlen(d);
	int i = 0, j = 0;

	while (i < lenr)
	{
		if (r[i] == d[j]) { i++;  j++; }
		else 
		{
			i = i - j + 1;   //���� i ָ��
			j = 0;
		}	
		if (j == lend) break;
	}
	if (j != lend) return -1;
	else return i - j + 1;
}

int main(void)
{
	char r[300];
	char d[300];
	int pos;

	while (1)
	{
		printf("����ԭ��: ");
		scanf("%s", r);
		printf("����ģʽ��: ");
		scanf("%s", d);
		pos = find(r, d);
		if (pos != -1)
			printf("�ҵ�, ��ʼλ��: %d\n\n", pos);
		else 
			printf("δ�ҵ�!\n\n");
	}
	return 0;
}
