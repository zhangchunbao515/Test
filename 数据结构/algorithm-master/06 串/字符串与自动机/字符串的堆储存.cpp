#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int status;

#define OK 1
#define ERROR 0

// ���ĶѴ���
typedef struct 
{
	char *base;
	int lenth;
}string;

int lenth(char *s)
{
	int len = 0;

	while (*s != '\0') 
	{
		len++;
		s++;
	}
	return len;
}

status strcopy(string *s, char *re)
{
	// �㷨������ԭ���ģ�Ȼ�󽨸��µģ��ٷŽ���
	char *cur;

	if (lenth(re) <= 0) return ERROR;
	// ����У����ͷŵ�
	if (s->base) free(s->base);
	// ���·����С
	s->lenth = lenth(re);
	s->base = (char *)malloc((s->lenth+1) * sizeof(char));
	if (!s->base) return ERROR;
	
	cur = s->base;
	while (*re != '\0') *cur++ = *re++;
	*cur = '\0';	// ���

	return OK;
}

status init(string *s)
{
	s->base = NULL;
	s->lenth = 0;

	return OK;
}

status strshow(string s)
{
	char *cur;

	if (s.lenth <= 0) return ERROR;
	// for (i=0; i<s.lenth; i++)  Ҳ�ǿ��Ե�
	for (cur=s.base; *cur!='\0'; cur++)
	{
		printf("%c", *cur);
	}
	printf("\n");

	return OK;
}

status strcompare(string s, string t)
{
	int i;

	for (i=0; i<s.lenth && i<t.lenth; i++)
	{
		if (s.base[i] != t.base[i]) 
			return s.base[i] - t.base[i];
	}
	// �����һ�����ĳ����� 0
	return s.lenth - t.lenth;
}

status strclear(string *s)
{
	if (s->base) free(s->base);
	s->lenth = 0;

	return OK;
}

status strback(string s, int pos, int len, string *back)
{
	int i;
	int now = 0;
	int end;

	// �� back �����ˣ��ٷ��µ�
	// abcd
	if (pos >= 1 && len >= 0 && pos+len <= s.lenth+1)
	{
		if (back->base) strclear(back);
		back->base = (char *)malloc((len+2)*sizeof(char));
		if (!back->base) return ERROR;
		back->lenth = len;
		
		pos--;	// λ����±���� 1
		end = pos + len;
		for (i=pos; i<end; i++)
		{
			back->base[now++] = s.base[i];
		}
		back->base[now] = '\0';

		return OK;
	}
	else return ERROR;
}

status strcatch(string s, string t)
{
	// �㷨��ԭ������������չ s �Ĵ�С���� t �Ž���
	int now = 0;
	int i;

	if (t.lenth <= 0) return ERROR;
	s.lenth += t.lenth;
	s.base = (char *)realloc(s.base, (s.lenth+1)*sizeof(char));
	if (!s.base) exit(0);

	for (i=s.lenth-t.lenth; i<s.lenth; i++)
	{
		s.base[i] = t.base[now++];
	}
	s.base[i] = '\0';

	return OK;
}

int main(void)
{
	string s1, s2;

	init(&s1);	// ��ʼ��
	init(&s2);

	strcopy(&s1, "abcdefg");	// ������
	strshow(s1);
	printf("���ȣ�%d\n", s1.lenth);

	strcopy(&s2, s1.base);	// ������
	strshow(s2);	

	strcatch(s2, s1);	// ������
	strshow(s2);	

	strback(s1, 4, 4, &s2);	// ����ȡ
	strshow(s2);

	// ���Ƚ�
	strcopy(&s2, "bbcdefg");
	if (strcompare(s1, s2) > 0) printf("s1 > s2\n");
	else if (strcompare(s1, s2) < 0) printf("s1 < s2\n");
	else if (strcompare(s1, s2) == 0) printf("s1 = s2\n");

	strclear(&s1);	// �ͷ�
	strclear(&s2);

	return 0;
}