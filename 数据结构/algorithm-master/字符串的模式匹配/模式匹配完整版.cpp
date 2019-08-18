//朴素模式匹配的简单代码实现
#include <iostream>
using namespace std;
int main()
{
	const int Maxsize = 18;
	const int maxsize = 5;//两处的长度随着下面字符串的改变而改变，否则回在编译时报错
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
		cout<<"没有与之匹配的字符串";
		return -1;
	}

}


