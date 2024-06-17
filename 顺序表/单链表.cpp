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
	//�����ʼ��
	LinkList()
	{
		Head = new LNode;
		Head->next = NULL;
	}

	//����һ������_ǰ�巨
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

	//����һ������_��巨
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

	//��ȡ��i��Ԫ��,����ֵ������e������λ�ò���
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

	//��ֵ����
	LNode* LocateElem(ElemType e)
	{
		LNode* p = Head->next;
		while (p && p->data != e)
		{
			p = p->next;
		}
		return p;
	}

	//�ڵ�i��Ԫ�ز���һ��Ԫ��
	bool ListInsert(int i, ElemType e)
	{
		LNode* p = Head;
		int j = 0;
		while (p && (j < i - 1))
		{
			p = p->next;
			++j;
		}
		if (!p || j > i - 1) return false;        //j>i-1��ֹiΪ����
		LNode* s = new LNode;
		s->data = e;
		s->next = p->next;
		p->next = s;
		return true;
	}

	//ɾ����i��Ԫ��
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