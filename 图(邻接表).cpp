#include<iostream>
using namespace std;
#include<queue>

#define Infinide_Int 32767
#define Max_VNum 20

typedef char VertexType;
typedef int ArcType;
typedef int InfoType;

struct ArcNode
{
	int verlist_index;
	ArcNode* nextarc;
	InfoType info;   //information
};

typedef struct VNode
{
	VertexType data;
	ArcNode* firstarc;
}VNode,VerList[Max_VNum];

struct ALGraph
{
	VerList verlist;
	int vexnum, arcnum;
};

int LocateVertex(ALGraph& G, VertexType v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.verlist[i].data == v)
			return i;
	}
}
	
//UNG��������ͼ       
bool GreateUNG(ALGraph& G)
{
	cout << "����������:";
	cin >> G.vexnum;
	cout << "���������:";
	cin >> G.arcnum;
	cout << "������:";
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.verlist[i].data;
		G.verlist[i].firstarc = NULL;
	}
	cout << "�����:" << endl;
	for (int i = 0; i < G.arcnum; i++)
	{
		VertexType v1, v2;
		cin >> v1 >> v2;
		int index1 = LocateVertex(G, v1);
		int index2 = LocateVertex(G, v2);
		ArcNode* nowarc = new ArcNode;
		nowarc->verlist_index = index2;
		nowarc->nextarc = G.verlist[index1].firstarc;
		G.verlist[index1].firstarc = nowarc;

		//���ɶԳƵ�
		nowarc = new ArcNode;
		nowarc->verlist_index = index1;
		nowarc->nextarc = G.verlist[index2].firstarc;
		G.verlist[index2].firstarc = nowarc;

	}
	return true;
}

//���������������
bool DFSvisited[Max_VNum] = {false};
void DFS_AL(ALGraph& G, int verindex)
{
	cout << G.verlist[verindex].data;
	DFSvisited[verindex] = true;
	for (ArcNode* nowarc = G.verlist[verindex].firstarc; nowarc != NULL; nowarc = nowarc->nextarc)
	{
		if (DFSvisited[nowarc->verlist_index] == false)
			DFS_AL(G, nowarc->verlist_index);
	}
}

//���������������
bool BFSvisited[Max_VNum] = { false };
void BFS_AL(ALGraph& G,int verindex)
{
	cout << G.verlist[verindex].data;
	BFSvisited[verindex] = true;
	queue<int> Q;
	Q.push(verindex);
	while (!Q.empty())
	{
		ArcNode* nowarc = G.verlist[Q.front()].firstarc;
		Q.pop();
		while (nowarc)
		{
			if (BFSvisited[nowarc->verlist_index] == false)
			{
				cout << G.verlist[nowarc->verlist_index].data;
				BFSvisited[nowarc->verlist_index] = true;
				Q.push(nowarc->verlist_index);
			}
			nowarc = nowarc->nextarc;
		}
	}
}

int main()
{
	ALGraph G;

	GreateUNG(G);
	cout << "������ȱ������:" << endl;
	DFS_AL(G, 0);
	cout << endl;

	cout << "������ȱ������:" << endl;
	BFS_AL(G, 0);
	cout << endl;
}