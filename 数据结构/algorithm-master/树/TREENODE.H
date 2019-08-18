#ifndef _TREENODE_H_
#define _TREENODE_H_
#include <iostream>
using namespace std;

template <class T>
class TreeNode
{
	public:
		T data;
		TreeNode<T> *leftchild;
		TreeNode<T> *nextsibling;
		TreeNode(T info, TreeNode<T> *newleftchild = NULL ,TreeNode<T> *newnextsibling = NULL)
		{
			data = info;
			leftchild = newleftchild;
			nextsibling = newnextsibling;
		}
};
#endif
			