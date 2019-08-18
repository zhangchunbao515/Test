
// ����һ��ͼƬ, ���������ͨ����ͼƬ

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char UC;

typedef struct		// ppm ��ɫ���ص�, �����ֽ�
{
	UC r;
	UC g;
	UC b;
}ppm_RGB;

// ��̬����һ����ά����
ppm_RGB **new_array(int x, int y)
{
	ppm_RGB **tmp = NULL;

	if (x <= 0 || y <= 0) return NULL;

	tmp = (ppm_RGB **)malloc(x * sizeof(ppm_RGB *));
	for (int i=0; i<x; i++)
		tmp[i] = (ppm_RGB *)malloc(y * sizeof(ppm_RGB));
	return tmp;
}

// �ͷ�һ����ά����
void del_array(ppm_RGB **tmp, int x)
{
	for (int i=0; i<x; i++)
		free(tmp[i]);
	free(tmp);
	tmp = NULL;
}

// �� tmp ͼ��д�� path ��
void write_pic(UC *tmp, char *type, 
			   int h, int w, int maxv, char *path)
{
	FILE *fp = fopen(path, "wb");
	int i, size;

	if (fp == NULL) return ;

	// �ļ�ͷ
	fprintf(fp, "%s\n%d %d\n%d\n", type, w, h, maxv);
	for (i=0, size = w * sizeof(UC); i<h; i++)
	{
		fwrite(tmp + i * w, 1, size, fp);
	}
	fclose(fp);
}

int main(void)
{
	FILE *fp = fopen("test.ppm", "rb");		// ��Ҫһ�� test.ppm ͼ��
	ppm_RGB **data = NULL;		// ԭͼ��
	UC *tmp = NULL;			// RGB�ĻҶ�ͼ
	int width, height;
	int maxv;
	char str[31];
	int i, j;

	if (fp != NULL)
	{
		fscanf(fp, "%s", str);
		if (strcmp(str, "P6") == 0)
		{
			fscanf(fp, "%d", &width);	// ��ȡ��
			fscanf(fp, "%d", &height);	// ��ȡ��
			fscanf(fp, "%d", &maxv);	// ��ȡ����
			data = new_array(height, width);
			if (data != NULL)
			{
				int flag = 1;			// ��ȡ�ֽ���
				for (i=0; i<height && flag; i++)
				{
					// ��Ϊ fread() һ��ֻ�ܶ�ȡ 64KB, ��������һ��һ�ж�
					flag = fread(data[i], 1, width * sizeof(ppm_RGB), fp);
				}
				// ��ȡ���
				tmp = (UC *)malloc(width * height * sizeof(UC));
				int cur;
				if (tmp != NULL)
				{
					for (i=0, cur=0; i<height; i++)
						for (j=0; j<width; j++, cur++)
							*(tmp + cur) = data[i][j].r;	// ��ȡ��ɫ
					write_pic(tmp, "P5", height, width, maxv, "��ɫ�Ҷ�ͼ.ppm");

					for (i=0, cur=0; i<height; i++)
						for (j=0; j<width; j++, cur++)
							*(tmp + cur) = data[i][j].g;
					write_pic(tmp, "P5", height, width, maxv, "��ɫ�Ҷ�ͼ.ppm");

					for (i=0, cur=0; i<height; i++)
						for (j=0; j<width; j++, cur++)
							*(tmp + cur) = data[i][j].b;
					write_pic(tmp, "P5", height, width, maxv, "��ɫ�Ҷ�ͼ.ppm");

					free(tmp);
				}
				else printf("�ڴ����ʧ��!\n");
				del_array(data, height);
			}
			else printf("�ڴ����ʧ��!\n");
		}
		else printf("����P6��ɫͼ��, %s\n", str);
		fclose(fp);
	}
	else printf("�Ҳ��� test.ppm\n");
	return 0;
}