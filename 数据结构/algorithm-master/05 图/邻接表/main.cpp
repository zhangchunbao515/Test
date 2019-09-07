# include "comdef.h"
# include <iostream>

using namespace std;

typedef  struct ArcNode{      //�����һ·�߹�ȥ��·
     int adjvex;              //�û���ָ��Ķ���λ��
     InfoType weight;         //Ȩ(Ĭ����int)
     struct ArcNode *nextarc; //ָ����һ�������λ��
}ArcNode;

typedef struct Vnode{          //����
      VertexType  data;        //������Ϣ(Ĭ����char)
      ArcNode      *firstarc;  //ָ���һ�������ö����ָ��
}VNode, AdjList[MAX_VERTEX_NUM ];    //���ǽṹ������,û������,���� 

typedef struct {               //ͼ
       AdjList   vertices;     //һά����,�����ÿ�������ָ��
       int  vexnum;            //������
	   int  arcnum;            //����
       GraphKind kind;         //ͼ�������־
}ALGraph;

Status CreateGraph(ALGraph &G);  //����ͼ�Ĳ˵�
int LocateVex(ALGraph G,VertexType v);  //���Ҹõ��ڶ����������λ��
Status CreateDG(ALGraph &G);   //����ͼ�Ĵ���
Status CreateDN(ALGraph &G);   //�������Ĵ���
Status CreateUDG(ALGraph &G);  //����ͼ�Ĵ���
Status CreateUDN(ALGraph &G);  //�������Ĵ���
Status PrintGraph(ALGraph G);  //�ڽӱ�����
void DFSTraverse(ALGraph G);
void DFS(ALGraph G,int v);

              /*------------------����ͼ�Ĳ˵�--------------------*/
Status CreateGraph(ALGraph &G){
   int kind;
   cout<<endl<<"����ͼ�����ͣ�0-DG,1-DN,2-UDG,3-UDN:"<<endl;
   cin>>kind;
   G.kind=(GraphKind)kind;
   switch (G.kind){
       	case  DG	:return CreateDG(G);
       	case  DN	:return CreateDN(G); 
       	case  UDG	:return CreateUDG(G);
       	case  UDN	:return CreateUDN(G);
       	default 	:return ERROR;
   }
}//CreateGraph

              /*--------------���Ҹõ��ڶ����������λ��----------*/
int LocateVex(ALGraph G,VertexType v)
{
	int i;
	for(i=0; G.vertices[i].data!=v; i++)   //���ڶ����������ѯʱ,δ�ҵ�ʱ�ͼ�������
		;
	return i;
}

             /*----------------����ͼ�Ĵ���DG------------*/
Status CreateDG(ALGraph &G)
{
	/*
	����С�㷨:���붥��,����,�Ͷ�����Ϣ(����������ݺ�ָ��ΪNULL),��ѭ������ߵ���Ϣ,��v1,v2,w;��1����2��Ȩ;
	����ͼ����ȨΪ1
	����������,������G.vertices[i].firstarc,Ҳ��G.vertices[j].firstarc,˫���.
	*/
	cout<<"�����붥����,����"<<endl;
	cin>>G.vexnum>>G.arcnum;

	VertexType v1,v2;  //2����ʱ��
	ArcNode *p,*q;    //��Ҫ�����������,i��j,j��i

	cout<<"�����붥������(char):"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	for(int k=0; k<G.arcnum; k++)   //�����������
	{
		 cout<<"������v1,v2"<<endl;
		 cin>>v1>>v2;
		 int i,j;
		 i = LocateVex(G,v1);
		 j = LocateVex(G,v2);
		 p = (ArcNode *)malloc(sizeof(ArcNode));
		 p->adjvex = j;    //ָ��Ķ���λ��
		 p->weight = 1;    //Ȩ
		 p->nextarc = G.vertices[i].firstarc;
		 G.vertices[i].firstarc = p;
	}
	return OK;
}//CreateUDN

             /*----------------�������Ĵ���DN------------*/
Status CreateDN(ALGraph &G)
{
	/*
	����С�㷨:���붥��,����,�Ͷ�����Ϣ(����������ݺ�ָ��ΪNULL),��ѭ������ߵ���Ϣ,��v1,v2,w;��1����2��Ȩ;
	����������,������G.vertices[i].firstarc,Ҳ��G.vertices[j].firstarc,˫���.
	*/
	cout<<"�����붥����,����"<<endl;
	cin>>G.vexnum>>G.arcnum;

	VertexType v1,v2;  //2����ʱ��
	InfoType w;        //��ʱȨ
	ArcNode *p,*q;    //��Ҫ�����������,i��j,j��i

	cout<<"�����붥������(char):"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	for(int k=0; k<G.arcnum; k++)   //�����������
	{
		 cout<<"������v1,v2,w"<<endl;
		 cin>>v1>>v2>>w;
		 int i,j;
		 i = LocateVex(G,v1);
		 j = LocateVex(G,v2);
		 p = (ArcNode *)malloc(sizeof(ArcNode));
		 p->adjvex = j;
		 p->weight = w;
		 p->nextarc = G.vertices[i].firstarc;
		 G.vertices[i].firstarc = p;
	}
	return OK;
}//CreateUDN

             /*----------------����ͼ�Ĵ���UDG------------*/
Status CreateUDG(ALGraph &G)
{
	/*
	����С�㷨:���붥��,����,�Ͷ�����Ϣ(����������ݺ�ָ��ΪNULL),��ѭ������ߵ���Ϣ,��v1,v2,w;��1����2��Ȩ;
	����ͼ����ȨΪ1
	����������,������G.vertices[i].firstarc,Ҳ��G.vertices[j].firstarc,˫���.
	*/
	cout<<"�����붥����,����"<<endl;
	cin>>G.vexnum>>G.arcnum;

	VertexType v1,v2;  //2����ʱ��
	ArcNode *p,*q;    //��Ҫ�����������,i��j,j��i

	cout<<"�����붥������(char):"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	for(int k=0; k<G.arcnum; k++)   //�����������
	{
		 cout<<"������v1,v2"<<endl;
		 cin>>v1>>v2;
		 int i,j;
		 i = LocateVex(G,v1);
		 j = LocateVex(G,v2);
		 p = (ArcNode *)malloc(sizeof(ArcNode));
		 p->adjvex = j;
		 p->weight = 1;
		 p->nextarc = G.vertices[i].firstarc;
		 G.vertices[i].firstarc = p;

		 q = (ArcNode *)malloc(sizeof(ArcNode));
		 q->adjvex = i;
		 q->weight = 1;
		 q->nextarc = G.vertices[j].firstarc;
		 G.vertices[j].firstarc = q;
	}
	return OK;
}//CreateUDN

             /*----------------�������Ĵ���UDN------------*/
Status CreateUDN(ALGraph &G)
{
	/*
	����С�㷨:���붥��,����,�Ͷ�����Ϣ(����������ݺ�ָ��ΪNULL),��ѭ������ߵ���Ϣ,��v1,v2,w;��1����2��Ȩ;
	����������,������G.vertices[i].firstarc,Ҳ��G.vertices[j].firstarc,˫���.
	*/
	cout<<"�����붥����,����"<<endl;
	cin>>G.vexnum>>G.arcnum;

	VertexType v1,v2;  //2����ʱ��
	InfoType w;        //��ʱȨ
	ArcNode *p,*q;    //��Ҫ�����������,i��j,j��i

	cout<<"�����붥������(char):"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	for(int k=0; k<G.arcnum; k++)   //�����������
	{
		 cout<<"������v1,v2,w"<<endl;
		 cin>>v1>>v2>>w;
		 int i,j;
		 i = LocateVex(G,v1);
		 j = LocateVex(G,v2);
		 p = (ArcNode *)malloc(sizeof(ArcNode));
		 p->adjvex = j;
		 p->weight = w;
		 p->nextarc = G.vertices[i].firstarc;
		 G.vertices[i].firstarc = p;

		 q = (ArcNode *)malloc(sizeof(ArcNode));
		 q->adjvex = i;
		 q->weight = w;
		 q->nextarc = G.vertices[j].firstarc;
		 G.vertices[j].firstarc = q;
	}
	return OK;
}//CreateUDN

           /*-----------��ȵļ���------------*/
void FindIndegree(ALGraph G,int* indegree)
{
   //�������������ÿһ�������������浽indegree������    
	//����ÿһ��,�ڱ�����ͬʱ�������Ƕ�����Ǹ���,�����
	//���λ�õ���Ӧ��indegree�������1
	ArcNode *p;
	int j=0;
	for(int i=0; i<G.vexnum; i++)    //�������֮��            
	{
		for(p=G.vertices[i].firstarc; p; p = p->nextarc)   //vertices:һά����,�����ÿ�������ָ��
		{
			indegree[p->adjvex]++;
		}
	}
}//FindIndegree

          /*-----------���ȵļ���-------------*/
void FindOutdegree(ALGraph G,int* outdegree)
{
	//�������������ÿһ�������������浽indegree������	ɨ�趥�������ÿһ��,���ж��ٸ����,���ж��ٸ�����
   ArcNode *p;
   for(int i=0; i<G.vexnum; i++)
   {
	   p = G.vertices[i].firstarc;
	   while(p)
	   {
		   p = p->nextarc;
		   outdegree[i]++;
	   }
   }
}//FindOutdegree

          /*-----------����ȵ�ͳ�����---------*/
void GraphDegree(ALGraph G){
   int indegree[MAX_VERTEX_NUM]={0},outdegree[MAX_VERTEX_NUM]={0};
   int i;
   switch (G.kind){
       	case  DN	:
        case  DG	:FindIndegree(G,indegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vertices[i].data<<"�����Ϊ "<<indegree[i];
					 cout<<endl;
					 FindOutdegree(G,outdegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vertices[i].data<<"�ĳ���Ϊ "<<outdegree[i];
					 break;
       	
       	case  UDN	:
       	case  UDG	:FindOutdegree(G,outdegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vertices[i].data<<"�Ķ�Ϊ "<<outdegree[i];
					 break;
   }
  cout<<endl;
}//GraphDegree

            /*----------------�ڽӱ�����-------------*/
Status PrintGraph(ALGraph G)
{
	cout<<"\t\t--------�ڽӱ�����----------"<<endl;
	ArcNode *p;
	cout<<"ͼ�Ķ������ͻ��� :";
	cout<<G.vexnum<<",";
	cout<<G.arcnum<<endl;

	cout<<endl;
	cout<<"ͼ�Ķ�����Ϣ :"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cout<<G.vertices[i].data;
	}

	cout<<endl;
	cout<<"ͼ���ڽӱ� :"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cout<<G.vertices[i].data<<"���ڽӵ�Ϊ:"<<endl;
		p = G.vertices[i].firstarc;
		while(p)
		{
			//p->adjvexָ��Ķ���λ��
			cout<<G.vertices[p->adjvex].data<<endl;
			p = p->nextarc;
		}
		cout<<endl;
	}
	cout<<endl;
	return OK;
}

bool visited[MAX_VERTEX_NUM];
void DFSTraverse(ALGraph G)   //ѭ������Щ���ȥdfs,������ȱ���
{
	cout<<"-----------��������㷨----------"<<endl;
	for(int v=0; v<G.vexnum; v++)
		visited[v] = false;
	for(int v=0; v<G.vexnum; v++)
		DFS(G,v);
}
void DFS(ALGraph G,int v)
{
	if(visited[v]==false)
		cout<<G.vertices[v].data<<endl;       //����������������е�v���	
	ArcNode *p;
	visited[v] = true;
	for(p = G.vertices[v].firstarc; p; p = p->nextarc)        //���ÿһ�е�ÿһ����,һ��һ�е�
	{
		int w = p->adjvex;     //������һ�е���һ������λ��
		if( !visited[w] )
			DFS(G,w);
	}
}

int main(void)
{
	ALGraph G;
	CreateGraph(G);
	GraphDegree(G);
	PrintGraph(G);
	//DFSTraverse(G);
	system("pause");
	return 0;
}