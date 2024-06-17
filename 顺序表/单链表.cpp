#include <iostream>
using namespace std;

typedef int ElemType;

struct LNode
{
	ElemType data;
	LNode* next;
};

class LinkList
{
private:
	LNode* Head;
public:
	//链表初始化
	LinkList()
	{
		Head = new LNode;
		Head->next = NULL;
	}

	//创建一个链表_前插法
	void CreateList_H(int num)
	{
		for (int i = 0; i < num; ++i)
		{
			LNode* p = new LNode;
			cin >> p->data;
			p->next = Head->next;
			Head->next = p;
		}
	}

	//创建一个链表_后插法
	void CreateList_B(int num)
	{
		LNode* r = Head;
		for (int a = 0; a < num; ++a)
		{
			LNode* p = new LNode;
			cin >> p->data;
			p->next = NULL;
			r->next = p;
			r = p;
		}
	}

	//获取第i个元素,将其值返回至e——按位置查找
	bool GetElem(int i, ElemType& e)
	{
		LNode* p = Head->next;
		int j = 1;
		while (p && j < i)
		{
			p = p->next;
			++j;
		}
		if (!p || j > i) return false;
		e = p->data;
		return true;
	}

	//按值查找
	LNode* LocateElem(ElemType e)
	{
		LNode* p = Head->next;
		while (p && p->data != e)
		{
			p = p->next;
		}
		return p;
	}

	//在第i个元素插入一个元素
	bool ListInsert(int i, ElemType e)
	{
		LNode* p = Head;
		int j = 0;
		while (p && (j < i - 1))
		{
			p = p->next;
			++j;
		}
		if (!p || j > i - 1) return false;        //j>i-1防止i为负数
		LNode* s = new LNode;
		s->data = e;
		s->next = p->next;
		p->next = s;
		return true;
	}

	//删除第i个元素
	bool ListDelete(int i)
	{
		LNode* p = Head;
		int j = 0;
		while ((p->next) && (j < i - 1))
		{
			p = p->next;
			++j;
		}
		if (!(p->next) || (j > i - 1)) return false;
		LNode* q = p->next;
		p->next = q->next;
		delete q;
		return true;
	}

	void Show()
	{
		LNode* p = Head->next;
		while(p)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
};

int main()
{

}