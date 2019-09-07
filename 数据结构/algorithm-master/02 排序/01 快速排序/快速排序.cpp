     /*--------------��������---------------*/
//���������һ��ѭ��
//�㷨����һ����������С�ķŵ�������ǰ�棬������ķŵ������ĺ���
int Partition(SqList &L,int low,int high)
{
	ElemType pivotkey = L.elem[low];    //��׼��
	while(low<high)  //���ٽ�Ԫ�طŵ��ʵ���λ�ã�ǰС���
	{
		while( (low <high) && (L.elem[high]>=pivotkey) )
			high--;    //�� ����ǰѭ����������pivotkeyС�ģ��ͰѸ�ֵ�ŵ�ǰ��ȥ
		L.elem[low] = L.elem[high];       //�˳�ѭ��ʱ��L.elem[high]<=pivotkey
	    while( (low<high)&& (L.elem[low]<=pivotkey) )
			low++;
		L.elem[high] = L.elem[low];       //�˳�ѭ��ʱ��L.elem[low]>=pivotkey
	}
	L.elem[low] = pivotkey;     //�ع�

	return low;
}
//��������
void QSort(SqList &L,int low,int high)   
{
	int pivotloc;
	if(low<high)
	{
		pivotloc  = Partition(L,low,high);    //����pivotloc��ĳ��Ԫ�ص�λ��
		QSort(L,low,pivotloc-1);   //��pivotloc��λ��һֱ���ݹ飩��low=pivotloc-1   ��ֹ
		QSort(L,pivotloc+1,high);  ///��pivotloc��λ��һֱ���ݹ飩��pivotloc+1=high   ��ֹ
	}
}