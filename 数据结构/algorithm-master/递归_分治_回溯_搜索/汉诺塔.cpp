
// ��ŵ��

#include <stdio.h>

static int count = 0;

inline void move(char a, char b)
{
	printf("%c -> %c\n", a, b);
	count++;
}

void hanio(char a, char b, char c, int n)
{
	if (n == 1) move(a, c);
	else 
	{
		hanio(a, c, b, n-1);	// �� n-1 ��, a -> b
		move(a, c);				// �� n ��, a -> c
		hanio(b, a, c, n-1);	// �� n-1 ��, b -> c
	}
}

int main(void)
{
	int n;

	printf("���� n : ");
	scanf("%d", &n);
	// �� a �ϵ����Ƶ� c ��
	count = 0;
	hanio('a', 'b', 'c', n);
	printf("����: %d\n", count);

	return 0;
}