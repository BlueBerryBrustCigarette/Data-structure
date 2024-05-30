#pragma once
#include <iostream>
using namespace std;
#include <deque>

template<typename DataType>
class BiTNode
{
public:
	DataType Data;
	BiTNode* L_Child, * R_Child;
	BiTNode() :L_Child(NULL), R_Child(NULL)
	{}
};

template<typename DataType>
class BiTree
{
public:
	DataType Empty;
	BiTNode<DataType>* root;
	BiTree<DataType>* L_Child_Tree;
	BiTree<DataType>* R_Child_Tree;

	BiTree(DataType empty) :root(NULL), Empty(empty), L_Child_Tree(NULL), R_Child_Tree(NULL)
	{
	}

	void Pre_Traverse_CreateBiTree()
	{
		DataType data;
		cin >> data;
		if (data == this->Empty) return;
		else
		{
			this->root = new BiTNode<DataType>;
			root->Data = data;


			L_Child_Tree = new BiTree<DataType>(BiTree<DataType>(this->Empty));
			R_Child_Tree = new BiTree<DataType>(BiTree<DataType>(this->Empty));

			root->L_Child = L_Child_Tree->root;
			root->R_Child = R_Child_Tree->root;

			L_Child_Tree->Pre_Traverse_CreateBiTree();
			R_Child_Tree->Pre_Traverse_CreateBiTree();
		}
		return;
	}

	void In_Traverse_ShowBiTree()
	{
		if (this && this->root)
		{
			this->L_Child_Tree->In_Traverse_ShowBiTree();
			cout << root->Data;
			this->R_Child_Tree->In_Traverse_ShowBiTree();
		}
	}

	void Pos_Traverse_ShowBiTree()
	{
		if (this && this->root)
		{
			this->L_Child_Tree->In_Traverse_ShowBiTree();
			this->R_Child_Tree->In_Traverse_ShowBiTree();
			cout << root->Data;
		}
	}

	void Level_Traverse_ShowBiTree()
	{
		if (this->root)
		{
			//初始化一个队列容器
			deque<BiTree<DataType>> For_Level_Traverse;
			For_Level_Traverse.push_back(*this);
			while (!For_Level_Traverse.empty())
			{
				BiTree<DataType> now = For_Level_Traverse.front();
				For_Level_Traverse.pop_front();
				cout << now.root->Data;
				if (now.L_Child_Tree != NULL && now.L_Child_Tree->root != NULL)
					For_Level_Traverse.push_back(*now.L_Child_Tree);
				if (now.R_Child_Tree != NULL && now.R_Child_Tree->root != NULL)
					For_Level_Traverse.push_back(*now.R_Child_Tree);
			}
		}
	}
};

