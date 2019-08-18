//�������Ķ������������ʵ��
#include <iostream>
#include "stdlib.h"
using namespace std;

//�������Ľ����
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

		~BinaryTree()//��������
		{}

		bool isEmpty()//�ж϶������Ƿ�Ϊ�գ����Ϊ�շ���true�����򷵻�false
		{
			if (root == NULL)
			{
				cout<<"������Ϊ��";
				return true;
			}
			else
			{
				cout<<"��������Ϊ��";
				return false;
			}
		}

		void createBinaryTree(BinTreeNode<T> *&current);

		void Inorder(BinTreeNode<T> *current);//�ݹ�ʵ���������

		void Postorder(BinTreeNode<T> *current);//�ݹ�ʵ�ֺ������

		void Preorder(BinTreeNode<T> *current);//�ݹ�ʵ���������

		/*BinTreeNode<T> * GetTreeNode( T info, BinTreeNode<T> *lchild = NULL, BinTreeNode<T> *rchild = NULL)
		{
			BinTreeNode<T> *p;
			p = new BinTreeNode<T> (info,lchild,rchild);
			return p;
		}*///Ϊ���Ա�������ȷ������Ĵ���
		BinTreeNode<T> *getRoot()//��ȡ�������ĸ�ָ��
		{
			return root;
		}

		int Size(BinTreeNode<T> *current);//����������Ľ������
		int countLeaf(BinTreeNode<T> *current,int &count);
		void Preorder1(BinTreeNode<T> *current);//�ǵݹ��ǰ�����
		void Inorder1(BinTreeNode<T> *current);//�ǵݹ���������
		void PostOrder1(BinTreeNode<T> *current);//�ǵݹ�ĺ������
};


template <class T>
void BinaryTree<T> :: createBinaryTree(BinTreeNode<T> *&current)
{
	T temp;
	cout<<"�밴ǰ�����˳�����������������ֵ��";
	cin>>temp;
	if (temp != endTag)
	{
		current = new BinTreeNode<T> (temp);
		if (current == NULL)
		{
			cout<<"�ռ�������"<<endl;
			exit(1);
		}

		createBinaryTree(current->leftchild);
		createBinaryTree(current->rightchild);
	}
	else
	{
		current = NULL;
	}
	root = current;
}
/*{
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
}*/


//�ݹ�ʵ���������
template <class T>
void BinaryTree<T> :: Inorder(BinTreeNode<T> *current)
{
	if (current !=NULL)//�ݹ����������
	{
		Inorder(current->leftchild);
		cout<<current->data;
		Inorder(current->rightchild);
	}
}


//�ݹ�ʵ�ֺ�������
template <class T>
void BinaryTree<T> :: Postorder(BinTreeNode<T> *current)
{
	if (current != NULL)//�ݹ����������
	{
		Postorder(current->leftchild);
		Postorder(current->rightchild);
		cout<<current->data;
	}
}


//�ݹ�ʵ���������
template <class T>
void BinaryTree<T> :: Preorder(BinTreeNode<T> *current)
{
	if (current != NULL)//�ݹ����������
	{
		cout<<current->data;
		Preorder(current->leftchild);
		Preorder(current->rightchild);
	}
}


//��������Ľ������
template <class T>
int BinaryTree<T> ::Size(BinTreeNode<T> *current)
{
	if (current == NULL)
	{
		return 0;
	}

	else
	{

		return 1+Size(current->leftchild)+Size(current->rightchild);
	}
}


//����Ҷ�ӽ������
template <class T>
int BinaryTree<T> :: countLeaf(BinTreeNode<T> *current,int &count)
{
	if (current == NULL)
		return count;
	else
	{
		countLeaf(current->leftchild,count);
		countLeaf(current->rightchild,count);
		if (current->leftchild == NULL && current->rightchild == NULL)
		{
			count++;
			return count;
		}
	}
}



int main()
{
	char ch = '#';
	BinaryTree<char> tree(ch) ;

	BinTreeNode<char> *Root;
	BinTreeNode<char> *current;

	tree.createBinaryTree(current);
	Root =tree. getRoot();


	cout<<"�����������Ϊ��";
	tree.Preorder(Root);
	cout<<endl;

	cout<<"������������Ϊ��";
	tree.Postorder(Root);
	cout<<endl;

	cout<<"�����������Ϊ��";
	tree.Inorder(Root);
	cout<<endl;

	cout<<"��������Ϊ��"<<tree.Size(Root);
	cout<<endl;

	int count = 0;
	cout<<"Ҷ�ӽ���������"<<tree.countLeaf(Root,count);
	cout<<endl;
	return 0;
}








