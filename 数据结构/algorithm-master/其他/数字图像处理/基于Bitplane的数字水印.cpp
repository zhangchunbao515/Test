
// �������ṩд��ˮӡ, ��ȡˮӡ, ���ˮӡ�Ĺ���
// ˮӡ�� bitplane ����Ƕ��, ��ϸ��Ƽ�����
// ���뻷�� VC++6.0, C++����

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef unsigned char UC;
typedef unsigned long int ULI;
typedef struct		// ppm ͼ��ṹ��
{
	char type;		// P ��־
	char flag;		// ����
	char byte;		// ÿ������ռ���ֽ���
	int  width;		// ��
	int  height;	// ��
	int  maxv;		// �������ֵ
	UC   *data;		// ͼ������
}IMG;

const char *const WATER = "+-:";	// ˮӡ��ʼ��־

int open_img(IMG *ppm, char *path);						// �� P4, P5, P6 �Կ�
int save_img(IMG *ppm, char *path);						// ����
int copy_img(IMG *d, IMG const *s);						// ����
int close_img(IMG *ppm);								// �ر�
int extract_bit(IMG *d, IMG const *s, int bit);			// ��ȡ����
int update_bit(IMG *d, IMG const *s, int bit);			// �ϳɱ���
int extract_rgb(IMG *ppm, IMG *r, IMG *g, IMG *b);		// ��ȡ RGB ��������
int combine_rgb(IMG *ppm, IMG *r, IMG *g, IMG *b);		// �ϳ� RGB ��������
int read_watermaking(IMG *ppm, char *data);				// ��ȡˮӡ
int write_watermaking(IMG *ppm, char *data, char c);	// д��ˮӡ
int clear_watermaking(IMG *ppm);						// ���ˮӡ
ULI calc_size(IMG *ppm);								// ������д����ֽ���
int check(char *data, ULI size);						// �Ϸ����
int display_menu(IMG *ppm);								// ��ʾ�˵�


int main(void)
{
	IMG ppm;			// ͼ��
	char path[512];		// ·��

	printf("����ͼƬ·��: ���ͼƬֱ���ϵ���������\n");
	gets(path);
	if (open_img(&ppm, path))
	{
		display_menu(&ppm);		// ��ʾ�˵�������
		close_img(&ppm);		// �ǵùر�
	}
	else printf("�򿪴���!\n");

	return 0;
}

// ------------------------------------------------------------
// -------------------- ˮӡ��صĺ��� ------------------------
// ------------------------------------------------------------

// ��ȡˮӡ, ��ȡ�� data �� 
int read_watermaking(IMG *ppm, char *data)	
{
	IMG bit, r, g, b;
	int i, times, top;
	char *cur, *end;	// ����ˮӡ��ָ��

	if (ppm == NULL || data == NULL) return 0;

	bit.data = r.data = g.data = b.data = NULL;
	if (ppm->flag == '5')
	{
		copy_img(&b, ppm);
	}
	else if (ppm->flag == '6')
	{
		extract_rgb(ppm, &r, &g, &b);	// ��ȡ��������
		close_img(&r);
		close_img(&g);
	}
	else return 0;

	for (i=0; i<3; i++)		// �� 0-2 ������Ѱ��ˮӡ
	{
		extract_bit(&bit, &b, i);
		bit.data[bit.height * (bit.width / bit.byte) - 1] = '\0';
		times = 0;
		cur = (char *)bit.data;
		while (1)
		{
			// ��ֹ���������Ҳ�ܲ���ˮӡ��־
			// while ѭ����Ҫ�ҳ� 4 ��ˮӡ��־�����ҵ�ˮӡ
			// ����������ò��� 4 ��ˮӡ��־�ĸ��ʺ�С
			cur = strstr(cur, WATER);
			if (cur == NULL) break;
			else times++;
			if (times == 4) break;
		}
		if (times == 4) break;
	}
	close_img(&b);

	if (times != 4) 	// û�ҵ�
	{
		close_img(&bit);
		return 0;
	}
	cur = (char *)bit.data;
	cur = strstr(cur, WATER);		// �ҵ�һ����־
	end = strstr(cur + 1, WATER);	// ����һ����־
	cur += strlen(WATER);			// ������ʼ��־
	top = 0;
	while (cur != end)
	{
		data[top++] = *cur++;
	}
	data[top] = '\0';
	close_img(&bit);

	return 1;
}

// д��ˮӡ, ֧�ֲ�ɫͼ�ͻҶ�ͼ
int write_watermaking(IMG *ppm, char *data, char c)		
{
	IMG bit;			// �� c ����
	ULI size;			// bit ��С
	ULI top = 0;		// bit �±�
	int index = 0;		// ˮӡ�±�
	int len = 0;		// ˮӡ����
	char *tmp = NULL;	// ˮӡ��Ϣ

	c = c - '0' - 1;	// ��ȡ�� c ������Ϣ
	if (c < 0 || c > 3) return 0;
	if (!(ppm->flag != '5' || ppm->flag != '6')) return 0;

	bit.data = NULL;	// ��ʼ�� bit
	bit = *ppm;
	bit.flag = '4';
	bit.byte = 8;
	size = bit.width * bit.height / bit.byte;
	bit.data = (UC *)malloc(size * sizeof(UC));

	len = strlen(WATER) + strlen(data);		// ��ʼ��ˮӡ tmp
	tmp = (char *)malloc((len + 2) * sizeof(char));
	if (tmp == NULL) return 0;
	strcpy(tmp, WATER);
	strcat(tmp, data);

	while (top < size)		// ѭ��д��ˮӡ��Ϣ
	{
		bit.data[top++] = tmp[index];
		index = (index + 1) % len;
	}
	free(tmp);

	// д��ˮӡ��Ϣ
	if (ppm->flag == '5')
	{
		update_bit(ppm, &bit, c);	// д�뵽�� c ����
	}
	else if (ppm->flag == '6')		// ��ɫͼ
	{
		IMG r, g, b;

		r.data = g.data = b.data = NULL;
		extract_rgb(ppm, &r, &g, &b);	// ��ȡ��ɫ����
		update_bit(&b, &bit, c);		// д�뵽�� c ����
		combine_rgb(ppm, &r, &g, &b);	// д����ɫ����

		close_img(&r);
		close_img(&g);
		close_img(&b);
	}
	close_img(&bit);
	
	return 1;
}

void clear_gray(IMG *ppm)	// ����Ҷ�ͼ��ˮӡ
{
	IMG bit;
	char *cur;
	int len = strlen(WATER);
	int i, j;
	
	bit.data = NULL;
	for (i=0; i<3; i++)		// �� 0-2 ������Ѱ��ˮӡ
	{
		extract_bit(&bit, ppm, i);		// ��ȡ����
		bit.data[bit.height * (bit.width / bit.byte) - 1] = '\0';
		cur = (char *)bit.data;
		while (1)
		{
			cur = strstr(cur, WATER);
			if (cur == NULL) break;
			// �����һ����������
			for (j=0; j<len; j++) cur[j] = j + 1;
		}
		update_bit(ppm, &bit, i);		// д��ȥ��ˮӡ�ı���
	}
}

int clear_watermaking(IMG *ppm)		// ���ˮӡ
{
	IMG r, g, b;

	if (ppm == NULL) return 0;

	r.data = g.data = b.data = NULL;
	if (ppm->flag == '5')
	{
		clear_gray(ppm);
	}
	else if (ppm->flag == '6')
	{
		extract_rgb(ppm, &r, &g, &b);	// ��ȡ��������
		clear_gray(&b);
		combine_rgb(ppm, &r, &g, &b);
		close_img(&r);
		close_img(&g);
		close_img(&b);
	}
	else return 0;

	return 1;
}

ULI calc_size(IMG *ppm)		// ������д����ֽ���
{
	// (���ֽ� - ��־���� - '\0') / 4
	return ((ULI)(ppm->height * ppm->width / 8) - strlen(WATER) - 1) / 4;
}

// ------------------------ ���˵� ----------------------------
int display_menu(IMG *ppm)
{
	char data[2048];	// ˮӡ��Ϣ, ע���С
	char c;

	fflush(stdin);
	printf("\n1.��ȡˮӡ\t2.д��ˮӡ\t3.���ˮӡ\t������: ");
	c = getchar();
	if (c == '1')			// ��ȡˮӡ
	{
		if (read_watermaking(ppm, data))
			printf("\nˮӡ��Ϣ: %s\n", data);
		else printf("\nû��ˮӡ!\n");
	}
	else if (c == '2')		// д��ˮӡ
	{
		ULI size = calc_size(ppm);
		printf("\n��д����Ϣ���ֽ��� %u byte\n", size);
		printf("������Ƕ�����Ϣ: ");
		fflush(stdin);
		gets(data);
		if (check(data, size))
		{
			printf("������ˮӡ��ǿ��: 1.��  2.��  3.�� (���;�): ");
			c = getchar();
			if (write_watermaking(ppm, data, c)) 
			{
				printf("д��ɹ�!\n");
				save_img(ppm, "д��ˮӡ��.ppm");
			}
			else printf("д��ʧ��\n");
		}
		else printf("ˮӡ��Ϣ������ + ��\n");
	}
	else if (c == '3')		// ���ˮӡ
	{
		clear_watermaking(ppm);
		save_img(ppm, "���ˮӡ��.ppm");
		printf("����ɹ�!\n");
	}
	else printf("�������!\n");

	return 1;
}

// ------------------------------------------------------------
// ------------------ ͼ���������غ��� ----------------------
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
	size = d->height * (d->width / d->byte + 1);
	d->data = (UC *)malloc(size * sizeof(UC));

	b <<= bit;		// ��ȡģ��
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
		j >>= 1;
		if (j == 0)		// �˸�����ѭ������
		{
			j = 0x80;
			top++;
		}
	}
	return 1;
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

// ��ȡһ��ͼƬ, ֧�� p4, p5, p6 ͼ
int open_img(IMG *ppm, char *path)
{
	FILE *fp = fopen(path, "rb");
	int ret = 1;	// ����ֵ
	int f = 1;
	int w, h, i, ww;

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
			ppm->data = (UC *)malloc(h * (w / 8 + 1) * sizeof(UC));
			ppm->byte = 8;
		}
		else ret = 0;

		if (ret != 0 && ppm->data != NULL)	// ��ȡ����
		{
			if (ppm->flag == '5' || ppm->flag == '6')
				ww = w * ppm->byte;
			else if (ppm->flag == '4') 
				ww = ppm->width / ppm->byte;

			for (i=0, f=1; i<h && f!=0; i++)
			{
				// fread() һ�ζ������������, ����ֶζ�
				f = fread(ppm->data + i * ww, 1, ww, fp);
			}
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

// д��һ��ͼƬ, ֧�� p4, p5, p6 ͼ
int save_img(IMG *ppm, char *path)
{
	FILE *fp = fopen(path, "wb");
	int w = ppm->width;
	int h = ppm->height;
	int i, f, ww;
	int ret = 1;

	if (fp == NULL) return 0;

	if (ppm->flag == '5' || ppm->flag == '6')
	{
		// д�� ppm ͷ
		fprintf(fp, "%c%c\n%d\n%d\n%d\n", 
			ppm->type, ppm->flag, w, h, ppm->maxv);

		// д��ͼ������
		ww = w * ppm->byte;
		for (i=0, f=1; i<h && f!=0; i++)
			f = fwrite(ppm->data + i * ww, 1, ww, fp);

		if (f == 0) ret = 0;	// д�����
	}
	else if (ppm->flag == '4')
	{
		// д�� ppm ͷ
		fprintf(fp, "%c%c\n%d\n%d\n", ppm->type, ppm->flag, w, h);

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
		size = size / s->byte;

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

int check(char *data, ULI size)	// �Ϸ����, ��֤��ĸ������
{
	if (strlen(data) >= size) return 0;
	while (*data != '\0') 
	{
		if (*data++ == '+') return 0;
	}
	return 1;
}
