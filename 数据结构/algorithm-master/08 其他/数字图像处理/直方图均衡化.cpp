
// �Ҷ�ͼֱ�Ӿ��⻯, ��ɫͼ��R, G, B ���������ֱ���⻯

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
	int  width;		// ��
	int  height;	// ��
	int  maxv;		// �������ֵ
	int  byte;		// ÿ������ռ���ֽ���
	UC   *data;		// ͼ������
}IMG;

int open_img(IMG *ppm, char *path);		// ��
int save_img(IMG *ppm, char *path);		// ����
int close_img(IMG *ppm);				// �ر�

// ���һ���Ҷ�ֱ��ͼ
int hist_1(IMG *img, double *count)
{
	int size = img->height * img->width * img->byte;
	int i;

	// ͳ�����ظ���, ����һ��
	for (i=img->maxv; i>=0; i--) count[i] = 0.0;
	for (i=0; i<size; i++) count[img->data[i]] += 1;
	for (i=img->maxv; i>=0; i--) count[i] /= size;

	return 1;
}

// ֱ��ͼ���⻯, ֻ֧�ֻҶ�ͼ
// 1. �ȼ����һ��ֱ��ͼ, ���ĳһ���Ҷȵ����غܶ�, ��ô�����ֵԽ��
// 2. �����ۻ�ֱ��ͼ, ���ĳһ���Ҷȵĸ���ֵԽ��, ��ô�ۻ������������Ŀ�
// ���仯��Խ��, ���ԻҶ�ӳ������ĻҶ�ֵ��������
// ����ӳ�亯��, Ȼ��Ҷȱ任
void hist(IMG *ppm)
{
	int size = ppm->height * ppm->width * ppm->byte;
	double *count;		// ��һ��ֱ��ͼ
	int i;

	count = (double *)malloc((ppm->maxv + 2) * sizeof(double));
	hist_1(ppm, count);				// ��һ��ֱ��ͼ
	for (i=1; i<=ppm->maxv; i++) 
		count[i] += count[i-1];		// �ۻ�ֱ��ͼ
	for (i=0; i<=ppm->maxv; i++) 
		count[i] = count[i] * (ppm->maxv + 1) - 1;	// ����ӳ�亯��
	for (i=0; i<=ppm->maxv; i++)		// ���Ʒ�Χ
	{
		if (count[i] < 0) count[i] = 0;
		else if (count[i] > 255) count[i] = 255;
	}
	for (i=0; i<size; i++)			 	// ��ԭͼӳ��
		ppm->data[i] = (UC)count[ppm->data[i]];
	free(count);
}

// ֱ��ͼ���⻯, ֧�ֻҶ�ͼ���ɫͼ
int hist_EQ(IMG *ppm)
{
	int i, j, k;

	if (ppm->flag == '5')	// �Ҷ�ͼֱ�Ӵ���
	{
		hist(ppm);
		return 1;
	}
	else if (ppm->flag == '6')	// ��ɫͼ���������ֱ���
	{
		int ww = ppm->width * ppm->byte;
		int cur;
		IMG tmp;
		tmp = *ppm;
		tmp.byte = 1;
		tmp.flag = '5';
		tmp.data = (UC *)malloc(tmp.width * tmp.height * sizeof(UC));
		for (k=0; k<3; k++)
		{
			// һ���������Ƶ� tmp
			for (i=0, cur=0; i<ppm->height; i++)
				for (j=0; j<ww; j+=ppm->byte)
					tmp.data[cur++] = ppm->data[i * ww + j + k];
			hist(&tmp);		// ���⻯

			// ���ǵ�ԭͼ��
			for (i=0, cur=0; i<ppm->height; i++)
				for (j=0; j<ww; j+=ppm->byte)
					ppm->data[i * ww + j + k] = tmp.data[cur++];
		}
		close_img(&tmp);
		return 1;
	}
	return 0;
}

// ����ͼƬƽ����Ϣ��
float E(IMG *ppm)
{
	double *count = (double *)malloc((ppm->maxv + 2) * sizeof(double));
	double avg = 0;
	int i;

	hist_1(ppm, count);		// ��һ��ֱ��ͼ
	for (i=0; i<=ppm->maxv; i++)
	{
		if (count[i] > 0.000000001)
			avg = avg + (-count[i] * log(count[i]));
	}
	free(count);

	return (float)avg;
}

int main(void)
{
	IMG ppm;
	char path[512];		// ·��

	printf("����ͼƬ·��: ���ͼƬֱ���ϵ���������\n");
	scanf("%s", path);

	if (open_img(&ppm, path))
	{
		printf("���⻯ǰƽ����Ϣ��: %f\n", E(&ppm));
		hist_EQ(&ppm);
		printf("���⻯��ƽ����Ϣ��: %f\n", E(&ppm));
		save_img(&ppm, "���⻯��.ppm");
		close_img(&ppm);
	}
	return 0;
}

// ------------------------------------------------------------
// ---------------- ���´��벻�Ǳ�ʵ���ص� --------------------
// ------------------------------------------------------------

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

// �ر�һ��ͼƬ
int close_img(IMG *ppm)
{
	if (ppm->data) free(ppm->data);
	memset(ppm, 0, sizeof(IMG));

	return 0;
}
