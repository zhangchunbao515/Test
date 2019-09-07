
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int table_len = 62;
const char table[table_len + 1] = {
'a','b','c','d','e','f','g','h','i','j','k','l',
'm','n','o','p','q','r','s','t','u','v','w','x',
'y','z','A','B','C','D','E','F','G','H','I','J',
'K','L','M','N','O','P','Q','R','S','T','U','V',
'W','X','Y','Z','0','1','2','3','4','5','6','7',
'8','9'};

// �����ַ��� table �е��±�
inline int table_pos(char a)
{
	if ('a' <= a && a <='z')
		return a - 'a';
	else if ('A' <= a && a <='Z')
		return a - 'A' + 26;
	else if ('0' <= a && a <='9')
		return a - '0' + 52;
	else return -1;			// -1 ��������
}

// ����ṹ:
// ���볤�� 32 λ, ǰ��λ������
// ����λ����Կ, ����λ�����ĳ��� len
// ÿ�� 2 �������в���һ��������, �Ľ���ÿ�� k ��
// �����ļ�����Կ�������
void encode(char *m , char *d)		// ����
{
	int m_len = strlen(m);
	int p_key = rand() % 51 + 5;	// ��Կ [5-55]
	char *s = d;
	int top = 4;
	int i, pos;

	d[0] = table[rand() % table_len];	// ������
	d[1] = table[rand() % table_len];
	d[2] = table[p_key];				// ��Կ
	d[3] = table[m_len * 2 - 1];		// ����
	for (i=0; i<m_len; i++)			// �任����
	{
		if (i % 2 == 0)
			s[top++] = table[rand() % table_len];
		pos = (table_pos(m[i]) + p_key) % table_len;
		s[top++] = table[pos];
	}
	while (top < 32)			// ����������
		s[top++] = table[rand() % table_len];
	d[32] = '\0';
}

// ���ܹ����Ǽ��ܵ�������
int decode(char *d, char *m)
{
	int m_len = (table_pos(d[3]) + 1) / 2;	// ��ȡ����
	int p_key = table_pos(d[2]);			// ��ȡ��Կ
	char *s = d + 4;
	int i, pos;

	for (i=0; i<m_len; i++)
	{
		if (i % 2 == 0) s++;
		pos = table_pos(*s++);			// Ѱ���±�
		if (pos == -1) return 0;		// ����ṹ����
		m[i] = table[(pos - p_key + table_len) % table_len];
	}
	m[i] = '\0';
	return 1;
}

int main(void)
{
	char m[35];		// ����
	char d[35];		// ����

	srand(time(NULL));
	while (1)
	{
		printf("\n����Ӣ��+����(4-16)λ: ");
		scanf("%s", m);
		encode(m, d);
		printf("����: %s\n", d);
		m[0] = '\0';
		if (decode(d, m))
			printf("����: %s\n", m);
		else printf("�������!\n");
	}
	return 0;
}