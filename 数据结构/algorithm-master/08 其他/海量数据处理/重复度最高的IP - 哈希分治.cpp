
// �ں����������ҳ����ִ�����ߵ�ǰ 10 �� IP
// �㷨˼��, ���η�
// IP ��¼�ļ���С 10 GB, Լ 10 �ڸ� IP, �ڴ����� 64 MB
// �� IP ��¼�ļ��е� IP �� 500 ȡģ, ɢ�е� 500 ��С�ļ���
// ��ͬ�� IP �ᱻɢ�е�ͬһ���ļ���
// ƽ��ÿ��С�ļ� 20 MB, �� 64 MB ֮��
// ����ÿ��С�ļ����ö�����ͳ��ÿ�� IP �Ĵ���

// ������������������ IP �ͳ��ִ���
// ��Ϊ IP �� 2^32 ��, Ҫ��֤�ܲ����ظ��� IP ��Ҫ���� 2^32 �� IP
// ԼҪ 64 GB ���ļ�, Ϊ�˱�֤ 10 GB ���ļ���Ҳ�ܲ����ظ� IP 
// �� IP ������Ϊ 0.0.0.0 - 100.100.100.100
// fopen() ���ֻ�ܴ� 507 ���ļ�

// ���: ������¼�ļ��ֽ�� 500 ��С�ļ��� (��)
// ���Խ���ЩС�ļ�ͨ�����緢�͸�������������� (��)
// �ٽ�������ظ�������, ������ google �� MapReduce ����ԭ��

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>			// access()
#include <string.h>

const int num = 1000000;		// 10 ��, �ֶ��޸� num

unsigned int iton(char *ip);		// ��ּǷ��� IP ��ַתΪ����
void ntoi(unsigned int num, char *ip);
int  fileexist(char *path);			// �ж��ļ�����
void fclose_all(FILE **t);			// �ر������ļ�
int  random_write(char *path);		// ������� 6.7 �ڸ� IP, Լ 10 GB
// ͳ�� hashfile �д������� IP
void count(char *hashfile, unsigned int *data, unsigned int *num);
void sort(unsigned int *max, unsigned int *ip, int n);		// ����
inline unsigned int hash(unsigned int ip)				// ��ϣ����
{ return (ip % 500); }

typedef struct node		// ���������
{
	unsigned int ip;	// IP
	unsigned int n;		// ���ִ���
	node *left;
	node *right;
}node;

int main(void)
{
	FILE *in = NULL;
	FILE *tmpfile[505];
	char *path = "c:\\ip_data.dat";
	char hashfile[50];
	char buf[20];
	unsigned int add, data, n;
	unsigned int ip[10], max[10];	// ��¼ǰʮ�� IP
	unsigned int t1, t2, s, e;		// ��¼ʱ��
	int i, j, len, now;			// IP ����

	printf("������������ %s\n\n", path);
	if (!random_write(path)) return 0;	// ������� IP ��¼�ļ�

	// �ж��ļ����Ƿ����, access() == 0 ����
	if (access("c:\\hashfile", 0) == 0) 
		system("rmdir /s /q c:\\hashfile");
	system("mkdir c:\\hashfile");		// ��������Ŀ¼
	system("attrib +h c:\\hashfile");	// ����Ŀ¼

	in = fopen(path, "rt");			// �� IP ��¼�ļ�
	if (in == NULL) return 0;
	for (i=0; i<505; i++) tmpfile[i] = NULL;

	// �� 6.7 �ڸ� IP ɢ�е� 505 ��С�ļ���
	printf("\r���ڹ�ϣ %s\n\n", path);
	e = s = t1 = clock();
	now = 0;
	while (fscanf(in, "%s", buf) != EOF)
	{
		data = iton(buf);		// IP ���ֻ�
		add = hash(data);		// �����ϣ��ַ, �ļ���ַ
		sprintf(hashfile, "c:\\hashfile\\hash_%u.~tmp", add);
		if (tmpfile[add] == NULL)
			tmpfile[add] = fopen(hashfile, "a");
		sprintf(buf, "%u\n", data);
		len = strlen(buf);
		// ���� IP д�뵽�ļ���, ������д������
		fwrite(buf, len, 1, tmpfile[add]);
		now++;
		e = clock();
		if (e - s > 1000)		// �������
		{
			printf("\r������� %0.2f %%\t", (now * 100.0) / num);
			s = e;
		}
	}
	fclose(in);
	fclose_all(tmpfile);
	remove(path);

	// ��ÿ��С�ļ���ͳ���ظ�����ߵ� IP, �����ö�̨���������
	for (i=0; i<10; i++) max[i] = 0;
	for (i=0; i<500; i++)
	{
		sprintf(hashfile, "c:\\hashfile\\hash_%d.~tmp", i);
		if (fileexist(hashfile))
		{
			printf("\r���ڴ��� hash_%d.~tmp\t", i);
			// ͳ�Ƹ�С�ļ��еĴ������� IP
			count(hashfile, &data, &n);
			// ��Ϊֻ�� 10 ��Ԫ��, ��ѡ�������˼���¼���� 10 ��
			// ���Ԫ�ع���, �����ò��������˼���һ����ö�
			unsigned int min = 0xFFFFFFFF, pos;
			for (j=0; j<10; j++)
			{
				if (max[j] < min)
				{
					min = max[j];
					pos = j;
				}
			}
			if (n > min)
			{
				max[pos] = n;
				ip[pos] = data;
			}
		}
	}
	t2 = clock();
	sort(max, ip, 10);

	FILE *log = NULL;		// ͬʱ�� C:\ip_result.txt ��¼���
	log = fopen("C:\\ip_result.txt", "wt");
	fprintf(log, "\n���ʴ�����ߵ�ǰ 10 �� IP:\n\n");
	fprintf(log, "     %-15s%s\n", "IP", "���ʴ���");
	printf("\n\n���ʴ�����ߵ�ǰ 10 �� IP:\n\n");
	printf("     %-15s%s\n", "IP", "���ʴ���");
	for (i=0; i<10; i++)
	{
		ntoi(ip[i], buf);		// ����
		printf("   %-20s%u\n", buf, max[i]);
		fprintf(log, "   %-20s%u\n", buf, max[i]);
	}
	fprintf(log, "\n--- ��ʱ %0.3f ��\n", (t2 - t1) / 1000.0);
	printf("\n--- ��ʱ %0.3f ��\n\n", (t2 - t1) / 1000.0);
	fclose(log);
	system("rmdir /s /q c:\\hashfile");

	return 0;
}

void fclose_all(FILE **t)		// �ر������ļ�
{
	int i;

	for (i=0; i<500; i++)
	{
		if (t[i])
		{
			fclose(t[i]);
			t[i] = NULL;
		}
	}
}

// ������� 6.7 �ڸ� IP, Լ 10 GB
int random_write(char *path)
{
	FILE *out = NULL;
	int i, j, b;
	char buf[20];
	char *cur;
	unsigned int s, e;

	out = fopen(path, "wt");
	if (out == NULL) return 0;
	srand(time(NULL));
	e = s = clock();
	for (i=0; i<num; i++)
	{
		e = clock();
		if (e - s > 1000)		// �������
		{
			printf("\r������� %0.2f %%\t", (i * 100.0) / num);
			s = e;
		}
		for (j=0; j<20; j++) buf[j] = '\0';
		cur = buf;
		for (j=0; j<4; j++) 
		{
			// ��ּǷ���Ӧ�ò��� 0-255 ����ֵ
			// ������� 0-101 ����ֵ
			b = rand() % 101;
			sprintf(cur, "%d.", b);
			while (*cur != '\0') cur++;
		}
		*(cur - 1) = '\n';
		fwrite(buf, cur-(char *)buf, 1, out);
	}
	fclose(out);		// �ǵ�Ҫ�ر�
	return 1;
}

// �������Ĳ���
void insert(node **tree, unsigned int ip)
{
	if ((*tree) == NULL)
	{
		// new_node
		(*tree) = (node *)malloc(sizeof(node));
		(*tree)->ip = ip;
		(*tree)->n = 1;
		(*tree)->left = (*tree)->right = NULL;
	}
	else if ((*tree)->ip == ip)
	{
		(*tree)->n++;
		return ;
	}
	else if (ip < (*tree)->ip)		// ������
		insert(&((*tree)->left), ip);
	else insert(&((*tree)->right), ip);	// ������
}

unsigned int maxn;		// ��ڲ���
node *max_node;			// ���ڲ���
void max_n(node *tree)	// �ҳ����� n ���Ľ��
{
	if (tree)
	{
		if (tree->n > maxn)
		{
			maxn = tree->n;
			max_node = tree;
		}
		max_n(tree->left);
		max_n(tree->right);
	}
}

void destory(node *tree)		// �ͷ���
{
	if (tree)
	{
		destory(tree->left);
		destory(tree->right);
		free(tree);
	}
}

// ͳ�� hashfile �д������� IP
void count(char *hashfile, unsigned int *data, unsigned int *n)
{
	FILE *in = NULL;
	node *tree = NULL;
	unsigned int ip;

	in = fopen(hashfile, "rt");
	while (fscanf(in, "%d", &ip) != EOF)
	{
		insert(&tree, ip);
	}
	fclose(in);
	maxn = 0;
	max_n(tree);	// ����� max_node
	*n = max_node->n;
	*data = max_node->ip;
	destory(tree);
}

// ��������
void sort(unsigned int *max, unsigned int *ip, int n)
{
	int i, j;
	unsigned int tmpm, tmpi;

	for (i=1; i<n; i++)
	{
		if (max[i-1] < max[i])
		{
			tmpm = max[i];
			tmpi = ip[i];
			for (j=i; j>0; j--)
			{
				if (max[j-1] < tmpm)
				{
					max[j] = max[j-1];
					ip[j]  = ip[j-1];
				}
				else break;
			}
			max[j] = tmpm;
			ip[j]  = tmpi;
		}
	}
}

// ���ַ����� IP ��ַתΪ����
unsigned int iton(char *ip)
{
	unsigned int r = 0;
	unsigned int t;
	int i, j;

	for (j=i=0; i<4; i++)
	{
		sscanf(ip + j, "%d", &t);
		if (i < 3)
			while (ip[j++] != '.');
		r = r << 8;
		r += t;
	}
	return r;
}

// ������ num תΪ�ַ��� IP
void ntoi(unsigned int num, char *ip)
{
	unsigned int b, f;
	int i, cur;

	f = 0x00FFFFFF;
	cur = 0;
	for (i=3; i>=0; i--)
	{
		b = num >> (i * 8);
		num = num & f;
		f = f >> 8;
		sprintf(ip + cur, "%u.", b);
		while (ip[cur] != '\0') cur++;
	}
	ip[cur - 1] = '\0';
}

// �ж��ļ�����
int fileexist(char *path)
{
	FILE *fp = NULL;

	fp = fopen(path, "rt");
	if (fp)
	{
		fclose(fp);
		return 1;
	}
	else return 0;
}
