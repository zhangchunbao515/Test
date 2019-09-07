#ifndef _icp_H_
#define _icp_H_
#include <iostream>
using namespace std;

int icp(char ch)//栈外优先级的比较函数
{
	switch(ch)
	{
	case'#': return 0;break;
	case')': return 1;break;
	case'+':return 2;break;
    case'-':return 2;break;
	case'*':
	case'/': return 4;break;
	case'(':return 6;break;
	default:return -1;break;
	}
}

#endif