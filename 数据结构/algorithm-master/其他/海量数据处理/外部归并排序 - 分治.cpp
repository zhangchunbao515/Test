
// �� 2 �ڸ����ֽ�������, Լ 10 G ���ļ�, ÿ������ int �ܱ�ʾ
// �㷨����
// �� 10 G ���ļ�ɢ�е� 300 ���ļ���, ÿ���ļ���Լ 35 MB
// �� 35 MB ��С�ļ��ڲ�����, ���߷ַ�����̨�������, ���д��� MapReduce
// ���ʹ����С��, ���� 300 ·�鲢����, �ϳɴ��ļ�
// ��дһ���㷨�ж� 2 �ڸ������Ƿ�����

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <queue>

#define FILE_NUM  300				// ��ϣ�ļ���
#define HASH(a)   (a % FILE_NUM)

int num = 6000000;						// 2 �ڸ�����, �ֶ���
char path[20] = "c:\\data.dat";			// �����ļ�
char result[20] = "c:\\result.dat";		// ������ļ�
char tmpdir[100] = "c:\\hashfile";		// ��ʱĿ¼

// ������� 2 �ڸ�����
int write_file(void)
{
	FILE *out = NULL;
	int i;

	printf("\n�������� %d ������...\n\n", num);
	out = fopen(path, "wt");
	if (out == NULL) return 0;

	unsigned int s, e;
	e = s = clock();
	for (i=0; i<num; i++)
	{
		e = clock();
		if (e - s > 1000)		// �������
		{
			printf("\r������� %0.2f %%\t", (i * 100.0) / num);
			s = e;
		}
		fprintf(out, "%d\n", 
			(rand() % 31623) * (rand() % 31623));
	}
	fclose(out);
	return 1;
}

// �� 2 �ڸ����ֽ��й�ϣ, ��ɢ�����ļ���
// ��ڲ���: path, tmpdir
int map(void)
{
	FILE *in = NULL;
	FILE *tmp[FILE_NUM + 5];
	char hashfile[512];		// ��ϣ�ļ���ַ
	int data, add;
	int i;

	printf("\r���ڹ�ϣ %s\n\n", path);
	in = fopen(path, "rt");
	if (in == NULL) return 0;
	for (i=0; i<FILE_NUM; i++) tmp[i] = NULL;

	// ��ʼ��ϣ, ���Ĵ���Ҫ�����ܵļ���
	unsigned int s, e;
	e = s = clock();
	i = 0;
	while (fscanf(in, "%d", &data) != EOF)
	{
		add = HASH(data);
		if (tmp[add] == NULL)
		{
			sprintf(hashfile, "%s\\hash_%d.~tmp", tmpdir, add);
			tmp[add] = fopen(hashfile, "a");
		}
		fprintf(tmp[add], "%d\n", data);

		i++;
		e = clock();			// �������
		if (e - s > 1000)
		{
			printf("\r������� %0.2f %%\t", (i * 100.0) / num);
			s = e;
		}
	}
	for (i=0; i<FILE_NUM; i++)
		if (tmp[i]) fclose(tmp[i]);
	fclose(in);

	return 1;
}

// �� 300 ���ļ��������, ���ö����� STL �����ȶ���
void calc(void)
{
	int fileexist(char *path);		// �ж��ļ�����
	std::priority_queue<int> q;		// ������
	char hashfile[512];
	FILE *fp = NULL;
	int i, data;

	// ������� 300 ���ļ�, ���߽���Щ�ļ����͵�����������в��д���
	for (i=0; i<FILE_NUM; i++)
	{
		sprintf(hashfile, "%s\\hash_%d.~tmp", tmpdir, i);
		if (fileexist(hashfile))
		{
			printf("\r�������� hash_%d.~tmp\t", i);

			// С�ļ��Ӵ��̼����ڴ���
			fp = fopen(hashfile, "rt");
			while (fscanf(fp, "%d", &data) != EOF)
			{
				q.push(data);
				// ���ȶ���Ĭ���Ǵ󶥶�, ����������
				// Ҫ������Ҫ���� () �����
			}
			fclose(fp);

			// ������ٴ��ڴ�д�ش���
			fp = fopen(hashfile, "wt");		// ����ģʽд
			while (!q.empty())
			{
				fprintf(fp, "%d\n", q.top());
				q.pop();
			}
			fclose(fp);
		}
	}
}

typedef struct node		// ���н��
{
	int data;
	int id;			// ��ϣ�ļ��ı��
	bool operator < (const node &a) const
	{ return data < a.data; }
}node;

// �� 300 �������ļ��ϲ���һ���ļ�, K ·�鲢����
int reduce(void)
{
	int fileexist(char *path);
	std::priority_queue<node> q;		// ������
	FILE *file[FILE_NUM + 5];
	FILE *out = NULL;
	char hashfile[512];
	node tmp, p;
	int i, count = 0;

	printf("\r���ںϲ� %s\n\n", result);
	out = fopen(result, "wt");
	if (out == NULL) return 0;
	for (i=0; i<FILE_NUM; i++) file[i] = NULL;
	for (i=0; i<FILE_NUM; i++)		// ��ȫ����ϣ�ļ�
	{
		sprintf(hashfile, "%s\\hash_%d.~tmp", tmpdir, i);
		if (fileexist(hashfile))
		{
			file[i] = fopen(hashfile, "rt");
			fscanf(file[i], "%d", &tmp.data);
			tmp.id = i;
			q.push(tmp);		// ��ʼ������
			count++;			// ������
			printf("\r��ӽ��� %0.2f %%\t", (count * 100.0) / FILE_NUM);
		}
	}
	unsigned int s, e;
	e = s = clock();
	while (!q.empty())		// ��ʼ K ·�鲢
	{
		tmp = q.top();
		q.pop();
		// ���Ѷ���Ԫ��д�ش���, �ٴӴ�������һ�����ڴ�
		fprintf(out, "%d\n", tmp.data);
		if (fscanf(file[tmp.id], "%d", &p.data) != EOF)
		{
			p.id = tmp.id;
			q.push(p);
			count++;
		}

		e = clock();			// �������
		if (e - s > 1000)
		{
			printf("\r������� %0.2f %%\t", (count * 100.0) / num);
			s = e;
		}
	}
	for (i=0; i<FILE_NUM; i++)
		if (file[i]) fclose(file[i]);
	fclose(out);

	return 1;
}

int check(void)		// ����Ƿ�������
{
	FILE *in = NULL;
	int max  = 0x7FFFFFFF;
	int data;
	int count = 0;

	printf("\r���ڼ���ļ���ȷ��...\n\n");
	in = fopen(result, "rt");
	if (in == NULL) return 0;

	unsigned int s, e;
	e = s = clock();
	while (fscanf(in, "%d", &data) != EOF)
	{
		if (data <= max) max = data;
		else
		{
			fclose(in);
			return 0;
		}
		count++;
		e = clock();			// �������
		if (e - s > 1000)
		{
			printf("\r������� %0.2f %%\t", (count * 100.0) / num);
			s = e;
		}
	}
	fclose(in);
	return 1;
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

int main(void)
{
	char cmd_del[200];		// ɾ��Ŀ¼
	char cmd_att[200];		// ��������
	char cmd_mkdir[200];	// ����Ŀ¼

	// ��ʼ�� cmd ����, ��������Ŀ¼
	sprintf(cmd_del, "rmdir /s /q %s", tmpdir);
	sprintf(cmd_att, "attrib +h %s", tmpdir);
	sprintf(cmd_mkdir, "mkdir %s", tmpdir);
	if (access(path, 0) == 0) system(cmd_del);
	system(cmd_mkdir);		// ��������Ŀ¼
	system(cmd_att);		// ����Ŀ¼

	// ������� 2 �ڸ�����
	if (!write_file()) return 0;

	map();		// �� 2 �ڸ����ֽ��й�ϣ, �� Map
	calc();		// �� 300 ���ļ��������
	reduce();	// ��� 300 �������ļ��ϲ���һ���ļ�, �� reduce
	if (check()) printf("\r������ȷ!\t\t\t\n\n");
	else printf("\r�������!\t\t\t\n\n");

	system(cmd_del);	// ɾ����ϣ�ļ�
	remove(path);		// ɾ�� 2 �������ļ�
	remove(result);		// ɾ���������ļ�

	return 0;
}
