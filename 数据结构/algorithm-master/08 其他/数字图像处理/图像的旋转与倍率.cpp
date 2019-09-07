
// ͼ�����ת�뱶��, ԭ�������
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
int extract_rgb(IMG *ppm, IMG *r, IMG *g, IMG *b);	// ��ȡ RGB ��������
int combine_rgb(IMG *ppm, IMG *r, IMG *g, IMG *b);	// �ϳ� RGB ��������


// ----------------------����---------------------------
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

// �Ҷ�ͼ�ı���
void change_size_gray(IMG *ppm, double h, double w)
{
	IMG tmp = *ppm;		// ��ʱͼ��ռ�
	int i, j;
	double old_h, old_w;

	// ���ʲ�Ϊ 1, ��任
	if ((h-1) > EPS || (w-1) > EPS || (1-h) > EPS || (1-w) > EPS)
	{
		// ����任���С, �����¿ռ�
		tmp.height = (int)(ppm->height * h);
		tmp.width = (int)(ppm->width * w);
		tmp.data = (UC *)malloc(tmp.height 
			* tmp.width * tmp.byte * sizeof(UC));
		if (tmp.data == NULL) return ;

		int ww = tmp.width * tmp.byte;		// �¿��
		for (i=0; i<tmp.height; i++)
		{
			for (j=0; j<tmp.width; j++)
			{
				old_h = i * (1 / h);
				old_w = j * (1 / w);
				tmp.data[i * ww + j] = calc(ppm, old_h, old_w);		// ˫���Բ�ֵ
//				tmp.data[i * ww + j] = calc2(ppm, old_h, old_w);	// ����ڲ�ֵ
			}
		}
		copy_img(ppm, &tmp);		// ���ƻ� ppm ��
		close_img(&tmp);
	}
}

// ����, �����Ϊ w0 ��, �����Ϊ h0 ��, �任���� (w0, h0)
void change_size(IMG *ppm, double h, double w)
{
	if (ppm->flag == '5')		// �Ҷ�ͼֱ�Ӵ���
	{
		change_size_gray(ppm, h, w);
	}
	else if (ppm->flag == '6')	// ��ɫͼ�����������ֱ���, �ٺϳ�
	{
		IMG r, g, b;

		r.data = g.data = b.data = NULL;	// ��ʼ��
		if (extract_rgb(ppm, &r, &g, &b))	// ��ȡ RGB ��������
		{
			// ��������������̼߳ӿ촦���ٶ�
			change_size_gray(&r, h, w);
			change_size_gray(&g, h, w);
			change_size_gray(&b, h, w);

			combine_rgb(ppm, &r, &g, &b);	// �ϳ�ԭͼ

			close_img(&r);		// �ͷ��ڴ�
			close_img(&g);
			close_img(&b);
		}
	}
}


// ----------------��ת a �Ƕ�, ��ת���� (w0, h0)-----------------

// ����ԭ��������, �����������
inline void old_to_new(double h, double h0, double w0, 
					   double old_h, double old_w, 
					   double *new_h, double *new_w)
{
	*new_h = (old_w - w0) * sin(h) + (old_h - h0) * cos(h) + h0;
	*new_w = (old_w - w0) * cos(h) - (old_h - h0) * sin(h) + w0;
}

// �Ҷ�ͼ����ת
// �ȼ������ĸ�����, �������ͼƬ�Ĵ�С, Ȼ��ƽ�Ƶ�ͼƬ���м���
void change_degree_gray(IMG *ppm, double a)
{
	IMG tmp = *ppm;				// ��ʱͼ��ռ�
	double hu = a * PI / 180;	// ����
	double new_h[4], new_w[4];	// ��ͼ���ĵ�����
	int h = ppm->height;
	int w = ppm->width;
	int h0 = ppm->height / 2;	// ��ת���� (h0, w0)
	int w0 = ppm->width / 2;
	int i, j, ii, jj;

	// ����任����ĸ���������
	old_to_new(hu, h0, w0, 0, 0, new_h + 0, new_w + 0);
	old_to_new(hu, h0, w0, 0, w-1, new_h + 1, new_w + 1);
	old_to_new(hu, h0, w0, h-1, w-1, new_h + 2, new_w + 2);
	old_to_new(hu, h0, w0, h-1, 0, new_h + 3, new_w + 3);
//	for (i=0; i<4; i++) printf("%lf, %lf\n", new_h[i], new_w[i]);

	// ����任���С, �����¿ռ�
	double max_h, min_h, max_w, min_w;
	min_h = max_h = new_h[0];
	max_w = min_w = new_w[0];
	for (i=1; i<4; i++)			// �ҳ���ֵ
	{
		if (new_h[i] < min_h) min_h = new_h[i];
		if (new_h[i] > max_h) max_h = new_h[i];
		if (new_w[i] < min_w) min_w = new_w[i];
		if (new_w[i] > max_w) max_w = new_w[i];
	}
	tmp.height = (int)(max_h - min_h + 1);		// �¸߶� maxh - minh
	tmp.width = (int)(max_w - min_w + 1);
	tmp.data = (UC *)malloc(tmp.height * tmp.width * tmp.byte * sizeof(UC));
	if (tmp.data == NULL) return ;

	// �ҶȲ�ֵ
	int ww = tmp.width * tmp.byte;
	double old_h, old_w;
	// ii �� [min_h, max_h] ��ѭ��, �и���
	// jj �� [min_w, max_w] ��ѭ��
	// i, j����ͼ���ѭ��
	for (i=0, ii=(int)min_h; i<tmp.height; i++, ii++)
	{
		for (j=0, jj=(int)min_w; j<tmp.width; j++, jj++)
		{
			old_h = (ii - h0) * cos(hu) - (jj - w0) * sin(hu) + h0;
			old_w = (jj - w0) * cos(hu) + (ii - h0) * sin(hu) + w0;
			tmp.data[i * ww + j] = calc(ppm, old_h, old_w);		// ˫���Բ�ֵ
//			tmp.data[i * ww + j] = calc2(ppm, old_h, old_w);	// ����ڲ�ֵ
		}
	}
	copy_img(ppm, &tmp);		// ���ƻ� ppm ��
	close_img(&tmp);
}

// ��ת a �� , a �� [0, 360] ��֮��
void change_degree(IMG *ppm, double a)
{
	if (ppm->flag == '5')		// �Ҷ�ͼֱ�Ӵ���
	{
		change_degree_gray(ppm, a);
	}
	else if (ppm->flag == '6')	// ��ɫͼ�����������ֱ���, �ٺϳ�
	{
		IMG r, g, b;

		r.data = g.data = b.data = NULL;	// ��ʼ��
		if (extract_rgb(ppm, &r, &g, &b))	// ��ȡ RGB ��������
		{
			// ��������������̼߳ӿ촦���ٶ�
			change_degree_gray(&r, a);
			change_degree_gray(&g, a);
			change_degree_gray(&b, a);

			combine_rgb(ppm, &r, &g, &b);	// �ϳ�ԭͼ

			close_img(&r);		// �ͷ��ڴ�
			close_img(&g);
			close_img(&b);
		}
	}
}

int main(void)
{
	IMG ppm;
	char path[512];		// ·��
	double a, h, w;

	printf("����ͼƬ·��: ���ͼƬֱ���ϵ���������\n");
	gets(path);

	if (open_img(&ppm, path))
	{
		printf("��ת a ��[0, 360], h ����, w ����, ����a, h, w: ");
		scanf("%lf %lf %lf", &a, &h, &w);

		change_size(&ppm, h, w);	// ����
		change_degree(&ppm, a);		// ��ת

		save_img(&ppm, "result.ppm");
		close_img(&ppm);
		printf("�������!\n");
	}
	else printf("�򿪴���!\n");

	return 0;
}

// ------------------------------------------------------------
// ---------------- ���´��벻�Ǳ�ʵ���ص� --------------------
// ------------------------------------------------------------

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
