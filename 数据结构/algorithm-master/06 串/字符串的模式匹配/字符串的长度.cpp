#include <iostream>
using namespace std;
int main()
{
	char ch[5] = "work";//�Ӵ˳�����Եó��ַ����ĳ��Ȱ���\0,����ĳ�char ch[4]������
	cout<<"�ַ����ĳ���Ϊ:"<<sizeof(ch)<<endl;
	for(int i=0;i<4;i++)
	{
		cout<<ch[i]<<' ';
	}
	return 0;
}
