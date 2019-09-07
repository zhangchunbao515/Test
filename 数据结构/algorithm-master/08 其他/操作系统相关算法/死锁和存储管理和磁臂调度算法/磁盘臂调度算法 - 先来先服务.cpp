
// ���̱۵���֮�����ȷ���
// ������ 100 ���ŵ�, ������� 15 ��Ѱ������, �������һ����ͷλ��
// �������˳��, ��ͷ���ƶ�����

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <queue>

#define NUM 100
int s[NUM];			// 100 ���ŵ�
std::queue<int> q;		// �������

// �����ȷ���
int FIFO(int pos)
{
	int dis = 0;
	int tmp;

	printf("\n����˳��: ");
	while (!q.empty())
	{
		tmp = q.front();   q.pop();
		s[tmp]--;
		printf("%d, ", tmp);
		dis += abs(tmp - pos);		// �ƶ�����
		pos = tmp;			// ȥ����ǰλ��
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
		q.push(tmp);
		printf("%d, ", tmp);
	}
	pos = rand() % NUM;
	printf("\n��ͷ��ʼλ��: %d\n", pos);
	dis = FIFO(pos);
	printf("\n��ͷ�ƶ��ܾ���: %d\n", dis);
	return 0;
}