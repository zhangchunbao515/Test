#ifndef _GRAPHMTX_H_
#define _GRAPHMTX_H_
#include <iostream>
#include "QUEUE.H"
using namespace std;


//定义图的存储模板基类,此图为无向图，并且是带有权值的无向图
template <class T,class E>//参数T为顶点的数据类型，E为权值的数据类型，当为不带权图时此参数可以省略
class Graphmtx
{
	public:
		E maxWeight;//定义无穷大的值，由用户自定义
		T endTag;//上面两处不能加const，如果加，则必须在定义的时候初始化
		int curVertices;//当前顶点的个数
		int curEdges;//当前边的个数
		int maxVertices;//最大的顶点个数

	public:
		
		Graphmtx(int sz, E weight,T et);//构造函数
		~Graphmtx()
		{
			delete [] VerticesList;
			int i=0;
			for(i=0;i<maxVertices;i++)
			{
				delete [] Edge[i];
			}
			delete []Edge;
		}
		void createGraph();//创建无向图
		int getFirstNeighbor(int v);//得到以顶点为v的第一个邻接点
		int getNextNeighbor(int v1,int v2);//得到以v1为顶点，v2为第一个邻接点的下一个邻接点
		int getVertexPos( const T vertex)//根据顶点的数据值得到其位置并且返回其位置，当搜索成功时返回i，否则返回-1
		{
			for(int i = 0;i < curVertices;i++)
			{
				if (VerticesList[i] == vertex)
					return i;
			}
			return -1;
		};
		T getVertex(int v)
		{
			if (v>=0 && v<curVertices)
			{
				return VerticesList[v];
			}
			else
			{
				return NULL;
			}
		}
		void DFS(Graphmtx<T,E> &G,const T v);//深度优先遍历的主程序
		void DFS(Graphmtx<T,E> &G,int v,bool *visited);//深度优先遍历的子程序
		void BFS(Graphmtx<T,E> &G,const T v);//广度优先遍历
	private:
		T *VerticesList;//顶点数组，用于存放图的顶点
		E * * Edge;//邻接矩阵
};


//创建无向带权图
template <class T,class E>
void Graphmtx<T,E> :: createGraph()
{
	int i=0,j=0;
	E temp;
	cout<<"请输入顶点的数据值：";
	for(i=0;i<maxVertices;i++)
	{
		T tmp;

		cin>>tmp;
		if (tmp == endTag)  break;
		VerticesList[i] = tmp;
		curVertices++;
	}//先创建顶点数组
	for(i = 0 ; i<curVertices  ; i++)
		for(j = 0;j < curVertices ; j++)
		{
			if (i==j)
			Edge[i][j] = 0;
			else
			{
				cout<<"请输入邻接矩阵的相应值：";
				cin>>temp;
				if(temp == maxWeight) continue;
				Edge[i][j]  = temp;
				curEdges++;
				if (Edge[j][i] == Edge[i][j])
				{
					curEdges--;
				}
			}
		}//创建邻接矩阵
}

template <class T,class E>
Graphmtx<T,E> :: Graphmtx(int sz, E weight,T et)//构造函数
{
	maxVertices = sz;
	maxWeight = weight;
	endTag = et;
	curVertices = 0;
	curEdges = 0;
	int i,j;
	VerticesList = new T[maxVertices];//动态申请顶点的空间
	
	Edge = (E* *) new E *[maxVertices];//动态申请邻接矩阵的空间
    for(i=0;i<maxVertices;i++)
		Edge[i] = new E[maxVertices];//嵌套申请二维数组中的一维数组的空间
	

	for(i=0;i<maxVertices;i++)
		for(j=0;j<maxVertices;j++)
		{
			if (i == j)
				Edge[i][j] = 0;
			else
			{
				Edge[i][j] =maxWeight;
			}
		}
};//初步完成邻接矩阵的初始化

template <class T,class E>
int Graphmtx<T,E> :: getFirstNeighbor(int v)
//给出顶点位置为v的第一个邻接顶点的位置，如果找不到函数返回-1
{
	if (v>=0)
	{
		for(int col = 0;col < maxVertices;col++)
			if (Edge[v][col] >0 &&Edge[v][col] <maxWeight)
				return col;
	}
	else
		return -1;
	return -1;
}

template <class T,class E>
int Graphmtx<T,E> :: getNextNeighbor(int v,int w)
//给出顶点V的某邻接点w的下一个邻接点
{
	if(v >=0 && w >=0)
	{
		for(int col = w+1;col <maxVertices;col++)
			if (Edge[v][col] > 0 && Edge[v][col] <maxWeight)
				return col;
	}
	return -1;
}

template <class T,class E>
void Graphmtx<T,E> :: DFS(Graphmtx<T,E> &G,const T v)
//深度优先遍历的主程序
{
	bool *visited;
	visited = new bool[curVertices];
	for(int i = 0;i<curVertices;i++)
		visited[i] = false;
	int location =G.getVertexPos(v);
	DFS(G,location,visited);
	delete []visited;
}


template <class T,class E>
void Graphmtx<T,E> :: DFS(Graphmtx<T,E> &G,int v,bool *visited)
//深度优先遍历的子程序
{
	cout<<G.getVertex(v);
	visited[v] = true;
	int w = G.getFirstNeighbor(v);
	while (w>=0 && w<curVertices)
	{
		if (visited[w] == false) 
			DFS(G,w,visited);
		else
		{
			w = G.getNextNeighbor(v,w);
		}
	}
}

template <class T,class E>
void Graphmtx<T,E> :: BFS(Graphmtx<T,E> &G,const T v)
//广度优先遍历
{
	int size;
	cout<<"请输入所需队列的预计最大长度:";
	cin>>size;
	Queue<int> Q(size);
	int w;
	bool *visited;
	visited = new bool[curVertices];
	for(int i = 0;i<curVertices;i++)
		visited[i] = false;
	int location = G.getVertexPos(v);
	cout<<G.getVertex(location);
	visited[location] = true;
	Q.inQueue(location);
	while (!Q.isEmpty())
	{
		Q.outQueue(location);
		w = G.getFirstNeighbor(location);
		while (w >=0 && w <curVertices)
		{
			if (visited[w] == false)
			{
				cout<<G.getVertex(w);
				visited[w] = true;
				Q.inQueue(w);
			}
w = G.getNextNeighbor(location,w);
		}
	}
	delete []visited;
}
		





#endif




