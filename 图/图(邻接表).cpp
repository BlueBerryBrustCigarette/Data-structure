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
	
//UNG——无向图       
bool GreateUNG(ALGraph& G)
{
	cout << "输入结点总数:";
	cin >> G.vexnum;
	cout << "输入边总数:";
	cin >> G.arcnum;
	cout << "输入结点:";
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.verlist[i].data;
		G.verlist[i].firstarc = NULL;
	}
	cout << "输入边:" << endl;
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

		//生成对称点
		nowarc = new ArcNode;
		nowarc->verlist_index = index1;
		nowarc->nextarc = G.verlist[index2].firstarc;
		G.verlist[index2].firstarc = nowarc;

	}
	return true;
}

//深度优先搜索遍历
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

//广度优先搜索遍历
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
	cout << "深度优先遍历结果:" << endl;
	DFS_AL(G, 0);
	cout << endl;

	cout << "广度优先遍历结果:" << endl;
	BFS_AL(G, 0);
	cout << endl;
}