
// ���̱۵����㷨֮�����㷨
// ������ 100 ���ŵ�, ������� 15 ��Ѱ������, 
// �������һ����ͷλ��, �������һ���ƶ�����
// �������˳��, ��ͷ���ƶ�����

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define NUM   100
int s[NUM];			// 100 ���ŵ�
int DIR;			// �ƶ�����, ��-1, ��+1
int d[2] = {-1, +1};

// �����㷨, ��ͷһֱ��һ�������ƶ�, ֱ���÷���û��������
// �������ɨ��
int dian_ti(int pos)
{
	int dis = 0;
	int cur = pos;
	int flag;
	int count;
	// count ͳ��Ѱ�ҵĴ���, ������� NUM �λ�û�ҵ�˵����������
	// �������һ������, ����� count
	
	printf("\n����˳��: ");
	while (1)
	{
		flag = 0;
		count = 0;
		while (1)		// ��һ��������Ĵŵ�
		{
			cur += DIR;
			if (cur <= -1)		// ���Խ��, ����
			{
				cur = 0;
				DIR = 1;
			}
			else if (cur >= NUM)	// �Ҷ�Խ��, ����
			{
				cur = NUM - 1;
				DIR = -1;
			}
			if (s[cur] != 0)		// �ҵ�
			{
				s[cur]--;
				count = 0;
				flag = 1;
				break;
			}
			count++;
			if (count > NUM)		// û��������
			{
				count = 0;
				flag = 0;
				break;
			}
		}
		if (!flag) break;		// �Ҳ�����
		printf("%d, ", cur);
		dis += abs(pos - cur);
		pos = cur;
	}
	return dis;
}

int main(void)
{
	int pos;		// ��ͷλ��
	int dis;		// �ƶ��ܾ���
	int n = 15;
	int i, tmp;

	memset(s, 0, sizeof(s));
	srand(time(NULL));
	printf("����˳��: ");
	for (i=0; i<n; i++)
	{
		tmp = rand() % NUM;
		s[tmp]++;
		printf("%d, ", tmp);
	}
	DIR = d[rand() % 2];
	pos = rand() % NUM;
	printf("\n��ͷ��ʼλ��: %d\n", pos);
	dis = dian_ti(pos);
	printf("\n��ͷ�ƶ��ܾ���: %d\n", dis);

	return 0;
}