#include <iostream>//������<iostream.h>,�������ü�����
#include "stack.H"//����ļ����Լ�����ģ�����ֻ�������Ű���
#include "stack.H"//ͷ�ļ��е��������˵����ظ�ʱ�����б��룬���ظ�ռ�ÿռ䣬�����ظ�
#include "Queue.H"
#include "Queue.H"//ͷ�ļ��е��������˵����ظ�ʱ�����б��룬���ظ�ռ�ÿռ䣬�����ظ�
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


template <class T>
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
	while(!S1.isEmpty() || current != NULL);
}

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

	tree.Inorder();
	cout<<endl;
	tree.deletion();
    return 0;
}
