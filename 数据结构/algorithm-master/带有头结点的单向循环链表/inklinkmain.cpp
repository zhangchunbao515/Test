#include <iostream>
#include "LINKNODE.H"
#include "INKLINK.H"
using namespace std;


int main()
{
	InkLink<int> list;

	int m;
	cout<<"�������־λ:";
	cin>>m;
	list.create(m);
	list.output();
	cout<<endl;


	int i;
	cout<<"������Ҫ���ҵĺϷ�λ��i:";
	cin>>i;
	int n;
	list.setPos(i,n);
	if (list.setPos(i,n))
	{
		cout<<"Ҫ���ҵ�λ�õ�����ֵΪ"<<"n="<<n;
	}
	else
	{
		cout<<"�����λ�ò��Ϸ����޷�������Ҫ�Ĳ���";
	}
	cout<<endl;


	int k;
	cout<<"������Ҫ���ҵ�����ֵk=";
	cin>>k;
	int j;//���ص�λ�ñ���
	if( list.find(k,j))
	{
		cout<<"Ҫ���ҵ�λ��j="<<j;
	}
	else
	{
		cout<<"�����λ�ò��Ϸ����޷������û���Ҫ�Ĳ���";
	}
	cout<<endl;
    return 0;
}
