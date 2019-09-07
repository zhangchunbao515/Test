
// ͼ���ֵ�� ostu �㷨�Զ�ȷ����ֵ
// ԭ��� OTSU ȷ����ֵ����

#include <stdio.h>
#include <string.h>
#include <malloc.h>

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

// ��ɫͼת�Ҷ�ͼ
// ת����ʽ : y = 0.299R + 0.587G + 0.114B
void change_gray(IMG *ppm)
{
	int i, j;
	int ww = ppm->width * ppm->byte;
	UC *tmp = (UC *)malloc(ppm->height * ppm->width * sizeof(UC));
	int cur;

	for (i=0, cur=0; i<ppm->height; i++)
		for (j=0; j<ww; j+=3)
		{
			tmp[cur++] = (UC)(0.299 * ppm->data[i * ww + j]
				+ 0.587 * ppm->data[i * ww + j + 1]
				+ 0.114 * ppm->data[i * ww + j + 2]);
		}
	free(ppm->data);	// �ͷ�ԭ����
	ppm->flag = '5';
	ppm->byte = 1;
	ppm->data = tmp;	// �����µ�
}

// ��ͼ�� ppm ���շ�ֵ t ���ж�ֵ��
void threshold(IMG *ppm, UC t)
{
	int i;
	int size = ppm->height * ppm->width * ppm->byte;

	for (i=0; i<size; i++)
	{
		if (ppm->data[i] > t) ppm->data[i] = ppm->maxv;
		else ppm->data[i] = 0;
	}
}

// otsu �㷨����ͼƬ�������ֵ, ������ѷ�ֵ
UC otsu_threshold(IMG *ppm)
{
	if (ppm->flag != '5') return 0;		// ȷ���ǻҶ�ͼ

	int size = ppm->height * ppm->width * ppm->byte;
	ULI *count = (ULI *)malloc((ppm->maxv + 2) * sizeof(ULI));
	UC T = 0;
	int i, t;
	double p1, m1, n1, c1, p2, m2, n2, c2;
	// p1 ��������, m1 ����ƽ���Ҷ�, n1 �����ܻҶ�, c1 �����ܸ���
	double sum, mg, d, maxd;
	// sum ȫͼ�Ҷ���ֵ, mg ȫͼƽ���Ҷ�, d ���෽��, maxd �����෽��

	maxd = -1000000;		// ��ʼ��
	c1 = c2 = n1 = n2 = p1 = p2 = m1 = m2 = sum = mg = d = 0;
	for (i=ppm->maxv; i>=0; i--) count[i] = 0;

	for (i=0; i<size; i++) count[ppm->data[i]]++;	// ͳ��ֱ��ͼ
	for (i=ppm->maxv; i>=0; i--) sum = sum + (count[i] * i);
	mg = sum / size;				// mg ����ȫͼƽ���Ҷ�

	for (t=0; t<ppm->maxv; t++)		// t[0, 254]
	{
		c1 = c1 + count[t];			// ���ظ���
		c2 = size - c1;
		n1 = n1 + (count[t] * t);	// �Ҷ�ֵ����
		n2 = sum - n1;
		if (n1 > 0 && n2 > 0)
		{
			m1 = n1 / c1;		// ƽ���Ҷ�
			m2 = n2 / c2;
			p1 = c1 / size;		// ��������
			p2 = c2 / size;

			// ������෽��
			d = p1 * (m1 - mg) * (m1 - mg) 
				+ p2 * (m2 - mg) * (m2 - mg);
//			d = p1 * p2 * (m1 - m2) * (m1 - m2);	// ��ʽ2
			if (d > maxd)
			{
				maxd = d;
				T = t;		// ��¼��ѷָ�ֵ
			}
		}
	}
	free(count);
	return T;
}

// otsu �㷨��ֵ���Զ�ȷ����ֵ
void otsu(IMG *ppm)
{
	// ��ɫͼ��ת�Ҷ�ͼ
	if (ppm->flag == '6') change_gray(ppm);

	int t = otsu_threshold(ppm);	// otsu ���㷧ֵ
	printf("��ѷ�ֵ: %d\n", t);
	threshold(ppm, t);				// ��ֵ������
}

int main(void)
{
	IMG ppm;
	char path[512];		// ·��

	printf("����ͼƬ·��: ���ͼƬֱ���ϵ���������\n");
	scanf("%s", path);

	if (open_img(&ppm, path))
	{
		otsu(&ppm);
		save_img(&ppm, "��ֵ����.ppm");
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
