# include "comdef.h"
# include <iostream>
# include "Queue.h"   //�������

         /*-------------�������----------*/
void preorder1(BiTree T)    //BiTree�ǽṹ��ָ��
{
	if(T)         //�����������
	{
		cout<<T->data<<endl;            //����ýڵ��ֵ    �������
		preorder1(T->lchild);     //�Ӹýڵ������ӷ���̽��ָ��
		preorder1(T->rchild);
	}
}

        /*-------------�������----------*/
void preorder2(BiTree T)
{
	if(T)         //�����������
	{
		preorder2(T->lchild);     //�Ӹýڵ������ӷ���̽��ָ��
		cout<<T->data<<endl;     //�������        
		preorder2(T->rchild);
	}
}

        /*-------------�������----------*/
void preorder3(BiTree T)
{
	if(T)         //�����������
	{
		preorder3(T->lchild);     //�Ӹýڵ������ӷ���̽��ָ��  
		preorder3(T->rchild);
		cout<<T->data<<endl;      //��������
	}
}

                /*-------------------����洢���������� -----------------*/
//����������,����������ȷ,������Ҫ����int���͵Ľ������
Status CreateBiTree(BiTree &T)
{
	//�������������������нڵ��ֵ,(һ���ַ�),�ո��ַ���ʾ����
	//������������ʾ�Ķ�����T	
	TElemType ch;    //TElemType �� int ���͵�
	cin>>ch;
	if(ch=='#')      //������-1ʱ,��ýڵ�Ͳ�������ֵ,���ٴ����ռ�
		T=NULL;
	else
	{
		if(!(T=(BiTree)malloc(sizeof(BiTNode))))     //���ɴ�Ž����ڴ�ռ�
			exit(OVERFLOW);
		T->data = ch;            //�ýڵ� 
		CreateBiTree(T->lchild); //����
		CreateBiTree(T->rchild); //�Һ���
	}
	return OK; 
}

                /*------------------�Զ����������ķ�ʽ�洢������---------*/ 
//����������,��������������,�����ʱ�Ѿ��ź���,�ú���ֻ������ֵ���뵽���ʵ�λ��
void insert(BiTree &T,TElemType x)    //����� x Ϊ int ����,x��ʾ��Ҫ�����ֵ
{
	if(T==NULL)   //���Ϊ�յĻ�,������һ�����,�����Һ�����Ϊ��
	{
		T = (BiTree)malloc( sizeof(BiTNode) ); 
		T->data = x;
		T->lchild = T->rchild = NULL;   //�Ȱ����Һ���ָ����Ϊ��
	}
	else   //С->��   ��->��
	{
		if( x <= T->data )         //����Ҫ�����ֵС�ڵ�ǰ�ڵ��ֵ,�����Ÿýڵ����ӷ������Ѱ�Һ���λ��
			insert(T->lchild,x);  
		else
			insert(T->rchild,x);  
	}
}
//������������  
void CreateBiTree2(BiTree &root)
{
	root = NULL;    //�ʼʱ������Ϊ��
	TElemType x;    //�����������Ϊint
	cin>>x;
	while(x!=-1)
	{
		insert(root,x);   //��ʱ���û������ֵ�嵽�����������
		cin>>x;
	}
}

                 /*-----------------------�������Ĳ�α���--------------------*/
LinkQueue Q;
Status LevelOrder(BiTree T)
{
	/*
	*��������е�һ�����ʱ,��ʱ����һ�е���������Ӻ��Ӳ������β��.
	���Ǹ��б������,��һ�е����н���Ѳ������β��
	*/
	InitQueue(Q);      //���ǳ�ʼ������
	BiTree b=NULL;     //����һ��ָ��
	if(T)
	{
		EnQueue(Q,T);   //���д����ָ��
		while(!QueueEmpty(Q))    //�ж϶����Ƿ�Ϊ��
		{
			DeQueue(Q,b);       //�����е�b���ָ����
			cout<<b->data<<endl;
			if(b->lchild)       //�ж�b �������Ƿ����,���������ѭ��ȥ�������,���뵽����
			   EnQueue(Q,b->lchild);   //�����Ӳ������
			if(b->rchild)    //�ж�b ���Һ����Ƿ����,���������ѭ��ȥ(��ʱ)�������
				EnQueue(Q,b->rchild);   
		}
	}
	return OK;
}

              /*-----------------����������ĸ߶�--------------------------*/
int tree_depth(BiTree T)
{
	int h=0,lh=0,rh=0;  //�ܳ�
	if(!T)  //���Ϊ��
		h=0;
	else{
		lh = tree_depth(T->lchild);   //��ߵĸ߶�
		rh = tree_depth(T->rchild);   //�ұߵĸ߶�
		if(lh>=rh)         //��߸߶ȴ����ұ߸߶�
			h = lh+1;      //�߶�Ҫ�����Լ�����һ��
		else
			h = rh+1;
	}
	return h;
}

             /*-----------------��������������������-----------------------*/
void change_lr(BiTree T)   //��Ȼ,�еݹ�
{
	if(T)
	{
		change_lr(T->lchild);         //����ݹ�
		change_lr(T->rchild);         //���ҵݹ�
		
		    /*-------����������������ָ��-------*/
		BiTree temp;     //����һ���洢�������ṹ��ָ��
		temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
	}
}

             /*-----------------�����ܽ�����Ŀ------------------------------*/
/*
��T��Ϊ��,���εݹ���ȥ,��ͣ�ļ����Լ���������ҽ���ټ����Լ�    f(��)+f(��)+1
*/
int count_n(BiTree T)
{
	int num=0,num1=0,num2=0;   //��,��,��
	if(!T)   //���Ϊ��,num=0
		;
	else
	{
		num1 = count_n(T->lchild);      //�ݹ���ȥ������ָ����һ��Ľ����
		num2 = count_n(T->rchild);      //�ݹ���ȥ������ָ����һ��Ľ����
		num = num1 + num2 + 1;           //�ܽ���� = ��ߵĽ���� + �ұߵĽ����
	}
	return num;
}

            /*-----------------����Ҷ������----------------------------------*/
int count_n0(BiTree T)
{
	int num=0,num1=0,num2=0;
	if(!T)                                         // TΪ��
		num=0;
	else if(T->lchild==NULL && T->rchild==NULL)   //Tֻ��һ�����   ��Ҷ����Ϊ1
		num=1;
	else
	{
		num1 = count_n0(T->lchild);               //������ߵ���һ���Ҷ����
		num2 = count_n0(T->rchild);               //�����ұߵ���һ���Ҷ����
		num = num1 + num2;                        //��߼��ұߵ�������
	}
	return num;
}

            /*-----------------���㵥֧��������-----------------------------*/
int count_n1(BiTree T)
{
	int num = 0, num1 = 0, num2 = 0;   //��,��,��    ��֧��
	if(!T)    //���ǵݹ�ĳ���
		;
	else
	{
		num1 = count_n1(T->lchild);     //����ݹ�,���ϵ�Ѱ�ҵ�֧��
		num2 = count_n1(T->rchild);     //���ҵݹ�,���ϵ�Ѱ�ҵ�֧��
		//���������ӷǿ�,�Һ���Ϊ��,��ý��Ϊ��֧��,��ߵ���һ���һ����֧��
		if( T->lchild!=NULL && T->rchild==NULL )
		    num1++;
		//����������Ϊ��,�Һ��ӷǿ�,��ý��Ϊ��֧��,�ұߵ���һ���һ����֧��
		if( T->lchild==NULL && T->rchild!=NULL )        
	        num2++;
		num = num1 + num2;
	}
	return num;
}

            /*-----------------����˫֧�����������-----------------------------*/
            
int count_n2(BiTree T)
{
	int num=0,num1=0,num2=0;
	if(!T || (T->lchild==NULL && T->rchild==NULL))   //TΪ��,    ����Tû�к���
		num=0;
	else
	{
		if(!T->lchild)        //����Ϊ��,ֻ���Һ���
			num = count_n2(T->rchild);
		else if(!T->rchild)  //�Һ���Ϊ��,ֻ������
			num = count_n2(T->lchild);
		else
			num = count_n2(T->lchild) + count_n2(T->rchild) + 1;
	}
	return num;
}

           /*------------------�������еĶ������������Ϣ------------------------*/
void count(BiTree T,int &n0,int &n1,int &n2,int &n)   //Ҷ����,��֧��,˫֧��,�ܽ�����
{
	if(T)
	{
	    n++;                       //��������ʱ���н��,������+1
		if(T->lchild==NULL && T->rchild==NULL)    //�����Ҷ�û�к���,����Ҷ��,+1
			n0++;
		if( (T->lchild!=NULL && T->rchild==NULL) || (T->lchild==NULL && T->rchild!=NULL) )  //��ֻ��1���к���,��֧��+1 
			n1++;
		if(T->lchild!=NULL && T->rchild!=NULL)   //�����Ҷ��к���,��˫֧��=1
			n2++;
		count(T->lchild,n0,n1,n2,n);       //��������ݹ�
		count(T->rchild,n0,n1,n2,n);       //�������ҵݹ�
	}
}

int main(void)
{
	BiTree T=NULL;

	
	cout<<"a. ����洢����������"<<endl;
	CreateBiTree(T);

	int num1 = count_n1(T);
	cout<<"��֧�����"<<num1<<endl;

    int num = count_n2(T);
	cout<<"˫֧�����"<<num<<endl;

	//cout<<"b. �������Ĳ�α���"<<endl;
	//LevelOrder(T);

	/*cout<<"c. �������"<<endl;
	preorder1(T);
	cout<<"d. �������"<<endl;
	preorder2(T);
	cout<<"e. �������"<<endl;
	preorder3(T);*/

	

	/*
	int h = tree_depth(T);
	cout<<"���߶�Ϊ"<<h<<endl;
	*/

	/*
	cout<<"��������������������"<<endl;
	change_lr(T);
	cout<<"�������Ĳ�α���"<<endl;
	LevelOrder(T);*/

	/*
	cout<<"f. ͨ����������������Ӧ�ĵ�����"<<endl;
	int n0 = count_n0(T);
	cout<<"Ҷ����Ϊ"<<n0<<endl;

	int n1 = count_n1(T);
	cout<<"��֧����ĿΪ"<<n1<<endl;

	int n2 = count_n2(T);
	cout<<"˫֧����ĿΪ"<<n2<<endl;

	int n = count_n(T);
	cout<<"�������ĿΪ"<<n<<endl;*/

	cout<<endl;
	cout<<"g. ͨ��һ�������������еĵ�����"<<endl;
	int a[4] = {0};
	count(T,a[0],a[1],a[2],a[3]);   //�������еĵ�����
	
	cout<<"Ҷ����Ϊ"<<a[0]<<endl;
	cout<<"��֧����ĿΪ"<<a[1]<<endl;
	cout<<"˫֧����ĿΪ"<<a[2]<<endl;
	cout<<"�������ĿΪ"<<a[3]<<endl;

	/*
	cout<<"a. ����һ�ö���������"<<endl;
	CreateBiTree2(T);    //����һ�ö���������
	cout<<"b. �������"<<endl;
	preorder1(T);
	cout<<"c. �������"<<endl;
	preorder2(T);
	cout<<"d. �������"<<endl;
	preorder3(T);*/

	/*cout<<"a. ����һ�ö���������"<<endl;
	CreateBiTree2(T);    //����һ�ö���������
	cout<<"b. �������Ĳ�α���"<<endl;
	LevelOrder(T);*/
	system("pause");
	return 0;
}