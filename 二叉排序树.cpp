#include <iostream>
using namespace std;
#include<vector>

typedef int KeyType;
struct BSData
{
	KeyType key;
};
struct BSTNode 
{
	BSData data;
	BSTNode* lchild, * rchild;
};

class BiSortTree
{
private:
	BSTNode* root;
public:
	BiSortTree(vector<BSData> DataV):root(NULL)
	{
		for (int i = 0; i < DataV.size(); i++)
			Insert(root, DataV[i]);
	}
	BSTNode* BS_Search(BSData bsdata)
	{
		return Search(root, bsdata);
	}
	bool BS_Delete(BSData bsdata)             
	{
		return Search_Delete(root, bsdata);
	}
	void BS_Show()
	{
		InT_Show(root);
	}
private:
	void InT_Show(BSTNode* root)
	{
		if (root)
		{
			InT_Show(root->lchild);
			cout << root->data.key << " ";
			InT_Show(root->rchild);
		}
	}
	void Insert(BSTNode* &bst, BSData bsdata)
	{
		if (bst == NULL)
		{
			bst = new BSTNode;
			bst->data = bsdata;
			bst->lchild = NULL;
			bst->rchild = NULL;
		}
		else
		{
			if (bsdata.key < bst->data.key)
				Insert(bst->lchild, bsdata);
			else
				Insert(bst->rchild, bsdata);
		}
	}
	BSTNode* Search(BSTNode* bst, BSData bsdata)
	{
		if (bst == NULL)
			return NULL;
		else
		{
			if (bsdata.key == bst->data.key)
				return bst;
			else if (bsdata.key < bst->data.key)
				Search(bst->lchild, bsdata);
			else
				Search(bst->rchild, bsdata);
		}
	}
	void Delete_Node(BSTNode*& bst)                            //必须是&
	{
		if (bst->lchild && bst->rchild)							//用比他小的最大值来代替它
		{
			BSTNode** max_smaller = &bst->lchild;
			while ((*max_smaller)->rchild)
				max_smaller = &((*max_smaller)->rchild);
			bst->data = (*max_smaller)->data;
			Delete_Node(*max_smaller);
		}
		else if (bst->lchild)
		{
			BSTNode* temp = bst;
			bst = bst->lchild;
			delete temp;
		}
		else
		{
			BSTNode* temp = bst;
			bst = bst->rchild;
			delete temp;
		}
	}
	bool Search_Delete(BSTNode*& bst, BSData bsdata)              //必须是&
	{
		if (bst == NULL)
			return false;
		else
		{
			if (bsdata.key == bst->data.key)
			{
				Delete_Node(bst);
				return true;
			}
			else if (bsdata.key < bst->data.key)
				Search_Delete(bst->lchild, bsdata);
			else
				Search_Delete(bst->rchild, bsdata);
		}

	}
};


int main()
{
	int array[11] = { 38,12,34,56,13,6,98,3,17,40,78 };
	vector<BSData> DataV;
	for (int i = 0; i < 11; i++)
	{
		BSData bsdata;
		bsdata.key = array[i];
		DataV.push_back(bsdata);
	}
	BiSortTree T(DataV);

	BSData text;
	text.key = 12;
	T.BS_Show();
	cout << endl;

	T.BS_Delete(text);
	if (T.BS_Search(text))
		cout << T.BS_Search(text)->data.key;
	else
		cout << text.key << "没有查找到" << endl;
}
