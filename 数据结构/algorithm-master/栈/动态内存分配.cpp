/*
2015��8��28��16:15:25
��̬�����ڴ� 
*/
# include <stdio.h>
# include <malloc.h> 
# include <time.h>
# include <stdlib.h>

int main(void)
{
	int *p;
	int len;
	printf("��������Ҫ��������鳤��:");
	scanf("%d",&len); 
	p = (int *)malloc(sizeof(int)*len);    //���ص�һ���ֽڵĵ�ַ 
	if(p!=NULL)       //����NULL�����д,��Ȼ��ʧ�� 
	{
		printf("��̬�������ɹ�!");
		srand(time(0));
		for(int i=0;i<len;i++)
		{
			p[i] = rand()%20;
		} 
	}
	printf("�������:");
	for(int i=0;i<len;i++)
	{
		printf("%4d\n",p[i]);
	}
	free(p); 
	
	return 0;
}
