
// ���ڶ���ѵ����ȶ���

// ����ѵĻ������� - С����
// create()			������
// destory()		���ٶ�
// search()			����һ��Ԫ��
// insert()			����һ��Ԫ��
// deletetop()		ɾ���Ѷ�
// getttop()		��öѶ�
// remove()			ɾ������Ԫ��
// adjust()			�������ȼ�
// check()			���ѵ���ȷ��
// down_node()		�ϵ�һ�����
// up_node()		�µ�һ�����
// create_all()		�������齨��

#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef int status;
#define OK 1 
#define ERROR 0
#define MIN -0x4FFFFFFF		// ����С
#define SIZE 50				// �ѵĳ�ʼ��С
#define INC 20				// ��������

// ����ѵĴ洢�ṹ
typedef struct
{
	elemtype *base;		// ��ַ
	int lenth;			// ʹ����
	int size;			// ������
}heap;


status create(heap *h)		// ������
{
	h->base = (elemtype *)malloc((SIZE+1) * sizeof(elemtype));
	h->base[0] = MIN;	// 0 �ŵ�Ԫ������С, ������洦��
	h->lenth = 0;
	h->size = SIZE;
	return OK;
}

void destory(heap *h)		// ���ٶ�
{
	if (h->base) free(h->base);
	h->lenth = h->size = 0;
}

int search(heap *h, elemtype data)	// ˳�����һ��Ԫ��
{
	int i;
	for (i=1; i<=h->lenth; i++)
		if (h->base[i] == data) break;
	if (i == h->lenth + 1) return -1;
	else return i;
}


// �ϵ�һ�����
inline void up_node(heap *h, int p)
{
	int data = h->base[p];	// add ���ϵ���Ԫ��

	// ��ʼ����. p / 2 ���½���˫�׽ڵ�, 2p, 2p+1 �Ǻ���
	// С����, С��Ҫ�ϸ�, �󶥶������෴
	// ���Ҹ����ʵ�λ��, �ٲ���, ���ٸ�ֵ����
	while (data < h->base[p / 2])
	{
		h->base[p] = h->base[p / 2];   // ����³�
		p /= 2;
	}
	h->base[p] = data;	// �ڳ���λ��, ����
}

// �µ�һ�����, p �Ǵ��µ��Ľ��
// �µ�ʱ, Ҫע���Ƿ��к���, �м�������, �����Ƿ�Ҫ�ϸ�
inline void down_node(heap *h, int p)
{
	int len = h->lenth;
	int lc, rc;			// ���Һ���
	elemtype last = h->base[p];	// ��ô������Ľ��, Ҳ��Ϊ�˼��ٸ�ֵ

	while (1)
	{
		// Ҫ��ʱע��, �Ƿ��к��ӽ��
		// �����ĸ�С, С�Ľ���� last �Ƚ�, ����С���ϸ�, �����˳�
		lc = 2 * p;   rc = lc + 1;
		if (lc > len) break;		// û�к���
		else	// �϶�������
		{
			if (rc > len)		// û���Һ���
			{
				// ����С���ϸ�, ��С��, �Ϳ����˳���
				if (h->base[lc] < last)
				{
					h->base[p] = h->base[lc];
					p = lc;		// ��������һ��
				}
				else break;
			}
			else	// ���Ҷ���, ����С��
			{
				// �����Һ�����, ѡһ��С��, ��С�� last ���ϸ�
				if (h->base[lc] < h->base[rc])
				{
					if (h->base[lc] < last)
					{
						h->base[p] = h->base[lc];
						p = lc;		// add ��˫��
					}
					else break;
				}
				else	// �Һ���С
				{
					if (h->base[rc] < last)
					{
						h->base[p] = h->base[rc];
						p = rc;
					}
					else break;
				}
			}
		}
	} // end while
	h->base[p] = last;
}

// �ڶ��в���һ��Ԫ��, ͬʱ������ O(log N)
status insert(heap *h, elemtype data)
{
	if (h->lenth + 1 >= h->size)	// ������, ����
	{
		h->base = (elemtype *)realloc(h->base, 
			(h->size + INC) * sizeof(elemtype));
		h->size += INC;
	}
	h->lenth++;					// ��һ���¿ռ�
	h->base[h->lenth] = data;	// ���� data, ��ʱ�����ƻ�������
	up_node(h, h->lenth);		// ���� data ��λ��, ��֤������
	return OK;
}

// ɾ������һ��Ԫ��, ͬʱ������, O(log N)
// �����һ��Ԫ��, �滻����ɾ���Ľ�㴦, �ٽ����³�����
// �����������滻, ��Ϊ��ֵҪ��ʱ��, ��ʱ�߼����滻����
status remove(heap *h, int add)
{
	if (add < 1 || add > h->lenth) return ERROR;

	h->base[add] = h->base[h->lenth];	// �����һ���ŵ��Ѷ�
	down_node(h, add);		// �ٵ����Ѷ�
	h->lenth--;		// �ǵ�ɾ�����һ��
	return OK;
}

// ��öѶ�Ԫ��
status gettop(heap *h, elemtype *data)
{
	if (h->lenth == 0) return ERROR;	// ����

	*data = h->base[1];
	return OK;
}

// ɾ���Ѷ�Ԫ��
status deletetop(heap *h)
{
	if (remove(h, 1)) return OK;
	else return ERROR;
}

// �������ȼ� 
// С����, �����������ȼ�, ����������ȼ�, �󶥶��෴
status adjust(heap *h, elemtype data, int f)
{
	int add = search(h, data);

	if (add == -1) return ERROR;

	// �������� f, ��ʱ add ������������, ���е��� 
	h->base[add] += f; 
	if (f == 0) return OK;
	else if (f > 0) down_node(h, add);	// �ϵ�����
	else up_node(h, add);				// �µ�����

	return OK;
}

// �������齨��
// ��������ѵ�����, ȫ�������ϵ�
void create_all(heap *h)
{
	int i;
	for (i=h->lenth; i>0; i--) up_node(h, i);
}

// ����Ƿ����С��������, ���Ϸ��� ok
status check(heap *h, int i)
{
	char a = 1, b = 1;
	
	if (2 * i <= h->lenth)		// ���������
	{
		if (h->base[i] > h->base[2*i]) return ERROR;
		a = check(h, 2 * i);	// �ݹ�������
	}
	if (2 * i + 1 <= h->lenth)	// ������Һ���
	{
		if (h->base[i] > h->base[2*i + 1]) return ERROR;
		b = check(h, 2 * i + 1);
	}
	return a && b;
}

int main(void)
{
	heap h;
	int i, n;
	int add, f;
	elemtype data;

	// ���� n ��Ԫ�غ�, ��������������, ȫ������, �������ȶ�����
	create(&h);
	printf("����� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		scanf("%d", &data);		// �߽��ߵ�
//		data = rand() % 100;	// (������) �����ֶ�����, ���Զ���
		insert(&h, data);		// �������
	}
	printf("\n\n���� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		if (gettop(&h, &data))
		{
			printf("%d, ", data);
			deletetop(&h);		// ͬʱɾ���Ѷ�
		}
		else break;
	}
	printf("\n\nɾ��һ��Ԫ��: ");
	scanf("%d", &data);
	add = search(&h, data);
	if (add != -1 && remove(&h, add))	// ɾ������
		printf("ɾ���ɹ�!\n");
	else printf("û�и�Ԫ��!\n");

	printf("\n���� x �����ȼ�, ���� f ��(x f): ");
	scanf("%d %d", &data, &f);
	if (adjust(&h, data, f)) printf("�����ɹ�!\n");
	else printf("û�и�Ԫ��!\n");
	
	printf("\n��������ʣ���Ԫ��: ");
	while (h.lenth != 0)
	{
		gettop(&h, &data);
		printf("%d, ", data);
		deletetop(&h);
	}
	destory(&h);	// ����ԭ����
	create(&h);
	printf("\n\n����һ������, ͳһ����: ");
	scanf("%d", &n);
	for (i=1; i<=n; i++)
	{
		scanf("%d", h.base + i);
//		h.base[i] = rand() % 100;   // (������)
	}
	h.lenth = i - 1;
	create_all(&h);		// �����������鵽���������
	printf("\n��������ʣ���Ԫ��: ");
	while (h.lenth != 0)
	{
		gettop(&h, &data);
		printf("%d, ", data);
		deletetop(&h);
	}
	printf("\n\n");
	destory(&h);
	return 0;
}
