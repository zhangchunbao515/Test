# include "comdef.h"
# include "queue.h"
# include <iostream>

using namespace std;

typedef struct
{
	VRType adj;    //�����ϵ����:������Ȩͼ��Ϊ0��1,��ʾ�Ƿ�����,���ڴ�Ȩͼ���ʾȨ
}AdjMatrix[5][5];      //��ά����,ÿ�����ʾ��(i,j)��Ȩ
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];   //����(����)����(�洢��������)
	AdjMatrix arcs;                    //�ڽӾ���
	int vexnum;                        //ͼ�ĵ�ǰ������
	int arcnum;                        //ͼ�ĵ�ǰ����(����)
	GraphKind kind;                    //ͼ������
}MGraph;
int LocateVex(VertexType v,MGraph G);   //�ҵ�����λ��
Status CreateDG(MGraph &G);       //��������ͼDG
Status CreateDN(MGraph &G);       //����������DN
Status CreateUDG(MGraph &G);      //��������ͼUDG
Status CreateUDN(MGraph &G);      //����������UDN
Status Output(MGraph G);          //ͼ�����
void DFSTraverse(MGraph G);       //��������㷨
void DFS(MGraph G,int v);
     //����ͼ������ͼ����Ȩ
void ShortestPath_DIJ(MGraph G,int v0);

void ShortestPath_DIJ(MGraph G,int v0)   //P:·������,D:���·��
{
	/*
	ͨ��Dijkstra����ͼG�е����·��ʱ����Ҫָ�����s(���Ӷ���s��ʼ����)��
     ���⣬������������S��U��S�������Ǽ�¼��������·���Ķ���(�Լ���Ӧ�����·������)��
	 ��U���Ǽ�¼��δ������·���Ķ���(�Լ��ö��㵽���s�ľ���)��
     ��ʼʱ��S��ֻ�����s��U���ǳ�s֮��Ķ��㣬����U�ж����·����"���s���ö����·��"��
	 Ȼ�󣬴�U���ҳ�·����̵Ķ��㣬��������뵽S�У����ţ�����U�еĶ���Ͷ����Ӧ��·���� 
	 Ȼ���ٴ�U���ҳ�·����̵Ķ��㣬��������뵽S�У�
	 ���ţ�����U�еĶ���Ͷ����Ӧ��·���� ... �ظ��ò�����ֱ�����������ж��㡣
	*/
	int v,w,min;
	//  ���վ������          ·����ŵ�          �����ﵽ����        ·��
	int final[MAX_VERTEX_NUM],D[MAX_VERTEX_NUM],from[MAX_VERTEX_NUM],path[MAX_VERTEX_NUM];

	//��ʼ��
	for(int v=0; v<G.vexnum; v++)
	{
		final[v] = false;
		D[v] = G.arcs[v0][v].adj;   //Ȩ
		if(D[v]<INFINITY)
			from[v] = v0;
	}
	D[v0] = 0;  final[v0] = true;     //�Լ����Լ�,·��Ϊ0,������ȷ��

	//��ʼ��ѭ��,ÿ�����v0��ĳ����������·��,����v��S��                   
	for(int i=1; i<G.vexnum; i++)   //�����Լ�����������������
	{
		min = INFINITY;             //��ǰ��֪��v������������
		for(int w=0; w<G.vexnum; w++)
		{
			if(!final[w] && D[w]<min)
			{
				v = w;
				min = D[w];
			}
		} //vΪ���·�����Ǹ���
		final[v] = true;     //v��������Ѿ�����̾�����

		//���һ�����·��
		if(D[v]==INFINITY)
			cout<<G.vexs[v0]<<"��"<<G.vexs[i]<<"�����·��Ϊ��"<<endl;
		else
		{
			cout<<G.vexs[v0]<<"��"<<G.vexs[i]<<"�����·��Ϊ"<<D[i]<<endl;
			cout<<"�Ҿ���:"<<endl;
			int u = v;
			int k;
			for(k=0; u!=v0; k++)
			{
				path[k] = u;
				u = from[u];
			}
			cout<<G.vexs[v0];
			for(int p=k-1; p>=0; p--)
			{
				cout<<"--->"<<G.vexs[path[p]];
			}
			cout<<endl;
		}

		//���µ�ǰ���·��������
		for(int w=0; w<G.vexnum; w++)
		{
			if(!final[w] && (min+G.arcs[v][w].adj<D[w]))
			{
				D[w] = min+G.arcs[v][w].adj;
				from[w] = v;
			}
		}
	}//for
}

                  /*--------------ͼ�Ľ���----------------------*/
Status CreateGraph(MGraph &G)     
{
	cout<<"�밴������������봴����ͼ������"<<endl;
	cout<<"0:����ͼ  1:������  2:����ͼ  3:������"<<endl;
	int temp;
	cin>>temp;
	if(temp>3 || temp<0)
		return ERROR;
	G.kind = (GraphKind)temp;     //����Ӧ��ö������ȡ���ŵ�G�����൱��
	switch(temp)
	{
	    case DG:                 //��������ͼ
			 return CreateDG(G);
			 break;
		case DN:                   //����������
			return CreateDN(G);
			break;
		case UDG:                  //��������ͼ(û��Ȩ)
			return CreateUDG(G);
			break;
		case UDN:                  //����������
			return CreateUDN(G);
			break;
		default:
			return ERROR;
	}
	return OK;
}

                  /*---------------��������ͼDG-----------------*/
Status CreateDG(MGraph &G)
{
	cout<<"������ͼ�Ķ������ͻ���"<<endl;
	cin>>G.vexnum>>G.arcnum;
	cout<<"���춥������(���������붥�������)"<<endl;
	for(int i=0; i<G.vexnum; i++)  //�洢���������   �浽����������
		cin>>G.vexs[i];
	     
	for(int i=0; i<G.vexnum; i++)    //��ʼ���ڽӾ���,ÿ��(i,j)Ȩ��ʼ��Ϊ��
		for(int j=0; j<G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;

	for(int k=0; k<G.arcnum; k++)     //С�ڵ�ǰ�ı���
	{
		VertexType v1,v2;            //2������
		cout<<"������һ���������Ķ���(2��)"<<endl;
		cin>>v1>>v2;
		int i = LocateVex(v1,G);        //������������� ����v1λ���ҵ�
		int j = LocateVex(v2,G);        //������������� ����v2λ���ҵ�
		G.arcs[i][j].adj = 1;           //�Ѹ�(i,j)����֮���Ȩ��ֵ
	}

	return OK;
}

                 /*---------------����������DN-----------------*/
Status CreateDN(MGraph &G)
{
	cout<<"������ͼ�Ķ������ͻ���"<<endl;
	cin>>G.vexnum>>G.arcnum;
	cout<<"���춥������(���������붥�������)"<<endl;
	for(int i=0; i<G.vexnum; i++)  //�洢���������   �浽����������
		cin>>G.vexs[i];
	     
	for(int i=0; i<G.vexnum; i++)    //��ʼ���ڽӾ���,ÿ��(i,j)Ȩ��ʼ��Ϊ��
		for(int j=0; j<G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;

	for(int k=0; k<G.arcnum; k++)     //С�ڵ�ǰ�ı���
	{
		VertexType v1,v2;            //2������
		int w;                       //2������֮���Ȩ
		cout<<"������һ���������Ķ���(2��)����Ȩֵ(1��)"<<endl;
		cin>>v1>>v2>>w;
		int i = LocateVex(v1,G);        //������������� ����v1λ���ҵ�
		int j = LocateVex(v2,G);        //������������� ����v2λ���ҵ�
		G.arcs[i][j].adj = w;           //�Ѹ�(i,j)����֮���Ȩ��ֵ
	}

	return OK;
}

                 /*---------------��������ͼUDG-----------------*/
Status CreateUDG(MGraph &G)
{
	cout<<"������ͼ�Ķ������ͻ���"<<endl;
	cin>>G.vexnum>>G.arcnum;
	cout<<"���춥������(���������붥�������)"<<endl;
	for(int i=0; i<G.vexnum; i++)  //�洢���������   �浽����������
		cin>>G.vexs[i];
	     
	for(int i=0; i<G.vexnum; i++)    //��ʼ���ڽӾ���,ÿ��(i,j)Ȩ��ʼ��Ϊ��
		for(int j=0; j<G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;

	for(int k=0; k<G.arcnum; k++)     //С�ڵ�ǰ�ı���
	{
		VertexType v1,v2;            //2������
		cout<<"������һ���������Ķ���(2��)"<<endl;
		cin>>v1>>v2;
		int i = LocateVex(v1,G);        //������������� ����v1λ���ҵ�
		int j = LocateVex(v2,G);        //������������� ����v2λ���ҵ�
		G.arcs[i][j].adj = 1;           //�Ѹ�(i,j)����֮���Ȩ��ֵ
		G.arcs[j][i] = G.arcs[i][j];    //�������ǶԳƵ�,���Կ���ֱ�Ӹ�ֵ  ���Ǿ���
	}
	return OK;
}

                 /*----------------����������UDN-----------------*/

Status CreateUDN(MGraph &G)
{
	cout<<"������ͼ�Ķ������ͻ���"<<endl;
	cin>>G.vexnum>>G.arcnum;
	cout<<"���춥������(���������붥�������)"<<endl;
	for(int i=0; i<G.vexnum; i++)  //�洢���������   �浽����������
		cin>>G.vexs[i];
	     
	for(int i=0; i<G.vexnum; i++)    //��ʼ���ڽӾ���,ÿ��(i,j)Ȩ��ʼ��Ϊ��
		for(int j=0; j<G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;

	for(int k=0; k<G.arcnum; k++)     //С�ڵ�ǰ�ı���
	{
		VertexType v1,v2;            //2������
		int w;                       //2������֮���Ȩ
		cout<<"������һ���������Ķ���(2��)����Ȩֵ(1��)"<<endl;
		cin>>v1>>v2>>w;
		int i = LocateVex(v1,G);        //������������� ����v1λ���ҵ�
		int j = LocateVex(v2,G);        //������������� ����v2λ���ҵ�
		G.arcs[i][j].adj = w;           //�Ѹ�(i,j)����֮���Ȩ��ֵ
		G.arcs[j][i] = G.arcs[i][j];    //�������ǶԳƵ�,���Կ���ֱ�Ӹ�ֵ  ���Ǿ���
	}

	return OK;
}//CreateUDN

                /*----------------�ҵ������ڶ��������е�λ��-------------------*/
int LocateVex(VertexType v,MGraph G)   //���͹����Ķ���,�ҵ��ڶ����������λ��
{
	int i;
	for(i=0; v!=G.vexs[i]; i++)     //���ڶ����������ҵ���v�������ͬ��,�򷵻ظõ��λ��
		;
	return i;
}

                /*-----------------ͼ�����----------------------*/
Status Output(MGraph G)
{
	cout<<"-------------------------------ͼ�����------------------------------------"<<endl;

	cout<<"ͼ�Ķ������ͱ��� :"<<endl;
    cout<<setw(3)<<G.vexnum<<setw(3)<<G.arcnum;
	cout<<endl;

	cout<<"����Ķ�����Ϣ :"<<endl;      //�����������
	for(int i=0; i<G.vexnum; i++)
		cout<<G.vexs[i]<<":"<<i<<" ";
	cout<<endl;

	//�������֮���Ȩ
	//cout<<"�������֮���Ȩ:"<<endl;
	cout<<endl<<"ͼ���ڽӾ���"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)   
		{
			cout.width(6);
			if(G.arcs[i][j].adj!=INFINITY)   //������м���Ȩ,�����Ȩֵ
				cout<<G.arcs[i][j].adj;
			else                      //�м���Ȩ�Ļ�,�����������
				cout<<"��";
		}
		cout<<endl;
	}
	return OK;
}

                /*-----------------���������--------------------*/
void FindIndegree(MGraph G,int* indegree)   //indegree�Ǵ���������������
{
	/*
	�㷨:������е���Ԫ�ز�Ϊ�����,������ֵ��,�������
	*/
	for(int i=0; i<G.vexnum; i++)       
	{   
		for(int j=0; j<G.vexnum; j++)
		{
			if(G.arcs[j][i].adj!=INFINITY)     //0,0  1,0  2,0  3,0    һ��һ�е�
				indegree[i]++;
		}
	}
}//FindIndegree

               /*-----------------����������--------------------*/
void FindOutdegree(MGraph G,int* outdegree){
   /*
	�㷨:������е���Ԫ�ز�Ϊ�����,������ֵ��,���ǳ���
	*/
	for(int i=0; i<G.vexnum; i++)       
	{
		for(int j=0; j<G.vexnum; j++)
		{
			if(G.arcs[i][j].adj!=INFINITY)       //0,0  0,1  0,2  0,3  һ��һ�е� 
				outdegree[i]++;
		}
	}
   
}//FindOutdegree

              /*-----------------���������Ϣ----------------------*/
void GraphDegree(MGraph G){
   int indegree[MAX_VERTEX_NUM]={0},outdegree[MAX_VERTEX_NUM]={0};   //��ÿ����ĳ������������洢,����ʼ��Ϊ0
   int i;
   switch (G.kind){
       	case  DN	:   //����ͼ�޶�
        case  DG	:FindIndegree(G,indegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vexs[i]<<"�����Ϊ "<<indegree[i];
					 cout<<endl;
					 FindOutdegree(G,outdegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vexs[i]<<"�ĳ���Ϊ "<<outdegree[i];
					 break;
       	
       	case  UDN	:  //����ͼ�޶�
       	case  UDG	:FindOutdegree(G,outdegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vexs[i]<<"�Ķ�Ϊ "<<outdegree[i];
					 break;
   }
    cout<<endl;
}//GraphDegree

               /*-----------��������㷨----------*/
bool visited[MAX_VERTEX_NUM];
void DFSTraverse(MGraph G)   //ѭ������Щ���ȥdfs,������ȱ���
{
	cout<<"-----------��������㷨----------"<<endl;
	for(int v=0; v<G.vexnum; v++)
		visited[v] = false;
	for(int v=0; v<G.vexnum; v++)
		DFS(G,v);
}
void DFS(MGraph G,int v)
{
	if(visited[v]==false)
	    cout<<G.vexs[v]<<endl;       //����������������е�v���	
	visited[v] = true;
	for(int w=0; w<G.vexnum; w++)                           //���ÿһ�е�ÿһ����,һ��һ�е�
	{
		if( (G.arcs[v][w].adj!=INFINITY) && !visited[w] )   //�����е��Ǹ�����ֵ,������û���������
		    DFS(G,w);
	}
}

              /*-----------������ȱ���----------*/
LinkQueue Q;
void BFSTraverse(MGraph G)
{
	/*
	*����С�㷨:��0�������,�ڷ�����0���֮�����η���0���δ�����ʵ��ڽ��,
	Ȼ��ֱ����Щ�����,ȥ�������Ǹ��Ե��ڽӵ�,�����˵ľ������.
	����Ҫ���ʵĽ�㼰�ýڵ���ڽ�����,���γ���,���ӵ�ͬʱ�����õ���ڽӵ��Ƿ񱻷���
	*/
	cout<<"---------------������ȱ���---------------"<<endl;
	for(int i=0; i<G.vexnum; i++)  visited[i] = false;   //�ȳ�ʼ����־�����ÿһ��Ϊfalse,δ���
	InitQueue(Q);             //��ʼ����������,����Ϊ��
	VertexType u = -10;
	for(int i=0; i<G.vexnum; i++)
	{
		if( !(visited[i]) )   //�����false(δ�����)
		{
			cout<<G.vexs[i]<<endl;    
		    visited[i] = true;   //�����Ԫ�غ󼴿̽���Ԫ�صı�־������Ӧλ����Ϊtrue
			EnQueue(Q,i);        //����ǰԪ�ز������
			while( !QueueEmpty(Q) )
			{
				DeQueue(Q,u);    //��������Ԫ�طŵ�u����
				for(int j=0; j<G.vexnum; j++)   //�ٶ�uԪ�ض�Ӧ����һ�е�����Ԫ�ؽ��б���
				{
					//�����λ�õ�Ԫ����ֵ,���ұ�־�������Ԫ��û�������,�������,�����
					if( G.arcs[u][j].adj!=INFINITY && !visited[j] )  
					{
						visited[j] = true;           //��Ԫ����Ϊtrue,��ʾ�Ѿ��������
						cout<<G.vexs[j]<<endl;       
						EnQueue(Q,j);                //���
					}//if
				}//for
			}//while
		}//if
	}//for
}//BFSTraverse

int main(void)
{
	MGraph G;
	CreateGraph(G);   //����ͼ
	Output(G);
	ShortestPath_DIJ(G,0);
	system("pause");
	return 0;
}