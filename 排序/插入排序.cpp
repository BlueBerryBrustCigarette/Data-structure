#include <iostream>
using namespace std;

typedef int Record;
class SqList
{
public:
	Record * Base;
	int Length;

	SqList(Record* base, int length) :Base(base), Length(length)
	{
	}
	
	//直接插入排序
	void InsertSort()
	{
		for (int i = 2; i <= Length; i++)
		{
			if (Base[i] < Base[i - 1])
			{
				Base[0] = Base[i];
				Base[i] = Base[i - 1];
				int j = i - 2;
				for (; Base[0] < Base[j]; j--)
					Base[j + 1] = Base[j];
				Base[j+1] = Base[0];
			}
		}
	};
	//折半插入排序
	void BinInsertSort()
	{
		for (int i = 2; i <= Length; i++)
		{
			Base[0] = Base[i];
			int low = 1, high = i - 1;
			int mid;
			while (low <= high)
			{
				mid = (low + high) / 2;
				if (Base[mid] < Base[i])
					low = mid + 1;
				else if (Base[mid] > Base[i])
					high = mid - 1;
				else
				{
					high = mid;
					break;
				}
					
			}
			for (int j = i - 1; j >= high + 1; j--)
				Base[j + 1] = Base[j];
			Base[high + 1] = Base[0];
		}
	};
	//希尔排序
	void ShellSort(int D[],int t)
	{
		for (int i = 0; i < t; i++)
		{
			this->ShellInsert(D[i]);
			cout << "第" << i + 1 << "次排序后的结果:";
			this->Show();
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
	void ShellInsert(int d)
	{
		for (int i = 1 + d; i <= Length; i++)
		{
			if (Base[i] < Base[i - d])
			{
				Base[0] = Base[i];
				Base[i] = Base[i - d];
				int j = i - 2 * d;
				for (; j > 0 && Base[0] < Base[j]; j -= d)
					Base[j + d] = Base[j];
				Base[j + d] = Base[0];
			}
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
	T1.InsertSort();
	cout << "直接插入排序后:";
	T1.Show();

	Record Data2[7];
	cout << "请输入记录:" << endl;
	for (int i = 1; i < 7; i++)
		cin >> Data2[i];
	SqList T2(Data2, 6);
	T2.BinInsertSort();
	cout << "折半插入排序后:";
	T2.Show();

	Record Data3[11];
	cout << "请输入记录:" << endl;
	for (int i = 1; i < 11; i++)
		cin >> Data3[i];
	SqList T3(Data3, 10);
	int D[3] = { 5,3,1 };
	cout << "希尔排序:";
	T3.ShellSort(D, 3);
	
}


//6 1 5 3 2 4
//49 38 65 97 76 13 27 49 55 4