#include <stdio.h>

// �ݹ鷨, �� n �Ľ׳�
// ����Ȼ��һ���������㷨, �õ��ƹ�ʽ����
__int64 jie(__int64 n)
{
	if (n == 0) return 1;
	else return n * jie(n-1);
}

int main(void)
{
	int n;

	printf("�� n �Ľ׳�, ������n: ");
	scanf("%d", &n);
	if (n < 0 || n >= 17) printf("\n���������Χ!\n");
	else printf("\n���: %ld\n", jie(n));

	return 0;
}
