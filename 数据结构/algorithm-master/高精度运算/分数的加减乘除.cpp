
#include <stdio.h>

typedef struct
{
	int z;		// ����
	int m;		// ��ĸ
}fen;

int gcd(int a, int b)		// ���Լ��
{
	int r;

	while (b)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void simple(fen *f)			// ��������
{
	int d = gcd(f->z, f->m);

	f->z /= d;
	f->m /= d;
	if (f->z < 0 && f->m < 0)
	{ f->z = -f->z;   f->m = -f->m; }
}

fen add(fen f1, fen f2)		// �ӷ�, ͬʱ����
{
	fen f3;
	int m1 = f1.m;
	int m2 = f2.m;

	f1.m *= m2;
	f1.z *= m2;
	f2.m *= m1;
	f2.z *= m1;
	f3.z = f1.z + f2.z;
	f3.m = f1.m;
	simple(&f3);

	return f3;
}

fen sub(fen f1, fen f2)		// ����ת��Ϊ�ӷ�
{
	f2.z = -f2.z;
	return add(f1, f2);
}

fen mul(fen f1, fen f2)		// �˷�
{
	f1.z *= f2.z;
	f1.m *= f2.m;
	simple(&f1);

	return f1;
}

fen div(fen f1, fen f2)		// ����ת��Ϊ�˷�
{
	int tmp;

	tmp = f2.z;
	f2.z = f2.m;
	f2.m = tmp;

	return mul(f1, f2);
}

int main(void)
{
	fen f1, f2, f3;

	while (1)
	{
		// ��ĸ����Ϊ 0, ����Ϊ 0 ����ֵΪ 0
		printf("\n�������, ��ĸ: ");
		scanf("%d %d", &(f1.z), &(f1.m));
		printf("�������, ��ĸ: ");
		scanf("%d %d", &(f2.z), &(f2.m));
		f3 = add(f1, f2);
		printf("���: %d / %d\n", f3.z, f3.m);
		f3 = sub(f1, f2);
		printf("���: %d / %d\n", f3.z, f3.m);
		f3 = mul(f1, f2);
		printf("���: %d / %d\n", f3.z, f3.m);
		f3 = div(f1, f2);
		printf("���: %d / %d\n", f3.z, f3.m);
	}
	return 0;
}