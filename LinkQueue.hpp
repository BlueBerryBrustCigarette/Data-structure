#pragma once
#include<iostream>
using namespace std;

template<typename DataType>
class QNode
{
public:
	DataType data;
	QNode* next;
};

template<typename DataType>
class LinkQueue
{
public:
	QNode<DataType>* rear;
	QNode<DataType>* front;

	//初始化队列
	bool InitLinkQueue()
	{
		this->front = new QNode;
		this->rear = this->front;
		this->front->next;
		return true;
	}

	//从队尾入队
	bool EnQueue(DataType e)
	{
		QNode* p = new QNode;
		p->data = e;
		p->next = NULL;

		this->rear->next = p;
		this->rear = p;
		return true;
	}

	//队头元素出队
	bool DeQueue()
	{
		if (this->front == this->rear) return false;

		QNode* p = this->front->next;
		this->front->next = p->next;

		if (p == this->rear) this->rear = this->front;
		delete p;
		return true;
	}

	//获得队头元素
	DataType GetHead()
	{
		if (this->front != this->rear)
			return this->front->next->data;
	}
};






