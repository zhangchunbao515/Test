//KMP算法，其中next数组未被优化

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
		}

		else
		{
			k = next[k];
		}
	}


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



