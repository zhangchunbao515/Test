
// ��ϣ������ͻ - ����Ѱַ��

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int keytype;	// ������ֵ����
typedef int status;
#define OK 1
#define ERROR 0
#define FOUND -1
#define NO -1		// ������־
#define R 11		// ȡ������

// ��ϣ���С��������, NO ��ʾû����չ��
// ��ϣ��Ҫ��������, ֻ���޸�����, ���￪�� 97 �Ͳ��ٿ���
int hashsize[] = {11, 19, 29, 37, 47, 59, 67, 83, 97, NO};

typedef struct 
{
	keytype *base;	// ��ַ
	int count;		// Ԫ�ظ���
	int psize;		// �ܴ�С��ָ��
}hashtable;


status create(hashtable *t)		// ������ϣ��
{
	int i;
	if (!t) return ERROR;
	
	t->count = t->psize = 0;
	t->base = (keytype *)malloc(
		hashsize[t->psize]* sizeof(keytype));
	if (t->base)
	{
		for (i=0; i<hashsize[t->psize]; i++)
			t->base[i] = NO;	// NO û��Ԫ��
	}
	return OK;
}

void destory(hashtable *t)		// ���ٹ�ϣ��
{
	if (t)
	{
		t->count = t->psize = 0;
		if (t->base) free(t->base);
	}
}

// ���� n �Ĺ�ϣֵ, ������ȡ�෨
// ���ƵĻ������ַ�����, ���з�, ��β��ӷ�......
// ������������, ����һ��"����"�Ĺ�ϣ��������
inline int hash(int n)
{
	return n % R;		// �� R ȡ��
}
/* �پ�һ�� PASCAL ���Թؼ��ֵ� hash ��������
// ͷβ�ַ��� ASCLL ��������� hash ��ַ
int hash(char *str)
{
	return str[0] + str[strlen(str) - 1];
}
*/

inline void nextadd1(int *n)   // ����̽��
{ (*n)++; }	

inline void nextadd2(int *n, int c)   // ƽ��̽��
{
	static int f = -1;
	f = -f;   c /= 2;		// ���� +1, -1 Ҫ̽������, ���� c/2
	(*n) = f * c * c;
}

inline void nextadd3(int *n, int c)   // 쳲�����̽��
{
	static int fib[] = {1,2,3,5,8,13,21,34,55,89,97};
	static int f2 = -1;

	f2 = -f2;   c /= 2;
	(*n) = f2 * fib[c - 1];
}

// �ڹ�ϣ���в���һ��Ԫ��, ���ؿɲ���λ��, Ҳ���Է��س�ͻ���� c
status search(hashtable *t, keytype data, int *pos)
{
	int add, c = 1;
	char flag = 1;		// ��ַ�����־

	add = hash(data);		// ���� data �Ĺ�ϣֵ
	while (t->base[add] != NO && t->base[add] != data)
	{
		// ���г�ͻ, �Ҳ�����ͬ��Ԫ��ʱ, ����̽����һ��ϣ��ַ
		c++;					// ��ͻ����
		nextadd1(&add);			// ����̽��
//		nextadd2(&add, c);		// ƽ��̽��
//		nextadd3(&add, c);		// 쳲�����̽��
		// ��������̽�ⷨ, ȫ������ͨ��, ��ѡһ�ּ���
		// �����ñ��̽��, ����� nextadd1() Ҫ��, ���� ASL ����������!
		if (add < 0)
		{
			c++;   nextadd1(&add);		// ��ַ�Ǹ�����
		}
		if (add >= hashsize[t->psize])		// add ���
		{
			flag = 0;   break;
		}
	}
	*pos = add;
	if (flag && t->base[add] == data) return OK;
	else return ERROR;
}

// ���ϣ���в���һ��Ԫ��
status insert(hashtable *t, keytype data)
{
	int add, i;

	if (search(t, data, &add)) return FOUND;	// ������
	else 
	{	// ��ϣ��������, ׷�ӿռ�, ֱ���ŵ���
		while (add >= hashsize[t->psize])
		{
			if (hashsize[t->psize] != NO)
			{
				t->psize++;
				t->base = (keytype *)realloc(t->base, 
					hashsize[t->psize] * sizeof(keytype));
				for (i=hashsize[t->psize-1]; i<hashsize[t->psize]; i++)
					t->base[i] = NO;
			}
			else return ERROR;
		}
		t->base[add] = data;	// ����
		t->count++;
	}
	return OK;
}

// ��ƽ�����ҳ���
// ����ʵ��λ��������λ�õ�ƫ��ֵ������ҳ���
// �÷���ֻ��������̽�ⷨ���� ASL
float ASL(hashtable *t)
{
	int i, len = 0;
	for (i=0; i<hashsize[t->psize]; i++)
	{
		if (t->base[i] != NO)
			len += i - t->base[i] % R + 1;
		// ʵ���� i, ������ n % R
	}
	return (float)len / t->count;
}

void show(hashtable *t)		// �����ϣ��
{
	int i;
	for (i=0; i<hashsize[t->psize]; i++)
		if (t->base[i] != NO)
			printf("%d, ", t->base[i]);
		else printf("-, ");
}

int main(void)
{
	hashtable table;
	keytype data;
	status s;

	create(&table);
	while (1)		// �������
	{
		printf("������Ҫ���ҵ�Ԫ��: ");
		scanf("%d", &data);
		s = insert(&table, data);		// ����

		if (s == OK) printf("\n��Ԫ�ز�����, �Ѳ���!");
		else if (s == FOUND) printf("\n���ҵ�!");
		else printf("\n����ʧ��!");

		printf("\n\n��ϣ��: ");   show(&table);
		printf("\n\nASL = %.3f\t��װ���� = %.3f", 
			ASL(&table), (float)table.count / hashsize[table.psize]);
		printf("\n\n�� c �˳�, ���س�����...\n");
		getchar();
		if (getch() == 'c') break;
		system("cls");
	}
	// ɾ��һ��Ԫ�ز��ٲ���, ֻ��ͨ�� search() �ҵ����Ԫ��, �ٸ�ֵ NO ����
	destory(&table);
	return 0;
}