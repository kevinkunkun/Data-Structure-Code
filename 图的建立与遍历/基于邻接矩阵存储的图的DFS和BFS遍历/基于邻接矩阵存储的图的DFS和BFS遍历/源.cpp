#define _CRT_SECURE_NO_WARNINGS
//4-1图的深度优先遍历与广度优先遍历（基于邻接矩阵）

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define INFINITE 9999//定义无穷大为9999
#define MAX 10

int  A[MAX][MAX];
int visited[MAX];
int V[MAX];

//清楚输入输出缓存
void safe_flush(FILE* fp)
{
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n');
}

//生成图
void creatadj(int n, int e, int t)
{
	int i, j, k, w, v1;
	printf(" 生成图G\n");
	printf(" 请输入顶点值，输入格式： number（or char)<回车>):\n");
	for (i = 1; i <= n; i++)
	{
		safe_flush(stdin);//清除输入输出缓存
		scanf("%c", &V[i]);//录入顶点
	}
	printf(" 顶点为：");
	for (i = 1; i <= n; i++)
		printf(" V%c   ", V[i]);//打印顶点
	printf("\n");
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			if (t > 2) //两种图，1表示无向无权图，2表示有向无权图，3表示无向带权图，4表示有向带权图  
				A[i][j] = INFINITE;//若为无向图，将邻接矩阵中各边初始化为无穷大
			else
				A[i][j] = 0;//若为有向图，则将各边初始化为0

	//处理无权图
	if (t == 1 || t == 2)
	{
		printf(" 输入边，输入格式：i,j<回车>，其中，i,j为顶点的存储下标，1<=i<=%d,1<=j<=%d)\n", n, n);
		for (k = 1; k <= e; k++)
		{	//printf("输入第%d条边，输入格式：i,j<CR>):\n",k);
			scanf("%d,%d", &i, &j);
			while (i > n || j > n || i < 1 || j < 1)
			{
				printf(" 顶点的存储下标越界，请重新输入第%d条边 ", k);
				scanf("%d,%d", &i, &j);
			}
			A[i][j] = 1;
			if (t == 1)
				A[j][i] = 1;
		}
	}

	//处理带权图
	if (t == 3 || t == 4)
	{
		printf(" 输入条边及其权值，输入格式(w<9999,1<=i<=%d,1<=j<=%d)：i,j,w<CR>):\n", n, n);
		for (k = 1; k <= e; k++)
		{
			scanf("%d,%d,%d", &i, &j, &w);
			while (i > n || j > n || i < 1 || j < 1)
			{
				printf(" 顶点的存储下标越界，请重新输入第%d条边 ", k);
				scanf("%d,%d,%d", &i, &j, &w);
			}
			A[i][j] = w;
			if (t == 3)//如果是无向图
				A[j][i] = w;//将另一半矩阵的对称位置也赋值为w
		}
	}
}

//访问节点函数
void visit(int i)
{
	printf("V%c   ", V[i]);
}

//输出邻接矩阵g
void DispMG(int n)
{
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			if (A[i][j] == INFINITE)
				printf(" %3s", "∞");//如果是无穷大则输出∞
			else
				printf(" %3d", A[i][j]);//否则输出值
		printf("\n");
	}
}

//对于有向图与无向图的深度优先遍历封装函数 
void dfs(int i, int n)        
{  //有向图，无向图 
	int j;
	visit(i);//输出v[i]顶点 
	visited[i] = 1;//标志已经输出 
	for (j = 1; j <= n; j++)
		if ((A[i][j] == 1) && (!visited[j])) //若没有输出且有边 
			dfs(j, n);//递归

}

//对于有向网与无向网深度优先遍历封装函数
void dfs34(int i, int n)
{
	int j;
	visit(i);//输出v[i]顶点 
	visited[i] = 1;//标志已经输出 
	for (j = 1; j <= n; j++)
		if ((A[i][j] < INFINITE) && (!visited[j])) //若没有输出且有边 
			dfs34(j, n);//递归   
}

//调用dfs与dfs34处理所有深度优先遍历问题
void dfs1(int i, int n, int t) {

	int k, j;
	printf(" 深度优先遍历序列：");
	for (k = 1; k <= n; k++)
		visited[k] = 0;
	if (t == 1 || t == 2)//处理图
	{
		dfs(i, n);
		for (j = 1; j <= n; j++)
			if (!visited[j]) dfs(j, n);
	}
	else//处理网
	{
		dfs34(i, n);
		for (j = 1; j <= n; j++)
			if (!visited[j]) dfs34(j, n);
	}
	printf("\n");
}

//广度优先遍历的封装函数
void bfs(int i, int n, int t)
{
	int q[10] = { 0 };  //定义一个顺序队列  
	int j, r = 0, f = 0; //队列的队头队尾指针初始化为0
	visit(i);//输出v[i]顶点 
	visited[i] = 1;//标志已经输出 
	q[f] = i;
	f++;
	if (t == 1 || t == 2) //有向图，无向图 
	{
		while (r != f)
		{
			i = q[r];
			r++;
			for (j = 1; j <= n; j++)
			{
				if ((A[i][j] == 1) && (!visited[j]))//若没有输出且有边
				{
					visit(j);//输出v[i]顶点 
					visited[j] = 1;//标志已经输出 
					q[f] = j;
					f++;
				}
			}
		}
	}
	if (t == 3 || t == 4) //有向网，无向网
	{
		while (r != f)
		{
			i = q[r];
			r++;
			for (j = 1; j <= n; j++)
			{
				if ((A[i][j] < INFINITE) && (!visited[j]))//若没有输出且有边
				{
					visit(j);               //输出v[i]顶点 
					visited[j] = 1;           //标志已经输出 
					q[f] = j;
					f++;
				}
			}
		}
	}
}


//调用封装函数bfs完成广度优先遍历
void bfs1(int i, int n, int t) { //b 
	int k;
	printf(" 广度优先遍历序列：");
	for (k = 1; k <= n; k++)
		visited[k] = 0;
	bfs(i, n, t);
	int j;
	for (j = 1; j <= n; i++) {//判断是否全部输出 
		if (!visited[j]) {
			bfs(j, n, t);
		}
		j++;
	}
	printf("\n");
}

//生成菜单
void MenuList()
{
	printf("\n\n\n **************************\n");
	printf("  1  -------  生成图\n");
	printf("  2  -------  深度优先\n");
	printf("  3  -------  广度优先\n");
	printf("  0  -------  退出\n");
	printf(" **************************\n");

}

//主函数
int main()
{
	int n = 0, e, t, i;
	int k = 100;
	//system("color E0");
	MenuList();
	while (k != 0)
	{
		printf(" 请选择操作:");
		scanf("%d", &k);
		if (k == 1)
		{
			printf(" 请输入顶点数、边数、图的类型，输入格式：v,e,t):");
			scanf("%d,%d,%d", &n, &e, &t);
			creatadj(n, e, t);
			printf(" 图的邻接矩阵为：\n");
			DispMG(n);
		}
		if (k == 2)//广度和深度都只能用一次  
		{
			if (n <= 0)
				printf(" 图不存在，请运行功能1创建图\n");
			else
			{
				printf(" 请输入深度优先遍历的初始顶点：");
				scanf("%d", &i);
				dfs1(i, n, t);
			}
		}
		if (k == 3)
		{
			if (n <= 0)
				printf(" 图不存在，请运行功能1创建图\n");
			else
			{
				printf(" 请输入广度优先遍历的初始顶点：");
				scanf("%d", &i);
				bfs1(i, n, t);
			}
		}
	}

	return 0;
}
