#include<iostream>
using namespace std;
#include<vector>
#include<queue>

#define Infinide_Int 32767
#define Max_VNum 20

typedef char VertexType;
typedef int ArcType;
typedef struct 
{
	VertexType vertexs[Max_VNum];
	ArcType arcs[Max_VNum][Max_VNum];
	int Vertex_Num, Arc_Num;
}AMGraph;
//Adjacency Matrix Graph
 
int LocateVertex(AMGraph& G, VertexType v)
{
	for (int i = 0; i < G.Vertex_Num; i++)
	{
		if (G.vertexs[i] == v)
			return i;
	}
}

//UDN undirected net  ������
bool CreateUDN(AMGraph& G)
{
	cout << "����������:";
	cin >> G.Vertex_Num;
	cout << "���������:";
	cin >> G.Arc_Num;

	cout << "������:";
	for (int i = 0; i < G.Vertex_Num; i++)
		cin >> G.vertexs[i];
	//��ʼ��������
	for (int i = 0; i < G.Arc_Num; i++)
	{
		for (int j = 0; j < G.Arc_Num; j++)
			G.arcs[i][j] = Infinide_Int;
	}
	cout << "�����:" << endl;
	for (int i = 0; i < G.Arc_Num; i++)
	{
		VertexType v1, v2;
		ArcType w;
		cin >> v1 >> v2 >> w;
		int index1 = LocateVertex(G, v1);
		int index2 = LocateVertex(G, v2);
		G.arcs[index1][index2] = G.arcs[index2][index1] = w;
	}
	return true;
}

//������ȱ���
bool DFSvisited[Max_VNum] = {false};
void DFS(AMGraph& G, int nowindex)
{
	cout << G.vertexs[nowindex];
	DFSvisited[nowindex] = true;
	for (int i = 0; i < G.Vertex_Num; i++)
	{
		if ((G.arcs[nowindex][i] != Infinide_Int) && (DFSvisited[i] == false))
			DFS(G, i);
	}
}

//���������������
bool BFSvisited[Max_VNum] = { false };
void BFS(AMGraph& G, int startindex)
{
	
	queue<int> Q;
	Q.push(startindex);
	BFSvisited[startindex] = true;
	while (!Q.empty())
	{
		int nowindex = Q.front();
		Q.pop();
		cout << G.vertexs[nowindex];
		for (int i = 0; i < G.Vertex_Num; i++)
		{
			if (G.arcs[nowindex][i] != Infinide_Int && BFSvisited[i] == false)
			{
				Q.push(i);
				BFSvisited[i] = true;
			}
		}
	}
}


//Prim�㷨������С������
typedef struct Edge
{
	int Uver_index;
	ArcType weight;
}ShortEdge[Max_VNum];
//Uver_index��ʾȨֵ��С�����������,��U�е��Ǹ����
//ShortEdge[i]�ͱ�ʾU��G.vertexs[i]Ȩֵ��С�ı�
//�ҵ�U��V-UȨֵ��С�ı�
int MinEdge(ShortEdge& shortedge,int GVerNum)
{
	ArcType MinWeight = Infinide_Int;
	int minindex = -1;
	for (int i = 0; i < GVerNum; i++)
	{
		if ((shortedge[i].weight !=0) && (shortedge[i].weight < MinWeight))
		{
			MinWeight = shortedge[i].weight;
			minindex = i;
		} 
	}
	return minindex;
}
//�����С��������·��
void showMST(int minindex, ShortEdge& shortedge, AMGraph& G)
{
	cout << G.vertexs[shortedge[minindex].Uver_index] << "��" << G.vertexs[minindex] << endl;
}
//����ķ�㷨
void Prim(AMGraph& G, int start_index)
{ 
	ShortEdge shortedge;
	for (int i = 0; i < G.Vertex_Num; i++)
	{
		shortedge[i].Uver_index = start_index;
		shortedge[i].weight = G.arcs[start_index][i];
	}
	shortedge[start_index].weight = 0;                  //0��ʾ�Ѿ���U��
	
	for (int i = 0; i < G.Vertex_Num - 1; i++)
	{
		int nowminindex = MinEdge(shortedge, G.Vertex_Num);
		showMST(nowminindex, shortedge, G);
		shortedge[nowminindex].weight = 0;
		for (int j = 0; j < G.Vertex_Num; j++)
		{
			if (G.arcs[nowminindex][j] < shortedge[j].weight)
			{
				shortedge[j].Uver_index = nowminindex;
				shortedge[j].weight = G.arcs[nowminindex][j];
			}
		}
	}
}



//ʵ�ֿ�³˹�����㷨
struct KruEdge
{
	int from_index;
	int to_index;
	ArcType weight;
};
int FindRoot(vector<int>& VerRoot, int index)
{ 
	int rootindex = index;
	while (VerRoot[rootindex] != -1)
	{
		rootindex = VerRoot[rootindex];
	}
	return rootindex;
}
void Kruskal(AMGraph& G)
{
	vector<KruEdge> AMG_Edge;
	cout << "��Ȩֵ��С�����˳�������" << endl;
	for (int i = 0; i < G.Arc_Num; i++)
	{
		VertexType v1, v2;
		cin >> v1 >> v2;
		KruEdge nowedge;
		nowedge.from_index = LocateVertex(G, v1);
		nowedge.to_index = LocateVertex(G, v2);
		cin >> nowedge.weight;

		AMG_Edge.push_back(nowedge);
	}

	vector<int> VerRoot;
	for (int i = 0; i < G.Vertex_Num; i++)
		VerRoot.push_back(-1);
	for (int i = 0; i < G.Arc_Num; i++)
	{
		int fromroot = FindRoot(VerRoot, AMG_Edge[i].from_index);
		int toroot = FindRoot(VerRoot, AMG_Edge[i].to_index);

		if (fromroot != toroot)
		{
			cout << G.vertexs[AMG_Edge[i].from_index] << "��" << G.vertexs[AMG_Edge[i].to_index] << endl;
			VerRoot[toroot] = fromroot;
		}
	}
}


int main()
{
	AMGraph amg;
	CreateUDN(amg);
	

}