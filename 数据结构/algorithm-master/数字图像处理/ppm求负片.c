
// ��Ƭ: �Ҷ�ֵ = �������ֵ - �Ҷ�ֵ

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
	UC   *data;		// ͼ������
}img;

// ��ȡһ��ͼƬ, ֻ�ܶ�ȡ�Ҷ�ͼ�Ͳ�ɫͼ
int open_img(img *ppm, char *path)
{
	FILE *fp = fopen(path, "rb");
	int size;		// ÿ�����ش�С
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
		if (ppm->flag == '2' || ppm->flag == '5')
		{
			// �Ҷ�ͼ��, һ���ֽ�
			ppm->data = (UC *)malloc(w * h);
			size = 1;
		}
		else if (ppm->flag == '3' || ppm->flag == '6')
		{	
			// ��ɫͼ��, �����ֽ�
			ppm->data = (UC *)malloc(w * h * 3);
			size = 3;
		}
		else ret = 0;

		// ��ȡ����
		if (ret != 0 && ppm->data != NULL)
		{
			// ��ȡ����, fread() һ��ֻ�ܶ��� 64KB ������, ����ֶζ�
			for (i=0, f=1; i<h && f!=0; i++)
			{
				f = fread(ppm->data + i * w * size, 1, w * size, fp);
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
int write_img(img *ppm, char *path)
{
	FILE *fp = fopen(path, "wb");
	int w = ppm->width;
	int h = ppm->height;
	int size;
	int i, f;

	if (fp == NULL) return 0;

	// д�� ppm ͷ
	fprintf(fp, "%c%c\n%d\n%d\n%d\n", 
		ppm->type, ppm->flag, w, h, ppm->maxv);
	// д��ͼ������
	if (ppm->flag == '2' || ppm->flag == '5') size = 1;
	else size = 3;
	for (i=0, f=1; i<h && f!=0; i++)
	{
		f = fwrite(ppm->data + i * w * size, 1, w * size, fp);
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

void fupian(img *ppm)		// ��Ƭ
{
	int size;	// ͼ�������ֽ���
	int i;

	size = ppm->height * ppm->width;
	if (ppm->flag == '6') size *= 3;

	for (i=0; i<size; i++)
	{
		ppm->data[i] = ppm->maxv - ppm->data[i];
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
		if (ppm.type == 'P')
		{
			if (ppm.flag == '6' || ppm.flag == '5')
			{
				fupian(&ppm);	// ��Ƭ
				write_img(&ppm, "��Ƭ.ppm");
			}
			else printf("ͼ�����\n");
		}
		else printf("���� pmm ͼ��\n");
		close_img(&ppm);
	}
	else printf("�Ҳ�����ͼƬ\n");

	return 0;
}