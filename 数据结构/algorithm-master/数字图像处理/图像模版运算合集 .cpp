
// ���뻷�� VC++6.0, �� C++ ����������
// ����������ĸ�ʵ��: 
// ��ֵ�˲�, ��ֵ�˲�, ͼ����, ��Ե���

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define ABS(a) ((a) > 0 ? (a) : (-a))
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

// �ĸ���ֵ�˲�ģ��
int board1[9] = {1,2,1, 2,4,2, 1,2,1};
int board2[9];		// ȫ 1
int board3[25];		// ȫ 1
int board4[49];		// ȫ 1

// ������ֵ�˲�ģ��, 1 ����, 0 ������
int middle1[25] = {0,0,1,0,0, 0,0,1,0,0, 1,1,1,1,1, 0,0,1,0,0, 0,0,1,0,0};
int middle2[25] = {0,0,1,0,0, 0,1,1,1,0, 1,1,1,1,1, 0,1,1,1,0, 0,0,1,0,0};

// ���� Laplace ����
int laplace1[9] = {0,-1,0, -1,5,-1, 0,-1,0};
int laplace2[9] = {-1,-1,-1, -1,9,-1, -1,-1,-1};

// ���� Sobel ����, prewitt ����
int sobel_x[9] = {1,2,1, 0,0,0, -1,-2,-1};
int sobel_y[9] = {-1,0,1, -2,0,2, -1,0,1};
int prewitt_x[9] = {1,1,1, 0,0,0, -1,-1,-1};
int prewitt_y[9] = {-1,0,1, -1,0,1, -1,0,1};

// ��������
int open_img(IMG *ppm, char *path);		// ��
int close_img(IMG *ppm);				// �ر�
int save_img(IMG *ppm, char *path);		// ����
int copy_img(IMG *d, IMG const *s);		// ����


// �˲�������ppm��ԭͼ��board��ģ��, h ��, w ��, s �ܺ�, result �ǽ��ͼ
// ֧�ֻҶ�ͼ, ��ɫͼ, ��̬��Ӧģ���С
void filters(IMG *ppm, int *board, int h, int w, int s, IMG *result)
{
	int i, j, ii, jj;
	int is = h / 2;					// ����Χ [is, ie)
	int ie = ppm->height - is;
	int js = (w / 2) * ppm->byte;	// [js, je)
	int je = ppm->width * ppm->byte - js;
	int hh = h / 2;					// ���ȷ�Χ [-hh, hh]
	int ww = (w / 2) * ppm->byte;	// ��� [-ww, ww]
	int k = ppm->byte * ppm->width;		// һ�� k ������
	int cur;
	long int sum, tmp;
	UC *temp = (UC *)malloc(ppm->height * ppm->width * ppm->byte * sizeof(UC));
	// temp ������ͼ����ʱ�ռ�

	for (i=is; i<ie; i++)	// ���
	{
		for (j=js; j<je; j++)
		{
			// ԭͼ�� [-inc, inc] ���� byte ��
			// ��ɫͼ������������, ����ԭ��������, ������
			cur = sum = 0;
			for (ii=-hh; ii<=hh; ii++)				// ��������һ��
				for (jj=-ww; jj<=ww; jj+=ppm->byte)		// �����ɫͼ���� 3 ��
					sum += ppm->data[(i + ii) * k + (j + jj)] * board[cur++];

			// С�� 0 ���ȡ����ֵ, ���� maxv ��� maxv, Ϊ�˱�Ե������
			tmp = (long int)((double)sum / s + 0.5);
			tmp = ABS(tmp);
			if (tmp > (long int)ppm->maxv) tmp = (long int)ppm->maxv;
			temp[i * k + j] = (UC)tmp;
		}
	}
	cur = 0;
	for (i=is; i<ie; i++)	// ���ǻ�ԭͼ����
		for (j=js; j<je; j++)
			result->data[cur++] = temp[i * k + j];
	free(temp);
}

// �˲�����, �Ȱ�ԭͼ����ģ���С�ؿ�, �ٽ����˲�, �Ա㴦����Ե
void my_filters(IMG *ppm, int *board, int h, int w, int s=1)
{
	IMG new_ppm;
	int new_h = h / 2;
	int new_w = (w / 2) * ppm->byte;
	int i, j, k;		// k ��ÿ�е����ظ���

	new_ppm = *ppm;
	new_ppm.height += (2 * (h / 2));		// �ؿ�
	new_ppm.width += (2 * (w / 2));
	new_ppm.data = (UC *)malloc(new_ppm.height * new_ppm.width
		* new_ppm.byte * sizeof(UC));

	// �ؿ��������������� 0
	k = new_ppm.width * new_ppm.byte;
	for (j=0; j<k; j++)
	{
		for (i=0; i<new_h; i++)		
			new_ppm.data[i * k + j] = 0;	// �ϱ���� 0
		for (i=new_ppm.height-new_h; i<new_ppm.height; i++)
			new_ppm.data[i * k + j] = 0;	// �±���� 0
	}
	for (i=0; i<new_ppm.height; i++)
	{
		for (j=0; j<new_w; j++)	
			new_ppm.data[i * k + j] = 0;	// ������ 0
		for (j=k-new_w; j<k; j++)
			new_ppm.data[i * k + j] = 0;	// �ұ���� 0
	}

	// ��ԭͼ���ݸ��ƽ���
	int is = h / 2;				// ����Χ [is, ie)
	int ie = new_ppm.height - is;
	int js = (w / 2) * new_ppm.byte;	// [js, je)
	int je = new_ppm.width * new_ppm.byte - js;
	int cur = 0;
	for (i=is; i<ie; i++)
		for (j=js; j<je; j++)
			new_ppm.data[i * k + j] = ppm->data[cur++];

	// Ȼ������˲�����
	filters(&new_ppm, board, h, w, s, ppm);
	free(new_ppm.data);		// �������ͷ��ڴ�
}

// ��ֵ�˲�, ppm ͼ��, board ģ��, h ��, w ��
// ֧�ֻҶ�ͼ, ��ɫͼ, ��̬��Ӧģ���С
void median(IMG *ppm, int *board, int h, int w)
{
	int i, j, ii, jj;
	int is = h / 2;					// ����Χ [is, ie)
	int ie = ppm->height - is;
	int js = (w / 2) * ppm->byte;	// [js, je)
	int je = ppm->width * ppm->byte - js;
	int hh = h / 2;					// ���ȷ�Χ [-hh, hh]
	int ww = (w / 2) * ppm->byte;	// ��� [-ww, ww]
	int k = ppm->byte * ppm->width;	// һ�� k ������
	int cur, sum;		// 1 �ĸ���
	UC arr[100];		// ��������
	int index = 0;
	int top = 0;

	// temp ����ʱ�ռ�, map �Ǽ�������ĸ���ռ�
	UC *temp = (UC *)malloc(ppm->height * ppm->width * ppm->byte * sizeof(UC));
	int *map = (int *)malloc((ppm->maxv + 2) * sizeof(int));
	for (ii=0; ii<=ppm->maxv; ii++) map[ii] = 0;
	for (i=0, sum=0; i<w * h; i++) sum += board[i];		// ѡ�е����ظ���
	for (i=is; i<ie; i++)
	{
		for (j=js; j<je; j++)		// ���ͼ���
		{
			top = index = cur = sum = 0;
			for (ii=-hh; ii<=hh; ii++)
				for (jj=-ww; jj<=ww; jj+=ppm->byte, cur++)
					if (board[cur])
						arr[index++] = ppm->data[(i + ii) * k + (j + jj)];

			// ��������� O(n), ����ֵһ���� 0 - 255, �����и����, 
			for (ii=0; ii<index; ii++) map[arr[ii]]++;	// ����
			for (ii=0; ii<=ppm->maxv; ii++) 
				if (map[ii] != 0)
				{
					for (jj=0; jj<map[ii]; jj++) arr[top++] = ii;
					map[ii] = 0;		// ˳�����
				}
			temp[i * k + j] = arr[index / 2];	// ȡ��ֵ
		}
	}
	for (i=is; i<ie; i++)	// ���ǻ�ԭͼ����
		for (j=js; j<je; j++)
			ppm->data[i * k + j] = temp[i * k + j];
	free(temp);
	free(map);
}


// ��Ե���, ����: ԭͼ, ����ģ��, ����ģ��, ģ���, ��, λ��, ��Ե��ֵ
void side_detect(IMG *ppm, int *board_x, int *board_y, 
			   int h, int w, int s, double c)
{
	int i, j, cur, tmp;
	IMG side_x;
	IMG side_y;
	
	memset(&side_x, 0, sizeof(IMG));
	memset(&side_y, 0, sizeof(IMG));
	copy_img(&side_x, ppm);
	copy_img(&side_y, ppm);

	// �ֱ��˲�
	my_filters(&side_x, board_x, h, w, s);
	my_filters(&side_y, board_y, h, w, s);

	// �ϳ��ݺ�����ͼ
	int k = ppm->width * ppm->byte;
	for (i=0; i<ppm->height; i++)
		for (j=0; j<k; j++)
		{
			cur = i * k + j;
			// �ϳɺ��� g(x,y) = C * (|gx(x,y)| + |gy(x,y)|);
			tmp = (int)(c * (ABS(side_x.data[cur]) + ABS(side_y.data[cur])));
			if (tmp > ppm->maxv) tmp = ppm->maxv;
			if (tmp < 0) tmp = 0;
			ppm->data[cur] = (UC)tmp;
		}
	close_img(&side_x);
	close_img(&side_y);
}

int main(void)
{
	IMG ppm;			// ԭͼ
	IMG tmp;			// ���ͼ
	char path[512];		// ·��
	int i, number;

	// ֧�ֻҶ�ͼ�Ͳ�ɫͼ
	printf("����ͼƬ·��: ���ͼƬֱ���ϵ���������, Ȼ��ᵯ���˵�\n");
	scanf("%s", path);
	memset(&ppm, 0, sizeof(ppm));	// ��ʼ������
	memset(&tmp, 0, sizeof(tmp));
	for (i=0; i<9; i++) board2[i] = 1;
	for (i=0; i<25; i++) board3[i] = 1;
	for (i=0; i<49; i++) board4[i] = 1;

	if (open_img(&ppm, path))
	{
		printf("\n����ͼ��: \n\n   1. ��ֵ�˲�\n\n   2. ��ֵ�˲�\n\n");
		printf("   3. ͼ����\n\n   4. ��Ե���\n\n---���������: ");
		scanf("%d", &number);
		printf("������,,,");
		if (number == 1)		// ��ֵ�˲�
		{
			copy_img(&tmp, &ppm);		// ���ƻ�ԭͼ������ copy һ��
			my_filters(&tmp, board1, 3, 3, 16);	// �˲�ģ��1
			save_img(&tmp, "��ֵ�˲�1.ppm");

			copy_img(&tmp, &ppm);
			my_filters(&tmp, board2, 3, 3, 9);	
			save_img(&tmp, "��ֵ�˲�2.ppm");

			copy_img(&tmp, &ppm);
			my_filters(&tmp, board3, 5, 5, 25);
			save_img(&tmp, "��ֵ�˲�3.ppm");

			copy_img(&tmp, &ppm);
			my_filters(&tmp, board4, 7, 7, 49);
			save_img(&tmp, "��ֵ�˲�4.ppm");
		}
		else if (number == 2)	// ��ֵ�˲�
		{
			copy_img(&tmp, &ppm);
			median(&tmp, middle1, 5, 5);
			save_img(&tmp, "��ֵ�˲�1.ppm");

			copy_img(&tmp, &ppm);
			median(&tmp, middle2, 5, 5);
			save_img(&tmp, "��ֵ�˲�2.ppm");
		}
		else if (number == 3)	// ͼ����
		{
			copy_img(&tmp, &ppm);
			my_filters(&tmp, laplace1, 3, 3, 1);
			save_img(&tmp, "laplace��1.ppm");

			copy_img(&tmp, &ppm);
			my_filters(&tmp, laplace2, 3, 3, 1);
			save_img(&tmp, "laplace��2.ppm");
		}
		else if (number == 4)	// ��Ե���
		{
			copy_img(&tmp, &ppm);
			side_detect(&tmp, sobel_x, sobel_y, 3, 3, 1, 0.7);
			save_img(&tmp, "sobel��Ե���.ppm");

			copy_img(&tmp, &ppm);
			side_detect(&tmp, prewitt_x, prewitt_y, 3, 3, 1, 0.7);
			save_img(&tmp, "prewitt��Ե���.ppm");
		}
		close_img(&tmp);	// �ͷ��ڴ�
		close_img(&ppm);
		if (number >=1 && number <= 4) printf("\n���!\n");
		else printf("\n�������!\n");
	}
	else printf("ֻ�ܴ򿪻ҶȺͲ�ɫppmͼ\n");

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

int copy_img(IMG *d, IMG const *s)		// ����
{
	if (d == NULL || s == NULL) return 0;

	if (d->data != NULL) free(d->data);		// �ͷ�ԭ����ͼ��
	*d = *s;								// ���Ƴ�Ա
	d->data = (UC *)malloc(s->height * s->width * d->byte * sizeof(UC));
	int size = s->height * s->width * s->byte;

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
