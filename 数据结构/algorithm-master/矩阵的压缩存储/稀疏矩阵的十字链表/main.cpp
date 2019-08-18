# include "comdef.h"
# include <iostream>

using namespace std;

//----------------ϡ������ʮ������洢��ʾ-----------
typedef struct OLNode
{
	int i,j;      //����Ԫ�ص��к����±�
	ElemType e;  //����Ԫ�ر���
	struct OLNode *right,*down;   //�÷���Ԫ�ص��б���б�ĺ������
}OLNode,*OLink;
typedef struct
{
	OLink *rhead,*chead;   //�к�������ͷָ��������ַ��CreateSmatrix����
	int mu;             //����
	int nu;              //����
	int tu;          //ϡ�����ķ���Ԫ�ظ���
}CrossList;

//����ϡ�����M,����ʮ������洢��ʾ
Status CreateSmatrix(CrossList &M)
{
	/*
	          ����С�㷨:
	����M������,����,����Ԫ�ĸ���
	��ÿһ��,ÿһ�е�ͷָ�����ռ�
	ѭ���������Ԫ���к�,�к�,ֵ
	����һ������Ԫ�غ������жϸò��뵽����,�е�ȷ��λ��
	(��:if�����ǿյ�,������Ҫ�����Ԫ�ص��кű���ǰ�Ѵ��ڵĸ��еĵ�һ��Ԫ�ص��к�С,��ֱ�Ӳ���;
	    ������Ҫ���Ҹ�Ԫ�ظ÷��ڸ��е��ʵ�λ���ٽ��в���;   )
	*/
	M.mu = 6;   M.nu = 7;   M.tu = 3;   //Ĭ�ϵ����������ͷ���Ԫ����
	if( !(M.rhead=(OLink *)malloc(sizeof(OLNode)*(M.mu+1))) )     exit(0);  //ÿһ��ͷָ�����ռ�,0�Ų�Ҫ
	if( !(M.chead=(OLink *)malloc(sizeof(OLNode)*(M.nu+1))) )     exit(0);
	//��ÿһ��,�е������ͷָ��ָ��NULL
	for(int i=0; i<=M.mu; i++)    M.rhead[i] = NULL;
	for(int i=0; i<=M.nu; i++)    M.chead[i] = NULL;

	int mu,nu;   ElemType e;     //����Ԫ�ص���,��,ֵ
	OLink p,q;
	for(scanf("%d,%d,%d",&mu,&nu,&e);mu!=0;scanf("%d,%d,%d",&mu,&nu,&e))   //���������(hang)Ϊ0ʱ�˳�����ѭ��
	{
		p = (OLNode *)malloc(sizeof(OLNode));
		p->i = mu;   p->j = nu;    p->e = e;

		//-----------------������-------------
		if( M.rhead[mu]==NULL || M.rhead[mu]->j>nu)
			//if�����ǿյ�,������Ҫ�����Ԫ�ص��кű���ǰ�Ѵ��ڵĸ��еĵ�һ��Ԫ�ص��к�С,��ֱ�Ӳ���
		{
			p->right = M.rhead[mu];  M.rhead[mu] = p;   p->right = NULL;
		}
		else  //������Ҫ���Һ���λ��
		{
			for(q=M.rhead[mu];(q->right)&&(q->right->j<nu);q=q->right) ;    //��ѭ��,��ѭ��ʱ,�Ѿ��ҵ�����λ��
			p->right = q->right;
			q->right = p;
		}

		//---------------������---------------------
		if(M.chead[nu]==NULL || M.chead[nu]->i>mu)
		{
			p->down = M.chead[nu];  M.chead[nu] = p;  p->down = NULL;
		}
		else
		{
			for(q=M.chead[nu];(q->down)&&(q->down->i<mu);q=q->down) ;
			p->down = q->down;
			q->down = p;
		}
	}
	return OK;
}

//�������(��)
Status Show(CrossList M)
{
	OLNode *q;
	for(int i=1; i<=M.mu; i++)
	{
		q = M.rhead[i];   //ÿһ�е������ͷָ��
		for(int j=1; j<=M.nu; j++)
		{
			if( (q!=NULL) && (q->i==i)&& (q->j==j) )
			{
				cout.width(4);
				cout<<q->e;
				q = q->right;
			}
			else
			{
				cout.width(4);
				cout<<0;
			}
		}
		cout<<endl;
	}
	return OK;
}

int main(void)
{
	CrossList M;
	CreateSmatrix(M);
	Show(M);

	system("pause");
	return 0;
}