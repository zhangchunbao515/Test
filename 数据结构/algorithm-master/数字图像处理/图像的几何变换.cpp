
// ͼ��ļ��α任
// ���뻷�� VC++6.0, C++����

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#define NUM 192			// ��ͼ�ĻҶ�ֵ
#define PI  3.1415926	// PI
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

const double EPS = 1e-6;				// ���
int open_img(IMG *ppm, char *path);		// ��
int save_img(IMG *ppm, char *path);		// ����
int copy_img(IMG *d, IMG const *s);		// ����
int close_img(IMG *ppm);				// �ر�
int extract_rgb(IMG *ppm, IMG *r, IMG *g, IMG *b);		// ��ȡ RGB ��������
int combine_rgb(IMG *ppm, IMG *r, IMG *g, IMG *b);		// �ϳ� RGB ��������
inline UC calc(IMG *ppm, double old_h, double old_w);	// ˫���Բ�ֵ
inline UC calc2(IMG *ppm, double old_h, double old_w);	// ����ڲ�ֵ


// ----------------------- ͼ��ı任1 ----------------------------
void change1_gray(IMG *ppm, int m)
{
	IMG tmp = *ppm;		// ��ʱͼ��ռ�
	int i, j;
	double old_h, old_w;

	// ����任���С, �����¿ռ�
	tmp.data = (UC *)malloc(tmp.height 
		* tmp.width * tmp.byte * sizeof(UC));
	if (tmp.data == NULL) return ;
	
	int ww = tmp.width * tmp.byte;		// �¿��
	double k = (double)m / ppm->height;
	for (i=0; i<tmp.height; i++)
	{
		for (j=0; j<tmp.width; j++)
		{
			old_h = i;		// ��ʽ������
			old_w = (j-i*k) / (1 - i / (double)ppm->height);
			tmp.data[i * ww + j] = calc(ppm, old_h, old_w);		// ˫���Բ�ֵ
//			tmp.data[i * ww + j] = calc2(ppm, old_h, old_w);	// ����ڲ�ֵ
		}
	}
	copy_img(ppm, &tmp);		// ���ƻ� ppm ��
	close_img(&tmp);
}

// ����, �����Ϊ w0 ��, �����Ϊ h0 ��, �任���� (w0, h0)
void change1(IMG *ppm, int m)
{
	if (ppm->flag == '5')		// �Ҷ�ͼֱ�Ӵ���
	{
		change1_gray(ppm, m);
	}
	else if (ppm->flag == '6')	// ��ɫͼ�����������ֱ���, �ٺϳ�
	{
		IMG r, g, b;
		r.data = g.data = b.data = NULL;	// ��ʼ��
		if (extract_rgb(ppm, &r, &g, &b))	// ��ȡ RGB ��������
		{
			change1_gray(&r, m);
			change1_gray(&g, m);
			change1_gray(&b, m);
			combine_rgb(ppm, &r, &g, &b);	// �ϳ�ԭͼ
			close_img(&r);		// �ͷ��ڴ�
			close_img(&g);
			close_img(&b);
		}
	}
}

// ----------------------- ͼ��ı任2 ----------------------------
void change2_gray(IMG *ppm, int A, int T, int B)
{
	IMG tmp = *ppm;		// ��ʱͼ��ռ�
	int i, j;
	double old_h, old_w;

	// ����任���С, �����¿ռ�
	tmp.height += (2 * A);
	tmp.data = (UC *)malloc(tmp.height 
		* tmp.width * tmp.byte * sizeof(UC));
	if (tmp.data == NULL) return ;
	
	int ww = tmp.width * tmp.byte;		// �¿��
	for (i=0; i<tmp.height; i++)
	{
		for (j=0; j<tmp.width; j++)
		{
			old_h = (i-A) - A * sin(((2.0 * T * PI) / tmp.width) * j + B);
			old_w = j;		// ��ʽ������
			tmp.data[i * ww + j] = calc(ppm, old_h, old_w);		// ˫���Բ�ֵ
//			tmp.data[i * ww + j] = calc2(ppm, old_h, old_w);	// ����ڲ�ֵ
		}
	}
	copy_img(ppm, &tmp);		// ���ƻ� ppm ��
	close_img(&tmp);
}

// ����, �����Ϊ w0 ��, �����Ϊ h0 ��, �任���� (w0, h0)
void change2(IMG *ppm, int A, int T, int B)
{
	if (ppm->flag == '5')		// �Ҷ�ͼֱ�Ӵ���
	{
		change2_gray(ppm, A, T, B);
	}
	else if (ppm->flag == '6')	// ��ɫͼ�����������ֱ���, �ٺϳ�
	{
		IMG r, g, b;
		r.data = g.data = b.data = NULL;	// ��ʼ��
		if (extract_rgb(ppm, &r, &g, &b))	// ��ȡ RGB ��������
		{
			change2_gray(&r, A, T, B);
			change2_gray(&g, A, T, B);
			change2_gray(&b, A, T, B);
			combine_rgb(ppm, &r, &g, &b);	// �ϳ�ԭͼ
			close_img(&r);		// �ͷ��ڴ�
			close_img(&g);
			close_img(&b);
		}
	}
}

int main(void)
{
	IMG ppm, tmp;
	char path[512];		// ·��
	int m, A, T, B;

	printf("����ͼƬ·��: ���ͼƬֱ���ϵ���������\n");
	gets(path);

	if (open_img(&ppm, path))
	{
		tmp.data = NULL;

		// ѡ��ʵ��һ:
		printf("1. ������ 0 �� %d ��һ��ϵ��: ", ppm.width);
		scanf("%d", &m);

		copy_img(&tmp, &ppm);
		change1(&tmp, m);		// �任1
		save_img(&tmp, "�任1.ppm");

		// ѡ��ʵ���: 
		printf("2. ��������� A, ������ T, ���� B, ������ A T B : ");
		scanf("%d %d %d", &A, &T, &B);

		copy_img(&tmp, &ppm);
		change2(&tmp, A, T, B);		// �任2
		save_img(&tmp, "�任2.ppm");
		
/*		for (int i=0, T=1; i<3; i++, T+=T)
		{
			for (A=5, B=0; A<21; A+=5)
			{
				copy_img(&tmp, &ppm);
				change2(&tmp, A, T, B);		// �任2
				sprintf(path, "%d_%d_%d.ppm", T, A, B);
				save_img(&tmp, path);
			}
		}*/
		close_img(&ppm);
		close_img(&tmp);
		printf("�������!\n");
	}
	else printf("�򿪴���!\n");

	return 0;
}

// ------------------------------------------------------------
// ---------------- ���´��벻�Ǳ�ʵ���ص� --------------------
// ------------------------------------------------------------

// ˫���ԻҶȲ�ֵ, (old_h, old_w) ��ԭͼ����
inline UC calc(IMG *ppm, double old_h, double old_w)
{
	int b = ppm->byte;
	int h = (int)old_h;
	int w = (int)old_w;
	int k = ppm->width * ppm->byte;		// һ�е��ֽ���

	if (h < 0 || w < 0 || h > ppm->height - 1 || w > ppm->width - 1)
		return NUM;		// Խ���˷��� 128 �Ҷ�ֵ

	// �ĵ������ (h, w), (h+1, w), (h, w+b), (h+1, w+b)
	double left = (1.0 - (old_h - h)) * (int)ppm->data[h * k + w] 
		+ (1.0 - (h + 1.0 - old_h)) * (int)ppm->data[(h + 1) * k + w];
	double right = (1.0 - (old_h - h)) * (int)ppm->data[h * k + w + b] 
		+ (1.0 - (h + 1.0 - old_h)) * (int)ppm->data[(h + 1) * k + w + b];
	return (UC)((1.0 - (old_w - w)) * left + (1.0 - (w + 1.0 - old_w)) * right);
/*
	return (UC)((1.0 - (old_w - w)) * ((1.0 - (old_h - h)) 
		* (int)ppm->data[h * k + w] + (1.0 - (h + 1.0 - old_h)) 
		* (int)ppm->data[(h + 1) * k + w]) + (1.0 - (w + 1.0 - old_w)) 
		* ((1.0 - (old_h - h)) * (int)ppm->data[h * k + w + b] 
		+ (1.0 - (h + 1.0 - old_h)) * (int)ppm->data[(h + 1) * k + w + b]));
*/
}

// �ٽ����ֵ, ��������ĵ�, ��Ϊ��ֵ
inline UC calc2(IMG *ppm, double old_h, double old_w)
{
	int b = ppm->byte;
	int h = (int)old_h;
	int w = (int)old_w;
	int k = ppm->width * ppm->byte;		// һ�е��ֽ���

	if (h < 0 || w < 0 || h > ppm->height - 1 || w > ppm->width - 1)
		return NUM;		// Խ���˷��� 128 �Ҷ�ֵ

	if ((old_h - h) > (h + 1.0 - old_h))	// �� h+1 �������
	{
		if ((old_w - w) > (w + 1.0 - old_w))	// �� w+1 ��
			return ppm->data[(h + 1) * k + w + b];
		else return ppm->data[(h + 1) * k + w];
	}
	else	// �� h �������
	{
		if ((old_w - w) > (w + 1.0 - old_w))	// �� w+1 ��
			return ppm->data[h * k + w + b];
		else return ppm->data[h * k + w];
	}
	return NUM;
}

// ��ȡ RGB ���������� r, g, b, ��� r �����ݻᱻ�ͷŵ�
int extract_rgb(IMG *ppm, IMG *r, IMG *g, IMG *b)
{
	if (ppm == NULL) return 0;

	if (r->data != NULL) free(r);	// �ͷ�ԭ����
	if (g->data != NULL) free(g);
	if (b->data != NULL) free(b);
	*r = *g = *b = *ppm;
	r->byte = g->byte = b->byte = 1;
	r->flag = g->flag = b->flag = '5';

	int new_size = r->height * r->width * r->byte * sizeof(UC);
	r->data = (UC *)malloc(new_size);	// ����ռ�
	g->data = (UC *)malloc(new_size);
	b->data = (UC *)malloc(new_size);

	int i, j, top;
	int ww = ppm->width * ppm->byte;
	for (i=0, top=0; i<ppm->height; i++)	// ����
	{
		for (j=0; j<ww; j+=3, top++)
		{
			r->data[top] = ppm->data[i * ww + j];
			g->data[top] = ppm->data[i * ww + j + 1];
			b->data[top] = ppm->data[i * ww + j + 2];
		}
	}
	return 1;
}

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
