//�������Ķ������������ʵ��
#include <iostream>
#include "stdlib.h"
using namespace std;

const int stackIncreament = 20;//ȫ�ֱ����������������ʱ��̬��������Ҫ�Ĵ洢��Ԫ��
template <class T>
class Stack
{
	private:
		T *elements;
		int maxSize;
		int top;//ջ��ָ��
		void overflowprocess();//���������
	public:
		Stack ( int size )
		{
			maxSize = size;
			elements = new T[maxSize];
			//�˺�������ʹ�ã�ϵͳ��ʾ���ṩ��assert( elements != NULL );//ʹ���˶�����䣬���������ʽ����ʱ���������ִ�У���������жϴ�����򣬳�����ֹ������������
			if ( elements == NULL)
			{
				cout<<"����洢�ռ����\n"<<endl;
				exit(1);
			}//�ж϶�̬����ռ��Ƿ�ɹ�����ע�������
			top = -1;
		}
		~Stack()
		{
			delete []elements;//�����������ָ�����ʱ�õı�ע������
		}
		bool Push( const T &x );//ѹ��ջ��
		bool Pop( T &x );//��ջ
		bool getTop(T &x);//���ջ��Ԫ�ص�ֵ
		bool isEmpty()
		{
			if (top == -1)
				return true;
			else
				return false;
		};
};

//�˺���Ϊ�����������������Ŀռ䲻��ʱ����̬����Ϊ�����洢�ռ�
template <class T>
void Stack<T> :: overflowprocess()
{
	T *arrStack = new T[maxSize + stackIncreament];//��̬��������һ������Ĵ洢�ռ䣬�����������
	if (arrStack == NULL)
	{
		cout<<"����洢�ռ����\n"<<endl;
		exit(1);
	}//��׼�����ж϶�̬����Ŀռ��Ƿ�ɹ�������
	int i=0;
	for ( i = 0;i <=top;i++ )
	{
		arrStack[i] = elements[i];//��ԭ�������ÿһ��Ԫ�طֱ�ֵ���´���������
	}
	delete []elements;//����������
	elements = arrStack;//���´����ĸ������������Ϊǰ��������֣����ڲ���
}


template <class T>
bool Stack<T> :: Push( const T &x )//ѹջ��������һ�������Ͳ���
{
	if (top == maxSize - 1) //�ж�ջ�Ƿ�Ϊ����������������������������·���ռ�
	{
		cout<<"����ռ䲻�㣬�����ຯ������Ϊ�����ռ�";
		cout<<endl;
		overflowprocess();
	}
	top++;
	elements[top] = x;//�ֽ�ջ��ָ�����ƣ�Ȼ���û���Ҫ����ֵѹ��ջ��
	return true;//������䣬��������ת����䣬ִ��return֮�󣬺������佫����ִ�У���Ϊ�ѻص�����ϵ�
}


template <class T>
bool Stack<T> :: Pop( T &x )//��ջ����
{
	if ( top == -1)//�ж�ջ�Ƿ�Ϊ�գ����Ϊ��ֱ�ӷ��أ�����ִ����������
	{
		//cout<<"ջΪ��"<<endl;
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
bool Stack<T> :: getTop( T &x )//���ջ��ָ���ֵ���������Ͳ������⴫��ջ��Ԫ�ص�ֵ
{
	if ( top == -1 )//�ж�ջ�Ƿ�Ϊ��
	{
		//cout<<"ջΪ��"<<endl;
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
				cout<<"����洢�ռ����\n"<<endl;
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
		//cout<<"ѭ������Ϊ��"<<endl;
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
		cout<<"������"<<endl;
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
		cout<<"����Ϊ��"<<endl;
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
		cout<<"����Ϊ��"<<endl;
		return false;
	}
	else
	{
		value=arrQueue[front];
		return true;
	}
}

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
		Queue<BinTreeNode<T> *> Q;
	public:
		BinaryTree( T eT,int size = 0):Q(size)
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
		void Preorder();//�ǵݹ��ǰ�����
		void Inorder();//�ǵݹ���������
		void PostOrder();//�ǵݹ�ĺ������
		void Levelorder();//��α����㷨������Ҫ�õ����е�֧��
		bool deletion();//ɾ���㷨
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
			cout<<"Ҷ�ӽ�������ֵΪ��"<<current->data;
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
	cout<<"������Ϊ��"<<endl;
	return true;
}


template <class T>
void BinaryTree<T> :: Preorder()
{
	int size;
	cout<<"����������ջ��Ԥ����󳤶ȣ�";
	cin>>size;
	Stack<BinTreeNode<T> *> S(size);
	BinTreeNode<T> *current = root;
	S.Push(current);
	cout<<"�ǵݹ��㷨�õ����������Ϊ��";
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
	cout<<"����������ջ��Ԥ����󳤶ȣ�";
	cin>>size;
	Stack<BinTreeNode<T> *> S1(size);
	BinTreeNode<T> *current = root;
	cout<<"�ǵݹ�õ��������������Ϊ��";
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
	cout<<"������������е�Ԥ�����ռ䣺";
	cin>>size;
	char ch = '#';
	BinaryTree<char> tree(ch,size) ;

	BinTreeNode<char> *Root;
	BinTreeNode<char> *current;
    cout<<"�밴ǰ�����ȱ���˳�����������������ֵ��";
	tree.createBinaryTree(current);
	Root =tree. getRoot();


	cout<<"�������ȱ�������Ϊ��";
	tree.Preorder(Root);
	cout<<endl;

	cout<<"�������ȱ�������Ϊ��";
	tree.Postorder(Root);
	cout<<endl;

	cout<<"�������ȱ�������Ϊ��";
	tree.Inorder(Root);
	cout<<endl;

	cout<<"����������Ϊ��"<<tree.Size(Root);
	cout<<endl;

	int count = 0;
	cout<<"Ҷ�ӽ���������"<<tree.countLeaf(Root,count);
	cout<<endl;

    cout<<"������ȱ�������Ϊ��";
	tree.Levelorder();
	cout<<endl;


	tree.Preorder();
    cout<<endl;

	//tree.Inorder();
	//cout<<endl;
	tree.deletion();
    return 0;

}








