#include <stdio.h>

// Ǯ���� 1 Ԫ, 5 Ԫ, 10 Ԫ, Ǯ�ұ����Ǳ�����ϵ, ��������̰���㷨
// Ҫ���ҳ�Ǯ�ҵ���������

void zhao(int *y, int *wu, int *shi, int pay)
{
	(*y) = (*wu) = (*shi) = 0;
	while (pay >= 10) { (*shi)++;   pay -= 10; }
	while (pay >= 5) { (*wu)++;   pay -= 5; }
	(*y) += pay;
}

int main(void)
{
	int pay;
	int yi, wu, shi;

	printf("����Ҫ�ҳ���Ǯ��: ");
	scanf("%d", &pay);
	zhao(&yi, &wu, &shi, pay);
	printf("\n�� %d ��һԪ, %d ����Ԫ, %d ��ʮԪ\n", yi, wu, shi);
	printf("���� %d ��Ǯ��\n", yi + wu + shi);

	return 0;
}