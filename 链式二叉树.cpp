#include <iostream>
using namespace std;
#include<queue>
#include<stack>
#include<vector>

typedef struct Threaded_BiTNode
{
	char data;
	Threaded_BiTNode* lchild, * rchild;
}Threaded_BiTNode, * Threaded_BiTree;

void PreT_Create(Threaded_BiTree& T)
{
	char ch;
	cin >> ch;

	if (ch == '#') T = NULL;
	else
	{
		T = new Threaded_BiTNode;
		T->data = ch;
		PreT_Create(T->lchild);
		PreT_Create(T->rchild);
	}
}
void NR_InT_Show(Threaded_BiTree T)
{
	if (T)
	{
		stack<Threaded_BiTree> BiTree_Sta;
		Threaded_BiTree now = T;
		while (!BiTree_Sta.empty() || now)
		{
			if (now)
			{
				BiTree_Sta.push(now);
				now = now->lchild;
			}
			else
			{
				now = BiTree_Sta.top();
				BiTree_Sta.pop();
				cout << now->data;
				now = now->rchild;
			}
		}
	}
}
void InT_Show(Threaded_BiTree T)
{
	if (T)
	{
		InT_Show(T->lchild);
		cout << T->data;
		InT_Show(T->rchild);
	}
}
void PosT_Show(Threaded_BiTree T)
{
	if (T)
	{
		PosT_Show(T->lchild);
		PosT_Show(T->rchild);
		cout << T->data;
	}
}
void LevelT_Show(Threaded_BiTree& T)
{
	if (T)
	{
		//初始化一个队列
		queue<Threaded_BiTree> BiTree_Que;
		BiTree_Que.push(T);
		while (!BiTree_Que.empty())
		{
			Threaded_BiTree now = BiTree_Que.front();
			BiTree_Que.pop();
			cout << now->data;
			if (now->lchild != NULL)
				BiTree_Que.push(now->lchild);
			if (now->rchild != NULL)
				BiTree_Que.push(now->rchild);
		}
	}
}
void Copy(Threaded_BiTree &NewT, Threaded_BiTree T)
{
	if (T == NULL)
	{
		NewT = NULL;
		return;
	}
	else
	{
		NewT = new Threaded_BiTNode;
		NewT->data = T->data;
		Copy(NewT->lchild, T->lchild);
		Copy(NewT->rchild, T->rchild);
	}
}
int Depth(Threaded_BiTree T)
{
	if (T == NULL) return 0;
	else
	{
		int ldep = Depth(T->lchild);
		int rdep = Depth(T->rchild);
		if (ldep > rdep) return ldep + 1;
		else return rdep + 1;
	}
}
int NodeCount(Threaded_BiTree T)
{
	if (T == NULL) 
		return 0;
	else
	{
		int lnode = NodeCount(T->lchild);
		int rnode = NodeCount(T->rchild);
		return lnode + rnode + 1;
	}
}
int LeafCount(Threaded_BiTree T)
{
	if (T == NULL)
		return 0;
	else
	{
		if (T->lchild || T->rchild)
		{
			int lL = LeafCount(T->lchild);
			int rL = LeafCount(T->rchild);
			return lL + rL;
		}
		else
			return 1;
	}
}
vector<char> path;
void ShowPath(Threaded_BiTree T)
{
	if (T->lchild == NULL && T->rchild == NULL)
	{
		cout << T->data << "到根结点的路径为:"<<T->data;
		for (vector<char>::reverse_iterator now = path.rbegin(); now != path.rend(); now++)
			cout << *now;
		cout << endl;
	}
	else
	{
		path.push_back(T->data);
		if (T->lchild)
			ShowPath(T->lchild);
		if (T->rchild)
			ShowPath(T->rchild);
		path.pop_back();
	}
}
int main()
{
	Threaded_BiTree T;
	PreT_Create(T);

	cout << "层次遍历结果:";
	LevelT_Show(T);
	cout << endl;
	
	ShowPath(T);
	cout << endl;
}

/* 示例输入
ABC##DE#G##F###
中序遍历结果:CBEGDFA
后序遍历结果:CGEFDBA
层次遍历结果:ABCDEFG
*/
