/*
2015��8��29��22:03:09
���������������Ա� �Ķ��� 
*/

# include <stdio.h>
# include <malloc.h> 
# include <Windows.h>

struct Student   //ѧ�� 
{
	int num;                  //ѧ�� 
	int age;                  //���� 
	struct Student * next;    //������һ����ָ�� 
};
typedef struct Student st; 

//��������
st *Initlist(void)   
{
	st *h,*p,*q;     //ͷָ��,ǰһ��,��һ��
	h = (st *)malloc( sizeof(st) );
	h->next=NULL;
	p = h;
	int num,age;
	printf("������ѧ��ѧ��,����(�м��Զ��Ÿ���)\n");
	scanf("%d,%d",&num,&age);
	printf("\n"); 
	while(num!=-1)
	{
		q = (st *)malloc( sizeof(st) );   //��ʱ����һ������Ԫ��
		q->num=num;
		q->age=age;
		p->next = q;
		p = q;   //һ��һ������ǰ�� 
		scanf("%d,%d",&num,&age);
	} 
	p->next = '\0';   //����Ǹ�Ԫ���ǿյ� 
	return h; 
}   

//�������
void Show(st *h)
{
	st *p;   //ֻ��Ҫһ������,���Լ�����ƶ�����ȫ�����,֪����һ��Ϊ '\0' 
	p = h->next;
	if(p == '\0')
	{
		printf("���ǿյ�����!\n");
	}
	else
	{
		printf("ѧ����Ϣ����:\n");
		printf("ѧ�� ����\n"); 
	    while(p != '\0')
		{
			printf(" %d   %d  \n",p->num,p->age);
			p = p->next;   //����� 
		} 
    }

} 

//�������Ա�
void ClearList(st *h)
{
	st *p,*q;
	p = h->next;
	q = p->next;
	while(q!=NULL)
	{
		free(p);
		p = q;
		q = q->next;
	}
}

//�ж����Ա��Ƿ�Ϊ�ձ�
bool Listempty(st *h)
{
	if(h->next == NULL)   //����ҿձ�,�򷵻�true
		return true;
	else
		return false;
}

//�������Ա�Ԫ�ظ���
int ListLength(st *h)
{
	int len = 0;
	st *p;
	p = h->next;
	if(p==NULL)
	   return 0;
	else
	{
		while(p!=NULL)
		{
			len++;
			p = p->next;
		}
	}
	return len;
}

//�������Ա��е�i��Ԫ�ص�ֵ
int Getelem(st *h,int i,int *t)
{
	int temp=0;
	st *p;
	p = h->next;
	if(p==NULL)
	   return 0;
	else
	{
		while(p!=NULL)
		{
			temp++;
			if(temp==i)
			{
				*t=p->num;
				break;
			}
			p = p->next;
		}
	}
}

//���ص�һ������e����Ԫ�ص�λ��
int Locateelem(st *h,int t)
{
	int temp=0;
	st *p;
	p = h->next;
	if(p==NULL)
	   printf("����,���б�\n");
	else
	{
		while(p!=NULL)
		{
			temp++;
			if(t == p->num)
				return temp;
			p = p->next;
		}
	}
}

//��iλ��֮ǰ����Ԫ��
void Listinsert(st *h,int num,int age,int local)
{
	st *p,*q;    //ǰһ��,��һ��
	int temp = 0;
	p = h->next;
    q = p->next;
	if(p == NULL && local!=1)
	    printf("������\n");
	else if(local==1)
	{
		st *t = (st *)malloc(sizeof(st));
		t->num = num;
		t->age = age;
		h->next = t;
		t->next = p;
	}
	else
	{
		while(p!=NULL)
		{
			temp++;
			if(temp == local-1)
			{
				st *t = (st *)malloc(sizeof(st));
				t->num = num;
				t->age = age;
				p->next = t;
				t->next = q;
				break;
			}
			p = p->next;
			if(q->next!=NULL)
			  q = q->next;
		}
	}
}

//ɾ����i��Ԫ��
void Listdelete(st *h,int i)
{
	st *p,*q;
	p = h->next;
	q = p->next;
	int temp=0;
	if(p==NULL)
		printf("������!\n");
	else
	{
		while(p!=NULL)
		{
			temp++;
			if(temp == i-1)
			{
				p->next = q->next;
			}
			p = p->next;
			q = q->next;
		}
	}
}

//����ѧ������
void Sortlist(st *h)    //ֻ��Ҫ�������������
{
	st *p,*q;  
	st *t = (st *)malloc(sizeof(st));   //��ʱ�Ľṹ��
	p = h->next;
	if(p==NULL)
	{
		printf("�Ǻ�,�յ�����!\n");
	}
	else
	{
		for(p=h->next; p!=NULL; p=p->next)
	   {
		   for(q=h->next; q!=NULL; q=q->next)
		   {
			   if( (p->num) < (q->num) )
			   {
				   t->num = p->num;
				   t->age = p->age;
				   p->num = q->num;
				   p->age = q->age;
				   q->num = t->num;
				   q->age = t->age;
			   }
		   }
	   }
	}
}

int main(void)
{
	st *h;   //ͷָ�� 
	h = Initlist(); 
	Show(h);
	Sortlist(h);
	//ClearList(h);
	/*bool temp = Listempty(h);
	if(temp==true)
		printf("����,Ϊ�ձ�\n");
	else
		printf("�Ǻ�,���ǿձ�\n");*/
	//printf("Ԫ�ظ���Ϊ%d\n", ListLength(h) );
	//int len = ListLength(h);  //���㳤��
	//printf("���������뷵�صؼ���Ԫ�ص�ֵ\n");
	//int temp2,e;
	//scanf("%d",&temp2);
	//if(1 <= temp2 && temp2 <= len)
	//{
	//	Getelem(h,temp2,&e);
	//	printf("������ҵ�Ԫ�ص�numΪ%d\n",e);
	//}
	//else
	//	printf("�Բ�,���õ�,���ٳ�������\n");

	/*printf("������������ҵ�Ԫ��,���ǽ���Ϊ����������λ��\n");
	int temp3;
	scanf("%d",&temp3);
	int localtion;
	localtion = Locateelem(h,temp3);
	printf("������ҵ�Ԫ�ص�λ��Ϊ%d\n",localtion);*/

	/*printf("��������Ҫ�����Ԫ�����ݺ�λ��(ѧ��,����,λ��)\n");
	int num1,age1,local1;
	scanf("%d,%d,%d",&num1,&age1,&local1);
	if(local1>=1 && local1<=len)
	  Listinsert(h,num1,age1,local1);*/

	/*printf("����������Ҫɾ����Ԫ�ص�λ��");
	int i;
	scanf("%d",&i);
	Listdelete(h,i);*/
	Show(h);

	system("pause");

	return 0; 
} 