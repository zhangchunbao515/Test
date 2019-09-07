//next数组的物理实现,未优化
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	const int maxsize =20;
	char pattern[maxsize]="abcdaabcab";

	int length = strlen(pattern);
	int *next = new int[length];

	int i = 0;
	int k = -1;
	next[0] = -1;
	while (i<length)
	{
		if (k == -1||pattern[i] == pattern[k])
		{
			i++;
			k++;
			next[i] = k;
		}
		else
			k = next[k];
	}

	int j = 0;
	for(j=0;j<length;j++)
	{
		cout<<next[j]<<'\t';
	}
	cout<<endl;
	return 0;
}
