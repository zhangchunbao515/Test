#include <iostream>
using namespace std;
int main()
{
	char ch[5] = "work";//从此程序可以得出字符串的长度包含\0,如果改成char ch[4]，错误
	cout<<"字符串的长度为:"<<sizeof(ch)<<endl;
	for(int i=0;i<4;i++)
	{
		cout<<ch[i]<<' ';
	}
	return 0;
}
