#include <iostream>
#include "Queue.H"
#include "stack.H"
#include "BinaryTree4.H"
#include "BinaryTree4.H"//对条件编译语句进行测试
using namespace std;
int main()
{
	int size;
	cout<<"请输入所需队列的预计最大空间：";
	cin>>size;
	char ch = '#';
	BinaryTree<char> tree(ch,size) ;

	BinTreeNode<char> *Root;
	BinTreeNode<char> *current;
    cout<<"请按前序优先遍历顺序依次输入结点的数据值：";
	tree.createBinaryTree(current);
	Root =tree. getRoot();


	cout<<"先序优先遍历序列为：";
	tree.Preorder(Root);
	cout<<endl;

	cout<<"后序优先遍历序列为：";
	tree.Postorder(Root);
	cout<<endl;

	cout<<"中序优先遍历序列为：";
	tree.Inorder(Root);
	cout<<endl;

	cout<<"树结点的总数为："<<tree.Size(Root);
	cout<<endl;

	int count = 0;
	cout<<"叶子结点的总数："<<tree.countLeaf(Root,count);
	cout<<endl;

    cout<<"广度优先遍历序列为：";
	tree.Levelorder();
	cout<<endl;


	tree.Preorder();
    cout<<endl;

	tree.Inorder();
	cout<<endl;
	tree.deletion();
	return 0;
}

/*************************************************************************************************
                 请输入所需队列的预计最大长度：100
                 请按前序优先遍历序列一次输入结点的数据值：ABC##DE#G##F###
                 先序优先遍历序列为：ABCDEGF
                 中序优先遍历序列为：CGEFDBA
                 后序优先遍历序列为：CBEGDFA
                 树结点的总数为：7
                 叶子节点的数据值为：C
                 叶子节点的数据值为：G
                 叶子节点的数据值为：F
                 叶子节点的总数为：3
                 广度优先遍历序列为：ABCDEFG
                 请输入所需栈的最大长度：100
                 非递归算法得到的先序遍历序列为：ABCDEGF
                 请输入所需栈的最大长度:100
                 非递归算法得到的中序遍历序列为：CGEFDBA
                 二叉树为空
**************************************************************************************************/



