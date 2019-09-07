
// �ں���������, Լ��һ�ڸ����� (700 MB), �ҳ�����ǰ k ������
// �ڴ����� 1 MB, ���ֲ����� int ��Χ
// �ⷨ, ����������һ��һ�����, �ӶѶ�����, ͨ���ǴӶѵͽ����
// ���ҽ��ѿ����� k ��Ԫ��, �����ϵ�Ԫ�ض���

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int num = 100000000;		// ���ָ���
const int k = 30;				// ǰ k ��
const int INT_MIN = -2147483647;

int heap[k + 1];	// ��С��

// ������� num ������, Լ 500 MB
int random_write(char *path)
{
	FILE *out = NULL;
	int i, j, len;
	char buf[12];

	out = fopen(path, "wt");
	if (out == NULL) return 0;
	srand(time(NULL));
	for (i=0; i<num; i++)
	{
		len = rand() % 9 + 1;
		for (j=0; j<len; j++) 
			buf[j] = rand() % 10 + '0';
		buf[len] = '\n';
		buf[++len] = '\0';
		fwrite(buf, len, 1, out);
	}
	fclose(out);		// �ǵ�Ҫ�ر�
	return 1;
}

void init_heap(void)		// ��ʼ����С��
{
	for (int i=0; i<=k; i++)
		heap[i] = INT_MIN;
}

// ���Խ��� pos λ��Ԫ���µ�
void node_down(int pos)
{
	int key = heap[pos];
	int left, right;

	while (pos <= k)
	{
		left = 2 * pos;
		right = 2 * pos + 1;
		if (left <= k)
		{
			if (right <= k)		// ���Һ��Ӷ���
			{
				if (heap[left] <= heap[right] && key > heap[left])
				{
					heap[pos] = heap[left];
					pos = left;
				}
				else if (heap[left] >= heap[right] && key > heap[right])
				{
					heap[pos] = heap[right];
					pos = right;
				}
				else break;
			}
			else		// ֻ������
			{
				if (key >= heap[left])
				{
					heap[pos] = heap[left];
					pos = left;
				}
				else break;
			}
		}
		else break;
	}
	heap[pos] = key;
}

// ����в���һ��Ԫ��, ͬʱ��֤���в����� k ��Ԫ��
void insert(int *heap, int data)
{
	if (data <= heap[1]) return ;	// Ԫ��û�Ѷ���
	heap[1] = data;
	node_down(1);		// �����µ��Ѷ�
}

int main(void)
{
	char *path = "c:\\input.dat";
	FILE *in = NULL;
	int data, i;
	unsigned int t1, t2;

	printf("������������ %s\n", path);
	random_write(path);
	in = fopen(path, "rt");
	if (in == NULL) return 0;

	// ��ʼ����
	init_heap();

	// ѭ���������ݴ���
	printf("���ڴ�������\n", path);
	t1 = clock();
	while (fscanf(in, "%d", &data) != EOF)
	{
		insert(heap, data);
	}
	t2 = clock();
	printf("�����ǰ %d ��Ԫ��:\n", k);
	for (i=1; i<=k; i++)
		printf("%d\n", heap[i]);
	printf("\n��ʱ: %.3f ��\n", (t2 - t1) / 1000.0);
	fclose(in);
	remove(path);

	return 0;
}