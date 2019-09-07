#ifndef _TREE_H_
#define _TREE_H_
#include <iostream>
#include "Queue.H"
#include "TREENODE.H"
using namespace std;

template <class T>
class Tree
{
	private:
		TreeNode<T> *root;
		T endTag;
		Queue <TreeNode<T> *> Q;

	public:
		Tree(T eT,int size):Q(size)
		{
			root = NULL;
			endTag = eT;
		}
		~ Tree()
		{
		}

		void createTree(TreeNode<T> *&current );

		void Preorder(TreeNode<T> *current);

		void Postorder(TreeNode<T> *current);
		
		TreeNode<T> *getRoot()//获取树的根指针
		{
			return root;
		}

		void Levelorder();
};

template <class T>
void Tree<T> :: createTree(TreeNode<T> *&current)
{
	current = root;
	T temp;
	
	cin>>temp;
	if (temp != endTag)
	{
		current = new TreeNode<T> (temp);
		if (current == NULL)
		{
			cout<<"空间分配错误"<<endl;
			exit(1);
		}
		
		createTree(current->leftchild);
		createTree(current->nextsibling);
	}
	else
	{
		current = NULL;
	}
	root = current;
}

template <class T>
void Tree<T> :: Preorder(TreeNode<T> *current)
{
	if (current == NULL)
	{
		cout<<"树为空";
		return;
		
	}
	else
	{
		cout<<current->data;
		for(current = current -> leftchild;current != NULL;current = current ->nextsibling)
		{
			Preorder(current);
		}
	}
}

template <class T>
void Tree<T> :: Postorder(TreeNode<T> *current)
{
	TreeNode<T> *p;
	if (current == NULL)
	{
		cout<<"树为空";
		return;
	}

	else
	{
		for(p = current ->leftchild;p != NULL; p = p->nextsibling)
		{
			Postorder(p);
		}
		cout<<current->data;
	}
}


template <class T>
void Tree<T> :: Levelorder()
{
	TreeNode<T> *current = root;
	Q.inQueue(current);
	while(!Q.isEmpty())
	{
		Q.outQueue(current);
		cout<<current->data;
		for(current = current ->leftchild ; current != NULL;current = current->nextsibling)
		{
			Q.inQueue(current);
		}
	}
}
#endif

		




