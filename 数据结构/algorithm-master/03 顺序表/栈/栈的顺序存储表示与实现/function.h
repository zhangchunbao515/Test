# include "comdef.h"

typedef struct
{
	ElemType *top;    //ջ��ָ��
	ElemType *base;  //ջ�ĵײ�
	int stacksize;   //ջ�Ĵ�С
}SqStack;

//����һ����ջ
Status InitStack(SqStack &S)
{
	S.base = (ElemType *)malloc( (sizeof(ElemType)) * LIST_INIT_SIZE );//��ʼ��ջ�Ĵ�С
	if(!S.base)  return ERROR;   //���䶯̬�ڴ�ʧ��
	S.top = S.base;
	S.stacksize = LIST_INIT_SIZE;   //��С��ʼ��ΪLIST_INIT_SIZE
	return OK;
}

//ѹջ
Status Push(SqStack &S,ElemType e)
{
	if(S.top-S.base>=S.stacksize)
	{
		ElemType * newbase;
		//�½�һ��ָ��,��ֹԭ���ĵ�ַ��ʧ
		//realloc,                        ԭ��ַ,�´�С
		newbase = (ElemType *)realloc( S.base,(S.stacksize+LISTINCREMENT)*sizeof(ElemType) );
		if(!newbase)  return ERROR;   //����ʧ��
		S.base = newbase;
		S.stacksize +=  LISTINCREMENT;
	}
	*S.top++ = e;  //�ȼ���S.top = e;   *S.top++;     ����վ�� 
	return OK;
}

//��ջ
Status Pop(SqStack &S,ElemType &e)
{
	if(S.base == S.top)
		return ERROR;   //��ջ
	e = *(S.top-1);
	//cout<<e<<endl;
	*S.top--;
	return OK;
}

//ȡ��ջ��Ԫ��
Status GetTop(SqStack S,ElemType &e)
{
	e = *(S.top-1);   //��������ǿյ�..�ڶ������������ݵ�
	//cout<<e<<endl;
	return OK;
}

//ջ��
int StackLength(SqStack S)
{
	return (S.top - S.base);
}

//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(SqStack S)
{
	if( S.top == S.base )
		return TRUE;
	else
		return FALSE;
}

//����ջ
Status DestroyStack(SqStack &S)
{
	if(!S.base)
	{
	   free(S.base);
	   return OK;
	}
	else
		return ERROR;
}
