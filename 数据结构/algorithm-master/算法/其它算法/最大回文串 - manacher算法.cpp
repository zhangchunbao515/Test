
// ���� XMADAMYX,  ��� MADAM
// ���� AYXMAAMXY  ��� YXMAAMXY
// �㷨:
// XMADAMYX �����: #X#M#A#D#A#M#Y#X# 
// ����ö�ٻ��Ĵ�����, �� p[] ��¼���ĳ���
// ������ p[]

#include <stdio.h>
#include <string.h>

void out(char *str)
{
	int i, j, k;
	char buf[1000];
	int p[1000];
	int len = strlen(str);
	int max = -1, pos;

	for (j=i=0; i<len; i++, j++)	// �� #
	{
		buf[j++] = '#';
		buf[j] = str[i];
	}
	buf[j++] = '#';
	buf[j] = '\0';
	for (i=0; i<=j; i++)		// ö������
	{
		k = 0;
		while (1)
		{
			if (i+k<=j && i-k>=0 && buf[i+k] == buf[i-k])
				k++;
			else break;
		}
		p[i] = k;
	}
	for (i=0; i<=j; i++)		// ����������
	{
		if (p[i] > max)
		{ max = p[i];   pos = i; }
	}
	max--;				// �������� [pos-max, pos]
	pos += max;
	max *= 2;
	for (i=pos-max; i<pos; i++)
	{
		if (buf[i] != '#') putchar(buf[i]);
	}
	putchar('\n');
}

int main(void)
{
	char buf[1000];

	while (1)
	{
		printf("����һ����: ");
		scanf("%s", buf);
		out(buf);
	}
	return 0;
}