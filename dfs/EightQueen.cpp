#include <stdio.h>
#include <math.h>

/*八皇后问题是在8*8的棋盘上放置8枚皇后，使得棋盘中每个横向、纵向、左上至右下斜向、右上至左下斜向均只有一枚皇后*/

const int N = 8; //棋盘行数
int a[N] = {0}; //表示棋盘，若a[2]=2,则表示在第3行第2列放一个皇后，因为同一行不能放两个皇后，所以只需要1维数组就可以表示一个棋盘。

int num = 0;//解的个数

//纵向，斜向，若没有有皇存在，则返回true;否则返回false;
bool IsValid(int n)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == a[n] || (abs(a[i] - a[n]) == n - i))
		{
			return false;
		}
	}
	return true;
}

//打印出所有解
void Print()
{
	printf("第%d种解：\n",++num);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (a[i] == j)
			{
				printf("%d", i);
			}
			else
			{
				printf("#");
			}
		}
		printf("\n");
	}

	printf("-----------------\n");
}

void Put(int n)
{
	if (n == N)
	{
		Print();
		return;
	}
	for (int i = 0; i < N; i++)
	{
		a[n] = i;
		if (IsValid(n))
		{
			Put(n + 1);
		}
	}
}

int main()
{
	Put(0);
	return 0;
}