#include <iostream>
#include "GRAPHMTX.H"
using namespace std;

int main ()
{
	int size;
	cout<<"�������ڽӾ����Ԥ����󶥵�����";
	cin>>size;

	char et;
	cout<<"�����붥�������־��";
	cin>>et;

	int max = 9999;

	Graphmtx<char ,int > G (size,max,et);
	G.createGraph();


	int v;
	cout<<"������Ҫ���ҵĺϷ�λ�ã�";
	cin>>v;
	cout<<"��һ���ڽӵ��λ��Ϊ��"<<G.getFirstNeighbor(v);
	cout<<endl;

	int w = 0;
	cout<<"��֪λ�õ���һ���ڽӵ㣺"<<G.getNextNeighbor(v,w);
	cout<<endl;

	char ch = 'B';
	G.DFS(G,ch);
	cout<<endl;

	G.BFS(G,ch);
	cout<<endl;
	return 0;
}
