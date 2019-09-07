#include <iostream>
#include "LINKNODE.H"
#include "INKLINK.H"
using namespace std;


int main()
{
	InkLink<int> list;

	int m;
	cout<<"请输入标志位:";
	cin>>m;
	list.create(m);
	list.output();
	cout<<endl;


	int i;
	cout<<"请输入要查找的合法位置i:";
	cin>>i;
	int n;
	list.setPos(i,n);
	if (list.setPos(i,n))
	{
		cout<<"要查找的位置的数据值为"<<"n="<<n;
	}
	else
	{
		cout<<"输入的位置不合法，无法返回需要的参数";
	}
	cout<<endl;


	int k;
	cout<<"请输入要查找的数据值k=";
	cin>>k;
	int j;//返回的位置变量
	if( list.find(k,j))
	{
		cout<<"要查找的位置j="<<j;
	}
	else
	{
		cout<<"输入的位置不合法，无法返回用户需要的参数";
	}
	cout<<endl;
    return 0;
}
