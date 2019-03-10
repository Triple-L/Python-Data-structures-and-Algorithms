
原稿：http://blog.csdn.net/yan_____/article/details/8219462#comments  
IDA*算法是A*算法和迭代加深算法的结合.  
A*算法需要维护open表和close表，以及排序选择最小代价的结点内存空间消耗过多。  
IDA*的答题思路是。首先 根据最初的数码表  

```
5	1	2	4
9	6	3	8
13	15	10	11
14	0	7	12

目标状态：
1	2	3	4
5	6	7	8
9	10	11	12
13	14	15	0
```
计算它到目标状态的曼哈顿距离之和，以它作为一个标尺即整个程序的走步最多也不会多于初状态的曼哈顿距离。
曼哈顿距离就是 每个数字最少需要几步走到最终位置。
下面的程序按照 上左右下的顺序执行，递归调用.先调用dfs()函数执行0与其上面的数字交换，此处是15 判断是否可解（逆序数)，可解可用则递归调用dfs() 如果OK 则继续调用深一层，不OK 进行向左 ，当上左右下都判断完毕不OK的话 回退一层，判断上一层的左 、右、下情况可以走通的话则继续向下递归。
每一步执行之前 使用判断语句 当前调用深度+当前的曼哈顿距离<=最初的曼哈顿距离则可以继续。一旦大于就可以直接舍弃了。

```
#include<stdio.h>  
#include<string.h>  
#include<math.h>  
#define size 4

int move[4][2]={{-1,0},{0,-1},{0,1},{1,0}};//上 左 右 下  置换顺序
char op[4]={'U','L','R','D'};  
int map[size][size],map2[size*size],limit,path[100];  
int flag,length;   
int goal[16][2]= {{3,3},{0,0},{0,1}, {0,2},{0,3}, {1,0},   
            {1,1}, {1,2}, {1,3},{2,0}, {2,1}, {2,2},{2,3},{3,0},{3,1},{3,2}};//各个数字应在位置对照表
int nixu(int a[size*size])  
{  
    int i,j,ni,w,x,y;  //w代表0的位置 下标，x y 代表0的数组坐标
    ni=0;  
    for(i=0;i<size*size;i++)  //，size*size=16
    {  
        if(a[i]==0)  //找到0的位置
            w=i;  
        for(j=i+1;j<size*size;j++)  //注意！！每一个都跟其后所有的比一圈 查找小于i的个数相加
        {  
            if(a[i]>a[j])  
                ni++;  
        }  
    }  
    x=w/size;  
    y=w%size;  
    ni+=abs(x-3)+abs(y-3);  //最后加上0的偏移量 
    if(ni%2==1)  
        return 1;  
    else  
        return 0;  
}  

int hv(int a[][size])//估价函数，曼哈顿距离，小等于实际总步数  
{  
    int i,j,cost=0;  
    for(i=0;i<size;i++)  
    {  
        for(j=0;j<size;j++)  
        {  
            int w=map[i][j];  
            cost+=abs(i-goal[w][0])+abs(j-goal[w][1]);  
        }  
    }  
    return cost;  
}  

void swap(int*a,int*b)  
{  
    int tmp;  
    tmp=*a;  
    *a=*b;  
    *b=tmp;  
}  
void dfs(int sx,int sy,int len,int pre_move)//sx,sy是空格的位置  
{  
    int i,nx,ny;  
		if(flag)  
			return;  
    int dv=hv(map);  
		if(len==limit)  
		{  
			if(dv==0)  //成功！ 退出 
			{  
				flag=1;  
				length=len;  
				return;  
			}  
			else  
				return;  //超过预设长度 回退
		}  
		else if(len<limit)  
		{  
			if(dv==0)  //短于预设长度 成功！退出
			{  
				flag=1;  
				length=len;  
				return;  
			}  
		}  
    for(i=0;i<4;i++)  
    {  
			if(i+pre_move==3&&len>0)//不和上一次移动方向相反，对第二步以后而言  
				continue;      
        nx=sx+move[i][0];  //移动的四步 上左右下
        ny=sy+move[i][1];  
        if(0<=nx&&nx<size && 0<=ny&&ny<size)  //判断移动合理
        {  
            swap(&map[sx][sy],&map[nx][ny]);  
            int p=hv(map);   //移动后的 曼哈顿距离p=16
            if(p+len<=limit&&!flag)  //p+len<=limit&&!flag剪枝判断语句
            {  
                path[len]=i;  
                dfs(nx,ny,len+1,i);  //如当前步成功则 递归调用dfs
                if(flag)  
                    return;  
            }  
            swap(&map[sx][sy],&map[nx][ny]);  //不合理则回退一步
        }  
    }  
}  
int main()  
{  
    int i,j,k,l,m,n,sx,sy;  
    char c,g;  
    i=0;
	printf("请输入您要判断几组十五数码：\n");
    scanf("%d",&n);  
    while(n--)       
    {   printf("请输入十五数码：\n");
        flag=0,length=0;
        memset(path,-1,sizeof(path));  //已定义path[100]数组，将path填满-1   void* memset(void*s,int ch,size_t n):将S中前n个字节用ch替换并返回S。
        for(i=0;i<16;i++)  //给map 和map2赋值map是二维数组，map2是一维数组
        {  
            scanf("%d",&map2[i]);  
            if(map2[i]==0)  
            {   
                map[i/size][i%size]=0;  
                sx=i/size;sy=i%size;  
            }  
            else  
            {  
                map[i/size][i%size]=map2[i];  
            }  
          
        }                                      


        if(nixu(map2)==1)                     //该状态可达  
        {  
            limit=hv(map);  //全部的曼哈顿距离之和
            while(!flag&&length<=50)//要求50步之内到达  
            {  
                dfs(sx,sy,0,0);  
                if(!flag)  
                limit++; //得到的是最小步数  
            }  
            if(flag)  
            {  
                for(i=0;i<length;i++)  
                printf("%c",op[path[i]]);  //根据path输出URLD路径
                printf("\n");  
            }  
        }  
        else if(!nixu(map2)||!flag)  
            printf("This puzzle is not solvable.\n");  
    }  
    return 0;  
}  
```
