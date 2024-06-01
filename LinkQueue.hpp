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

	//��ʼ������
	bool InitLinkQueue()
	{
		this->front = new QNode;
		this->rear = this->front;
		this->front->next;
		return true;
	}

	//�Ӷ�β���
	bool EnQueue(DataType e)
	{
		QNode* p = new QNode;
		p->data = e;
		p->next = NULL;

		this->rear->next = p;
		this->rear = p;
		return true;
	}

	//��ͷԪ�س���
	bool DeQueue()
	{
		if (this->front == this->rear) return false;

		QNode* p = this->front->next;
		this->front->next = p->next;

		if (p == this->rear) this->rear = this->front;
		delete p;
		return true;
	}

	//��ö�ͷԪ��
	DataType GetHead()
	{
		if (this->front != this->rear)
			return this->front->next->data;
	}
};






