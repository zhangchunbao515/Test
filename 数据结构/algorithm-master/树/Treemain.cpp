#include <iostream>
#include "TREE.H"
#include "TREENODE.H"
using namespace std;

void main()
{
	cout<<"请输入所需队列的预计最大长度:";
	int size;
	cin>>size;
	char ch = '#';
	Tree<char> tree(ch,size);

	TreeNode<char> *current = tree. getRoot();
	cout<<"请输入创建树的结点的数据值:";
	tree.createTree(current);
	
	cout<<"前序遍历序列为：";
	tree.Preorder(current);
	cout<<endl;
	
	cout<<"后序遍历序列为：";
	tree.Postorder(current);
	cout<<endl;
	
	cout<<"广度优先遍历序列为:";
	tree.Levelorder();
	cout<<endl;
}

/*===========================================================================
         请输入所需队列的预计最大长度：100
		 请输入创建树的结点的数据值：ABC##DE#G##F###
		 前序遍历序列为：ABCDEGF
		 后续遍历序列为：CBEGDFA
		 广度优先遍历序列为：ABDFCEG
		 Press any key to continue
===========================================================================*/



	
