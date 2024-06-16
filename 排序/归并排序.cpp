#include <iostream>
using namespace std;

typedef int Record;
class SqList
{
public:
	Record* Base;
	Record* Sup;
	int Length;

	SqList(Record* base, Record* sup, int length) :Base(base), Sup(sup), Length(length)
	{
	}

	//πÈ≤¢≈≈–Ú
	void MergeSort()
	{
		MSort(1, Length);
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
	void Merge(int start,int mid,int end)
	{
		int p1 = start, p2 = mid + 1;
		int S_index = start;
		while (p1 <= mid && p2 <= end)
		{
			if (Sup[p1] >= Sup[p2]) Base[S_index++] = Sup[p2++];
			else Base[S_index++] = Sup[p1++];
		}
		while (p1 <= mid) 
			Base[S_index++] = Sup[p1++];
		while (p2 <= end) 
			Base[S_index++] = Sup[p2++];
	}
	void Copy(int start,int end)
	{
		for (int i = start; i <= end; i++)
			Sup[i] = Base[i];
	}
	void MSort(int low,int high)           //∂‘low-high∑∂ŒßΩ¯––πÈ≤¢≈≈–Ú
	{
		if (low == high) Sup[low] = Base[low];
		else
		{
			int mid = (low + high) / 2;
			MSort(low, mid);
			MSort(mid + 1, high);
			Merge(low, mid, high);
			Copy(low, high);
		}
	}
};

int main()
{
	Record Data[7];
	Record Sup[7];
	cout << "«Î ‰»Îº«¬º:" << endl;
	for (int i = 1; i < 7; i++)
		cin >> Data[i];
	SqList T(Data, Sup, 6);
	T.MergeSort();
	cout << "πÈ≤¢≈≈–Ú∫Û:";
	T.Show();
}

//6 1 5 3 2 4
