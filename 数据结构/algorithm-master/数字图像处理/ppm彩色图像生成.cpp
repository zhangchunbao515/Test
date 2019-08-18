
#include <stdio.h>
#include <string.h>

typedef unsigned char WORD;

typedef struct		// ppm ��ɫ���ص�, �����ֽ�
{
	WORD r;
	WORD g;
	WORD b;
}ppm_RGB;

// �ļ��ṹ
// P6		��ʾ��ɫͼ��
// x, y		���Ϳ�
// max		�����ɫ����, [0..max] ֮��ȡֵ
// ͼ������...

int main(void)
{
	FILE *fp = fopen("pic.ppm", "wb");
	ppm_RGB data[160][128];
	int i, j;

	if (fp != NULL)
	{
		memset(data, 0, sizeof(data));

		for (i=0; i<20; i++)
			for (j=0; j<128; j++)
				data[i][j].r = 255;	// ��ɫ
		for (i=20; i<40; i++)
			for (j=0; j<128; j++)
				data[i][j].g = 255;	// ��ɫ
		for (i=40; i<60; i++)
			for (j=0; j<128; j++)
				data[i][j].b = 255;	// ��ɫ
		for (i=60; i<80; i++)
			for (j=0; j<128; j++)
				data[i][j].r = 255, data[i][j].g = 255;	// ����
		for (i=80; i<100; i++)
			for (j=0; j<128; j++)
				data[i][j].r = 255, data[i][j].b = 255;	// ����
		for (i=100; i<120; i++)
			for (j=0; j<128; j++)
				data[i][j].b = 255, data[i][j].g = 255;	// ����
		for (i=120; i<140; i++)
		{
			for (j=0; j<128; j++)	// ��ɫ
			{
				data[i][j].r = 255;
				data[i][j].g = 255;
				data[i][j].b = 255;
			}
		}
		fprintf(fp, "%s\n%d %d\n%d\n", "P6", 160, 128, 255);
		// fwrite() һ����д�����������, ������ 64K, ����д��ʧ��
		// ������Ĵ�д��
		for (i=0; i<4; i++)
			fwrite(data[i * 40], 1, 40 * 128 * sizeof(ppm_RGB), fp);
		fclose(fp);
	}
	return 0;
}