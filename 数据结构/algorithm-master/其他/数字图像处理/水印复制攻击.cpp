
// ���뻷�� VC++6.0, C++����

#include <stdio.h>
#include <string.h>
#include <malloc.h>

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

int open_img(IMG *ppm, char *path);		// ��, ֧�� p4, p5, p6 ͼ
int save_img(IMG *ppm, char *path);		// ����, ֧�� p4, p5, p6 ͼ
int copy_img(IMG *d, IMG const *s);		// ����, ֧�� p4, p5, p6 ͼ
int close_img(IMG *ppm);				// �ر�
int extract_bit(IMG *d, IMG const *s, int bit);		// ��ȡ����
int update_bit(IMG *d, IMG const *s, int bit);		// �ϳɱ���

int main(void)
{
	IMG ppm, tmp, ppm2;
	char path[512];		// ·��
	int i;

	printf("������ˮӡͼƬ·��: ���ͼƬֱ���ϵ���������\n");
	gets(path);

	tmp.data = ppm.data = ppm2.data = NULL;		// ��ʼ��
	if (open_img(&ppm, path))
	{
		printf("������ˮӡ��ͼƬ: \n");
		gets(path);
		if (open_img(&ppm2, path))
		{
			for (i=0; i<3; i++)		// ��ǰ 3 �����ؼӵ���ˮӡ��ͼƬ��
			{
				extract_bit(&tmp, &ppm, i);
				update_bit(&ppm2, &tmp, i);
			}
			save_img(&ppm2, "��ˮӡ��lena�����.ppm");
			close_img(&ppm2);
			printf("�������!\n");
		}
		close_img(&ppm);
		close_img(&tmp);
	}
	else printf("�򿪴���!\n");

	return 0;
}

// ------------------------------------------------------------
// ---------------- ���´��벻�Ǳ�ʵ���ص� --------------------
// ------------------------------------------------------------

// d �ǽ��ͼ��(��ֵ), s �ǻҶ�ͼ, ��ȡ�� bit ������
int extract_bit(IMG *d, IMG const *s, int bit)		// ��ȡ����
{
	UC b = 1;		// ��ȡλ��ģ��
	UC tmp;
	int i, j, size;
	int top = 0;	// s ͼ����±�

	if (d == NULL || s == NULL || s->data == NULL 
		|| bit < 0 || bit > 7) return 0;

	if (d->data) free(d->data);		// �ͷ�ԭ����ͼ��
	*d = *s;
	d->flag = '4';
	d->byte = 8;
	d->maxv = 1;
	d->data = (UC *)malloc(d->height * (d->width / d->byte) * sizeof(UC));

	b <<= bit;		// ��ȡģ��
	size = d->height * d->width / d->byte;
	for (i=0; i<size; i++)
	{
		for (j=0, tmp=0; j<8; j++)
		{
			tmp <<= 1;		// tmp һ�ηŰ˸����صı���
			if ((s->data[top++] & b) != 0) tmp |= 1;
		}
		d->data[i] = tmp;
	}
	return 1;
}

// �� d ���صĵ� i �������޸�Ϊ s , Ҫ�� s �Ƕ�ֵͼ��, ��С�� d ���
int update_bit(IMG *d, IMG const *s, int bit)		// �ϳɱ���
{
	if (d == NULL || s == NULL || s->data == NULL
		|| d->height != s->height 
		|| d->width != s->width
		|| s->flag != '4') return 0;

	int i, size;
	int top;		// s ���±�
	UC j = 0x80;	// ���ұ��� 1
	UC b1 = 1;		// ���Ϊ 1
	UC b0;			// ���Ϊ 0

	b1 <<= bit;		// ��ȡλ��ģ�� 0000 0001
	b0 = ~b1;		// ȡ����       1111 1110
	size = d->height * d->width * d->byte;
	for (top=i=0, j=0x80; i<size; i++)
	{
		if (s->data[top] & j)
			d->data[i] |= b1;
		else 
			d->data[i] &= b0;
		// j++
		j >>= 1;
		if (j == 0)		// �˸�����ѭ������
		{
			j = 0x80;
			top++;
		}
	}
	return 1;
}

// ��ȡһ��ͼƬ, ֻ�ܶ�ȡ�Ҷ�ͼ�Ͳ�ɫͼ
int open_img(IMG *ppm, char *path)
{
	FILE *fp = fopen(path, "rb");
	int ret = 1;	// ����ֵ
	int f = 1;
	int w, h, i;

	if (fp != NULL)
	{
		ppm->type = fgetc(fp);
		ppm->flag = fgetc(fp);
		fgetc(fp);		// ����ո�
		fscanf(fp, "%d", &(ppm->width));
		fgetc(fp);
		fscanf(fp, "%d", &(ppm->height));
		fgetc(fp);
		if (ppm->flag == '5' || ppm->flag == '6')
		{
			fscanf(fp, "%d", &(ppm->maxv));
			fgetc(fp);
		}
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
		else if (ppm->flag == '4')
		{
			ppm->data = (UC *)malloc(h * (w / 8) * sizeof(UC));
			ppm->byte = 8;
		}
		else ret = 0;

		// ��ȡ����
		if (ret != 0 && ppm->data != NULL)
		{
			if (ppm->flag == '5' || ppm->flag == '6')
			{
				// ��ȡ����, fread() һ��ֻ�ܶ��� 64KB ������, ����ֶζ�
				for (i=0, f=1; i<h && f!=0; i++)
					f = fread(ppm->data + i * w * ppm->byte, 1, w * ppm->byte, fp);
			}
			else if (ppm->flag == '4')
			{
				int ww = ppm->width / ppm->byte;
				for (i=0, f=1; i<h && f!=0; i++)
					f = fread(ppm->data + i * ww, 1, ww, fp);
			}
			else ret = 0;

			if (f == 0)		// һ�������ݶ�ȡʧ��
			{
				free(ppm->data);
				ret = 0;
			}
		}
		else ret = 0;
		fclose(fp);		// �ر��ļ�
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
	int ret = 1;

	if (fp == NULL) return 0;

	if (ppm->flag == '5' || ppm->flag == '6')
	{
		// д�� ppm ͷ
		fprintf(fp, "%c%c\n%d\n%d\n%d\n", 
			ppm->type, ppm->flag, w, h, ppm->maxv);

		// д��ͼ������
		for (i=0, f=1; i<h && f!=0; i++)
			f = fwrite(ppm->data + i * w * ppm->byte, 1, w * ppm->byte, fp);

		if (f == 0) ret = 0;	// д�����
	}
	else if (ppm->flag == '4')
	{
		// д�� ppm ͷ
		fprintf(fp, "%c%c\n%d\n%d\n", 
			ppm->type, ppm->flag, w, h);

		// д��ͼ������
		int ww = w / ppm->byte;
		for (i=0, f=1; i<h && f!=0; i++)
			f = fwrite(ppm->data + i * ww, 1, ww, fp);

		if (f == 0) ret = 0;	// д�����
	}
	else ret = 0;
	fclose(fp);		// �ǵùر�

	return ret;
}

int copy_img(IMG *d, IMG const *s)		// ����
{
	if (d == NULL || s == NULL) return 0;

	if (d->data != NULL) free(d->data);		// �ͷ�ԭ����ͼ��
	*d = *s;								// ���Ƴ�Ա
	int size = s->height * s->width;

	if (s->flag == '5' || s->flag == '6')
		size *= s->byte;
	else if (s->flag == '4')
		size /= s->byte;

	d->data = (UC *)malloc(size * sizeof(UC));

	// ����ͼ������
	for (int i=0; i<size; i++) d->data[i] = s->data[i];

	return 0;
}

// �ر�һ��ͼƬ
int close_img(IMG *ppm)
{
	if (ppm->data) free(ppm->data);
	memset(ppm, 0, sizeof(IMG));

	return 0;
}
