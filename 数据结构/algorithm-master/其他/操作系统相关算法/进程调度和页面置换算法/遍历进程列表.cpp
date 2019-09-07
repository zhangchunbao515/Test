
// ���̲��ϱ仯, ����ֻ�ܻ�ȡĳһʱ�̵Ŀ���
// CreateToolhelp32Snapshot() ������ȡ�����б�Ŀ���
// ���ұ��浽һ����� snap ��
// Process32First() �� snap �л�õ�һ��������Ϣ
// ���ѽ��̵���Ϣ����ṹ�� info ��
// Process32Next() ��� snap �е���һ���ṹ��, ��ȡʧ�ܷ��� NULL

#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int main(void)
{
	// ���浥��������Ϣ�Ľṹ��
	PROCESSENTRY32 info;
	HANDLE snap;		// ���̿��յľ��
	int flag;
	
	info.dwSize = sizeof(info);
	snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	flag = Process32First(snap, &info);
	printf("%-38s%-15s%-15s\n\n", "������", "����ID", "�߳���");
	while (flag)
	{
		printf("%-38s%-15u%-15u\n", 
			info.szExeFile, info.th32ProcessID, info.cntThreads);
		flag = Process32Next(snap, &info);
	}
	CloseHandle(snap);
	return 0;
}
