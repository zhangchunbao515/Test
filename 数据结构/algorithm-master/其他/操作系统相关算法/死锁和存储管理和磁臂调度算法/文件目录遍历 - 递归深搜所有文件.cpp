
// ���ĳ��Ŀ¼�µ�ȫ���ļ����ļ���
// ��ϸ��ע�ͼ� "�ļ�Ŀ¼���� - ��ǰĿ¼.cpp"

#include <stdio.h>
#include <windows.h>
#include <string.h>

int file_num = 0;		// �ļ���
int dir_num = 0;		// Ŀ¼��


// �ݹ�����, ��ȱ���Ŀ¼, f �ǵݹ�Ĳ���
void DFS(char *_path, int f=0)
{
	WIN32_FIND_DATA file_infor;		// �ļ���Ϣ��¼�ṹ
	HANDLE in;			// �ļ����
	int i;
	char path[2048];		// ��ǰĿ¼��
	char next_path[2048];	// ��һ��Ŀ¼��

	strcpy(path, _path);
	strcat(path, "\\*");
	in = FindFirstFile(path, &file_infor);
	while (in != INVALID_HANDLE_VALUE)
	{
		if (file_infor.cFileName[0] != '.')		// .�Ǹ�Ŀ¼  ..�ǵ�ǰĿ¼
		{
			for (i=0; i<f; i++) putchar('\t');	// ͻ�����
			printf("%s", file_infor.cFileName);
			if (file_infor.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{	
				// ���ֱ���� path ���޸�, ����ʱҪ�ָ��ֳ�
				dir_num++;
				printf("\t<Ŀ¼>\n");
				strcpy(next_path, _path);		// ������һ��Ŀ¼��
				strcat(next_path, "\\");
				strcat(next_path, file_infor.cFileName);
				DFS(next_path, f + 1);		// �����Ŀ¼, �ݹ�������һ��
			}
			else
			{
				file_num++;		// ��¼�ļ���
				putchar('\n');
			}
		}
		// ����ʱ, ����������һ���ļ�, ����ʧ�ܷ��� 0, false
		if (FindNextFile(in, &file_infor) == false) break;
	}
	FindClose(in);
}

int main(void)
{
	DFS("C:\\test", 0);			// ʵ��Ŀ¼ c:\test
	printf("\n�ļ��� %d   Ŀ¼�� %d\n", file_num, dir_num);

	return 0;
}