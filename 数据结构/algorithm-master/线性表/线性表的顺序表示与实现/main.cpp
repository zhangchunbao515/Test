# include "function.h"

int main(void)
{
	SqList L;      //����
	InitList(L);  //��ʼ��
	Random(L);    //��һЩ��ֵ
	/*----------------�˵����-------------*/
	cout<<"\t---˳���---"<<endl;
	cout<<"1.��ʾ����Ԫ��"<<endl;
	cout<<"2.����"<<endl;
	cout<<"3.ɾ��"<<endl;
	cout<<"4.����"<<endl;
	cout<<"��ѡ������Ҫ�Ĳ���(�ѳ�ʼ��һ��Ԫ��):"<<endl;
	int temp;
	cin>>temp;
	if(temp>0 && temp<=4)
	{
		switch(temp)
		{
				case 1:
					Show(L);
					break;
				case 2:
					ListInsert(L);
					break;
				case 3:
					Listdelete(L);
					break;
				case 4:
					Seek(L);
					break;
		}
	}

	system("pause");

	return 0;
}