# include <iostream>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFFASIBLE -1
typedef int Status;   
typedef int ElemType ; 
typedef ElemType* Triplet ; 

//��ʼ����Ԫ��
Status InitTriplet(Triplet &T,ElemType v1,ElemType v2,ElemType v3)
{
	T = (Triplet)malloc( sizeof(ElemType) * 3 );
	if(!T)
		exit(ERROR);
	T[0] = v1;
	T[1] = v2;
	T[2] = v3;
	return OK;
}

//������Ԫ��
Status DestroyTriplet(Triplet &T)
{
	free(T);
	T = NULL;  
	return OK;
}

//�õ���i��Ԫ�ص�ֵ,�����ظ�e
Status Get(Triplet &T,int i,ElemType &e)
{
	if(i<1 || i>3)
		return ERROR;
	e = T[i-1];
	return OK;
}

//�ı�T�ĵ�iԪ��ֵΪe
Status Put(Triplet &T,int i,ElemType e)
{
	if(i<1 || i>3)
		return ERROR;
	T[i-1] = e;
	return OK;
}

//���T������������,�򷵻�1
Status IsAscending(Triplet T)
{
	if(T[2]>T[1] && T[1]>T[0])
		return OK;
	else
		return ERROR;
}

//����3��Ԫ�������ֵ
Status Max(Triplet T,ElemType &e)
{
	e = T[0];
	for(int i=0;i<3;i++)
	{
		if(T[i]>e)
			e = T[i];
	}
	return OK;
}

int main()
{
	Triplet T;
	int p1 = InitTriplet(T,2,5,6);
	if(p1==1)
	{
		cout<<"����,�ɹ�������Ԫ��"<<endl;
		cout<<T[0]<<endl;
		cout<<T[1]<<endl;
		cout<<T[2]<<endl;
	}
	else
		cout<<"�Ǻ�,����ʧ��"<<endl;

	/*int p2 = DestroyTriplet(T);
	if(p2==1)
		cout<<"����,�ɹ�������Ԫ��"<<endl;
	else
		cout<<"�Ǻ�,����ʧ��"<<endl;*/

	/*int temp1,p3;
	p3 = Get(T,2,temp1);
	if(p3 == 1)
		cout<<"��2��Ԫ�ص�ֵΪ"<<temp1<<endl;*/

	/*int p4 = Put(T,2,45);
	if(p4 ==1 )
	   cout<<"��2��Ԫ�ص�ֵΪ"<<T[1]<<endl;*/

	/*int p5 = IsAscending(T);
	if(p5 == 1)
		cout<<"���������е�\n"<<endl;*/

	int temp2,p6;
	p6 = Max(T,temp2);
	if(p6 == 1)
		cout<<"���Ԫ��Ϊ"<<temp2<<endl;
	system("pause");

	return 0;
}
