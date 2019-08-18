# include "comdef.h"
# include <iostream>

using namespace std;

typedef struct
{
	int i,j;    //�÷���Ԫ�ص����±�����±�
	ElemType e;  //Ԫ��
}Triple;
typedef struct
{
	Triple *data;  //����Ԫ��Ԫ�����̬����
	int mu,nu,tu; //�����������������������ͷ���Ԫ�ĸ���
}TSMatrix;

//����ϡ�����
Status CreatSMatrix(TSMatrix &M)
{
	M.data = (Triple *)malloc(sizeof(Triple)*42);   //��ʼ����6�У�7��
	M.mu = 6;  //����
	M.nu = 7;  //����
	M.tu = 8;  //����Ԫ�ĸ���
	/*--------�����ǳ�ʼ������Ԫ��----------*/
	M.data[1].i = 1;   //��0��ʼ
	M.data[1].j = 2;
	M.data[1].e = 12;
	M.data[2].i = 1;
	M.data[2].j = 3;
	M.data[2].e = 9;
	M.data[3].i = 3;
	M.data[3].j = 1;
	M.data[3].e = -3;
	M.data[4].i = 3;
	M.data[4].j = 6;
	M.data[4].e = 14;
	M.data[5].i = 4;
	M.data[5].j = 3;
	M.data[5].e = 24;
	M.data[6].i = 5;
	M.data[6].j = 2;
	M.data[6].e = 18;
	M.data[7].i = 6;
	M.data[7].j = 1;
	M.data[7].e = 15;
	M.data[8].i = 6;
	M.data[8].j = 4;
	M.data[8].e = -7;
	return OK;
}

//���ϡ�����
void PrintSMatrix(TSMatrix M)
{
	if(M.data==NULL)
	{
		cout<<"����Ϊ��"<<endl;
		return ;
	}
	int p = 1;   //����Ԫ�أ����ηŵ�����
	for(int k=1; k<=M.mu; k++)  //����6
	{
		for(int t=1; t<=M.nu; t++)  //����7
		{
			if(M.data[p].i==k && M.data[p].j==t)
			{
				cout.width(4);  //ռ4λ
				cout<<M.data[p].e<<"   ";
				p++;
			}
			else
			{
				cout.width(4);
				cout<<0<<"   ";		
			}
		}
		cout<<endl;
	}
}

//����
Status DestroySMatrix(TSMatrix &M)
{
	free(M.data);
	M.data = NULL;
	return OK;
}

//����ת��2   ��M���������ת��
Status TransposeSMatrix2(TSMatrix M,TSMatrix &T)
{
	//M.data  ��1~8
	T.mu = M.nu;  T.nu = M.mu; T.tu = M.tu;   //����,��,����Ԫ����Ū��ȥ    ת�ú�����������
	int p=1;  //��ʱֵ
	for(int k=1; k<=M.nu; k++)  //���п�ʼѭ��,�����д�1��ʼ,��ֱ�ӽ�����,�������򼴿�
	{
		for(int l=1; l<=M.tu; l++)  //����Ԫ����   ��M�ķ���Ԫ�ش�1��ʼ�����ж�����һ��
		{
			if( M.data[l].j==k )  //��һ��,l==3��l==7ʱ,�պ�j==1    ��ʼת��,���Լ���ֵ���Ƹ�T
			{
				T.data[p].j = M.data[l].i;
				T.data[p].i = M.data[l].j;
				T.data[p].e = M.data[l].e;
				p++;   //����һ��Ԫ��֮��,�����
			}
		}
	}
	return OK;
}

//����Ŀ���ת��   
Status FastTranspose(TSMatrix M,TSMatrix &T)
{
	T.mu = M.nu;  T.nu = M.mu; T.tu = M.tu;
	if(T.tu)   //�з���Ԫ��
	{
		/*---------------ͳ��-----------------*/
		int num[9];   //��:Mÿһ���еķ���Ԫ�ĸ���   0��Ԫ�ز���
		int cpot[9];  //��:T��ÿһ�еķ���Ԫ�ص��ʼ��λ��
		for(int col=0; col<=M.tu; col++)   num[col]=0;     //��ʼ��num������ÿ��Ԫ�ض�Ϊ��
		for(int t=1; t<=M.tu; t++)    num[M.data[t].j]++;  //��M�е�ÿһ�����м���Ԫ�طŵ�num������
		cpot[1] = 1;
		int col=0;
		for(col=2; col<=M.tu; col++)  cpot[col] = num[col-1] + cpot[col-1];   //ǰһ��num��ǰһ��cpot�ĺͼ�����һ�е�
		//��һ�������(���col���е�һ������Ԫ��T.data�е����)

		/*---------------�ؼ�����-------------*/
		int q=1;
		for(int p=1; p<=M.tu; p++)
		{
			col = M.data[p].j;    //�����Ԫ�ص�ԭ������,�����µľ������
			q = cpot[col];   //�����Ԫ�ظ÷����¾������һ�еĵڼ���λ��
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			cpot[col]++;    //��Ԫ�ظ÷����¾������һ�е��Ǹ�λ��Ҫ��1
		}
 	}
	return OK;
}

int main(void)
{
	TSMatrix M;
	CreatSMatrix(M);  //����
	PrintSMatrix(M);  //���
	//DestroySMatrix(M);
	//PrintSMatrix(M);
	cout<<"-----------���������---------------"<<endl;
	TSMatrix T;
	CreatSMatrix(T);  //����
	//TransposeSMatrix2(M,T);
	FastTranspose(M,T);
	PrintSMatrix(T);
	system("pause");
	return 0;
}