/*
* 删除c语言中的单行跟多行注释，注意其中的action
*
*/

#include <stdio.h>
int main(void)
{
    char c, state;
    state = 0;
    while ((c = getchar()) != EOF) 
	{
		if (state == 0)		
		{
			if (c == '/') // 例子： int a = b; /
			{
				state = 1;
			}
			else
			{
				putchar(c); //action
			}
		}
		else if (state == 1)
		{
			if (c == '/')  //例子： int a = b; //
			{
				state = 2;

			} 
			else if (c == '*')  //例子： int a= b; /*
			{
				state = 3;
			} 
			else  //例子： <common/md5.h> or 8/3
			{
				state = 0;
				putchar('/'); //action
				putchar(c); //action
			}
		}
		else if (state == 2)	
		{
			if (c == '\n')  //例子： int a = b; //hehe<enter>
			{
				state = 0;
				putchar(c); //action
			}
			//例子： int a = b; //hehe
		}
		else if (state == 3)	
		{
			if (c == '*')  //例子： int a = b; /*heh*
			{
				state = 4;
			}
			//例子： int a = b; /*hehe
		}
		else if (state == 4)
		{
			if (c == '/')  //例子： int a = b; /*hehe*/
			{
				state = 0;
			}
			else  //例子： int a = b; /*hehe*h
			{
				state = 3;
			}
		}
		else
		{
			printf("state error!");
		}
		
	}
	return 0;
}
	
