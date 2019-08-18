#ifndef _isdigit_H_
#define _isdigit_H_
#include <iostream>
using namespace std;

bool isdigit(char ch)//判断是不是操作数的函数
{
	if ( ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '#' && ch != '('&& ch !=')' )
		return true;
	else 
		return false;
}
#endif