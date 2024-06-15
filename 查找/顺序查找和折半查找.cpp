#include <iostream>
using namespace std;

struct Elem
{
	int key;
	int info;
};
class SSTable
{
public:
	Elem* Base;
	int Length;

	SSTable(Elem* base, int length) :Base(base), Length(length)
	{
	}

	int Search_Bin(Elem key)
	{
		int low = 1, high = Length;
		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (this->Base[mid].key < key.key)
				low = mid + 1;
			else if (this->Base[mid].key > key.key)
				high = mid - 1;
			else
				return mid;
		}
		return 0;
	}
	int Search_Seq(Elem key)
	{
		this->Base[0].key = key.key;
		int i = this->Length;
		for (; this->Base[i].key != key.key; i--);
		return i;
	}

};

int main()
{
	Elem Data[7];
	for (int i = 1; i < 7; i++)
		cin >> Data[i].key;
	SSTable T(Data, 6);
	cout << "输入要查找的关键字:" << endl;
	Elem text;
	cin >> text.key;
	cout << T.Base[T.Search_Bin(text)].key << endl;
}