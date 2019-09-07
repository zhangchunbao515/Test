#include <stdio.h>
#include <string.h>

// �� a �еĵ� pos ֮���λ���� b ��
int kmp(char *a, char *b, int pos)
{
	int next[50] = {0};
	int lena = strlen(a);
	int lenb = strlen(b);
	int i, j;

	// ���� next ����
	// a b a a b c a c
	//-1 0 0 1 1 2 0 1
	next[0] = -1;	// -1 ��ʾ�����ٻ��� j ��
	j = -1;		// ��ʼ j==-1 ��ʾ�ַ�����ͷ�ˣ�
	i = 0;		// i �ӵ�һ���ַ���ʼ
	while (i < lena)
	{
		if (j == -1 || b[i] == b[j])
		{
			i++;   j++;
			next[i] = j;
		}
		else j = next[j];	// ƥ��ʧ��ʱ, �ص� next[j]
	}

	// ��ʼ kmp �㷨
	i = pos;
	j = 0;
	while (i < lena && j < lenb)
	{
		if (j == -1 || a[i] == b[j]) {i++;  j++;}
		else j = next[j];	// ���� j ָ��
	}
	if (j == lenb) return i - j + 1;
	return -1;
}

int main(void)
{
	char a[500];
	char b[100];
	int flag;
	int pos;

	printf("����������: ", a);
	gets(a);
	printf("������ģʽ��: ");
	gets(b);
	printf("�����뿪ʼƥ��λ��: ");
	scanf("%d", &pos);

	flag = kmp(a, b, pos-1);
	if (flag >= 0)
		printf("ƥ��ɹ�!\nλ��: %d\n", flag);
	else 
		printf("ƥ��ʧ��!\n");

	return 0;
}