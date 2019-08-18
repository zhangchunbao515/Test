#include <iostream>//不能用<iostream.h>,而且是用尖括号
#include "stack.H"//这个文件是自己定义的，所以只能用引号包含
#include "stack.H"//头文件中的语句决定了当其重复时不进行编译，不重复占用空间，避免重复
#include "Queue.H"
#include "Queue.H"//头文件中的语句决定了当其重复时不进行编译，不重复占用空间，避免重复
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
		Queue<BinTreeNode<T> *> Q;
	public:
		BinaryTree( T eT,int size = 0):Q(size)
		{
			root = NULL;
			endTag = eT;
		}

		~BinaryTree()//析构函数
		{}

		bool isEmpty()//判断二叉树是否为空，如果为空返回true，否则返回false
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

		void createBinaryTree(BinTreeNode<T> *&current);

		void Inorder(BinTreeNode<T> *current);//递归实现中序遍历

		void Postorder(BinTreeNode<T> *current);//递归实现后序遍历

		void Preorder(BinTreeNode<T> *current);//递归实现先序遍历

		/*BinTreeNode<T> * GetTreeNode( T info, BinTreeNode<T> *lchild = NULL, BinTreeNode<T> *rchild = NULL)
		{
			BinTreeNode<T> *p;
			p = new BinTreeNode<T> (info,lchild,rchild);
			return p;
		}*///为测试遍历的正确性增设的代码
		BinTreeNode<T> *getRoot()//获取二叉树的根指针
		{
			return root;
		}

		int Size(BinTreeNode<T> *current);//计算二叉树的结点总数
		int countLeaf(BinTreeNode<T> *current,int &count);
		void Preorder();//非递归的前序遍历
		void Inorder();//非递归的中序遍历
		void PostOrder();//非递归的后序遍历
		void Levelorder();//层次遍历算法，其中要用到队列的支持
		bool deletion();//删除算法
};


template <class T>
void BinaryTree<T> :: createBinaryTree(BinTreeNode<T> *&current)
{
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


//递归实现中序遍历
template <class T>
void BinaryTree<T> :: Inorder(BinTreeNode<T> *current)
{
	if (current !=NULL)//递归结束的条件
	{
		Inorder(current->leftchild);
		cout<<current->data;
		Inorder(current->rightchild);
	}
}


//递归实现后续遍历
template <class T>
void BinaryTree<T> :: Postorder(BinTreeNode<T> *current)
{
	if (current != NULL)//递归结束的条件
	{
		Postorder(current->leftchild);
		Postorder(current->rightchild);
		cout<<current->data;
	}
}


//递归实现先序遍历
template <class T>
void BinaryTree<T> :: Preorder(BinTreeNode<T> *current)
{
	if (current != NULL)//递归结束的条件
	{
		cout<<current->data;
		Preorder(current->leftchild);
		Preorder(current->rightchild);
	}
}


//求二叉树的结点总数
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


//计算叶子结点总数
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
			cout<<"叶子结点的数据值为："<<current->data;
			cout<<endl;
			count++;
			return count;
		}
	}
}


template <class T>
void BinaryTree<T> :: Levelorder()
{



	BinTreeNode<T> *current = root;
	Q.inQueue(current);
	while (!Q.isEmpty())
	{
		Q.outQueue(current);
		cout<<current->data;
		if (current->leftchild != NULL)
			Q.inQueue(current->leftchild);
		if (current->rightchild != NULL)
			Q.inQueue(current->rightchild);
	}
}

template <class T>
bool BinaryTree<T> :: deletion()
{
	BinTreeNode<T> *current = root;
	if (current != NULL)
	{
		Q.inQueue(current);
	}
	while(!Q.isEmpty())
	{
		Q.outQueue(current);
		if (current->leftchild != NULL)
			Q.inQueue(current->leftchild);
		if (current->rightchild != NULL)
			Q.inQueue(current->rightchild);
		delete current;
	}
	cout<<"二叉树为空"<<endl;
	return true;
}


template <class T>
void BinaryTree<T> :: Preorder()
{
	int size;
	cout<<"请输入所需栈的预计最大长度：";
	cin>>size;
	Stack<BinTreeNode<T> *> S(size);
	BinTreeNode<T> *current = root;
	S.Push(current);
	cout<<"非递归算法得到的先序遍历为：";
	while(!S.isEmpty())
	{
		S.Pop(current);
		cout<<current->data;
		if (current->rightchild != NULL)
			S.Push(current->rightchild);
		if (current->leftchild != NULL)
			S.Push(current = current->leftchild);
	}
}


template <class T>
void BinaryTree<T> :: Inorder()
{
	int size;
	cout<<"请输入所需栈的预计最大长度：";
	cin>>size;
	Stack<BinTreeNode<T> *> S1(size);
	BinTreeNode<T> *current = root;
	cout<<"非递归得到的中序遍历序列为：";
	do
	{
		while(current != NULL)
		{
			S1.Push(current);
			current = current->leftchild;
		}

		if (!S1.isEmpty())
		{
			S1.Pop(current);
			cout<<current->data;
			current = current->rightchild;
		}
	}
	while(!S1.isEmpty() || current != NULL);
}

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
