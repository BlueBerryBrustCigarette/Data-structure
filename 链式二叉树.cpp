#include <iostream>
using namespace std;
#include<queue>
#include<stack>
#include<vector>

typedef struct BiTNode
{
	char data;
	BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

void PreT_Create(BiTree& T)
{
	char ch;
	cin >> ch;

	if (ch == '#') T = NULL;
	else
	{
		T = new BiTNode;
		T->data = ch;
		PreT_Create(T->lchild);
		PreT_Create(T->rchild);
	}
}
void NR_InT_Show(BiTree T)
{
	if (T)
	{
		stack<BiTree> BiTree_Sta;
		BiTree now = T;
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
void InT_Show(BiTree T)
{
	if (T)
	{
		InT_Show(T->lchild);
		cout << T->data;
		InT_Show(T->rchild);
	}
}
void PosT_Show(BiTree T)
{
	if (T)
	{
		PosT_Show(T->lchild);
		PosT_Show(T->rchild);
		cout << T->data;
	}
}
void LevelT_Show(BiTree& T)
{
	if (T)
	{
		//初始化一个队列
		queue<BiTree> BiTree_Que;
		BiTree_Que.push(T);
		while (!BiTree_Que.empty())
		{
			BiTree now = BiTree_Que.front();
			BiTree_Que.pop();
			cout << now->data;
			if (now->lchild != NULL)
				BiTree_Que.push(now->lchild);
			if (now->rchild != NULL)
				BiTree_Que.push(now->rchild);
		}
	}
}
void Copy(BiTree& NewT, BiTree T)
{
	if (T == NULL)
	{
		NewT = NULL;
		return;
	}
	else
	{
		NewT = new BiTNode;
		NewT->data = T->data;
		Copy(NewT->lchild, T->lchild);
		Copy(NewT->rchild, T->rchild);
	}
}
int Depth(BiTree T)
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
int NodeCount(BiTree T)
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
int LeafCount(BiTree T)
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
void ShowPath(BiTree T)
{
	if (T->lchild == NULL && T->rchild == NULL)
	{
		cout << T->data << "到根结点的路径为:" << T->data;
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
	BiTree T;
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
