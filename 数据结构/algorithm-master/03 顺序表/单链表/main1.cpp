#include <iostream>
#include "LINKNODE.H"
#include "ONLYINKLINK.H"
using namespace std;


int  main()
{
	InkLink<int> list;
	cout<<"�������־λ�����û��Զ���,�����ڼ�������������ַ�:";
	int m;//��־λ�����û��Զ���
	cin>>m;

	list.create(m);
	list.output();
	list.length();

	int i;
	cout<<"������Ҫ�������λ��:";
	cin>>i;
	list.setPos(i);
	list.insert(i);
	list.output();

	list.makeEmpty();
	list.output();
	return 0;
}
