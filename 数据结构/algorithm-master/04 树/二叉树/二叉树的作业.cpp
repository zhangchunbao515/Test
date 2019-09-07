//二叉树的二叉链表的物理实现
#include <iostream>
#include "stdlib.h"
using namespace std;

const int stackIncreament = 20;//全局变量，用于溢出处理时动态的增加需要的存储单元数
template <class T>
class Stack
{
	private:
		T *elements;
		int maxSize;
		int top;//栈顶指针
		void overflowprocess();//溢出处理函数
	public:
		Stack ( int size )
		{
			maxSize = size;
			elements = new T[maxSize];
			//此函数不能使用，系统提示不提供，assert( elements != NULL );//使用了断言语句，当参数表达式成立时，程序继续执行；否则进入中断处理程序，程序终止其代替语句如下
			if ( elements == NULL)
			{
				cout<<"分配存储空间错误\n"<<endl;
				exit(1);
			}//判断动态申请空间是否成功，标注化的语句
			top = -1;
		}
		~Stack()
		{
			delete []elements;//析构数组类的指针对象时用的标注化方法
		}
		bool Push( const T &x );//压入栈顶
		bool Pop( T &x );//出栈
		bool getTop(T &x);//获得栈顶元素的值
		bool isEmpty()
		{
			if (top == -1)
				return true;
			else
				return false;
		};
};

//此函数为溢出处理函数，当分配的空间不足时，动态重新为其分配存储空间
template <class T>
void Stack<T> :: overflowprocess()
{
	T *arrStack = new T[maxSize + stackIncreament];//动态重新申请一个更大的存储空间，用于溢出处理
	if (arrStack == NULL)
	{
		cout<<"分配存储空间错误\n"<<endl;
		exit(1);
	}//标准化的判断动态申请的空间是否成功的申请
	int i=0;
	for ( i = 0;i <=top;i++ )
	{
		arrStack[i] = elements[i];//将原来数组的每一个元素分别赋值给新创建的数组
	}
	delete []elements;//析构旧数组
	elements = arrStack;//将新创建的更大的数组命名为前数组的名字，便于操作
}


template <class T>
bool Stack<T> :: Push( const T &x )//压栈函数，带一个引用型参数
{
	if (top == maxSize - 1) //判断栈是否为满，如果满，则调用溢出处理函数重新分配空间
	{
		cout<<"分配空间不足，调用类函数重新为其分配空间";
		cout<<endl;
		overflowprocess();
	}
	top++;
	elements[top] = x;//现将栈顶指针上移，然后将用户需要的数值压入栈顶
	return true;//返回语句，无条件的转移语句，执行return之后，后面的语句将不再执行，因为已回到程序断点
}


template <class T>
bool Stack<T> :: Pop( T &x )//出栈函数
{
	if ( top == -1)//判断栈是否为空，如果为空直接返回；否则执行下面的语句
	{
		//cout<<"栈为空"<<endl;
		return false;
	}
	else
	{
		x = elements[top];
		top--;
		return true;
	}
}


template <class T>
bool Stack<T> :: getTop( T &x )//获得栈顶指针的值，用引用型参数向外传递栈顶元素的值
{
	if ( top == -1 )//判断栈是否为空
	{
		//cout<<"栈为空"<<endl;
		return false;
	}
	else
	{
		x = elements[top];
		return true;
	}
}

template <class T>
class Queue
{
	public:
		int front;
		int rear;
		T *arrQueue;
		int maxSize;
		Queue(int sz)
		{
			front = rear = 0;
			maxSize = sz;
			arrQueue = new T[maxSize];
			if (arrQueue == NULL)
			{
				cout<<"分配存储空间错误\n"<<endl;
				exit(1);
			}
		}
		~Queue()
		{
			delete[] arrQueue;
		}
		bool inQueue(const T &value);
		bool outQueue(T &value);
		bool getQueuetop(T &value);
		bool isEmpty();
		bool isFull();
};


template <class T>
bool Queue<T> :: isEmpty()
{
	if (front == rear)
	{
		//cout<<"循环队列为空"<<endl;
		return true;
	}
	else
	{
		return false;
	}
}


template <class T >
bool Queue<T> :: isFull()
{
	if (front == (rear+1)%maxSize)
		return true;
	else return false;
}


template <class T>
bool Queue<T> :: inQueue(const T&value)
{
	if (isFull())
	{
		cout<<"队列满"<<endl;
		return false;
	}
	else
	{
		arrQueue[rear] = value;
		rear = (rear+1)%maxSize;
		return true;
	}
}



template <class T>
bool Queue<T> :: outQueue(T &value)
{
	if (isEmpty())
	{
		cout<<"队列为空"<<endl;
		return false;
	}
	else
	{
		value=arrQueue[front];
		front = (front+1)%maxSize;
		return true;
	}
}

template <class T>
bool Queue<T> :: getQueuetop(T&value)
{
	if (isEmpty())
	{
		cout<<"队列为空"<<endl;
		return false;
	}
	else
	{
		value=arrQueue[front];
		return true;
	}
}

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


/*template <class T>
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
	while(!S1.isEmpty() || current != NULL)
}*/

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

	//tree.Inorder();
	//cout<<endl;
	tree.deletion();
    return 0;

}








