#include <iostream>
#include "TREE.H"
#include "TREENODE.H"
using namespace std;

void main()
{
	cout<<"������������е�Ԥ����󳤶�:";
	int size;
	cin>>size;
	char ch = '#';
	Tree<char> tree(ch,size);

	TreeNode<char> *current = tree. getRoot();
	cout<<"�����봴�����Ľ�������ֵ:";
	tree.createTree(current);
	
	cout<<"ǰ���������Ϊ��";
	tree.Preorder(current);
	cout<<endl;
	
	cout<<"�����������Ϊ��";
	tree.Postorder(current);
	cout<<endl;
	
	cout<<"������ȱ�������Ϊ:";
	tree.Levelorder();
	cout<<endl;
}

/*===========================================================================
         ������������е�Ԥ����󳤶ȣ�100
		 �����봴�����Ľ�������ֵ��ABC##DE#G##F###
		 ǰ���������Ϊ��ABCDEGF
		 ������������Ϊ��CBEGDFA
		 ������ȱ�������Ϊ��ABDFCEG
		 Press any key to continue
===========================================================================*/



	
