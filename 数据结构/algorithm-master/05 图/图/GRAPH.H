#ifndef _GARPH_H_
#define _GRAPH_H_
#include <iostream>
using namespace std;

template <class T,class E>
class Graph
{
	public:
		Graph();//建立一个空的图
		void insertVertex(const T&vertex);//插入一个顶点，其值已知，该顶点暂时没有入边
		void insertEdge(int v1,int v2,int weight);//若构成v1，v2的两个顶点是图中的顶点，则在图中插入一条边（v1，v2）
		void removeVertex(int v);//删除一个顶点，并且删除与其相关联的边
		void removeEdge(int v1,int v2);//删除以v1，v2为顶点的边
		bool isEmpty();//判断图是否为空
		T getWeight(int v1,int v2);//得到以v1，v2为顶点的边的权值
		int getFirstNeighbor(int v);//得到以顶点为v的第一个邻接点
		int getNextNeighbor(int v1,int v2);//得到以v1为顶点，v2为第一个邻接点的下一个邻接点
};
#endif