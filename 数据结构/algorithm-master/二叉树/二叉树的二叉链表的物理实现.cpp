//二叉树的二叉链表的物理实现
#include <iostream>
#include "stdlib.h"
using namespace std;

//二叉树的结点类
template <class T>
class BinTreeNode
{
	public:
		T data;
		BinTreeNode<T> *leftchild;
		BinTreeNode<T> *rightchild;
		BinTreeNode(const T info, BinTreeNode<T> *lchild = NULL, BinTreeNode<T> *rchild = NULL)
		{
			data = info;
			leftchild = lchild;
			rightchild = rchild;
		}
		BinTreeNode(BinTreeNode<T> *lchild = NULL, BinTreeNode<T> *rchild = NULL)
		{
			leftchild = lchild;
			rightchild = rchild;
		}

};

template <class T>
class BinaryTree
{
	public:
		BinTreeNode<T> *root;
		T endTag;
	public:
		BinaryTree( T eT)
		{
			root = NULL;
			endTag = eT;
		}

		~BinaryTree()
		{}

		bool isEmpty()
		{
			if (root == NULL)
			{
				cout<<"二叉树为空";
				return true;
			}
			else
			{
				cout<<"二叉树不为空";
				return false;
			}
		}

		void createBinaryTree();

		void Inorder(BinTreeNode<T> *current);//递归实现中序遍历

		void Postorder(BinTreeNode<T> *current);//递归实现后序遍历

		void Preorder(BinTreeNode<T> *current);//递归实现先序遍历

		BinTreeNode<T> * GetTreeNode( T info, BinTreeNode<T> *lchild = NULL, BinTreeNode<T> *rchild = NULL)
		{
			BinTreeNode<T> *p;
			p = new BinTreeNode<T> (info,lchild,rchild);
			return p;
		}
		BinTreeNode<T> *getRoot()
		{
			return root;
		}



};


template <class T>
void BinaryTree<T> :: createBinaryTree()
/*{
	T temp;
	cin>>temp;
	if (temp != endTag)
	{
		current = new BinTreeNode<T> (temp);
		if (current == NULL)
		{
			cout<<"空间分配错误"<<endl;
			exit(1);
		}
		createBinaryTree(current->leftchild);
		createBinaryTree(current->rightchild);
	}
	else
	{
		current = NULL;
	}
}*/
{
	BinTreeNode<T> *a, *b, *c, *d, *e, *f, *g, *h, *i;
	g = GetTreeNode('G');
    h = GetTreeNode('H');
    i = GetTreeNode('I');
	d = GetTreeNode('D');
	e = GetTreeNode('E',g, (BinTreeNode<char> *)NULL);
    f = GetTreeNode('F',h, i);
	b = GetTreeNode('B',d, e);
	c = GetTreeNode('C',(BinTreeNode<char> *)NULL, f);
	a = GetTreeNode('A',b, c);
	root = a;
}



template <class T>
void BinaryTree<T> :: Inorder(BinTreeNode<T> *current)
{
	if (current !=NULL)
	{
		Inorder(current->leftchild);
		cout<<current->data;
		Inorder(current->rightchild);
	}
}

template <class T>
void BinaryTree<T> :: Postorder(BinTreeNode<T> *current)
{
	if (current != NULL)
	{
		Postorder(current->leftchild);
		Postorder(current->rightchild);
		cout<<current->data;
	}
}

template <class T>
void BinaryTree<T> :: Preorder(BinTreeNode<T> *current)
{
	if (current != NULL)
	{
		cout<<current->data;
		Preorder(current->leftchild);
		Preorder(current->rightchild);
	}
}


int main()
{
	char ch = '#';
	BinaryTree<char> tree(ch) ;

	BinTreeNode<char> *Root;

	tree.createBinaryTree();
	Root =tree. getRoot();

	tree.Preorder(Root);
	cout<<endl;

	tree.Postorder(Root);
	cout<<endl;

	tree.Inorder(Root);
	cout<<endl;
	return 0;
}








