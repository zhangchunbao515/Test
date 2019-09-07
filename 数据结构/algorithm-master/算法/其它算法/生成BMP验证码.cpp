
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pshpack2.h>
#include <windows.h>

typedef long int LONG;
typedef unsigned char BYTE;
typedef unsigned long int DWORD;
typedef unsigned short int WORD;

/*
// BMP �ļ��ṹ 
// λͼ�ļ�ͷ (bitmap-file header)
// λͼ��Ϣͷ (bitmap-information header)
// ��ɫ��     (color table), 24λ����û�е�ɫ��
// λͼ����   (bitmap-data)

// ���½ṹ���� pshpack2.h �Ѿ�����
typedef struct		// λͼ�ļ�ͷ
{
	WORD   bfType;			// BMP Ϊ 0x4D42 (BM��ascll��)
	DWORD  bfSize;			// �ļ���С
	WORD   bfReserved1;		// ������, ��Ϊ0
	WORD   bfReserved2;		// ������, ��Ϊ0
	DWORD  bfOffBits;		// BMP �ļ�ͷ��С
}BMP_FILE_HEADER;

typedef struct		// λͼ��Ϣͷ
{
	DWORD  biSize;			// ���ṹ�Ĵ�С
	LONG   biWidth;			// ���
	LONG   biHeight;		// �߶�
	WORD   biPlanes;		// Ŀ���豸�ļ���
	WORD   biBitCount;		// ÿ�����������λ��
	DWORD  biCompression;	// ѹ�����ͣ�0Ϊ��ѹ��
	DWORD  biSizeImage;		// λͼ�Ĵ�С
	LONG   biXPelsPerMeter;	// ˮƽ�ֱ���
	LONG   biYPelsPerMeter;	// ��ֱ�ֱ���
	DWORD  biClrUsed;		// ��ɫ���е���ɫ��
	DWORD  biClrImportant;	// ��Ҫ����ɫ��
}BMP_INFO_HEADER;
*/

typedef struct		// λͼ����
{
	BYTE b;
	BYTE g;
	BYTE r;
}pRGB;

// ��д��ͷ��Ϣ, ������Ϣ, д���ļ�
int write_pic(BYTE *pData, int width, int height, char *filename)
{	
	int size = width * height * 3;

	// ��һ���֣��ļ�ͷ��Ϣ
	BITMAPFILEHEADER  bfh;
	bfh.bfType = 0x4d42;
	bfh.bfSize = size + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfOffBits = bfh.bfSize - size;
	
	// �ڶ����֣�������Ϣ
	BITMAPINFOHEADER  bih;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;	// 24 ɫ��û�е�ɫ��
	bih.biCompression = 0;
	bih.biSizeImage = size;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;      
	
	FILE *fp = fopen(filename, "wb");
	if (!fp) return 0;

	// д���ļ�
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(pData, size, 1, fp);
	fclose(fp);

	return 1;
}

// ������, �������� i = is to ie, j = js to je
inline void draw_line(pRGB (*rgb)[48], int is, int js, int ie, int je)
{
	int i, j;

	if (is > ie) {i = is; is = ie; ie = i;}
	if (js > je) {i = js; js = je; je = i;}
	for (i=is; i<ie; i++)
	{
		for (j=js; j<je; j++)
		{
			rgb[i][j].r = 3;	// ������
			rgb[i][j].g = 3;
			rgb[i][j].b = 3;
		}
	}
}

// ���Ƶ�������
void draw_num(pRGB (*rgb)[48], int num, int s)
{
	int e = s + 10;
	switch (num)
	{
	case 0 : 
		draw_line(rgb, 3, s, 4, e-2);		// ��
		draw_line(rgb, 18, s, 19, e-2);		// ��
		draw_line(rgb, 3, s, 19, s+1);		// ��
		draw_line(rgb, 3, e-3, 19, e-2);	// ��
		break;
	case 1 : 
		draw_line(rgb, 3, e-3, 19, e-2);	// ��
		break;
	case 2 : 
		draw_line(rgb, 3, s, 4, e-2);		// ��
		draw_line(rgb, 11, s, 12, e-2);		// ��
		draw_line(rgb, 18, s, 19, e-2);		// ��
		draw_line(rgb, 3, s, 11, s+1);		// ����
		draw_line(rgb, 12, e-3, 19, e-2);	// ����
		break;
	case 3 : 
		draw_line(rgb, 3, s, 4, e-2);		// ��
		draw_line(rgb, 11, s, 12, e-2);		// ��
		draw_line(rgb, 18, s, 19, e-2);		// ��
		draw_line(rgb, 3, e-3, 19, e-2);	// ��
		break;
	case 4 : 
		draw_line(rgb, 11, s, 12, e-2);		// ��
		draw_line(rgb, 3, e-3, 19, e-2);	// ��
		draw_line(rgb, 12, s, 19, s+1);		// ����
		break;
	case 5 : 
		draw_line(rgb, 3, s, 4, e-2);		// ��
		draw_line(rgb, 11, s, 12, e-2);		// ��
		draw_line(rgb, 18, s, 19, e-2);		// ��
		draw_line(rgb, 12, s, 19, s+1);		// ����
		draw_line(rgb, 3, e-3, 11, e-2);	// ����
		break;
	case 6 : 
		draw_line(rgb, 3, s, 4, e-2);		// ��
		draw_line(rgb, 11, s, 12, e-2);		// ��
		draw_line(rgb, 18, s, 19, e-2);		// ��
		draw_line(rgb, 3, s, 19, s+1);		// ��
		draw_line(rgb, 3, e-3, 11, e-2);	// ����
		break;
	case 7 : 
		draw_line(rgb, 18, s, 19, e-2);		// ��
		draw_line(rgb, 3, e-3, 19, e-2);	// ��
		break;
	case 8 : 
		draw_line(rgb, 3, s, 4, e-2);		// ��
		draw_line(rgb, 11, s, 12, e-2);		// ��
		draw_line(rgb, 18, s, 19, e-2);		// ��
		draw_line(rgb, 3, s, 19, s+1);		// ��
		draw_line(rgb, 3, e-3, 19, e-2);	// ��
		break;
	case 9 : 
		draw_line(rgb, 3, s, 4, e-2);		// ��
		draw_line(rgb, 11, s, 12, e-2);		// ��
		draw_line(rgb, 18, s, 19, e-2);		// ��
		draw_line(rgb, 3, e-3, 19, e-2);	// ��
		draw_line(rgb, 12, s, 19, s+1);		// ����
		break;
	default : break;
	}
}

// �� path ������֤��, ���󷵻� -1
// �����㷨: 
// ��������ĸ�����
// ������ɸ��ŵ�
int create_pic(char *path)
{
	pRGB rgb[22][48];	// ����λͼ����
	int id = 0;			// ��֤��
	int i, r;
	int x, y;
	int pos = 4;
	
	srand(time(NULL));
	memset(rgb, 250, sizeof(rgb));		// 250 ��ɫ�԰�

	// ���ֻ�ͼ���� i = 3 to 19, j = 4 to 44
	// ÿ������ 22 * 10
	for (i=0; i<4; i++)		// ����ĸ�����
	{
		r = rand() % 10;
		id = id * 10 + r;
		draw_num(rgb, r, pos);
		pos += 10;
	}
	for (i=0; i<150; i++)	// ������� n �����ŵ�
	{
		x = rand() % 22;
		y = rand() % 48;
		rgb[x][y].r = rand() % 256;
		rgb[x][y].g = rand() % 256;
		rgb[x][y].b = rand() % 256;
	}
	if (!write_pic((BYTE *)rgb, 48, 22, path)) return -1;

	return id;
}

int main(void)
{
	int k = create_pic("c:\\rgb.bmp");
	printf("��֤��: %d\n", k);

	return 0;
}
