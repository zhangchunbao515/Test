#include <iostream>
#include "stack.H"
#include "icp.H"
#include "isp.H"
#include "calculator.H"
#include "isdigit.H"
using namespace std;
int icp(char ch);//非主函数的函数声明
int isp(char ch);//非主函数的函数声明
bool isdigit(char ch);//非主函数的函数声明
void main ()
{
	int size;
	cout<<"请输入操作数栈的预计最大长度：";
	cin>>size;
	Calculator<double> CALC(size);//创建计算器类的对象
	CALC.infixTopostfix();//计算器类的对象调用函数实现计算
}
//运行结果：
/*==========================================================================================
                         请输入操作数栈的预计最大长度：10
			           	 请输入字符栈的预计最大长度：10
				         5+3*(4+6)-9/3#
				         表达式的计算结果为：32
				         Press any key to continue




                         请输入操作数栈的预计最大长度：10
			         	 请输入字符栈的预计最大长度：10
				         5+3*(4+6)-1/2#
				         表达式的计算结果为：34.5
				         Press any key to continue
  ===========================================================================================*/






