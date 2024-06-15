#include <iostream>
using namespace std;

typedef int Record;
class Heap
{
public:
	Record* Base;
	int Length;

	Heap(Record* base, int length) :Base(base), Length(length)
	{
	}

	void HeapSort()
	{
		this->ToRealHeap();
		for (int i = Length; i > 1; --i)
		{
			Base[0] = Base[1];
			Base[1] = Base[i];
			Base[i] = Base[0];
			HeapAjust(1, i - 1);
		}
	}

	void Show()
	{
		for (int i = 1; i <= Length; i++)
		{
			cout << Base[i] << " ";
		}
		cout << endl;
	}
private:
	void HeapAjust(int start, int end)
	{
		int root = Base[start];
		for (int i = 2 * start; i <= end; i *= 2)
		{
			if (i + 1 <= end && Base[i] < Base[i + 1]) ++i;
			if (root > Base[i]) break;
			Base[start] = Base[i]; 
			start = i;
		}
		Base[start] = root;
	}
	void ToRealHeap()
	{
		for (int k = Length / 2; k >= 1; k--)
			HeapAjust(k, Length);
	}
};

int main()
{
	Record Data1[7];
	cout << "ÇëÊäÈë¼ÇÂ¼:" << endl;
	for (int i = 1; i < 7; i++)
		cin >> Data1[i];
	Heap T1(Data1, 6);
	T1.HeapSort();
	cout << "¶ÑÅÅÐòºó:";
	T1.Show();
}

//6 1 5 3 2 4
