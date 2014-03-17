#include <iostream.h>

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int Partion(int a[], int l, int r)
{
	while (l < r)
	{
		while(l < r && a[l] < a[r])l++;
		if (l < r)
		{
			swap(a[l], a[r]);
		}
		while(l < r && a[r] > a[l])r--;
		if (l < r)
		{
			swap(a[l], a[r]);
		}
	}
	return l;
}

void QuickSort(int a[], int l, int r)
{
	if (l >= r)
	{
		return;
	}
	int pivot = Partion(a, l, r);
	QuickSort(a, l, pivot - 1);
	QuickSort(a, pivot + 1, r);
}

void Display(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

int FindKthMaxNum(int a[], int l, int r, int kth)
{
	int pivot = Partion(a, l, r);
	if (kth < pivot)
	{
		return FindKthMaxNum(a, l, pivot - 1, kth);
	}
	else if (kth == pivot)
	{
		return pivot;
	}
	else
	{
		return FindKthMaxNum(a, pivot+1, r, kth);
	}
}

int main()
{

	int a[10] = {0, 2, 1, 3, 4, 5, 6, 17, 9, 8};
	int n = sizeof(a) / sizeof(int);
	int kth, index;
	//QuickSort(a, 0, n -1);
	//cout<<"QuickSort:";
	//Display(a, n);
	
	kth = 10;
	index = FindKthMaxNum(a, 0, n-1, kth);//indexΪkth
	cout<<"KthMaxNum:"<<a[index-1]<<endl;
	return 0;
}