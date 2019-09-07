
// ����ĳ��Ŀ¼�µ������ļ�
// �漰���� windows API ����
// FindFirstFile()			// ��õ�һ���ļ�
// FindnextFile()			// �����һ���ļ�
// FindClose()				// �ͷž��
// GetLastError()			// ������Ĵ�����Ϣ
// INVALID_HANDLE_VALUE		// ��Ч���
// ERROR_NO_MORE_FILES		// û�и�����ļ�
// FILE_ATTRIBUTE_DIRECTORY	// ��Ŀ¼

// ʵ��Ŀ¼ c:\test, �������һЩ�ļ���Ŀ¼

#include <stdio.h>
#include <windows.h>

int main(void)
{
	WIN32_FIND_DATA filedata;	// �ļ���Ϣ, WIN32_FIND_DATA ��������
	HANDLE in;		// �ļ����

	// filedata �����ɲ���ϵͳ��д
	in = FindFirstFile("c:\\test\\*.*", &filedata);
	while (in != INVALID_HANDLE_VALUE)		// ���������Ч���
	{
		printf("%s", filedata.cFileName);
		if (filedata.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			printf("\t<Ŀ¼>");			// �ж��ǲ���Ŀ¼
		putchar('\n');
		if (FindNextFile(in, &filedata) == false) break;
//		if (GetLastError() == ERROR_NO_MORE_FILES) break;		// �þ�Ҳ��
	}
	FindClose(in);			// �ͷ���Դ

	return 0;
}
/*
typedef struct _WIN32_FIND_DATA
{ 
���� DWORD dwFileAttributes;			// �ļ����� 
���� FILETIME ftCreationTime;			// �ļ�����ʱ�� 
���� FILETIME ftLastAccessTime;			// �ļ����һ�η���ʱ�� 
���� FILETIME ftLastWriteTime;			// �ļ����һ���޸�ʱ�� 
���� DWORD nFileSizeHigh;				// �ļ����ȸ�32λ 
���� DWORD nFileSizeLow;				// �ļ����ȵ�32λ 
���� DWORD dwReserved0;					// ϵͳ���� 
���� DWORD dwReserved1;					// ϵͳ���� 
���� TCHAR cFileName[ MAX_PATH ];		// ���ļ��� 
���� TCHAR cAlternateFileName[ 14 ];	// 8.3��ʽ�ļ��� 
}WIN32_FIND_DATA, *PWIN32_FIND_DATA; 

dwFileAttributes (�ļ�����) ȡֵ����
FILE_ATTRIBUTE_ARCHIVE
FILE_ATTRIBUTE_COMPRESSED
FILE_ATTRIBUTE_DIRECTORY		// Ŀ¼, �ж���Ŀ¼�����ļ�
FILE_ATTRIBUTE_HIDDEN			// ����
FILE_ATTRIBUTE_NORMAL			// ����
FILE_ATTRIBUTE_OFFLINE
FILE_ATTRIBUTE_READONLY			// ֻ��
FILE_ATTRIBUTE_SYSTEM			// ϵͳ�ļ���
FILE_ATTRIBUTE_TEMPORARY		// ��ʱ�ļ���
*/