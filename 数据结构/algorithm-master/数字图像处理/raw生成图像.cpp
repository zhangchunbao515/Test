
// raw ��ʽֱ�ӱ���ͼ������, �򿪵�ʱ��Ҫָ�����

#include <stdio.h>

typedef unsigned char UC;

int main(void)
{
	FILE *fp = fopen("41035_H1.raw", "wb");
	UC data[256];
	int i;

	if (fp != NULL)
	{
		// data ֻ���� 0 - 256, ��д 64 �ξ��� 256 * 64 ��
		for (i=0; i<256; i++) data[i] = (UC)i;
		for (i=0; i<64; i++)
		{
			// fwrite() һ��д�������������, �����������д��
			// ���񳬹� 64KB �ͻ�д��ʧ��, ���� 0
			fwrite(data, 1, 256, fp);
		}
		fclose(fp);
	}
	else printf("���ļ�����\n");
	return 0;
}