/*
2015��8��26��19:46:40
Ԥ��֪ʶ-ָ�� 
*/
# include <stdio.h>

int main()
{
	int *p;   //p����ֻ�ܱ��� int* ���͵ı����ĵ�ַ 
	int i=10;
	int j;
	
	p = &i;
	j = *p;
	printf("i=%d,j=%d,*p=%d\n",i,j,*p); 
	
	int a[5] = {1,2,3,4,5}; 
	 //a[3]�ȼ���*(a+3)        *(a+3) ���ʸ��� 
	 
	printf("%p\n",a+1);    //a+1�����ַ     
	printf("%p\n",a+2);
	printf("%p\n",a+3);
	
	return 0;
}
