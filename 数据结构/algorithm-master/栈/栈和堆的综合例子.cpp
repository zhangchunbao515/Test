/*
2015��9��17��14:18:05
ջ�Ͷѵ��ۺ����� 
*/
# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

void push(int);
int pop();
int *pi,*tos;

void push(int i)    //ѹջ 
{
	pi++;    //�Ƚ�ȥ����ֵ����ջ�� 
	if(pi == (tos+50))
	{
		//printf("stack overflow\n");
		printf("������ѹջ��,�Ѿ���ջ���˿�"); 
		exit(0);
	}
	*pi = i;
}

int pop()  //��ջ 
{
	if(pi == tos)   //�ж��Ƿ񵽴�ջ�ĵͶ� 
	{
		//printf("stack underflow\n");
		printf("�Ѿ�����ջ�ĵز���\n"); 
		exit(0);
	}
	pi--;
	return *(pi+1);    //���ﷵ��pi+1,����Ϊ����pi�ĵ�ַ�Ѿ���1�� 
}

int main(void)
{
	int v;
	pi = (int *)malloc(50*sizeof(int));   //��̬����50��int�ڴ� 
	if(!pi)
	{
		printf("����ʧ��,�����˳�!\n");
		exit(0);
	}
	tos = pi;
	do
	{
		printf("������ֵ,ѹջ   ����0�ͳ�ջ  ����-1��ֹͣ");
		scanf("%d",&v);
		if(v!=0)     //�������ֵ��λ0,��ѹջ 
		   push(v);
		else         //����0,��ջ 
		   printf("pop this is it %d\n",pop());
	}while(v!=-1);
	
	return 0;
} 
