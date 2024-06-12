#include<iostream>
using namespace std;
#include<stack>
#include<vector>

#define Infinide_Int 32767
#define Max_VNum 20

typedef char VertexType;
typedef int ArcType;

struct ArcNode
{
	int verlist_index;
	int weight;
	ArcNode* nextarc;	
};

typedef struct VNode
{
	int indegree;
	VertexType data;
	ArcNode* firstarc;
}VNode, VerList[Max_VNum];

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

//AOE   Activity On Vertex Network
bool GreateAOV(ALGraph& G)
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
		G.verlist[i].indegree = 0;
	}
	cout << "输入边:" << endl;
	for (int i = 0; i < G.arcnum; i++)
	{
		VertexType v1, v2;
		cin >> v1 >> v2;
		int index1 = LocateVertex(G, v1);
		int index2 = LocateVertex(G, v2);
		ArcNode* nowarc = new ArcNode;
		cin >> nowarc->weight;
		nowarc->verlist_index = index2;
		nowarc->nextarc = G.verlist[index1].firstarc;
		G.verlist[index1].firstarc = nowarc;
		G.verlist[index2].indegree++;
	}
	return true;
}

//拓扑排序
bool TopologicalSort(ALGraph& G, vector<int>& topo)
{
	stack<int> NoIn_S;
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.verlist[i].indegree == 0)
			NoIn_S.push(i);
	}
	while (!NoIn_S.empty())
	{
		ArcNode* nowarc = G.verlist[NoIn_S.top()].firstarc;
		topo.push_back(NoIn_S.top());
		NoIn_S.pop();
		while (nowarc)
		{
			G.verlist[nowarc->verlist_index].indegree--;
			if (G.verlist[nowarc->verlist_index].indegree == 0)
				NoIn_S.push(nowarc->verlist_index);
			nowarc = nowarc->nextarc;
		}
	}
	if (topo.size() < G.vexnum) return false;
	else
		return true;
}

//实现求AOE的关键路径
bool CriticalPath(ALGraph& G)
{
	vector<int> topo;
	if (!TopologicalSort(G, topo))
		cout << "该有向图有回路,不能求关键路径";

	vector<ArcType>ve(G.vexnum,0);
	for (int i = 0; i < G.vexnum; i++)
	{
		int index = topo[i];
		ArcNode* nowarc = G.verlist[index].firstarc;
		while (nowarc)
		{
			if (ve[nowarc->verlist_index] < ve[index] + nowarc->weight)
				ve[nowarc->verlist_index] = ve[index] + nowarc->weight;
			nowarc = nowarc->nextarc;
		}
	}

	vector<ArcType>vl(G.vexnum,ve[topo[G.vexnum-1]]);
	for (int i = G.vexnum - 1; i >= 0; i--)
	{
		int index = topo[i];
		ArcNode* nowarc = G.verlist[index].firstarc;
		while (nowarc)
		{
			if (vl[index] > vl[nowarc->verlist_index] - nowarc->weight)
				vl[index] = vl[nowarc->verlist_index] - nowarc->weight;
			nowarc = nowarc->nextarc;
		}
	}

	//找关键事件—>得关键路径
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* nowarc = G.verlist[i].firstarc;
		while (nowarc)
		{
			if (ve[i] == (vl[nowarc->verlist_index] - nowarc->weight))
				cout << G.verlist[i].data << "—>" << G.verlist[nowarc->verlist_index].data << endl;
			nowarc = nowarc->nextarc;
		}	
	}
	return true;
}

int main()
{
	ALGraph G;
	GreateAOV(G);
	CriticalPath(G);
}


/*
9
11
ABCDEFGHI
AB 6
AC 4
AD 5
BE 1
CE 1
DF 2
EG 9
EH 7
FH 4
HI 4
GI 2
*/