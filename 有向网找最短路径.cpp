#include<iostream>
using namespace std;
#include<vector>

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

//DN directed net  无向网
bool CreateDN(AMGraph& G)
{
	cout << "输入结点总数:";
	cin >> G.Vertex_Num;
	cout << "输入边总数:";
	cin >> G.Arc_Num;

	cout << "输入结点:";
	for (int i = 0; i < G.Vertex_Num; i++)
		cin >> G.vertexs[i];
	//初始化边数组
	for (int i = 0; i < G.Arc_Num; i++)
	{
		for (int j = 0; j < G.Arc_Num; j++)
			G.arcs[i][j] = Infinide_Int;
	}
	cout << "输入边:" << endl;
	for (int i = 0; i < G.Arc_Num; i++)
	{
		VertexType v1, v2;
		ArcType w;
		cin >> v1 >> v2 >> w;
		int index1 = LocateVertex(G, v1);
		int index2 = LocateVertex(G, v2);
		G.arcs[index1][index2] = w;
	}
	return true;
}


//实现迪杰斯特拉算法
void ShowPath(AMGraph& G, vector<int>Path, int index)
{
	if (Path[index] != -1)
	{
		ShowPath(G, Path, Path[index]);
		cout<<G.vertexs[Path[index]];
	}
}
void Dijkstra(AMGraph &G,int startindex)
{
	vector<bool>VerInPath(G.Vertex_Num, false);						//标记结点是否已经在生成的路径中  
	VerInPath[startindex] = true;

	vector<ArcType>Distance;									//记录目前到各终点的最短距离
	for (int i = 0; i < G.Vertex_Num; i++)
		Distance.push_back(G.arcs[startindex][i]);

	vector<int>Path(G.Vertex_Num,-1);							//记录目前已经生成的路径中到各终点的最近的结点
	for (int i = 0; i < G.Vertex_Num; i++)
	{
		if (Distance[i] != Infinide_Int)
			Path[i] = startindex;
	}
	//初始化结束

	for (int j = 0; j < G.Vertex_Num - 1; j++)
	{
		int mindistance = Infinide_Int;
		int minindex = 0;
		for (int i = 0; i < G.Vertex_Num; i++)
		{
			if (VerInPath[i] == false && Distance[i] < mindistance)
			{
				mindistance = Distance[i];
				minindex = i;
			}
		}
		VerInPath[minindex] = true;
		for (int i = 0; i < G.Vertex_Num; i++)
		{
			if (VerInPath[i] == false && (G.arcs[minindex][i] + Distance[minindex]) < Distance[i])
			{
				Distance[i] = G.arcs[minindex][i] + Distance[minindex];
				Path[i] = minindex;
			}
		}
	}

	for (int j = 0; j < G.Vertex_Num ; j++)
	{
		if (j != startindex)
		{
			cout << "从" << G.vertexs[startindex] << "到" << G.vertexs[j] << "的路径:" << endl;
			ShowPath(G, Path, j);
			cout << G.vertexs[j] << endl;
		}
	}
}

//实现弗洛伊德算法
void Floyd(AMGraph& G)
{
	vector<vector<ArcType>>Distance(G.Vertex_Num,vector<ArcType>(G.Vertex_Num,Infinide_Int));
	vector<vector<string>>Path(G.Vertex_Num,vector<string>(G.Vertex_Num,""));
	for (int a = 0; a < G.Vertex_Num; a++)
	{
		for (int b = 0; b < G.Vertex_Num; b++)
		{
			Distance[a][b] = G.arcs[a][b];
			if (Distance[a][b] != Infinide_Int)
			{
				Path[a][b].push_back(G.vertexs[a]);
				Path[a][b].push_back(G.vertexs[b]);
			}
		}
	}

	for (int a = 0; a < G.Vertex_Num; a++)
	{
		for (int b = 0; b < G.Vertex_Num; b++)
		{
			for (int c = 0; c < G.Vertex_Num; c++)
			{
				if (Distance[b][c] > Distance[b][a] + Distance[a][c])
				{
					Distance[b][c] = Distance[b][a] + Distance[a][c];
					Path[b][c] = Path[b][a];
					Path[b][c].pop_back();
					Path[b][c] += Path[a][c];
				}
			}
		}
	}
	
	for (int a = 0; a < G.Vertex_Num; a++)
	{
		for (int b = 0; b < G.Vertex_Num; b++)
		{
			if (a != b&&Path[a][b]!="")
				cout << Path[a][b] << endl;
		}
	}

}




int main()
{
	AMGraph dn;
	CreateDN(dn);
	Floyd(dn);
}

/*
7
12
ABCDEFG
AB 4
AC 6
AD 6
BC 1
DC 2
BE 7
CE 6
CF 4
DF 5
FG 8
FE 1
EG 6
*/