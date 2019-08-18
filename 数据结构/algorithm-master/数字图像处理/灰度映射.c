
// 灰度映射, 灰度值 = f(灰度值)

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

typedef unsigned char UC;

typedef struct		// ppm 图像
{
	char type;		// P 标志
	char flag;		// 几号
	int  width;		// 宽
	int  height;	// 长
	int  maxv;		// 最大量化值
	UC   *data;		// 图像数据
}img;

int open_img(img *ppm, char *path);		// 打开
int save_img(img *ppm, char *path);		// 保存
void close_img(img *ppm);				// 关闭

void img_trans_1(img *ppm)		// 2次幂灰度映射
{
	int size;	// 图像数据字节数
	int i;
	int LUT[256];

	size = ppm->height * ppm->width;
	if (ppm->flag == '6') size *= 3;

	for (i=0; i<ppm->maxv; i++)		// 生成表
		LUT[i] = i * i / ppm->maxv;
	// LUT(x) = 1/255 * x^2

	for (i=0; i<size; i++)		// 查表, 避免重复计算 
		ppm->data[i] = LUT[ ppm->data[i] ];
}

void img_trans_2(img *ppm)		// 1/2次幂灰度映射
{
	int size;	// 图像数据字节数
	int i;
	int LUT[256];

	size = ppm->height * ppm->width;
	if (ppm->flag == '6') size *= 3;

	for (i=0; i<ppm->maxv; i++)		// 生成表
		LUT[i] = (int)(pow(i, 0.5) * 16);
	// LUT(x) = 16 * x^0.5

	for (i=0; i<size; i++)
		ppm->data[i] = LUT[ ppm->data[i] ];
}

int main(void)
{
	img ppm;
	char path[256];

	printf("输入图片路径: ");
	scanf("%s", path);

	if (open_img(&ppm, path))
	{
		img_trans_1(&ppm);
		save_img(&ppm, "2次幂变换.ppm");
		close_img(&ppm);
	}
	else printf("ERROR!\n");

	if (open_img(&ppm, path))
	{
		img_trans_2(&ppm);
		save_img(&ppm, "0.5次幂变换.ppm");
		close_img(&ppm);
	}
	else printf("ERROR!\n");

	return 0;
}

// 读取一张图片, 只能读取灰度图和彩色图
int open_img(img *ppm, char *path)
{
	FILE *fp = fopen(path, "rb");
	int size;		// 每个像素大小
	int ret = 1;	// 返回值
	int w, h;
	int i, f;

	if (fp != NULL)
	{
		ppm->type = fgetc(fp);
		ppm->flag = fgetc(fp);
		fgetc(fp);		// 多余空格
		fscanf(fp, "%d", &(ppm->width));
		fgetc(fp);
		fscanf(fp, "%d", &(ppm->height));
		fgetc(fp);
		fscanf(fp, "%d", &(ppm->maxv));
		fgetc(fp);

		// 分配内存空间
		w = ppm->width;
		h = ppm->height;
		if (ppm->type == 'P')
		{
			if (ppm->flag == '2' || ppm->flag == '5')
			{
				// 灰度图像, 一个字节
				ppm->data = (UC *)malloc(w * h);
				size = 1;
			}
			else if (ppm->flag == '3' || ppm->flag == '6')
			{	
				// 彩色图像, 三个字节
				ppm->data = (UC *)malloc(w * h * 3);
				size = 3;
			}
			else ret = 0;
		}
		else ret = 0;

		// 读取数据
		if (ret != 0 && ppm->data != NULL)
		{
			// 读取数据, fread() 一次只能读入 64KB 的数据, 这里分段读
			for (i=0, f=1; i<h && f!=0; i++)
			{
				f = fread(ppm->data + i * w * size, 1, w * size, fp);
			}
			if (f == 0)		// 一部分数据读取失败
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

// 写入一张图片
int save_img(img *ppm, char *path)
{
	FILE *fp = fopen(path, "wb");
	int w = ppm->width;
	int h = ppm->height;
	int size;
	int i, f;

	if (fp == NULL) return 0;

	// 写入 ppm 头
	fprintf(fp, "%c%c\n%d\n%d\n%d\n", 
		ppm->type, ppm->flag, w, h, ppm->maxv);
	
	// 写入图像数据
	if (ppm->flag == '2' || ppm->flag == '5') size = 1;
	else size = 3;
	for (i=0, f=1; i<h && f!=0; i++)
	{
		f = fwrite(ppm->data + i * w * size, 1, w * size, fp);
	}
	if (f == 0) return 0;	// 写入错误
	return 1;
}

// 关闭一张图片
void close_img(img *ppm)
{
	if (ppm->data) free(ppm->data);
	memset(ppm, 0, sizeof(img));
}
