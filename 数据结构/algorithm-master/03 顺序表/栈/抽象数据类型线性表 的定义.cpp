/*
2015��8��29��22:03:09
���������������Ա� �Ķ��� 
*/

# include <stdio.h>
# include <malloc.h> 

struct Student   //ѧ�� 
{
	int num;                  //ѧ�� 
	int age;                  //���� 
	struct Student * next;    //������һ����ָ�� 
};
typedef struct Student st; 

st *Initlist(void)   //�������� 
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
		//q = s->next;
		//p = s;
		p = q;   //һ��һ������ǰ�� 
		scanf("%d,%d",&num,&age);
	} 
	p->next = '\0';   //����Ǹ�Ԫ���ǿյ� 
	return h; 
}

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
		printf("ѧ��  ����"); 
	    while(p != '\0')
		{
			printf("%d  %d  \n",p->num,p->age);
			p = p->next;   //����� 
		} 
    }

} 

int main(void)
{
	st *h;   //ͷָ�� 
	h = Initlist(); 
	Show(h);
	
	return 0; 
} 
