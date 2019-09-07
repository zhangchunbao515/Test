
// α��ɫ����
// ���뻷�� VC++6.0, C++����

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

typedef unsigned char UC;
typedef unsigned long int ULI;

typedef struct		// ppm ͼ��
{
	char type;		// P ��־
	char flag;		// ����
	char byte;		// ÿ������ռ���ֽ���
	int  width;		// ��
	int  height;	// ��
	int  maxv;		// �������ֵ
	UC   *data;		// ͼ������
}IMG;

UC LUT_R[256];		// RGB ��ӳ�亯��
UC LUT_G[256];
UC LUT_B[256];

int open_img(IMG *ppm, char *path);		// ��
int save_img(IMG *ppm, char *path);		// ����
int copy_img(IMG *d, IMG const *s);		// ����
int close_img(IMG *ppm);				// �ر�
int combine_rgb(IMG *ppm, IMG *r, IMG *g, IMG *b);	// �ϳ� RGB ��������

// �Ҷ�ӳ��
void change_gray(IMG *ppm, UC *LUT)
{
	int size = ppm->height * ppm->width * ppm->byte;
	int i;

	for (i=0; i<size; i++) ppm->data[i] = LUT[ppm->data[i]];
}

// α��ɫ����
int change_color(IMG *ppm)
{
	IMG rgb[3];		// RGB ��������
	int i;

	if (ppm == NULL || ppm->data == NULL || ppm->flag != '5')
		return 0;

	// �� ppm ��������, Ҳ���Ը���һ�ݴ���һ��, ��ʡһЩ�ռ�
	for (i=0; i<3; i++) rgb[i].data = NULL;
	for (i=0; i<3; i++) copy_img(rgb + i, ppm);
	
	change_gray(rgb + 0, LUT_R);	// �ֱ�Ҷ�ӳ��
	change_gray(rgb + 1, LUT_G);
	change_gray(rgb + 2, LUT_B);

	combine_rgb(ppm, rgb + 0, rgb + 1, rgb + 2);	// �ϳɲ�ɫͼ

	return 1;
}

void init_LUT(void)		// ��ʼ��ӳ�亯��
{
	int i;

	for (i=0; i<256; i++) 
	{
		LUT_R[i] = (UC)i;			// �����
		LUT_B[i] = (UC)(255 - i);	// ������
	}
	for (i=0; i<128; i++) LUT_G[i] = (UC)(2 * i);	// �̷���
	for (i=128; i<256; i++) LUT_G[i] = (UC)(2 * (255 - i));

	for (i=0; i<256; i++)
		printf("%u\t%u\t%u\n", LUT_R[i], LUT_G[i], LUT_B[i]);
}

int main(void)
{
	IMG ppm;
	char path[512];		// ·��

	printf("����ͼƬ·��: ���ͼƬֱ���ϵ���������\n");
	gets(path);

	if (open_img(&ppm, path))
	{
		init_LUT();		// ��ʼ��ӳ�亯��
		if (change_color(&ppm))
		{
			save_img(&ppm, "α��ɫ�任.ppm");
			printf("�������!\n");
		}
		else printf("�Ѿ��ǲ�ɫͼ��!\n");
		close_img(&ppm);
	}
	else printf("�򿪴���!\n");

	return 0;
}

// ------------------------------------------------------------
// ---------------- ���´��벻�Ǳ�ʵ���ص� --------------------
// ------------------------------------------------------------

// �ϳ� RGB ��������, ��ȷ�� r, g, b, ��Сһ��
int combine_rgb(IMG *ppm, IMG *r, IMG *g, IMG *b)
{
	if (r == NULL || g == NULL || b == NULL) return 0;
	if (ppm->data) free(ppm->data);		// �ͷ�ԭ����

	ppm->type = 'P';
	ppm->flag = '6';
	ppm->maxv = 255;
	ppm->height = r->height;
	ppm->width = r->width;
	ppm->byte = 3;
	ppm->data = (UC *)malloc(ppm->height 
		* ppm->width * ppm->byte * sizeof(UC));

	int i, j, top;
	int ww = ppm->width * ppm->byte;
	for (i=0, top=0; i<ppm->height; i++)	// �ϳ�
	{
		for (j=0; j<ww; j+=3, top++)
		{
			ppm->data[i * ww + j] = r->data[top];
			ppm->data[i * ww + j + 1] = g->data[top];
			ppm->data[i * ww + j + 2] = b->data[top];
		}
	}
	return 1;
}

// ��ȡһ��ͼƬ, ֻ�ܶ�ȡ�Ҷ�ͼ�Ͳ�ɫͼ
int open_img(IMG *ppm, char *path)
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
		if (ppm->flag == '5')
		{
			ppm->data = (UC *)malloc(w * h * sizeof(UC));
			ppm->byte = 1;
		}
		else if (ppm->flag == '6')
		{
			ppm->data = (UC *)malloc(w * h * 3 * sizeof(UC));
			ppm->byte = 3;
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
				ret = 0;
			}
		}
		else ret = 0;
		fclose(fp);
	}
	else ret = 0;

	return ret;
}

// д��һ��ͼƬ
int save_img(IMG *ppm, char *path)
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
	fclose(fp);

	return 1;
}

int copy_img(IMG *d, IMG const *s)		// ����
{
	if (d == NULL || s == NULL) return 0;

	if (d->data != NULL) free(d->data);		// �ͷ�ԭ����ͼ��
	*d = *s;								// ���Ƴ�Ա
	int size = s->height * s->width * s->byte;
	d->data = (UC *)malloc(size * sizeof(UC));

	for (int i=0; i<size; i++)
		d->data[i] = s->data[i];	// ����ͼ������
	return 0;
}

// �ر�һ��ͼƬ
int close_img(IMG *ppm)
{
	if (ppm->data) free(ppm->data);
	memset(ppm, 0, sizeof(IMG));

	return 0;
}
