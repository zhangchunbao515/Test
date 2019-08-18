#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>

typedef int status;
typedef int elemtype;

#define OK 1
#define ERROR 0
#define OVERFLOW -1	// ��ַ���
#define MAX_DIM 10	// ���ά�� 10 ά

// �����˳�򴢴�ṹ
typedef struct
{
	elemtype *base;		// ����Ļ�ַ
	int dim;			// ��¼ά��
	int *bound;			// ��¼ά�ȣ��� int a[10][10];
	int *dp;			// ����ӳ���������ƶ�̬�滮�ļ�¼����
}array;

status create(array *a, int dim, ...)
{
	// ���ά��
	// ����ά�ȣ�����ÿά��ά��
	// ����ÿά��ά�磬����ռ��ܴ�С������
	// ���㺯��ӳ������Ϊ�˱���ÿ���ظ��ļ���
	
	int i;
	int size;
	va_list aq;

	// ��ʼ��� dim...
	if (dim <= 0 && dim > MAX_DIM) return ERROR;
	a->dim = dim;

	// ��ʼ��¼ÿάά��...
	a->bound = (int *)malloc(dim * sizeof(int));
	if (!a->bound) return ERROR;
	size = 1;
	va_start(aq, dim);		// �� aq ջ����ȡ����
	for (i=0; i<dim; i++)	// ��¼ÿάά��
	{
		a->bound[i] = va_arg(aq, int);
		size *= a->bound[i];	// ˳������ܴ�С
	}
	va_end(aq);

	// ��ʼ�����ܿռ�...
	a->base = (elemtype *)malloc(size * sizeof(int));
	if (!a->base) return ERROR;

	// ��ʼ���㺯��ӳ����...
	a->dp = (int *)malloc(dim * sizeof(int));
	if (!a->dp) return ERROR;
	a->dp[dim-1] = 1;
	for (i=dim-2; i>=0; i--)
	{
		a->dp[i] = a->dp[i+1] * a->bound[i+1];
		// �þ仰���� DP ��˼�룬�ÿռ任ʱ��
	}
	return OK;
}

status destory(array *a)
{
	if (a->base) free(a->base);
	a->base = NULL;
	if (a->bound) free(a->bound);
	a->bound = NULL;
	if (a->dp) free(a->dp);
	a->dp = NULL;
	
	return OK;
}

// Ѱ����Ե�ַ, �Ҳ����ͷ��� OVERFLOW
// ����������ջ aq �ù���������
int find(array *a, va_list *aq)
{
	// ���� a �Ƕ���ά�ģ��Ҳſ�����ȡ���ٲ���
	// ���ݶ��ٲ������Ҳſ��Լ����ַ
	// ����ӳ�� dp �ڴ˴����Ա����ظ����㣬
	
	int address;	// ��Ե�ַ
	int border;		// ��ǰά��
	int i;

	address = 0;
	for (i=0; i<a->dim; i++)
	{
		border = va_arg(*aq, int);
		// ���ά��
		if (border<0 || border>=a->bound[i]) return OVERFLOW;
		address += border * a->dp[i];
		// border �൱��Ȩֵ
	}
	return address;
}

// �޸�ֵ������ a[1][2][3] = 100;
status update(array *a, elemtype *data, ...)
{
	// �ҵ���Ե�ַ
	// ��ַ���ʣ�Ȼ����޸�
	va_list aq;
	int address;

	va_start(aq, data);
	address = find(a, &aq);
	va_end(aq);
	if (address < 0 || address >= a->bound[a->dim]*a->dp[a->dim]) return ERROR;
	*(a->base + address) = *data;

	return OK;
}

// ȡֵ������ b = a[1][2][3]
status getvalue(array *a, elemtype *back, ...)
{
	va_list aq;
	int addr;

	va_start(aq, back);
	addr = find(a, &aq);
	va_end(aq);
	if (addr < 0) return ERROR;
	*back = *(a->base + addr);

	return OK;
}

int main(void)
{
	array a;
	elemtype data;
	int i, j;
	elemtype num = 0;

	create(&a, 2, 5, 10);
	data = 520;
	if (update(&a, &data, 2, 3)) printf("��ֵ�ɹ�!\n");
	else printf("��ֵʧ��!\n");
	if (update(&a, &data, 2, 17)) printf("��ֵ�ɹ�!\n");
	else printf("��ֵʧ��!\n");

	if (getvalue(&a, &data, 2, 3)) printf("ȡֵ�ɹ���%d\n", data);
	else printf("ȡֵʧ��!\n");
	if (getvalue(&a, &data, 7, 2)) printf("ȡֵ�ɹ���%d\n", data);
	else printf("ȡֵʧ��!\n");

	// ��ֵ��ȡֵ����ͨ��
	for (i=0; i<5; i++)
	{
		for (j=0; j<10; j++)
		{
			update(&a, &num, i, j);
			num++;
		}
	}
	for (i=0; i<5; i++)
	{
		for (j=0; j<10; j++)
		{
			getvalue(&a, &num, i, j);
			printf("%3d", num);
		}
		printf("\n");
	}
	destory(&a);

	return 0;
}