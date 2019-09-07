# include "comdef.h"
# include <iostream>

using namespace std;

//��ʼ��
Status InitList(SqList &L)
{
	//ֻ��Ҫһ���ṹ��
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE *sizeof(ElemType) );  
	//��ʼ������ṹ���elem������,100��
	if(! L.elem)  exit(OVERFLOW);  //����ʧ��
	L.length = 0;                  //���Ա�ĳ���Ϊ0
	L.listsize = LIST_INIT_SIZE;   //��ʼ��ʱ�Ĵ�СΪ100
	return OK;   //���سɹ�
}

//��ʾ
void Show(SqList &L)
{
	cout<<"---------------���Ƿָ���--------------"<<endl;
	for(int i=0; i<L.length; i++)
	{
		cout<<L.elem[i]<<endl;
	}
}

//��һЩ��ֵ��ȥ
void Random(SqList &L)
{
	for(int i = 0; i<10; i++)
	{
		L.elem[i] = i+3;
		L.length++;
	}
}

//���뺯��   ��˳���L�е�i��λ��֮ǰ�����µ�Ԫ��e
//Status ListInsert(SqList &L,int i,ElemType e)
Status ListInsert(SqList &L)  //Ϊ����ϲ˵����ܵ�ʵ��
{
	cout<<"��Ҫ��i��λ��֮ǰ�����µ�Ԫ��e,so.....������i,e"<<endl;
	int i;
	ElemType e;
	cin>>i>>e;
	if(i<1 || i>L.length+1)   //i��λ�ò���
		return ERROR;
	if(L.length >= L.listsize)    //��ǰ�洢�ռ�����,��Ҫ�����·���
	{
		ElemType *newbase;   //��ֹ����ʱʧ��,�ȷ��䵽����
		//��ԭ�����ݴ�ͷ��β�������·�����ڴ�������,�����ص�ַ
		newbase = (ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)                    //����ʧ��
			exit(0);     
		L.elem = newbase;              //�»�ַ
		L.listsize +=LISTINCREMENT;    //���Ӵ洢����
	}
	ElemType  *q = &(L.elem[L.length-1]);    //������Ǹ�Ԫ�صĵ�ַ����q
	for(int j = L.length-1; j>=i-1; j--)   //������Ǹ�Ԫ�ؿ�ʼ,ֱ����i��Ԫ��,ȫ��������һλ
	{
		*(q+1) = *q;  
		q--;
	}
	L.elem[i-1] = e;      //����Ҫ�����Ԫ�ظ�ֵ����i��Ԫ��
	L.length++;           //���Ա���+1
	cout<<"�������֮��Ч������:"<<endl;
	Show(L);
	return OK;
}

//ɾ������   ����Ҫɾ����Ԫ�طŵ�e��ȥ
//Status Listdelete(SqList &L,int i,ElemType &e)
Status Listdelete(SqList &L)
{
	int i;
	ElemType e;
	cout<<"��Ҫ�ڵ�i��λ��ɾ��Ԫ��,so.....������i"<<endl;
	cin>>i;
	if(i<1 || i>L.length)
		return ERROR;
	e = L.elem[i-1];   //����Ҫɾ����Ԫ�ص�ֵ��ʱ��������
	ElemType *q = &(L.elem[i-1]);   //����Ҫɾ�����Ǹ�Ԫ�ؿ�ʼ,һֱ������Ǹ�Ԫ��,��ǰ��һλ
	for(int j=i-1; j<L.length-1; j++)
	{
		*q = *(q+1);   //ֱ����ǰ����
		q++;
	}
	L.length--;   //���ȼ�һ 
	cout<<"���Ѿ�ɾ����Ԫ��Ϊ"<<e<<endl;
	cout<<"ɾ�������Ա���������:"<<endl;
	Show(L);
	return OK;
}

//���Һ���   �ҵ���ֱ�ӷ����±�
//int Seek(SqList L,ElemType e)
int Seek(SqList L)
{
	ElemType e;
	cout<<"��������Ҫ���ҵ�Ԫ��"<<endl;
	cin>>e;
	int len=L.length,i=0;
	while(i<=len)
	{
		if( e == L.elem[i] )
		{
			cout<<"�ҵ�Ԫ����,�±�Ϊ"<<i<<endl;
			return i;   //�ҵ���e,�����±�
		}
		i++;
	}
	if( i==(len+1) )
		cout<<"����,��û���ҵ�������ҵ�Ԫ��"<<endl;
	return -1;   //û���ҵ���Ӧ��e
}