#include <iostream>
#include "GRAPHMTX.H"
using namespace std;

int main ()
{
	int size;
	cout<<"请输入邻接矩阵的预计最大顶点数：";
	cin>>size;

	char et;
	cout<<"请输入顶点结束标志：";
	cin>>et;

	int max = 9999;

	Graphmtx<char ,int > G (size,max,et);
	G.createGraph();


	int v;
	cout<<"请输入要查找的合法位置：";
	cin>>v;
	cout<<"第一个邻接点的位置为："<<G.getFirstNeighbor(v);
	cout<<endl;

	int w = 0;
	cout<<"已知位置的下一个邻接点："<<G.getNextNeighbor(v,w);
	cout<<endl;

	char ch = 'B';
	G.DFS(G,ch);
	cout<<endl;

	G.BFS(G,ch);
	cout<<endl;
	return 0;
}
