#include <stdio.h>
int c1, c2;         //分别载重量
int n;              //书的捆数 
int w[100];         //书捆的分别重量
int cw;             //c1当前载重量
int bestw;          //c1当前最优载重量
int r;              //剩余书捆总重量 
int x[100];         //当前解
int bestx[100];      //当前最优解
int isok=1;
void Backtrack(int i);
void input();
void init();
void output();
void enough();
int main()
{
	input();
	init();
	if(isok){
	Backtrack(1);
	enough();
	output();
	return 0;
	}
} 

void input()
{
	int i,j,m;
	//文件输入
    FILE *file;
	file = fopen("data5.txt","r+");
    fscanf(file,"%d\n",&c1);
    fscanf(file,"%d\n",&c2);
    fscanf(file,"%d\n",&n);

	for(j = 0;j < n;j++){
		w[j]=0;
	}
	
    for(i = 1;i<=n;i++){
		fscanf(file,"%d\n",&w[i]);
		if(w[i]<=0||c1<=0||c2<=0||n<=0)
		{
			printf("输入数据不合法！！！请检查！ "); 
			isok=0;
			break;
    	}
	}
    fclose(file);

}
void init()
{
	cw = 0;             //每组样例初始化
	r = 0;
	bestw = 0;
	for( int i = 1; i <= n; i++)
	{
	        r += w[i];	
	}	
	if(r<=0)
	{
	printf("输入书捆重量不合法！！！ "); 
	isok=0;
    }	
}
void enough()
{
//c1为最优装载量后，判断C2是否能装下 
	for(int i = 1; i <=n; i++)
	{
		{
		    int sumc2,sum;
			sumc2+=(1-bestx[i])*w[i];
			if(sumc2>c2)
			{
				printf(" unsolvable!!!   ");
				isok=0;
				break;
				
			}
		}
	}	
}
void output()
{
	if(isok==1)
	{
		printf("book  ");
		for(int i = 1; i <= n; i++)
		{
		    printf("%d ",w[i]);
		}
		printf("\n");
		printf("c1    ");
		for(int i = 1; i <=n; i++)
		{
		    printf("%d  ",bestx[i]);
		}
		printf("\n");
		printf("c2    ");
		for(int i = 0; i < n; i++)
		{
		    printf("%d  ",1-bestx[i+1]);
		}
	}
}
void Backtrack(int i)
{
    if(i > n)
    {
        //当前解优于最优解，更新之
        if(cw > bestw)
        {
            for(int j = 1; j <= n; j++)
                bestx[j] = x[j];
            	bestw = cw;
        }
        return ;
    }
 
    //搜索子树,放入或不放入
    r -= w[i];              //剩余容量集合去掉w[i]
    if(cw + w[i] <= c1)     //可放入
    {
        x[i] = 1;           //放入
        cw += w[i];
        Backtrack(i+1);
 
        cw -= w[i];
    }

    if(cw + r > bestw)      //有可能有新的最优载重量
    {
        x[i] = 0;//向右子树移动
        Backtrack(i+1);
    }
    	r += w[i];              //回溯
}
