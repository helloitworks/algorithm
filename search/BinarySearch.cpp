#include <iostream.h>

/*l <= r的情况下
 *如果比mid小则继续查找小的一边
 *如果相等可以直接返回
 *如果比mid大则继续查找大的一边
 */
int BinarySearch(int a[], int n, int value)
{
	int l = 0;
	int r = n - 1;
	int mid;
	while (l <= r)
	{
		//mid = l + (r-l)/2;  
		mid = l + ((r-1)>>1);
		if (value < a[mid])
		{
			r = mid - 1;
		}
		else if(value == a[mid])
		{
			return mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	return -1;

}

int BinarySearchViaRecursion(int a[], int l, int r, int value)
{
	if (l > r)
	{
		return -1;
	}
	int mid = l + (r - l) / 2;
	if (value < a[mid])
	{
		return BinarySearchViaRecursion(a, l, mid-1, value);
	}
	else if (value == a[mid])
	{
		return mid;
	}
	else
	{
		return BinarySearchViaRecursion(a, mid+1, r, value);
	}
}
int main()
{
	int index, value;
	int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	cout << "Input the search number:";  
    cin >> value;  
	//index = BinarySearch(a, sizeof(a)/sizeof(int), value);
	index = BinarySearchViaRecursion(a, 0, sizeof(a)/sizeof(int)-1, value);
	if (index == -1)
	{
		cout<<"Not found!"<<endl;
	}
	else
	{
		cout<<"index:"<<index<<endl;
	}
	return 0;
}