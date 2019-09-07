
// ��Ҷ�ֱ��ͼ, ����һ��ͼƬ, ���ֱ��ͼ��CSV�ļ�

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef unsigned char UC;
typedef unsigned long int ULI;

typedef struct		// ppm ͼ��
{
	char type;		// P ��־
	char flag;		// ����
	int  width;		// ��
	int  height;	// ��
	int  maxv;		// �������ֵ
	int  byte;		// ÿ������ռ���ֽ���
	UC   *data;		// ͼ������
}IMG;

ULI *count_r = NULL;
ULI *count_g = NULL;
ULI *count_b = NULL;
ULI *count_all = NULL;

// ��������
int open_img(IMG *ppm, char *path);		// ��ͼƬ
void close_img(IMG *ppm);				// �ر�ͼƬ
void output_ppm(int len);				// �����ͼƬ
void output_csv(int len);				// ����� csv
void output_ppm_rgb(int len);			// �������������ֱ��ͼ

// ��Ҷ�ֱ��ͼ
int imgHist(IMG *img, int *len)
{
	int size = img->height * img->width * img->byte;
	int i;

	for (i=img->maxv + 1; i>=0; i--)
	{
		count_r[i] = 0;
		count_g[i] = 0;
		count_b[i] = 0;
		count_all[i] = 0;
	}
	*len = img->maxv;

	// ͳ�����ظ���
	for (i=0; i<size; i+=3)
	{
		count_r[img->data[i]]++;
		count_g[img->data[i+1]]++;
		count_b[img->data[i+2]]++;
	}
	for (i=img->maxv; i>=0; i--)
	{
		count_all[i] = count_r[i] + count_g[i] + count_b[i];
	}
	return 1;
}

int main(void)
{
	IMG ppm;			// ͼ��
	char path[256];		// ·��
	ULI *count = NULL;	// ����ֱ��ͼ����
	int lenth;			// count �ĳ���

	printf("����ͼƬ·��: ���߰�ͼƬֱ���ϵ����������\n");
	scanf("%s", path);

	// ��ʵ��ֻ�ܴ� P5, P6 �� ppm ͼ
	if (open_img(&ppm, path))
	{
		count_r = (ULI *)malloc((ppm.maxv + 5) * sizeof(ULI));
		count_g = (ULI *)malloc((ppm.maxv + 5) * sizeof(ULI));
		count_b = (ULI *)malloc((ppm.maxv + 5) * sizeof(ULI));
		count_all = (ULI *)malloc((ppm.maxv + 5) * sizeof(ULI));

		imgHist(&ppm, &lenth);	// ��ֱ��ͼ
		output_csv(lenth);		// ��� CSV
		output_ppm(lenth);		// ����ܵ�ֱ��ͼ
		output_ppm_rgb(lenth);	// �������������ֱ��ͼ
	
		free(count_r);
		free(count_g);
		free(count_b);
		free(count_all);

		close_img(&ppm);
	}
	else printf("��ͼƬ����\n");

	return 0;
}

// ---------------------------------------------------------
// -------------- ���´��벻�Ǳ�ʵ���ص� -------------------
// ---------------------------------------------------------

// ���һ�� P6 ��ֱ��ͼ
void output_ppm_rgb(int len)
{
	int MAXN(ULI *count, int len);	// �������Ԫ��
	int maxr = MAXN(count_r, len);
	int maxg = MAXN(count_g, len);
	int maxb = MAXN(count_b, len);
	int num = MAX(maxr, MAX(maxg, maxb));
	const int h = 150;
	const int w = len;
	const int size = h * w * 3 * sizeof(UC);
	FILE *fp = fopen("RGBֱ��ͼ.ppm", "wb");
	UC *data = NULL;
	int i, j;
	
	if (fp != NULL)
	{
		data = (UC *)malloc(size);
		if (data != NULL)
		{
			for (i=0; i<size; i++) data[i] = 0;	// ���ɫ
			for (i=0; i<len; i++)			// ��������
			{
				// ��������ɫ����
				for (j = h - (int)(count_r[i] * h / num); j<h; j++)
					data[j * w * 3 + i * 3] = 0xFF;
				for (j = h - (int)(count_g[i] * h / num); j<h; j++)
					data[j * w * 3 + i * 3 + 1] = 0xFF;
				for (j = h - (int)(count_b[i] * h / num); j<h; j++)
					data[j * w * 3 + i * 3 + 2] = 0xFF;
			}
			fprintf(fp, "%s\n%d\n%d\n%d\n", "P6", w, h, 255);
			for (i=0; i<h; i++)
				fwrite(data + i * w * 3, 1, w * 3, fp);
			free(data);
		}
		fclose(fp);
	}
}

// ���һ�� P4 ��ֱ��ͼ
void output_ppm(int len)
{
	int MAXN(ULI *count, int len);			// �������Ԫ��
	ULI num = MAXN(count_all, len) + 10;	// ֱ��ͼ��ߵ�ֵ
	const int h = 150;						// �߶�
	const int w = len / 8 + 1;				// ���
	unsigned char binary;					// ����
	int i, j, k;
	FILE *fp = fopen("ֱ��ͼ.ppm", "wb");
	UC *data = NULL;

	if (fp != NULL)
	{
		data = (UC *)malloc(h * w * sizeof(UC));
		if (data != NULL)
		{
			memset(data, 0, h * w * sizeof(UC));
			// ��ʼ��
			for (i=0; i<h; i++)
				for (j=0; j<w; j++)
					data[i * w + j] = 0;	// ���ð�ɫ

			// ��ֱ��ͼ
			k = 0;				// ���
			binary = 0x80;		// ���������ұ��� 1
			for (i=0; i<len; i++)		// ���� count
			{
				// �� [0..maxn] �����ظ���ѹ���� [0..150]
				for (j=h - (int)(count_all[i] * h / num); j<h; j++)
				{
					data[j * w + k] |= binary;	// �� 1, ���ɫ
				}
				binary >>= 1;
				if (binary == 0) 
				{
					binary = 0x80;		// ������ 1
					k++;
				}
			}
			// ���浽�ļ�
			fprintf(fp, "%s\n%d\n%d\n", "P4", w * 8, h);
			for (i=0; i<h; i++)
				fwrite(data + i * w, 1, w, fp);
			free(data);
		}
		fclose(fp);
	}
}

int MAXN(ULI *count, int len)	// ���������е����ֵ
{
	int i;
	ULI max = 0;

	for (i=0; i<len; i++)
		if (count[i] > max) max = count[i];
	return (int)max;
}

void output_csv(int len)		// ����� CSV
{
	FILE *fp = fopen("ֱ��ͼ.csv", "wb");
	int i;

	if (fp == NULL) return ;

	for (i=0; i<len; i++)
		fprintf(fp, "%d,%ld,%ld,%ld,%ld\n", 
			i, count_r[i], count_g[i], count_b[i], count_all[i]);

	fclose(fp);
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
		if (ppm->flag == '6')
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
				return 0;
			}
		}
		else ret = 0;
		fclose(fp);
	}
	else ret = 0;

	return ret;
}

// �ر�һ��ͼƬ
void close_img(IMG *ppm)
{
	if (ppm->data) free(ppm->data);
	memset(ppm, 0, sizeof(IMG));
}
