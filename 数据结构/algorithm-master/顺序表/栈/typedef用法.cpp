/*
2015��8��30��22:39:41
typedef�÷� 
*/
# include <stdio.h>

typedef struct Student
{
	int age;
	int num;
}* PSTU,PSU;    //PSTU �ȼ��� struct Student *    
//PSU�ȼ��� truct Student

int main(void)
{
	PSU st;
	PSTU ps = &st;
	ps->age = 99;
	printf("%d \n",st.age);
	
	return 0; 
} 
