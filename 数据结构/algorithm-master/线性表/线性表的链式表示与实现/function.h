# include "comdef.h"
# include <iostream>

using namespace std;
int len=0;
//��������
LinkList Create()
{
	//ͷ��㲻�������
	LinkList L,p,q;
	L = (LinkList)malloc(sizeof(LNODE));
	L->next = NULL;
	q = L;
	//int len=0;
	ElemType t;
	cout<<"��������Ҫ��ʼ����Ԫ�ظ���"<<endl;
	cin>>len;
	cout<<"������������ӦԪ�ص�ֵ"<<endl;
	for(int i=0; i<len; i++)
	{
		p = (LinkList)malloc(sizeof(LNODE));
		cin>>t;
		p->data = t;
		q->next = p;
		q = p;
	}
	q->next = NULL;   //β���ָ��NULL
	return L;
}

//�������
void Show(LinkList L)
{
	LinkList p;
	p = L->next;
	while(p)
	{
		cout<<p->data<<endl;
		p = p->next;
	}
}

//����i��Ԫ�ص�ֵ����ʱ,��ֵ����e������OK
Status GetElem(LinkList L,int i,ElemType &e)
{
	LinkList p = L->next;
	int j=1;
	while(p && j<i)
	{
		p = p->next;
		++j;
	}   //��ѭ��ʱ������:1.p�Ѿ��ǿյ���(��ʾ���鳤��С��i)  2.j=i
	if(!p || j>i)   //���鳤��С��i,    iֵ̫С
		return ERROR;    //��i��Ԫ�ز�����
	e = p->data;
	return OK;
}

//���Ԫ��   ָ��λ��
Status ListInsert(LinkList L,int i,ElemType e)
{
	LinkList p;
	p = L;
	int t=1;
	while(p && t<i)   //�п���p�ǿյ�
	{
		p = p->next;
		t++;
	}
	if(!p || t>i)   //���鳤��С��i,iֵ̫С
		return ERROR;

	LinkList t2 = (LinkList)malloc(sizeof(LNODE));
	t2->data = e;
	t2->next = p->next;  //   t2ָ��p����һ��
	p->next = t2;   //pָ��t2
	return OK;
}

//ɾ��Ԫ��
Status Listdelete(LinkList L,int i,ElemType &e)
{
	LinkList p,q;
	p = L;
	int j=1;
	while(p->next && j<i)   //���ѭ���������ڶ���,��Ȼ�����p = p->next��������
	{
		p = p->next;
		j++;
	}
	if(!p->next || j>i)
		return ERROR;
	q = p->next;
	e = q->data;   //����Ҫɾ����Ԫ�ص����ݱ�������
	cout<<"ɾ����Ԫ��Ϊ:"<<e<<endl;
	p->next = q->next;
	free(q);
	return OK;
}

           /*-----------------����ʽ��͵ص���-------------------*/
//����ʽ��͵ص���  һ
Status Convert1(LinkList &L)
{
	/*
	Ϊ�˷�ת�����������������ͷ����next��ָ����2��
	���ý��1��next��ָ����3����󽫽��2��next��ָ����1��
	������˵�һ�ν�����˳��ͱ����Header-���2-���1-���3-���4-NULL
	��Ȼ�������ͬ�Ľ��������3�ƶ������2��ǰ�棬
	Ȼ���ٽ����4�ƶ������3��ǰ�������˷�ת��˼·���ˣ��͸�д�����ˣ�
	*/
	LNODE *tmp = NULL;
	LNODE *p = NULL;
	if(L==NULL)
	{
		return ERROR; 
	}
	tmp = L->next;   //ָ��ڶ���
	
	while(tmp->next!=NULL)   //����Ҫ������һ����Ԫ�ز�Ϊ��
	{
        p = tmp->next;    //pΪtmp����һ��,Ҳ������Ҫ�л�����һ����Ԫ��
		tmp->next = p->next;  //��tmpָ����Ҫ��Ҫ�л�����һ����Ԫ�ص���һ��Ԫ��
		p->next = L->next;   //��pָ��ղŵĵ�һ��Ԫ��
	    L->next = p;         //p��ɵ�һ��
	}
	
	return OK;
}

//����ʽ��͵ص���  ��  (�׶�)
Status Convert2(LinkList &L)
{
	//��������Ԫ�ؿ�ʼһֱ�������,����������Ԫ��ָ��ǰһ��Ԫ��
	LinkList p,r,q;
	p = NULL;
	q = L->next;
	while(q)    //����һ��Ԫ��ָ����һ��Ԫ��
	{
		r = q->next;  //r��q����һ��
		q->next = p;  //(��һ��ʱ,��һ��ָ���µ�ͷָ��),�Ժ�ÿ�ζ�����һ��ָ����һ��Ԫ��
		p = q;        //�µ����������
		q = r;        //�ɵ�������ǰ��
	}
	L->next = p;
	return OK;
}

/*
������������Ԫ��ֵ�ǵݼ��������е����Ա����Ե�������ʽ�洢��
���ʵ�ֽ�������Ԫ�ص�������ĵ�����ϲ�Ϊһ���µİ�Ԫ�ص����ĵ�����
*/
void All(void)
{
	LinkList L1,L2,L3,p,q1,q2;   //L1,L2����     L3����
	L1 = (LinkList)malloc(sizeof(LNODE));
	L1->next = NULL;
	q1 = L1;
	L2 = (LinkList)malloc(sizeof(LNODE));
	L2->next = NULL;
	q2 = L2;
	/*---------------------��ʼ������1---------------------*/
	for(int i=1; i<12; i++)  
	{
		if(i%3==0)
		{
		   p = (LinkList)malloc(sizeof(LNODE));
		   p->data = i;
		   q1->next = p;
		   q1 = p;
		}
	}
	q1->next = NULL;
	cout<<"L1:"<<endl;
	Show(L1);     //3   6  9
	/*---------------------��ʼ������2---------------------*/
	for(int i=1; i<12; i++)
	{
		if(i%2==0)
		{
		   p = (LinkList)malloc(sizeof(LNODE));
		   p->data = i;
		   q2->next = p;
		   q2 = p;
		}
	}
	q2->next = NULL;
	cout<<"L2:"<<endl;
	Show(L2);     //4   8

	///*-----------------�����������Ϊ�ݼ�������-------------------*/
	//Convert1(L1);   
	//Convert1(L2);

	/*-------------����������ϲ�--------------------*/
	LinkList k,head;
	head = k = (LinkList)malloc(sizeof(LNODE));   //ͷ���head    k��һ����ʱԪ��
	k->data = 0;
	q1 = L1->next;
	q2 = L2->next;
	while( q1 && q2 )   //��2����������һ��û�е����
	{
		if( (q1->data)>=(q2->data) )  
		{
			k->next = q2;  //kָ��С���Ǹ�Ԫ��   
			k = q2;        //k�����
			q2 = q2->next; //q2Ҳ�����
		}
		else   //ͬ��
		{
			k->next = q1;
			k = q1;
			q1 = q1->next;
		}
	}
	k->next = q1? q1:q2;   //�ж��ĸ������Ѿ��ǿյ���,�ǿյ�����ĺ�����Щû�бȽϵ�Ԫ�طŵ�k�ĺ���
	k=head;   //������������,����
	cout<<"�ϲ���:"<<endl;
	Show(k);  //�������
}

//�Ա�д�ڴ�ͷ���ĵ�������ɾ����һ������Сֵ���ģ���Ч���㷨
void DeleteOne(LinkList L)
{
	//��һ��ѭ��ȥ�ҵ��������Сֵ,����¼��Сֵ��ǰ��ָ��
	ElemType temp;
	LinkList p,q,t1,t2;
	p = L->next;
	q = p->next;
	temp = p->data;
	while(q)
	{
		//cout<<p->data<<endl;    //�����ǰ���ڶ�ȡ���Ǹ�Ԫ�ص�ֵ
		if( temp > q->data )      //����С
		{
			temp = q->data;
			t1 = p;      //����СԪ�ص�ָ��
			t2 = q;
		}
		p = p->next;              //������
		q = q->next;
	}
	cout<<t2->data;
	t1->next = t2->next;
	free(t2);
}

/*
����һ����ͷ���ĵ��������������ֵ��Ϊ����������д������й��ܵ��㷨��
��1���ҳ���Сֵ��㣬���������ֵ��
��2��������ֵ��������������ֱ�Ӻ�̽�����ֵ������
��3��������ֵ��ż��������ֱ�Ӻ�̽��ɾ����
*/
void Odd(LinkList L)
{
	LinkList p;
}

//	Ԫ�ص�������ĵ�����L,��x�������к��Ա���L��������
Status  InsertX(LinkList &L,ElemType x)
{
	/*
	3�����,   x����������С,x���м�,x������������
	*/
	LinkList p,q;
	p = L->next;
	q = p->next;
	if( x<(p->data) )    //����x������������Ԫ�ض�ҪС(����)
	{
		LinkList e = (LinkList)malloc(sizeof(LNODE));
		e->data = x;
		L->next = e;
		e->next = p;
	}
	while(q)
	{
		if( (p->data)<=x && (q->data)>=x)   //���м�
		{
			LinkList e = (LinkList)malloc(sizeof(LNODE));
			e->data = x;
			p->next = e;
			e->next = q;
			return OK;
		}
		p = p->next;   //��������
		q = q->next;
	}  //��ѭ��ʱ,pָ�����һ��Ԫ��,qָ��NULL
	if( x>(p->data) )    //����x������������Ԫ�ض�Ҫ��(����)
	{
		LinkList e = (LinkList)malloc(sizeof(LNODE));
		e->data = x;
		p->next = e;
		e->next = NULL;
	}
	return OK;
}

//b��	�����ǵ����� ������ֵ����min��max֮��Ľ��ɾ����������L��������
Status DeleteM(LinkList L,ElemType min,ElemType max)
{
	if(max<min)
		return ERROR;
	LinkList p,q,t,temp;
	p = L->next;
	q = p->next;
	while(q)  //���ѭ��,ѭ�򽥽�,����min�ڵ�λ��
	{
		if( (q->data)>=min &&  (p->data)<=min)
		{
			t = p;   //��ʱ����minС���Ǹ��ڵ������
			while( (q->data)<=max)  //��ѭ��ʱ,q->data����max,   ����ѭ����ĩβ
			{
				if( (q->next)==NULL)   //��ѭ����ĩβ
				{
					t->next = NULL;
					return OK;
				}
				temp = q;     //��q��ָ����ʱ������
				p = p->next;
				q = q->next;  
				free(temp);  //��֮ǰqָ����Ǹ��ڵ�(����ڵ���min��max֮��)�ͷ�
			}
			t->next = q;
			return OK;
		}
		p = p->next;
		q = q->next;
	}
	return OK;
}