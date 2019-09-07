
#include <stdio.h>

typedef unsigned char WORD;		// һ���ֽ�

// �ļ��ṹ
// P5		��ʾ�Ҷ�ͼ��
// x, y		�ߺͿ�
// max		�����ɫ����, [0..max] ֮��ȡֵ
// ͼ������...

int main(void)
{
	FILE *fp = fopen("pic.ppm", "wb");
	WORD data[64][256];
	int i, j;

	if (fp != NULL)
	{
		// ����ͼƬ
		for (i=0; i<64; i++)
			for (j=0; j<256; j++)
				data[i][j] = (WORD)j;

		// ppm �ļ�ͷ, P5�Ҷ�ͼ, P6��ɫͼ
		fprintf(fp, "%s\n%u %u\n%u\n", "P5", 256, 64, 255);

		// ppm ���ݲ���
		fwrite(data, 1, 64 * 256 * sizeof(WORD), fp);
		fclose(fp);
	}

	// ��ȡͼƬ
	char str[20];
	fp = fopen("pic.ppm", "rb");
	if (fp != NULL)
	{
		fgets(str, 20, fp);
		printf("ͼ������: %s", str);
		fgets(str, 20, fp);
		printf("���볤: %s", str);
		fgets(str, 20, fp);
		printf("��󼶶�: %s\n", str);
	}
	return 0;
}