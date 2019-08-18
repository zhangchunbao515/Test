# include "comdef.h"
# include <iostream>

using namespace std;

//���
Status Show(SString T)
{
	for(int i=0; T[i]!='\0'; i++)
	{
		cout<<T[i]<<endl;
	}
	return OK;
}

//���ַ�������
int StrLength(SString T)
{
	int len=0;
	for(int i=0; T[i]!='\0'; i++)
	{
		len++;
	}
	return len;
}

//������
Status Concat(SString &T,SString S1,SString S2)
{//��T������S1��S2���Ӷ��ɵ��µĴ�����δ�ضϣ��򷵻�TRUE�����򷵻�FLASE
	bool uncut = true;         //δ����
	int i;
	int len1 = StrLength(S1);
	int len2 = StrLength(S2);
	if( (len1+len2)<MAXSTRLEN )
	{
		for(i=0 ; i<len1; i++)  //��S[1]��ʼ������Чֵ��������
		{
			T[i] = S1[i];
		}
		for(i=len1; i< len1+len2 ; i++)
		{
			T[i] = S2[i-len1];
		}
		T[len1+len2] = '\0';
		uncut = true;
	}
	else if( len1<MAXSTRLEN )
	{
		for(i=0 ; i<len1; i++)  //��S[1]��ʼ������Чֵ��������    �Ȱ�S1�е���Чֵ�ŵ�T��ȥ
		{
			T[i] = S1[i];
		}
		for(i=len1; i<MAXSTRLEN; i++)
		{
			T[i] = S2[i-len1+1];
		}
		T[MAXSTRLEN] = '\0';   //MAXSTRLEN+1��λ��
		uncut = false;
	}
	else  //��S1�ĳ��ȵ���MAXSTRLEN
	{
		for(i=0; i<MAXSTRLEN; i++)
		{
			T[i] = S1[i];
		}
		T[MAXSTRLEN] = '\0';
	}
	return OK;
}

//���Ӵ�
Status SubString(SString &T,SString S,int pos,int len)  //Ŀ���ַ�������Ҫ������ȡ���ַ��������λ�ã�����
{
	int lens = StrLength(S);   //�󳤶�
	if(pos<1 || pos>lens || len<0 || len>S[0]-pos+1)
		return ERROR;
	int i,j=0,t=0;
	for(i=pos; j<len; i++)
	{
		T[t] = S[i];
		t++;
		j++;
	}
	T[t] = '\0';
	return OK;
}

//�Ƚ��ַ����Ƿ����
Status StrCompare(SString S,SString T)
{
	int len1 = StrLength(S);
	int len2 = StrLength(T),count=0;  //T�ĳ���,���ȼ���
	if(len1!=len2)  //��������ַ������Ȳ�һ��
		return -1;
	else
	{
		for(int i=0; i<len1; i++)
		{
			if(S[i]==T[i])
				count++;
		}
		if(count==len1)
			return 0;
		else if(count!=len1)
		    return -1;
	}
}

//�ִ��Ƿ����   Brute-Force�㷨
int Index(SString S,SString T,int pos)
//TΪ�ǿմ�,������S�е�pos���ַ�֮�������T��ȵ��Ӵ�,�򷵻ص�һ���������Ӵ���S�е�λ��,���򷵻�0
{
	//eg:   S   q w e r w e w \0
	//      T   e w \0
	if(pos>0)  //λ�úϷ�
	{
		int i=pos,len1 = StrLength(S),len2 = StrLength(T);
		SString temp = "";
		while( i<=(len1-len2+1) )  //�±��ں���ķ�Χ֮��
		{
			SubString(temp,S,i,len2);  //���S��ÿһ���ַ������T���ȵ��ִ�,����T�Ƚ�
			temp[len2] = '\0';
			if(StrCompare(temp,T)!=0)   //��������,������i������Ǹ�Ԫ�ؿ�ʼ�Ƚ� 
				i++;
			else   //����ڵ�i��Ԫ�����,�򷵻�i���±�
				return i+1;   //���صڶ��ٸ�Ԫ��
		}
	}
	return 0;  //���򷵻�0
}

int main(void)
{
	SString T="";

	/*SString S1 = "qwertyuiop";
	S1[10] = '\0';
	SString S2 = "qwe";
	S2[4] = '\0';
	Concat(T,S1,S2);
	Show(T);*/

	//SString S1 = "qwertyuiop";
	//S1[10] = '\0';   //��β��־
	//cout<<StrLength(S1)<<endl;   10
	//Show(S1);

	/*SString S1 = "qwertyuiop";
	S1[10] = '\0';
	SubString(T,S1,1,6);
	Show(T);*/

	/*SString S1 = "abgd";
	S1[4] = '\0';
	SString S2 = "abgd";
	S2[4] = '\0';
	if( StrCompare(S1,S2) )
		cout<<"���"<<endl;*/

	SString S1 = "qwerwew";
	S1[7] = '\0';
	SString S2 = "ew";
	S2[2] = '\0';
	if( Index(S1,S2,1) )
		cout<<"��"<<endl;

	system("pause");
	return 0;
}