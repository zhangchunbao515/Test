#include <iostream>
#include <cstring>
using namespace std;
int main ()
{
	const int maxsize = 50;
	char target[maxsize] = "acabaabaabcacaabc";
	char pattern[maxsize] = "abaabcac";
	int lengthP = strlen(pattern);
	int lengthT = strlen(target);

	int *next = new int [lengthP];
	next[0] = -1;

	//确定next数组
	int i = 0;
	int k = -1;
	while (i<lengthP)
	{
		if (k == -1 ||pattern[i] == pattern[k])
		{
			i++;
			k++;
			next[i] = k;
			if (pattern[i] == pattern[k])
			{
				next[i] = next[k];
			}
		}

		else
		{
			k = next[k];
		}
	}
	cout<<"next数组为：";

	for (i=0;i<lengthP;i++)
	{
		cout<<next[i]<<'\t';
	}
	cout<<endl;


	//KMP算法的具体实现
	int posP = 0;
	int posT = 0;
	while (posP<lengthP && posT<lengthT)
	{
		if (posP==-1 ||pattern[posP] == target[posT])
		{
			posP++;
			posT++;
		}
		else
		{
			posP = next[posP];
		}
	}

	if (posP < lengthP)
		return -1;
	else
	{
		cout<<"匹配的初始位置为："<<(posT-lengthP)<<endl;
		return (posT-lengthP);
	}
}



