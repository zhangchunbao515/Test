#include <stdio.h>

// ���ڴ��͵Ľṹ, �����ڽ���, ���Ǿͽ������ǵĵ�ַ

typedef struct		// ��������ṹ�ܴ�
{
	int key;
	int other1;
	char *other2;
}keytype;

// �Ե�ַ��������, ��ʵ�����ñ������취, �����ò���
void addr_sort(keytype *add[], int n)
{
	int i, j;
	keytype *tmp;

	for (i=1; i<n; i++)
	{
		if (add[i-1]->key > add[i]->key)
		{
			tmp = add[i];
			for (j=i; j>0; j--)
			{
				if (add[j-1]->key > tmp->key)
					add[j] = add[j-1];
				else break;
			}
			add[j] = tmp;
		}
	}
}

int main(void)
{
	int i, n;
	keytype data[100];
	keytype *add[100];

	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) 
	{
		add[i] = &data[i];		// ��¼��ַ
		scanf("%d", &data[i].key);
	}
	addr_sort(add, n);		// �Ե�ַ����
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", add[i]->key);
	printf("\n\n");
	return 0;
}