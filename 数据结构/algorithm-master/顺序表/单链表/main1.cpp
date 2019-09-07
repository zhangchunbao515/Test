#include <iostream>
#include "LINKNODE.H"
#include "ONLYINKLINK.H"
using namespace std;


int  main()
{
	InkLink<int> list;
	cout<<"请输入标志位，由用户自定义,输入在键盘上能敲入的字符:";
	int m;//标志位，由用户自定义
	cin>>m;

	list.create(m);
	list.output();
	list.length();

	int i;
	cout<<"请输入要插入结点的位置:";
	cin>>i;
	list.setPos(i);
	list.insert(i);
	list.output();

	list.makeEmpty();
	list.output();
	return 0;
}
