//朴素模式匹配的简单代码实现
#include <iostream>
using namespace std;
int main()
{
	const int Maxsize = 18;
	const int maxsize = 9;
	char ch[Maxsize]="acabaabaabcacaabc";
	char sh[maxsize]="abaabcac";
	int i=0;
	int j=0;
	for(i=0;i<=Maxsize-maxsize;i++)
	{
		for(j=0;j<maxsize;j++)
			if (ch[i+j] != sh[j]) break;
			if (j==maxsize-1)
				cout<<i;
	}

	return 0;
}


