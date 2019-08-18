#include <stdio.h>
#include <malloc.h>

// ������ʽ����, ÿ������ 6 ��Ԫ��
#define OK 1
#define ERROR 0
#define SIZE 6

typedef int status;

// ���ṹ���� 6 ������
typedef struct node
{
	char data[SIZE];
	node *next;
}node;

// ͷ�ṹ
typedef struct 
{
	node *first;
	node *last;
	int lenth;	//  ����
}string;

// ����һ���ս�����������ã���������
status create(string *s)
{
	// [NULL] -> [1] -> [2]...
	s->first = (node *)malloc(sizeof(node));
	if (!s->first) return ERROR;
	s->first->next = NULL;	// ��ȫ��
	s->last = s->first;
	s->lenth = 0;

	return OK;
}

// ׷��һ���½��
status append(string *s)
{
	node *n;

	n = (node *)malloc(sizeof(node));
	if (!n) return ERROR;
	n->next = s->last->next;
	s->last->next = n;	// �� n ����ȥ
	s->last = n;		// last ����

	return OK;
}

// ����ַ���
status strclear(string *s)
{
	node *cur;

	if (!s->first) return ERROR;
	cur = s->first;
	while (cur->next)
	{
		s->first = cur->next;
		free(cur);
		cur = s->first;
	}
	s->last = s->first;
	s->lenth = 0;
	return OK;
}

// �������ݣ��൱�� scanf
status input(string *s)
{
	char buf[1024] = {0};	// ���ջ�����
	char *cur;
	int len = 0;
	int i;
	char *in;

	strclear(s);
	scanf("%s", buf);
	while (buf[len] != '\0') len++;
	cur = buf;
	// ������û������ַ����ĳ��ȣ���ʼд��
	while (len > 0)
	{
		// ĩβ׷��һ���½�㣬
		if (!append(s)) return ERROR;

		// һ��д�� SIZE ��
		// in ָ������½�㣬��ʼ��ֵ
		in = s->last->data;
		for (i=0; i<SIZE; i++)
		{
			if (cur[i] != '\0') 
			{
				in[i] = cur[i];
				s->lenth++;
			}
			else 
			{
				for ( ; i<SIZE; i++) in[i] = '#';
				break;
			}
		}
		// cur ȥ����һ�� 6 
		cur += SIZE;
		len -= SIZE;
	}
	return OK;
}

// ������ʽ�ַ����������
status strshow(string *s)
{
	node *cur;
	int times;
	char *c;

	if (!s->first) return ERROR;
	cur = s->first->next;
	while (cur)
	{
		times = SIZE;
		c = cur->data;
		while (times--)
		{
			if (*c != '#') printf("%c", *c++);
		}
		cur = cur->next;
	}
	printf("\n");
	return OK;
}

// ��ʡ�µķ�����ֱ�Ӱ� a �еĽ��ȫ��
// ���Ƶ� b �о��У�
// ���� a �п��ܴ��ںܶ�� # ��Ч����
// Ϊ��ʡ�ռ䣬���±��� a ȡ����Ԫ��
status strcopy(string *b, string *a)
{
	node *cur;
	int now;	// b��ָʾ������0��5֮��ѭ��
	int i;

	// ���ͷŵ� b ԭ���ģ�
	strclear(b);
	// ���� a ���Ƶ� b ��
	cur = a->first->next;
	now = SIZE;
	while (cur)
	{
		// ���� cur �������ݵ��� b ��
		for (i=0; i<SIZE; i++)
		{
			// �����ǰ�Ľ������
			if (now == SIZE)
			{
				if (!append(b)) return ERROR;
				now = 0;
			}
			// ��ʼ���뵽 b ��
			if (cur->data[i] != '#')
			{
				b->last->data[now++] = cur->data[i];
				b->lenth++;
			}
		}
		cur = cur->next;	// ������һ���������
	}
	// b �����һ����㲻һ������
	while (now != SIZE) b->last->data[now++] = '#';

	return OK;
}

// Ϊ�˲��ƻ� s ������ṹ��
// �������¸���һ�ݵ� re
status strcatch(string *re, string *s)
{
	node *cur;
	int i;

	if (!re->first) return ERROR;
	// ���� s
	cur = s->first->next; 
	while (cur)
	{
		// �� re ��׷��һ���½��
		if (!append(re)) return ERROR;
		for (i=0; i<SIZE; i++)
		{
			re->last->data[i] = cur->data[i];
		}
		cur = cur->next;
	}
	// ���³���
	re->lenth += s->lenth;
	return ERROR;
}

// �� re �н�ȡ�Ӵ��� s ��
// ֱ����
status strback(string *re, int pos, int len, string *s)
{
	int j = 0;
	node *cur;
	int i;
	char buf[1024];
	int now = 0;
	int position;

	// abcd
	if (pos >= 1 
		&& len >= 0 
		&& pos + len <= re->lenth + 1)
	{
		strclear(s);
		cur = re->first->next;
		position = pos + len - 1;
		while (cur)
		{
			// ����ÿ����������
			// ȡ�����ݷŵ� buf ��
			for (i=0; i<SIZE; i++)
			{
				if (cur->data[i] != '#') 
				{
					buf[now++] = cur->data[i];	
					if (now == position) break;
				}
			}
			cur = cur->next;
		}
		// �� buf �е����ݵ��� s ��
		now = SIZE;
		for (i=pos-1; i<position; i++)
		{
			if (now == SIZE)
			{
				if (!append(s)) return ERROR;
				now = 0;
			}
			s->last->data[now++] = buf[i];
		}
		s->lenth = len;
		while (now != SIZE) s->last->data[now++] = '#';
		return OK;

	}
	else return ERROR;
}

int strcompare(string *a, string *b)
{
	node *cura = a->first->next;	// ��¼���е�λ��
	node *curb = b->first->next;
	int posa = 0;
	int posb = 0;
	char aa, bb;

	if (a->lenth != 0 && b->lenth != 0)
	{
		while (cura && curb)
		{
			// Ѱ�� a �����һ��Ԫ��
			aa = bb = 0;
			while (1)
			{
				if (cura->data[posa] != '#')
				{
					aa = cura->data[posa];
					posa++;
					break;
				}
				else 
				{
					posa++;
					if (posa == SIZE)
					{
						posa = 0;
						cura = cura->next;
						if (!cura) break;
					}
				}
			}
			// Ѱ�� b �����һ��Ԫ��
			while (1)
			{
				if (curb->data[posb] != '#')
				{
					bb = curb->data[posb];
					posb++;
					break;
				}
				else 
				{
					posb++;
					if (posb == SIZE)
					{
						posb = 0;
						curb = curb->next;
						if (!curb) break;
					}
				}
			}
			if (aa && bb) 
			{
				if (aa != bb) return aa - bb;
			}
			else return aa - bb;
		}
	}
	
	// �����һ���� 0 �Ͳ�ִ��ѭ��
	return a->lenth - b->lenth;
}

status destory(string *s)
{
	node *cur;

	cur = s->first;
	while (cur)
	{
		s->first = cur->next;
		free(cur);
		cur = s->first;
	}
	s->last = s->first;
	s->lenth = 0;

	return OK;
}

int main(void)
{
	string s1, s2, s3;
	int a, b;

	create(&s1);	// ��ʼ��
	create(&s2);
	create(&s3);

	input(&s1);	// ������
	strshow(&s1);
	printf("���ȣ�%d\n", s1.lenth);

	strcopy(&s2, &s1);	// ������
	strshow(&s2);

	input(&s3);
	strcatch(&s2, &s3);	// ������
	strshow(&s2);	
	printf("���ȣ�%d\n", s2.lenth);

	printf("��ȡ��λ��+����:");
	scanf("%d%d", &a, &b);
	// �ӵ� 1 λ����ȡ 3 ��
	strback(&s1, a, b, &s2);	// ����ȡ
	strshow(&s2);

	// ���Ƚ�
	input(&s2);
	if (strcompare(&s1, &s2) > 0) printf("s1 > s2\n");
	else if (strcompare(&s1, &s2) < 0) printf("s1 < s2\n");
	else if (strcompare(&s1, &s2) == 0) printf("s1 = s2\n");

	strclear(&s1);	// ���
	strclear(&s2);
	strshow(&s2);

	destory(&s1);
	destory(&s2);
	destory(&s3);

	return 0;
}