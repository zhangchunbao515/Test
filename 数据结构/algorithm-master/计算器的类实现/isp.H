#ifndef _isp_H_
#define _isp_H_
#include <iostream>
using namespace std;

int isp(char ch)//栈内优先级的比较函数
{
	switch(ch)
	{
	case'#': return 0;break;
	case')': return 6;break;
	case'+':
	case'-':return 3;break;
	case'*': return 5;break;
    case'/': return 5;break;
	case'(':return 1;break;
	default:return -1;break;
	}
}
#endif


	