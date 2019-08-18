
// ���̱۵����㷨֮���Ѱ������
// ������ 100 ���ŵ�, ������� 15 ��Ѱ������, �������һ����ͷλ��
// �������˳��, ��ͷ���ƶ�����

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define NUM 100
int s[NUM];			// 100 ���ŵ�

// �� pos Ϊ����, ������ɨ��, �������Ѱ������
int short_path(int pos)
{
	int dis = 0;
	int left, right;	// left �������, right ���ұ���
	int zuo, you;
	int flag = 1;

	printf("\n����˳��: ");
	left = right = pos;
	while (1)			// ������ɨ��
	{
		for ( ; left  > -1  && s[left]==0;  left--);	// ��ɨ
		for ( ; right < NUM && s[right]==0; right++);	// ��ɨ

		// left == -1 ��ʾ���û����, right == NUM ��ʾ�ұ�û����
		// ���ö����Ƶ�˼���ж�, left, right ������״̬
		switch ((left == -1) + (right == NUM) * 2)
		{
		case 0 :		// s[left], s[right] ����, ��һ�������
			zuo = abs(pos - left);
			you = abs(pos - right);
			if (zuo < you)
			{
				printf("%d, ", left);
				dis += zuo;
				pos = zuo;
				s[left]--;		// ��ձ��
			}
			else 
			{
				printf("%d, ", right);
				dis += you;
				pos = you;
				s[right]--;
			}
			break;
		case 1 :		// �� s[right] ������
			you = abs(pos - right);
			printf("%d, ", right);
			dis += you;
			pos = you;
			s[right]--;
			break;
		case 2 :		// �� s[left]  ������
			zuo = abs(pos - left);
			printf("%d, ", left);
			dis += zuo;
			pos = zuo;
			s[left]--;
			break;
		case 3 :		// s[left], s[right] ��û������
			flag = 0;
			break;
		}
		if (!flag) break;
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
	pos = rand() % NUM;
	printf("\n��ͷ��ʼλ��: %d\n", pos);
	dis = short_path(pos);
	printf("\n��ͷ�ƶ��ܾ���: %d\n", dis);

	return 0;
}