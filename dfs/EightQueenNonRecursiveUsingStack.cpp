#include <stdio.h>
#include <math.h>
#include <stack>
using namespace std;
/*八皇后问题是在8*8的棋盘上放置8枚皇后，使得棋盘中每个横向、纵向、左上至右下斜向、右上至左下斜向均只有一枚皇后*/

const int N = 8; //棋盘行数
int a[N] = {0}; //表示棋盘，若a[2]=2,则表示在第3行第2列放一个皇后，因为同一行不能放两个皇后，所以只需要1维数组就可以表示一个棋盘。

int num = 0;//解的个数

struct Node
{
	int x;
	int y;
};

//纵向，斜向，若没有有皇存在，则返回true;否则返回false;
bool IsValid(Node node)
{
	for (int i = 0; i < node.x; i++)
	{
		if (a[i] == node.y || (abs(a[i] - node.y) == node.x - i))
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

void Put()
{
	Node node;
	stack<Node> stack;

	node.x = 0;
	node.y = 0;
	stack.push(node);
	while(stack.size() >= 1)
	{

		node = stack.top();
		while (node.y < N && !IsValid(node))
		{
			node.y++;
			a[node.x] = node.y;
		}

	
		if (node.y == N)
		{
			//回溯
			stack.pop();
			
			if (stack.size() == 0)
			{
				return;
			}
			node = stack.top();
			node.y++;
			a[node.x] = node.y;
			stack.pop();
			stack.push(node);
			
		}
		else
		{
			if (node.x == N-1)
			{
				//打印结果
				Print();
			
				//node = stack.top();
				node.y++;
				a[node.x] = node.y;
				stack.pop();
			    stack.push(node);
			}
			else
			{

				stack.pop();
				stack.push(node);
				
				//进入下一行
				node.x++;
				node.y = 0;
				a[node.x] = node.y;
				stack.push(node);
			}

		}

	}

}

int main()
{
	Put();
	return 0;
}