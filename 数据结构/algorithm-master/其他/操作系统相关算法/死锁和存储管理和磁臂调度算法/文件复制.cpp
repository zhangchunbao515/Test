#include <stdio.h>

// �ļ�����, �� c:\a.txt ���Ƶ� c:\b.txt
#define SPATH "c:\\a.txt"
#define DPATH "c:\\b.txt"
#define NUM 4069		// 4 KB

int main(void)
{
	FILE *in = NULL;
	FILE *out = NULL;
	char buffer[NUM];		// 4 KB �Ļ�����
	int count;

	in = fopen(SPATH, "rt");
	if (in == NULL) { printf("���ļ�ʧ��!\n");  return 0; }

	out = fopen(DPATH, "wt");
	if (out == NULL) { printf("д���ļ�ʧ��!\n"); return 0; }

	while (1)
	{		// ÿ�ζ�ȡһ���ֽ�, ��ȡ NUM ��, count ��¼��ȡ�ɹ��Ĵ���
		count = fread(buffer, 1, NUM, in);
		if (count <= 0) break;			// ��������, ���߶�ȡʧ����
		count = fwrite(buffer, 1, count, out);
		if (count <= 0) { printf("д��ʧ��!\n");   break; }
	}
	if (in != NULL) { fclose(in);   in = NULL; }
	if (out != NULL) { fclose(out);   out = NULL; }
	printf("���Ƴɹ�\n");
	return 0;
}
