//����ģʽƥ��ļ򵥴���ʵ��
#include <iostream>
using namespace std;
int main()
{
	const int Maxsize = 18;
	const int maxsize = 5;//�����ĳ������������ַ����ĸı���ı䣬������ڱ���ʱ����
	char ch[Maxsize]="acabaabaabcacaabc";
	char sh[maxsize]="abaa";
	int i=0;
	int j=0;
	for(i=0;i<=Maxsize-maxsize;i++)
	{
		for(j=0;j<maxsize;j++)
			if (ch[i+j] != sh[j]) break;
		if (j == maxsize-1) 
		{
			cout<<i;
			return i;
		}
		
	}
	if(j!=maxsize-1)
	{
		cout<<"û����֮ƥ����ַ���";
		return -1;
	}

}


