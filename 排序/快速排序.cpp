#include <iostream>
using namespace std;

typedef int Record;
class SqList
{
public:
	Record* Base;
	int Length;

	SqList(Record* base, int length) :Base(base), Length(length)
	{
	}
	//우醵탤埼
	void QuickSort()
	{
		Qsort(1, Length);
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
	int Partition(int low,int high)
	{
		Base[0] = Base[low];
		int pivotkey = Base[low];
		while (low < high)
		{
			while (low<high && Base[high]>=pivotkey) --high;
			Base[low] = Base[high];
			while (low<high && Base[low]<=pivotkey) ++low;
			Base[high] = Base[low];
		}
		Base[low] = Base[0];
		return low;
	}
	void Qsort(int low,int high)
	{
		if (low < high)
		{
			int pivotkey = Partition(low, high);
			Qsort(low, pivotkey - 1);
			Qsort(pivotkey + 1, high);
		}
	}
};

int main()
{
	Record Data1[7];
	cout << "请输入记录:" << endl;
	for (int i = 1; i < 7; i++)
		cin >> Data1[i];
	SqList T1(Data1, 6);
	T1.QuickSort();
	cout << "快速排序后:";
	T1.Show();
}


//6 1 5 3 2 4
