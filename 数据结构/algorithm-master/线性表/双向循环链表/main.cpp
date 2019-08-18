/*
2015��9��18��21:12:02
��dΪָ�����ĳһ�ڵ��ָ��,��
d->next->prior = d->prior->next = d
d����һ������һ��,d����һ������һ��
*/

# include <iostream>
# include "comdef.h"

using namespace std;

typedef struct NODE    //���Ա��˫������洢�ṹ
{
	ElemType data;
	struct NODE *prior;       //��һ��
	struct NODE *next;        //��һ��
}NODE,*NODELIST;

//��ʼ��
NODELIST Initlist(void)   
{
	//��̬����ͷ���,ǰһ�����Լ�,��һ�����Լ�,����Ϊ0
	NODELIST L = (NODELIST)malloc(sizeof(NODE));
	L->next = L;
	L->prior = L;
	L->data = 0;
	return L;
}

//�ж������Ƿ�Ϊ��
Status Judge(NODELIST L)  
{
	//ǰһ�����Լ�ʱ,Ϊ��
	if(L->prior==L && L->next==L)
	   return TRUE;
	else
		return FALSE;
}

//�жϵ�i��Ԫ���Ƿ���ֵ
bool GetElem(NODELIST L,int i)  
{
	 int j=1;
	 NODE *q; // = (NODELIST)malloc(sizeof(NODE));      ����ֻ��Ҫһ��ָ��,����Ҫһ���ռ�
	 q = L->next;
	 while(j<i)
	 {
		 q = q->next;
		 j++;
	 }
	 if(i<1 || (q==L))   //��q==Lʱ,��ʾiֵ̫��,������ĸ�����Χ
		 return FALSE;
	 else
		 return TRUE;   //��ǰλ����ֵ
}

//�ڱ�ĺ������һЩԪ��
Status Add(NODELIST &L)
{
	int t;
	cout<<"��������Ҫ��ӵ�Ԫ�ظ���"<<endl;
	cin>>t;
	NODELIST p;
	p = L;
	ElemType temp;
	cout<<"��������Ӧ��Ԫ�ص�ֵ"<<endl;
	for(int i=1; i<=t; i++)
	{
		//β�巨
		cin>>temp;
       	NODELIST q = (NODELIST)malloc(sizeof(NODE));
	    q->data = temp;

		q->prior = p;
		p->next = q;
		q->next = L;
		L->prior = q;
		p = q;
	}
	return OK;
}

//��ʾ���
Status Show(NODELIST L)
{
	NODELIST q;
	q = L->next;
	while(q->next != L->next)
	{
		cout<<q->data<<endl;
		q = q->next;
	}
	return OK;
}

//�ڵ�i��λ�����e���Ԫ��
Status ListInsert(NODELIST &L,int i,ElemType e)  
{
	NODE *p;
	if(i>0)
	   if(!(GetElem(L,i)))   //�жϱ��ڸõ�ַ�Ƿ���ֵ,��ֵ��˵��i��ַ�Ϸ�
		  return ERROR;
    if(i<1)
		return ERROR;
	p = L;    
	int j=1;
	while(j<=i)   //��Ҫѭ��������λ�õ���һ��λ��,�����źò���
	{
		p = p->next;
		j++;
	}    //p����Ҫ�����λ��(q������)

	NODELIST q = (NODELIST)malloc(sizeof(NODE));  //�½�һ�����
	q->data = e;
	//����ͼ,����һ��
	q->prior = p->prior;         //��q������p��ǰ��һ��λ��,��ͽ�p��λ���滻��
	q->next = p;
	p->prior->next = q;
	p->prior = q;
	return OK;
}


//ɾ����i��Ԫ�ص�ֵ,������Ԫ�ص�ֵ���浽e��
Status Listdelete(NODELIST &L,int i,ElemType &e)
{
	NODELIST q;// = (NODELIST)malloc(sizeof(NODE));
	q = L;
	int j=0;
	if(i<1)
		return ERROR;
	if( !(GetElem(L,i)) )   //�����λ��û��Ԫ��
		return ERROR;
	while(j<i)
	{
		q = q->next;
		j++;
	}//��ѭ��ʱ:i==j    �����ҵ�i��λ��
	e = q->data;
	q->prior->next = q->next;
	q->next->prior = q->prior;
	free(q);
}

int main(void)
{
	NODELIST L;
	L = Initlist();
	Add(L);
	cout<<"------------���Ƿֽ���-----------"<<endl;
	ListInsert(L,1,6666);
	Show(L);
	cout<<"------------���Ƿֽ���-----------"<<endl;
	/*if(Judge(L))
		cout<<"�ǿձ�"<<endl;
	else
		cout<<"�ñ�ǿ�"<<endl;*/

	/*if(GetElem(L,2))
		cout<<"��2��Ԫ����ֵ"<<endl;*/

	//ListInsert(L,2,3333);
	//Show(L);

	int e=-1;
	Listdelete(L,1,e);
	Show(L);
	system("pause");
	return 0;
}