#include <stdio.h>
#include <stdlib.h>   //malloc
#include <string.h> //memcpy
void Swap(int &a, int &b)
{
	int t;
	t = a;
	a = b;
	b = t;
}

/*
选择排序是从待排序的序列中选出最小的一个元素，将其跟已经有序的序列后面的元素交换位置，直到全部待排序的元素处理完。


设数组为a[0...n-1]
1、初始时，数组全为无序区为a[0..n-1]。令i=0
2、对于a[i],在a[i...n-1]中选择一个最小元素，并将其与a[i]交互。交换后a[0,i]就是有序的
3、i++重复第2步，直到处理完i==n-1，排序完成

时间复杂度：
上述程序的原操作有赋值、比较及交换，显然基本操作应该取比较。总的比较次数显然是：(n-1)+(n-2)+(n-3)+...+1这是一个等差数列之和，结果是n(n-1)/2
选择排序平均时间复杂度为O(n*n)

稳定性：
不稳定的
序列5 8 5 2，我们知道第一遍选择第1个元素5会和2交换，那么原序列中2个5的相对前后顺序就被破坏了，所以选择排序不是一个稳定的排序算法。

*/
void SelectSort(int a[], int n) 
{
	int i, j, minIndex;
	for (i = 0; i < n; i++)
	{
		minIndex = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < a[minIndex]) 
			{
				minIndex = j;
			}
		}
		Swap(a[i], a[minIndex]);
	}
}


/*
插入排序是通过不断扩大排序序列的长度来实现的，对于每一个待排序的元素，按其关键字大小插入到前面已经排好序的子序列中的适当位置，形成更长的有序子序列。
当每一个待排序的元素都这样子被循环迭代处理后，排序完成。

假设数组为a[0...n-1]
1、初始时，a[0]自成一个有序的子序列，无序区为a[1...n-1]，令i=1
2、对于每一个a[i...n-1]，将其并入到当前有序的子序列a[0...i-1]中形成更长的有序序列a[0,i]，直到处理完i==n-1，也即i==n的时候排序完成
3、当i == n的时候，a[0,n-1]的每一个元素都插入到正确的位置
上述1到3，采用了算法导论的循环不定式证明了这样的算法是正确的

*/

void InsertSort(int *a, int n) 
{
	int i, j;
	for (i = 1; i < n; i++) 
	{
		for (j = i - 1; j >= 0 && a[j] > a[j + 1]; j--) 
		{
			Swap(a[j], a[j + 1]);
		}
	}
}


/*
方法一：并入a[i]到有序子序列a[0...i-1]的时候,可以通过交换相邻数据的方法来实现
设j = i - 1;若a[j] > a[j+1]，则交换a[j]和a[j+1]，再j--继续这样循环处理，直到不满足这个条件或者j==-1。
*/

void InsertSort1(int *a, int n) 
{
	int i, j;
	for (i = 1; i < n; i++) 
	{
		for (j = i - 1; j >= 0 && a[j] > a[j + 1]; j--) 
		{
			Swap(a[j], a[j + 1]);
		}
	}
}


/*
方法二：并入a[i]到有序子序列a[0...i-1]的时候,可以通过搜索跟数据后移的方法来实现
1、先搜索到应该插入的位置pos
2、然后将a[pos...i-1]向后移动到a[pos+1...i]，腾出a[pos]的位置，然后将a[i]插入到a[pos]
*/

void InsertSort2(int a[], int n)
{
	int i, j, k,pos;
	//循环从第二个数组元素开始，因为arr[0]作为最初已排序部分
	for (i = 1; i < n; i++)
	{
		//为a[i]在前面的有序子序列中找一个合适的位置
		for (j = i - 1; j >= 0; j--)
			if (a[j] < a[i])
				break;
		//合适的位置是在j之后，也即j+1
		pos = j+1;
		//这个位置不是i自己（如是自己，不需要处理）
		if (pos != i)
		{
			//先将a[pos...i-1]向后移动到a[pos+1...i]，腾出a[pos]的位置，然后将a[i]插入到a[pos]
			int temp = a[i];
			for (k = i - 1; k >=pos ; k--)
				a[k + 1] = a[k];
			a[pos] = temp;
		}
	}
}

/*
方法三:并入a[i]到有序子序列a[0...i-1]的时候,可以通过搜索跟数据后移同时进行的方法来实现
设j = i-1;若a[j] > a[i]，则将a[j]后移到a[j+1]，然后再j--继续这样循环处理，直到不满足这个条件或者j==-1
*/
void InsertSort3(int a[], int n)
{
	int i, j;
	for (i = 1; i < n; i++)
	{
		if (a[i] >= a[i-1]) 
		{
			break;
		}
		int temp = a[i];
		for (j = i-1; j >= 0 && a[j] > temp; j--)
		{
			a[j + 1] = a[j];
		}
		a[j+1] = temp;
	}
}


/*
总结上述三种方法：
方法一，因为采用了Swap，每个Swap需要做三次赋值的操作，平均时间复杂度可以认为是3n*n
方法二，搜索后，再数据后移，分成两步，平均时间复杂度是2*n*n
方法三，搜索跟数据后移同时处理，平均时间复杂度是n*n
方法三是这三种插入排序方法中最优的算法

插入排序的时间复杂度分析：
最好情况就是，序列已经是升序排列了，在这种情况下，需要进行的比较操作需(n-1)次即可
最坏情况就是，序列是降序排列，那么此时需要进行的比较共有n(n-1)/2次，插入排序的赋值操作是比较操作的次数减去(n-1)次。
平均来说插入排序时间复杂度为O(n*n)

插入排序的稳定性分析：
若前面的元素跟当前元素一样，则不会做移位的操作，因此是稳定的
*/




/*冒泡排序是从待排序的序列中，比较相邻的前后二个数据，如前面元素值大于后面元素值则交换位置，第1趟下来最大的元素就沉在数组的第n-1的位置，起到全部待排序的元素处理完
设数组为a[0...n-1]
1、初始时，数组全为无序区为a[0...n-1]。令i=0
2、比较相邻的前面两个元素，若前面元素大于后面元素，则交换位置，一趟下来，最大的元素就"沉"在了a[n-1]
3、i++重复第2步，起码到处理完i=n-1,排序完成
*/

void BubbleSourt1(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				Swap(a[j], a[j+1]);
			}
		}
	}
}

/*冒泡排序可以优化，设置一个标记isSwapHappened，如果这一趟有发生交换，则为ture,否则为false.如果这一趟没有发生交换，则序列已经是有序的*/

void BubbleSourt2(int a[], int n)
{
	int i, j;
	bool isSwapHappened;
	for (i = 0; i < n; i ++)
	{
		isSwapHappened =  false;
		for (j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				Swap(a[j], a[j+1]);
				isSwapHappened = true;
			}
		}
		if (!isSwapHappened)
		{
			break;
		}
	}
}

/*另外还可以两向同时冒泡*/
void TwoWayBubbleSourt(int a[], int n)
{
	int i, low, high, isSwapHappend;
	low = 0;
	high = n - 1;

	while (low < high)
	{
		isSwapHappend = false;
		for (i = low; i < high; i++)
		{
			if (a[i] > a[i + 1])
			{
				Swap(a[i], a[i + 1]);
				isSwapHappend = true;
			}
		}
		if (!isSwapHappend) 
		{
			break;
		}
		high--;
		isSwapHappend = false;
		for(i = high; i > low; i--)
		{
			if (a[i] < a[i - 1])
			{
				Swap(a[i], a[i - 1]);
				isSwapHappend = true;
			}
		}
		if (!isSwapHappend) 
		{
			break;
		}
		low++;
	}
}
/* 
时间复杂度：
最好是一开始就有序的，只需要做n-1次判断，时间复杂度为O(n)
最差逆序的，需要做n(n-1)/2次比较，时间复杂度为O(n*n)
平均时间复杂度为O(n*n)

稳定性：
当相邻两个元素相等时，可以不交换，所以是稳定的
*/


/*
归并排序是建立在归并操作上的一种有效的排序算法。该算法是采用分治法的一个非常典型的应用。

1.两路归并递归算法思路
数组a[first...last] mid = (first + last) / 2;
可以把数组分成两组a[first...mid]以及a[mid+1...last]，然后让这两组都是有序的，合并这两组从而让a[first...last]有序
怎么让a[first...mid]以及a[mid+1...last]有序呢，可以把a[first...mid]跟a[mid+1...last]分别再分成两组，依次类推。
直到当分出来的小组只有一个元素时，可以认为这个小组已经有序，然后再合并相邻的两个小组。
这样通过先递归的分解数列，再合并数列就完成了归并排序。

时间复杂度：
设数组长度为N，将数组二分法分成N个小组，需要logN步，每一步都是一个合并有序序列的过程，时间复杂度为N,故一共为N * logN
空间复杂度：
需要另外一个辅助数组，空间复杂度为N
稳定性：
稳定的，因为在将两个有序的序列合并成一个大的有序序列时，在元素相等的情况下，可以优先选择左边有序序列的元素
*/

//将有两个有序序列a[first...mid]和a[mid+1...last]合并。借助一个跟a大小一样的temp数组
void Merge(int a[], int first, int mid, int last, int temp[]) 
{
	int i = first, j = mid+1;
	int k = 0;
	while (i <= mid && j <= last)
	{
		if (a[i] <= a[j])
		{
			temp[k++] = a[i++];
		} else {
			temp[k++] = a[j++];
		}
	}
	while (i <= mid ) 
	{
		temp[k++] = a[i++];
	}
	while (j <= last)
	{
		temp[k++] = a[j++];
	}
	for(int v = 0; v < k; v++)
	{
		a[first + v] = temp [v];
	}
}

//归并排序
void MergeSort(int a[], int first, int last, int temp[])
{
	if (first < last) //递归的终结条件：子区间长度为1（一个记录自然有序
	{
		int mid = (first + last)/2;
		MergeSort(a, first, mid, temp); //让左边a[first...mid]有序
		MergeSort(a, mid+1, last, temp); //让右边[mid+1...last]有序
		Merge(a, first, mid, last, temp); //再将两个有序序列合并
	}
}

/*2.两路归并排序非递归实现
①把 n 个记录看成 n 个长度为 l 的有序子序列；
②进行两两归并使记录关键字有序，得到 n/2 个长度为 2 的有序子序列；
③重复第②步直到所有记录归并成一个长度为 n 的有序子序列为止。
*/


void MergeSort2(int a[], int n, int temp[])
{
	int first, mid, last;
	int i = 0;
	//步长
	for (int step = 1; step < n; step *= 2)
	{
		for (i = 0; i < n; i += 2 * step)
		{
			first = i;
			mid = i + step - 1;
			last = i + 2 * step - 1;
			if (mid >= n) {
				break;
			}
			if (last >= n) {
				last = n-1;
			}
			Merge(a, first, mid, last, temp);
		}
	}
}


/*快速排序
快速排序是C.R.A.Hoare于1962年提出的一种划分交换排序。它采用了一种分治的策略，通常称其为分治法(Divide-and-Conquer Method)。
该方法的基本思想是：
1、选择轴值：pivot
2、分割，并返回轴值位置：将序列划分为两个子序列L和R，使得L中所有记录都小于或等于轴值，R中记录都大于轴值
3、递归处理：对子序列L和R递归进行快速排序

对于步骤1跟2，可以用下面的例子来说明：

例子：



说明：


代码如下：
*/


/*
//选择轴值，分割，并返回轴值位置
int Partition(int a[], int l, int r)
{
	//选择轴值
	int pivot = a[l];
	//分割
	int i = l, j = r;
	while (i < j)
	{
		while(i < j && a[j] > pivot) // 从右向左找第一个小于等于pivot的数
			j--;  
		if(i < j) 
			a[i++] = a[j];
		
		while(i < j && a[i] <= pivot) // 从左向右找第一个大于pivot的数
			i++;  
		if(i < j) 
			a[j--] = a[i];
	}
	a[i] = pivot;
	//返回轴值位置
	return i;
}

*/

/*
  步骤1、2再加上步骤3，一个完整的快速排序代码如下
*/
/*
void QuickSort(int a[], int l, int r)
{
	// 如果子序列中只有0或1个记录，就不需排序
	if (r <= l)
	{
		return;
	}
	//选择轴值，分割，并返回轴值
	int i = Partition(a,l,r);
	//对轴值左边的子序列进行递归快速排序
	QuickSort(a, l, i - 1);  
	//对轴值右边的子序列进行递归快速排序
    QuickSort(a, i + 1, r);
}*/
        

/*优化的快速排序*/

//选择轴值，分割，并返回轴值位置
int Partition(int a[], int l, int r)
{
	//优化1：取中间这一个数为轴值
	Swap(a[l], a[(r-l)/2]);
	//选择轴值
	int pivot = a[l];
	//分割
	int i = l, j = r;
	while (i < j)
	{
		while(i < j && a[j] > pivot) // 从右向左找第一个小于等于pivot的数
			j--;  
		if(i < j) 
			a[i++] = a[j];
		
		while(i < j && a[i] <= pivot) // 从左向右找第一个大于pivot的数
			i++;  
		if(i < j) 
			a[j--] = a[i];
	}
	a[i] = pivot;
	//返回轴值位置
	return i;
}


void QuickSort(int a[], int l, int r)
{
	// 如果子序列中只有0或1个记录，就不需排序
	if (r <= l)
	{
		return;
	}
	//优化2：如果序列长度小于等于阈值(16最佳),停止分割跳出递归
	if((r - l + 1) > 16)
	{
		//选择轴值，分割，并返回轴值
		int i = Partition(a,l,r);
		//对轴值左边的子序列进行递归快速排序
		QuickSort(a, l, i - 1);  
		//对轴值右边的子序列进行递归快速排序
		QuickSort(a, i + 1, r);
	}
}



void ImprovedQuickSort(int a[], int l, int r)
{
	QuickSort(a, l, r);
	//优化2收尾，进行一遍插入排序
	InsertSort(a,r - l + 1);
}



//	int a[3] = {5,24,24};的时候有问题，会死循环 QuickSort(a,0,1)
/*
void QuickSort(int a[], int first, int last)
{
	if (first >= last)
	{
		return;
	}
	int mid = (first + last) / 2;
	int i = first, j = last;
	while(i < j)
	{
		while(i < j && a[i] < a[mid]) {
			i++;
		}

		while(i < j && a[j] > a[mid]) {
			j--;
		}
		if(i < j){
			// <=mid的，在i的左边; >=mid的在j右边
			Swap(a[i], a[j]);
			i++;
			j--;
		}
	}

	QuickSort(a, 0, i - 1);
	QuickSort(a, i, last);
}*/

/*
void HeapShiftDown(int a[], int i, int n)
{
	int temp = a[i];
	int lchild = 2*i + 1;
	int rchild = 2*i + 2;
	while ((temp < a[lchild] || temp < a[rchild]) && i < n && lchild < n && rchild < n)
	{
		if (temp < a[lchild])
		{
			a[i] = a[lchild];
			i = lchild;
			lchild = 2*i + 1;
			rchild = 2*i + 2;
			continue;
		}

		if (temp < a[rchild])
		{
			a[i] = a[rchild];
			lchild = 2*i + 1;
			rchild = 2*i + 2;
			continue;
		}
	}
}
*/

//堆的插入


/*
void MaxHeapFixDown(int a[], int i, int n)
{
	int temp = a[i];
	int j = 2*i + 1;
	while (j < n)
	{
		if (j + 1 < n && a[j + 1] > a[j]) //在左右孩子中找最大的  
		{
			j = j + 1;
		}
		if (a[j] <= temp)
		{
			break;
		} 
		else 
		{
			a[i] = a[j]; //把较大的子结点往上移动,替换它的父结点，类似于插入排序
			i = j;
			j = 2 * i + 1;
		}
	}
	a[i] = temp;
}
*/

//将a[i]插入到最小堆a[0...i-1]中的适当位置，形成更大的最小堆a[0...i]，类似于插入排序 
void MinHeapFixUp(int a[], int i)
{
	int j,temp;
	temp = a[i];
	for (j = (i - 1)/2; j >= 0; j = (i-1)/2) //j为父结点
	{
		if (a[j] > temp)
		{
			a[i] = a[j]; //把较大的父结点往下移动,替换它的子结点  
			i = j;
		}
		else
		{
			break;
		}
	}
	a[i] = temp;
}

//在最小堆的索引为n处插入新的数据num
void MinHeapAddNumber(int a[], int n, int num)  
{  
    a[n] = num;  
    MinHeapFixUp(a, n);  
}  


//对a[i]进行自上而下的重建堆，n为结点总数,类似于插入排序 
void MinHeapFixDown(int a[], int i, int n)
{
	int temp = a[i];
	for (int j = 2 * i + 1; j < n ; j = 2 * i + 1) //j为子结点
	{
		if (j + 1 < n && a[j + 1] > a[j])
		{
			j = j + 1; //在左右结点中找最小的
		}
		if (a[j] < a[i])
		{
			a[i] = a[j]; //把较小的子结点往上移动,替换它的父结点 
			i = j;
		} 
		else 
		{
			break;
		}
	}
	a[i] = temp;
}

//删除最小节点 
void MaxHeapDeleteElement(int a[], int n)
{
	//交换
	Swap(a[0], a[n-1]);
	//删除
	MinHeapFixDown(a, 0, n-1);
}


//堆化数组建立最小堆
void MakeMinHeap(int a[], int n)
{
	for (int i = n/2 -1; i >= 0; i--)
	{
		MinHeapFixDown(a, i, n);
	}
}

//堆排序
void MinHeapSort(int a[], int n)
{
	//堆化数组，建立最小堆
	MakeMinHeap(a, n);
	for (int i = n-1; i > 0; i--)
	{
		Swap(a[i], a[0]);
		MinHeapFixDown(a, 0, i);
	}
}

/*---------------------------ShellSort---------------------------*/
void ShellSort1(int a[], int n) 
{
	//分组
	for (int gap = n/2; gap >= 1; gap /=2)
	{
		//分组的起点
		for (int i = 0; i < gap; i++)
		{
			//使用插入排序处理每一个分组	
			for (int j = i + gap; j < n; j += gap)
			{
				int temp = a[j];
				for (int k = j - gap; k >= 0; k -= gap)
				{
					if (a[k] > temp)
					{
						a[k + gap] = a[k]; 
					}
					else 
					{
						break;
					}
				}
				a[k + gap] = temp;
			}
		}
	}
}

void ShellSort2(int a[], int n) 
{
	//分组
	for (int gap = n/2; gap >= 1; gap /=2)
	{
		//对于从gap开始的每一个索引，在本组之内进行插入排序	
		for (int j = gap; j < n; j += gap)
		{
			int temp = a[j];
			for (int k = j - gap; k >= 0; k -= gap)
			{
				if (a[k] > temp)
				{
					a[k + gap] = a[k]; 
				}
				else 
				{
					break;
				}
			}
			a[k + gap] = temp;
		}
	}
}


void CountingSort(int a[], int n, int k)
{
	//counted_a用于存放计数
	int *counted_a = (int *)malloc(sizeof(int) * k);
	//sorted_a用于存放已经排序好的元素
	int *sorted_a = (int *)malloc(sizeof(int) * n);

	int i;
	for (i = 0; i < k; i++)
	{
		counted_a[i] = 0;
	}
	// 计数：统计待排序数组中元素的出现次数
	for (i = 0; i < n; i++)
	{
		counted_a[a[i]] ++;
	}

	//求计数和
	for (i = 1; i < k; i++)
	{
		counted_a[i] += counted_a[i - 1];
	}

	// 整理：根据数组counted_a来将待排序数组a中的元素排到正确的位置
	for (i = n-1; i >= 0; i--)
	{
		sorted_a[counted_a[a[i]] - 1] = a[i];
		counted_a[a[i]]--;
	}
	//将已经排序的数组复制回原来初始数组
	memcpy(a, sorted_a, sizeof(int) *n); 

	free(counted_a);
	free(sorted_a);

}


int main() 
{
	int a[5] = {25,13,50,18,35};
//	int a[3] = {5,24,24};
	int n = sizeof(a)/sizeof(int);
//	InsertSort3(a,n);
	int *temp = new int[n];
	CountingSort(a, n, 100);

	for (int i =0; i < n; i++) 
	{
		printf("%d ",a[i]);
	}
	return 0;
}
