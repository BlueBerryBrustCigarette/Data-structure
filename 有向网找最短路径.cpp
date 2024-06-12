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

//DN directed net  ������
bool CreateDN(AMGraph& G)
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
		G.arcs[index1][index2] = w;
	}
	return true;
}


//ʵ�ֵϽ�˹�����㷨
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
	vector<bool>VerInPath(G.Vertex_Num, false);						//��ǽ���Ƿ��Ѿ������ɵ�·����  
	VerInPath[startindex] = true;

	vector<ArcType>Distance;									//��¼Ŀǰ�����յ����̾���
	for (int i = 0; i < G.Vertex_Num; i++)
		Distance.push_back(G.arcs[startindex][i]);

	vector<int>Path(G.Vertex_Num,-1);							//��¼Ŀǰ�Ѿ����ɵ�·���е����յ������Ľ��
	for (int i = 0; i < G.Vertex_Num; i++)
	{
		if (Distance[i] != Infinide_Int)
			Path[i] = startindex;
	}
	//��ʼ������

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
			cout << "��" << G.vertexs[startindex] << "��" << G.vertexs[j] << "��·��:" << endl;
			ShowPath(G, Path, j);
			cout << G.vertexs[j] << endl;
		}
	}
}

//ʵ�ָ��������㷨
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