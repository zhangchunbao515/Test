/*
2015��8��27��22:21:37
�ṹ���ʹ�ø��� 

  Ϊ�˱�ʾһЩ���ӵ�����,����ͨ�Ļ��� �����޷�����Ҫ�� 
  ��������    ����Ƚ�����,�о����� ,û�з��� 
*/
# include <stdio.h>
# include <string.h> 

struct Student
{
	int num;
	char name[200];
	int age;
};     //�ֺŲ���ʡ

typedef struct Student st;  

int main(void)
{
	st p1 = {8,"��纮��2",19};
	printf("ѧ��:%d \n����:%s \n����:%d \n",p1.num,p1.name,p1.age); 
	p1.num=2;
	strcpy(p1.name,"��纮��");
	printf("ѧ��:%d \n����:%s \n����:%d \n",p1.num,p1.name,p1.age); 
	
	return 0; 
} 
