# include "comdef.h"

//��ʼ��
Status InitList(SqList &L)
{
	//ֻ��Ҫһ���ṹ��
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE *sizeof(ElemType) );  
	//��ʼ������ṹ���elem������,100��
	if(! L.elem)  exit(OVERFLOW);  //����ʧ��
	L.length = 0;                  //���Ա�ĳ���Ϊ0
	L.listsize = LIST_INIT_SIZE;   //��ʼ��ʱ�Ĵ�СΪ101
	return OK;   //���سɹ�
}

//��ʾ
void Show(SqList &L)
{
	//˳���ĵ�һ���ڵ��ǲ�������ݵ�
	for(int i=1; i<=L.length; i++)
	{
		cout<<L.elem[i]<<endl;
	}
}

//��һЩ��ֵ��ȥ
void Random(SqList &L)
{
	for(int i = 1; i<=10; i++)
	{
		L.elem[i] = i+3;
		L.length++;
	}
}

//������͵ص���
Status Convert(SqList &L)
{
	int i=1,j=L.length;
	ElemType t;
	while( i<=(L.length/2) )
	{
		t = L.elem[i];
		L.elem[i] = L.elem[j];
		L.elem[j] = t;
		i++;
		j--;
	}
	return OK;
}

int main(void)
{
	SqList L;
	InitList(L);
	Random(L);
	//Show(L);
	Convert(L);
	Show(L);
	system("pause");
	return 0;
}