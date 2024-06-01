#pragma once
#include <iostream>
using namespace std;
#include <queue>
#include <stack>

template<typename DataType>
class BiTree
{
public:
	template<typename DataType>
	class BiTNode
	{
	public:
		DataType Data;
		BiTree* LC_Tree, * RC_Tree;

		BiTNode(DataType data) :Data(data),LC_Tree(NULL),RC_Tree(NULL)
		{
		}
		~BiTNode()
		{
			if (this->LC_Tree!=NULL)
			{
				delete this->LC_Tree;
				this->LC_Tree = NULL;
			}
			if (this->RC_Tree != NULL)
			{
				delete this->RC_Tree;
				this->RC_Tree = NULL;
			}
		}
		bool Create_LCTree(DataType emptymark)
		{
			DataType data;
			cin >> data;
			if (data == emptymark) return false;
			else
			{
				LC_Tree = new BiTree<DataType>(BiTree<DataType>(emptymark));
				LC_Tree->Create_Root(data);
				return true;
			}
		}
		bool Create_RCTree(DataType emptymark)
		{
			DataType data;
			cin >> data;
			if (data == emptymark) return false;
			else
			{
				RC_Tree = new BiTree<DataType>(BiTree<DataType>(emptymark));
				RC_Tree->Create_Root(data);
				return true;
			}
		}

		bool Copy_LCTree(DataType emptymark, BiTree* lbitree)
		{
			if (!lbitree) return false;
			else
			{
				LC_Tree = new BiTree<DataType>(BiTree<DataType>(emptymark));
				LC_Tree->Create_Root(lbitree->root->Data);
				return true;
			}
		}
		bool Copy_RCTree(DataType emptymark, BiTree* rbitree)
		{
			if (!rbitree) return false;
			else
			{
				RC_Tree = new BiTree<DataType>(BiTree<DataType>(emptymark));
				RC_Tree->Create_Root(rbitree->root->Data);
				return true;
			}
		}


	};

	DataType Emptymark;
	BiTNode<DataType>* root;

	BiTree(DataType emptymark) :root(NULL), Emptymark(emptymark)
	{
	}

	~BiTree()
	{
		if (this->BiTree_Empty())
		{
			delete this->root;
			this->root = NULL;
		}
	}

	//判断是否为空树
	bool BiTree_Empty()
	{
		if (this->root == NULL)
			return true;
		else
			return false;
	}

	//创建根结点
	void Create_Root(DataType data)
	{
		this->root = new BiTNode<DataType>(BiTNode<DataType>(data));
	}
	 
	//递归,先序遍历,生成一个二叉树 且 生成时空的子树不会占用空间   必须是用一个空二叉树开始生成,既root=NULL
	void PreT_CreateBiTree()
	{
		if (this->BiTree_Empty())
		{
			DataType data;
			cin >> data;
			if (data == this->Emptymark)
				return;
			else
				this->Create_Root(data);
		}
		if (this->root->Create_LCTree(this->Emptymark))
			root->LC_Tree->PreT_CreateBiTree();
		if(this->root->Create_RCTree(this->Emptymark))
			root->RC_Tree->PreT_CreateBiTree();
	}

	//递归,中序遍历,打印一个非空二叉树
	void InT_ShowBiTree()
	{
		if (this)
		{
			this->root->LC_Tree->InT_ShowBiTree();
			cout << this->root->Data;
			this->root->RC_Tree->InT_ShowBiTree();
		}
	}

	//递归,后序遍历,打印一个非空二叉树
	void PosT_ShowBiTree()
	{
		if (this)
		{
			this->root->LC_Tree->PosT_ShowBiTree();
			this->root->RC_Tree->PosT_ShowBiTree();
			cout << this->root->Data;
		}
	}

	//非递归,通过一个队列实现层序遍历,打印一个二叉树
	void LeT_ShowBiTree()
	{
		if (this&&!this->BiTree_Empty())
		{
			//初始化一个队列
			queue<BiTree<DataType>*> For_LeT;
			For_LeT.push(this);
			while (!For_LeT.empty())
			{
				BiTree<DataType>* now = For_LeT.front();
				cout << now->root->Data;
				For_LeT.pop();
				if (now->root->LC_Tree)
					For_LeT.push(now->root->LC_Tree);
				if (now->root->RC_Tree)
					For_LeT.push(now->root->RC_Tree);
			}
		}
	}

	//非递归,通过一个栈实现先序遍历,打印一个二叉树
	void NR_PreT_ShowBiTree()
	{
		if (this && !this->BiTree_Empty())
		{
			//初始化一个栈
			stack<BiTree<DataType>*> For_NR_Int;
			BiTree<DataType>* now = this;
			while (!For_NR_Int.empty() || now)
			{
				if (now)
				{
					cout << now->root->Data;
					For_NR_Int.push(now);
					now = now->root->LC_Tree;
			}
				else
				{
					now = For_NR_Int.top();
					now = now->root->RC_Tree;
					For_NR_Int.pop();
				}
			}
		}
	}

	//非递归,通过一个栈实现中序遍历,打印一个二叉树
	void NR_InT_ShowBiTree()
	{
		if (this && !this->BiTree_Empty())
		{
			//初始化一个栈
			stack<BiTree<DataType>*> For_NR_Int;
			BiTree<DataType>* now = this;
			while (!For_NR_Int.empty() || now)
			{
				if (now)
				{
					For_NR_Int.push(now);
					now = now->root->LC_Tree;
				}
				else
				{
					now = For_NR_Int.top();
					cout << now->root->Data;
					now = now->root->RC_Tree;
					For_NR_Int.pop();
				}
			}
		}
	}

	//递归,将一个 **非空** 二叉树克隆给另一个 **空的** 二叉树,先序遍历
	void BiTree_Copy(BiTree<DataType>& bitree)
	{
		if (bitree.BiTree_Empty())
			return;
		else if(!this->root)
			this->Create_Root(bitree.root->Data);
		if (this->root->Copy_LCTree(bitree.Emptymark, bitree.root->LC_Tree))
			root->LC_Tree->BiTree_Copy(*bitree.root->LC_Tree);
		if (this->root->Copy_RCTree(bitree.Emptymark, bitree.root->RC_Tree))
			root->RC_Tree->BiTree_Copy(*bitree.root->RC_Tree);
	}

	//递归,获得二叉树的深度
	int BiTree_Depth()
	{
		if (this->BiTree_Empty()) return 0;
		else
		{
			int ldepth = 0;
			if(this->root->LC_Tree)
				ldepth = this->root->LC_Tree->BiTree_Depth();

			int rdepth = 0;
			if (this->root->RC_Tree)
				rdepth = this->root->RC_Tree->BiTree_Depth();

			if (ldepth > rdepth) return (ldepth + 1);
			else return (rdepth + 1);
		}
	}

	//递归,获得二叉树的结点个数
	int BiTNode_Number()
	{
		if (this->BiTree_Empty()) return 0;
		else
		{
			int ln_num = 0;
			if (this->root->LC_Tree)
				ln_num = this->root->LC_Tree->BiTNode_Number();

			int rn_num = 0;
			if (this->root->RC_Tree)
				rn_num = this->root->RC_Tree->BiTNode_Number();
			
			return ln_num + rn_num + 1;
		}
	}

	//递归,获得二叉树叶子结点数
	int BiTLeaf_Number()
	{
		if (this->BiTree_Empty()) return 0;
		else
		{
			int lf_num = 0;
			if (this->root->LC_Tree)
				lf_num = this->root->LC_Tree->BiTLeaf_Number();
			else
				lf_num = 1;

			int rf_num = 0;
			if (this->root->RC_Tree)
				rf_num = this->root->RC_Tree->BiTLeaf_Number();

			return lf_num + rf_num;
		}
	}
};

