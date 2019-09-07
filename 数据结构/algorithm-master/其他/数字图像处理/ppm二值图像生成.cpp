
#include <stdio.h>
#include <malloc.h>

// ��ֵͼ����һ���ֽ��а˸�����
typedef unsigned char UC;

typedef struct		// ppm ͼ��
{
	char type;		// P ��־
	char flag;		// ����
	int  width;		// ��
	int  height;	// ��
	UC   *data;		// ͼ������
}img;

int main(void)
{
	FILE *fp = fopen("pic.ppm", "wb");
	img ppm;
	int w, h, i, j;

	if (fp == NULL) return 0;

	ppm.type = 'P';
	ppm.flag = '4';
	w = ppm.width = 160;
	h = ppm.height = 100;
	ppm.data = (UC *)malloc((w / 8) * h * sizeof(UC));

	for (i=0; i<50; i++)
		for (j=0; j<20; j++)
			ppm.data[i * w / 8 + j] = 0xFF;	// ��
		
	for (i=50; i<100; i++)
		for (j=0; j<20; j++)
			ppm.data[i * w / 8 + j] = 0;	// ��

	fprintf(fp, "%c%c\n%d\n%d\n", ppm.type, ppm.flag, w, h);
	fwrite(ppm.data, 1, (w / 8) * h * sizeof(UC), fp);
	fclose(fp);

	return 0;
}