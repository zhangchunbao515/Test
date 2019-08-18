#include <stdio.h>

inline void move(char a, char b)
{
	printf("%c -> %c\n", a, b);
}

// ���غ�ŵ���ƶ��Ĵ���
int hanoi(int n, char a, char b, char c)
{
	static int count = 0;

	if (n > 0)
	{
		hanoi(n-1, a, c, b);	// Ҫ�Ȱ� n-1 ���Ƶ� b
		count++;
		move(a, c);				// �ٰѵ�ǰ n �Ƶ� c
		hanoi(n-1, b, a, c);	// �ٰ� n-1 �� c
	}
	return count;
}

int main(void)
{
	int n;

	printf("hanoi ������\n�� a  �Ƶ� c, ������ n: ");
	scanf("%d", &n);
	n = hanoi(n, 'a', 'b', 'c');
	printf("\nһ���ƶ��� %d ��\n", n);

	return 0;
}
