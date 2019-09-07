/*
*����n��Ȩֵ��Ϊn��Ҷ�ӽ�㣬����һ�ö�����������Ȩ·�����ȴﵽ��С���������Ķ�����Ϊ���Ŷ�������
Ҳ��Ϊ��������(Huffman Tree)�����������Ǵ�Ȩ·��������̵�����Ȩֵ�ϴ�Ľ������Ͻ���
*/

# include "comdef.h"
# include <iostream>

using namespace std;

typedef struct
{
	unsigned int weight;                 //Ȩ
	unsigned int parent,lchild,rchild;   //��,����,�Һ���
}HTNode,*HuffmanTree;

typedef char ** HuffmanCode;

                  /*---------------�����������---------------------*/
//ѡ����С��2�����
void Select(HuffmanTree HT,int t,int &s1,int &s2)   //���������ı�,�±�,��Ҫ���2����Сֵ
{
	s1 = s2 = HT[0].weight;
	for(int i=1; i<=t; i++)
	{
		if(HT[i].parent==0)              //�ж��Ƿ�������
		{
			if( s2 > HT[i].weight )      //�ȴ���Ǹ�����С
			{
				if( s1 > HT[i].weight )  //�ȽϺ�2��������С����˭��    ����С���Ǹ�����С
					s1 = HT[i].weight;
				else                     //a[i] ����2�����м�
				    s2 = HT[i].weight;
			}
		}
	}
}
void CreatHuffmanTree(HuffmanTree &HT,int w[],int n)   //��������,���������,������������
{
	if(n<=1)  return ;
	int s1=0,s2=0;
	int m = 2*n - 1;    //�������������ս����  == 2*����ĵ��� - 1
	HT = (HuffmanTree)malloc( sizeof(HTNode) * (m+1) );   //0���±겻��,���Զ�����һ�����ռ�
	for(int i=1; i<=m; i++)
	{
		if(i<=n)   //��ʼ����1��n�Ľ����Լ���Ȩ
		{
			HT[i].weight = w[i-1];   HT[i].parent = 0;
            HT[i].lchild = 0;        HT[i].rchild = 0;
		}
		else    //�����Ľ����ʱ�洢Ϊ0
		{
			HT[i].weight = 0;        HT[i].parent = 0;
			HT[i].lchild = 0;        HT[i].rchild = 0;
		}
	}
	for(int i=n+1; i<=m; i++)   //������������
	{
		Select(HT,i-1,s1,s2);
		HT[s1].parent = i;   HT[s2].parent = i;    //���Լ�������
		HT[i].lchild = s1;   HT[i].rchild = s2;    //���Լ��ĺ���
		HT[i].weight = HT[s1].weight + HT[s2].weight;  //�����Լ�(�������Ľ��)��Ȩ��
	}
}

                 /*---------------���������ı���--------------------*/
void HuffmanCoding(HuffmanTree HT,HuffmanCode &HC,int n)
{
	HC = (HuffmanCode)malloc( sizeof(char*) * (n+1) );  //�洢  ����n���ַ������ͷָ������([0]����)
	char *cd = (char *)malloc( sizeof(char) * n );      //���������Ĺ����ռ�
	cd[n-1] = '\0';     //�ռ������
	int start;          //���Ŵ��,start���±�
	int c,f;            //c�ǵ�ǰ�ڵ�����,f�ǵ�ǰ������˵����
	for(int i=1; i<=n; i++)
	{
		start=n-1;
		for(c=i,f=HT[i].parent; f!=0; c=f,f=HT[f].parent)
		{
			if(HT[f].lchild==c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char *)malloc( sizeof(char) * n-start );
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}
                 

int main(void)
{
	int w[4] = {7,5,2,4};
	HuffmanTree HT;
	CreatHuffmanTree(HT,w,4);
	HuffmanCode HC;
	HuffmanCoding(HT,HC,4);
	system("pause");
	return 0;
}