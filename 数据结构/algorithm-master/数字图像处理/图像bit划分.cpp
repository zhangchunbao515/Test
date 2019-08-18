
// һ�����س����ÿ��λ����, ����µ�ͼ��

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef unsigned char UC;

typedef struct		// ppm ͼ��
{
	char type;		// P ��־
	char flag;		// ����
	int  width;		// ��
	int  height;	// ��
	int  maxv;		// �������ֵ
	int  byte;		// һ������ռ���ֽ���
	UC   *data;		// ͼ������
}img;

int open_img(img *ppm, char *path);		// ��
int save_img(img *ppm, char *path);		// ����
int copy_img(img *d, img *s);			// ����ͼƬ
void close_img(img *ppm);				// �ر�

void output_8bit(img *ppm)		// �������ͼƬ
{
	int size = ppm->height * ppm->width * ppm->byte;
	unsigned char b;	// ����
	img tmp;
	int i, j;
	char path[50];

	for (i=0, b=0x80; i<8; i++, b>>=1)
	{
		copy_img(&tmp, ppm);	// ����һ���µ�
		for (j=0; j<size; j++)
			tmp.data[j] &= b;	// ������������
		sprintf(path, "%d.ppm", i);
		save_img(&tmp, path);	// ����
		close_img(&tmp);
	}
}

int main(void)
{
	img ppm;
	char path[256];

	printf("����ͼƬ·��: ");
	scanf("%s", path);

	if (open_img(&ppm, path))
	{
		output_8bit(&ppm);
		close_img(&ppm);
	}
	else printf("��ͼƬ����\n");

	return 0;
}

int copy_img(img *d, img *s)	// ����ͼƬ
{
	int size = s->height * s->width * s->byte * sizeof(UC);

	if (d == NULL || s == NULL) return 0;

	*d = *s;
	d->data = (UC *)malloc(size);		// ����ռ�
	if (d->data == NULL) return 0;

	memcpy(d->data, s->data, size);		// ����ͼ��

	return 1;
}

// ��ȡһ��ͼƬ, ֻ�ܶ�ȡ�Ҷ�ͼ�Ͳ�ɫͼ
int open_img(img *ppm, char *path)
{
	FILE *fp = fopen(path, "rb");
	int ret = 1;	// ����ֵ
	int w, h;
	int i, f;

	if (fp != NULL)
	{
		ppm->type = fgetc(fp);
		ppm->flag = fgetc(fp);
		fgetc(fp);		// ����ո�
		fscanf(fp, "%d", &(ppm->width));
		fgetc(fp);
		fscanf(fp, "%d", &(ppm->height));
		fgetc(fp);
		fscanf(fp, "%d", &(ppm->maxv));
		fgetc(fp);

		// �����ڴ�ռ�
		w = ppm->width;
		h = ppm->height;
		if (ppm->type == 'P')
		{
			if (ppm->flag == '2' || ppm->flag == '5')
			{
				// �Ҷ�ͼ��, һ���ֽ�
				ppm->data = (UC *)malloc(w * h * sizeof(UC));
				ppm->byte = 1;
			}
			else if (ppm->flag == '3' || ppm->flag == '6')
			{	
				// ��ɫͼ��, �����ֽ�
				ppm->data = (UC *)malloc(w * h * 3 * sizeof(UC));
				ppm->byte = 3;
			}
			else ret = 0;
		}
		else ret = 0;

		// ��ȡ����
		if (ret != 0 && ppm->data != NULL)
		{
			// ��ȡ����, fread() һ��ֻ�ܶ��� 64KB ������, ����ֶζ�
			for (i=0, f=1; i<h && f!=0; i++)
			{
				f = fread(ppm->data + i * w * ppm->byte, 1, w * ppm->byte, fp);
			}
			if (f == 0)		// һ�������ݶ�ȡʧ��
			{
				free(ppm->data);
				return 0;
			}
		}
		else ret = 0;
		fclose(fp);
	}
	else ret = 0;

	return ret;
}

// д��һ��ͼƬ
int save_img(img *ppm, char *path)
{
	FILE *fp = fopen(path, "wb");
	int w = ppm->width;
	int h = ppm->height;
	int i, f;

	if (fp == NULL) return 0;

	// д�� ppm ͷ
	fprintf(fp, "%c%c\n%d\n%d\n%d\n", 
		ppm->type, ppm->flag, w, h, ppm->maxv);

	// д��ͼ������
	for (i=0, f=1; i<h && f!=0; i++)
	{
		f = fwrite(ppm->data + i * w * ppm->byte, 1, w * ppm->byte, fp);
	}
	if (f == 0) return 0;	// д�����

	return 1;
}

// �ر�һ��ͼƬ
void close_img(img *ppm)
{
	if (ppm->data) free(ppm->data);
	memset(ppm, 0, sizeof(img));
}
