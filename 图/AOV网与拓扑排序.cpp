#include<iostream>
using namespace std;
#include<stack>
#include<vector>

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
       
//AOV   Activity On Vertex Network
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
		nowarc->verlist_index = index2;
		nowarc->nextarc = G.verlist[index1].firstarc;
		G.verlist[index1].firstarc = nowarc;
		G.verlist[index2].indegree++;
	}
	return true;
}
//实现拓扑排序
void TopologicalSort(ALGraph& G)
{
	vector<char> topo;
	stack<int> NoIn_S;
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.verlist[i].indegree == 0)
			NoIn_S.push(i);
	}
	while (!NoIn_S.empty())
	{
		ArcNode* nowarc = G.verlist[NoIn_S.top()].firstarc;
		topo.push_back(G.verlist[NoIn_S.top()].data);
		NoIn_S.pop();
		while (nowarc)
		{
			G.verlist[nowarc->verlist_index].indegree--;
			if (G.verlist[nowarc->verlist_index].indegree == 0)
				NoIn_S.push(nowarc->verlist_index);
			nowarc = nowarc->nextarc;
		}
	}
	if (topo.size() < G.vexnum) cout << "该有向图有回路" << endl;
	else
	{
		cout << "拓扑排序的结果为:";
		for (int i = 0; i < G.vexnum; i++)
		{
			cout << topo[i];
		}
		cout << endl;
	}	
}


int main()
{
	ALGraph G;
	GreateAOV(G);
	TopologicalSort(G);
}

/*
输入结点总数:6
输入边总数:9
输入结点:ABCDEF
输入边:
BA
BD
DA
CA
CD
EC
ED
EF
DF
ECBDAF
*/