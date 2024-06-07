#define _CRT_SECURE_NO_WARNINGS
//4-2 图的深度优先遍历与广度优先遍历（基于邻接表）

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0 //定义状态变量FALSE为0
#define TRUE 1 //定义状态变量TRUE为1
#define NULL 0 //定义NULL表示0

#define Error printf //定义错误提示信息输出单词为Error
#define MaxVNum 10 //最大顶点数为10个
#define QueueSize 10 //队列大小为10

//定义边的结构
typedef struct node 
{  
    int adjvex;        /*边结点结构*/
    int weight;        /*权*/
    struct node* next; /*下一个邻接点*/
} EdgeNode;

//定义顶点的结构
typedef struct vnode 
{ 
    int vertex;          /*顶点信息*/
    //   int pre;             /*记录第一个结点*/
    EdgeNode* firstedge; /*指向第一个邻接点的指针*/
} VertexNode;

//定义一个顶点数组
typedef VertexNode AdjList[MaxVNum + 1];

//定义图
typedef struct 
{
    AdjList adjlist;
    int n, e;//顶点数，边数
} ALGraph;

int visited[MaxVNum + 1];     /*访问标志域*/
typedef int DataType;

//定义队列
typedef struct 
{
    int front; /*队头指针*/
    int rear;  /*队尾指针*/
    //int count; /*队列中无数个数*/
    DataType data[MaxVNum];
} CirQueue;

void CreateALGraph(ALGraph* G);//创建图
void DFSTraverseAL(ALGraph* G);//深度优先遍历
void DFSAL(ALGraph* G, int i);
void BFSTraverseAL(ALGraph* G);//广度优先遍历
void BFSAL(ALGraph* G, int i);
void BFSAL1(ALGraph* G, int i);

//初始化队列
void InitQueue(CirQueue* Q) 
{
    Q->front = Q->rear = 0;
}

//判断队列是否为空
int QueueEmpty(CirQueue* Q) 
{
    return Q->front == Q->rear;
}

//判断队列是否已满
int QueueFull(CirQueue* Q) 
{
    if (Q->rear + 1 == Q->front)
        return 1;
    else
        return 0;
}

//进队函数
void EnQueue(CirQueue* Q, DataType x) 
{
    if (!QueueFull(Q)) 
    {
        // Q->count++;
        Q->data[Q->rear] = x;
        Q->rear = (Q->rear + 1) % QueueSize;
    }
    else 
    {
        Error("队列满！");
        exit(1);
    }
}

//出队函数
DataType DeQueue(CirQueue* Q)
{
    DataType temp;
    if (QueueEmpty(Q))
        Error("队列为空");
    else {
        temp = Q->data[Q->front];
        // Q->count--;
        Q->front = (Q->front + 1) % QueueSize;
        return temp;
    }
    return NULL;
}

//打印图函数，输出邻接表G
void DispAdj(ALGraph* G, int r)
{
    int i;
    EdgeNode* p;
    for (i = 1; i <= G->n; i++)
    {
        p = G->adjlist[i].firstedge;
        if (p != NULL) printf("V[%d]:  ", i);
        while (p != NULL)
        {
            printf("%3d", p->adjvex);
            if (r >= 3)
                printf(",%3d", p->weight);
            if (p->next != NULL)
                printf("->");
            p = p->next;
        }
        printf("\n");
    }
}

//打印菜单
void MenuList() 
{
    printf("\n\n\n******************************\n");
    printf("  1  -------  生成图的邻接表\n");
    printf("  2  -------  深度优先遍历\n");
    printf("  3  -------  广度优先遍历\n");
    printf("******************************\n");
}

//主函数
int main() 
{
    ALGraph* G; /*定义一个图变量*/
    int i = 100;
    //	system("color E0");
    MenuList();//打印菜单
    G = (ALGraph*)malloc(sizeof(ALGraph));
    G->n = 0;
    G->e = 0;
    while (i != 0) 
    {
        printf("请选择操作:");
        scanf("%d", &i);
        if (i == 1)   CreateALGraph(G);
        if (i == 2) DFSTraverseAL(G);
        if (i == 3) BFSTraverseAL(G);
    }
    return 0;
}

//生成图函数
void CreateALGraph(ALGraph* G) 
{
    int i, j, k, r, w;
    EdgeNode* s;
    printf("图的类型为：1—4,分别表示无向图、有向图、带权无向图、带权有向图");
    printf("请输入顶点数、边数和图的类型，输入格式：顶点数,边数，图的类型<回车>):");
    scanf("%d,%d,%d", &(G->n), &(G->e), &r);
    //	scanf("%d,%d",&(G->n),&(G->e));
    //printf("请输入图的类型，输入格式： number<CR>):\n");
   // scanf("%d", &r);

    printf("请输入顶点值，输入格式： number<CR>):\n");
    for (i = 1; i <= G->n; i++) 
    {
        printf("请输入第%d个顶点值:", i);
        scanf("\n%c", &(G->adjlist[i].vertex));  // 录入顶点
        G->adjlist[i].firstedge = NULL;
    }
    printf("输入边，输入格式(1<=i,j<=n)：i,j<回车>:\n");

    //处理无向图
    if (r == 1) 
    {
        for (k = 1; k <= G->e; k++) 
        {
            printf("输入第%d条边:", k);
            scanf("\n%d,%d", &i, &j);
            s = (EdgeNode*)malloc(sizeof(EdgeNode));
            s->adjvex = j;
            s->next = G->adjlist[i].firstedge;
            G->adjlist[i].firstedge = s;
            s = (EdgeNode*)malloc(sizeof(EdgeNode));
            s->adjvex = i;
            s->next = G->adjlist[j].firstedge;
            G->adjlist[j].firstedge = s;
        }
    }
    if (r == 2) // 处理有向图
    {  
        for (k = 1; k <= G->e; k++) 
        {
            printf("输入第%d条边:", k);
            scanf("\n%d,%d", &i, &j);
            s = (EdgeNode*)malloc(sizeof(EdgeNode));
            s->adjvex = j;
            s->next = G->adjlist[i].firstedge;
            G->adjlist[i].firstedge = s;
            //G->adjlist[j].indegree++; /*结点j的入度加1*/
           // G->adjlist[j].pre = -1;   /*默认上一个结点为-1（没有）*/
        }
    }

    if (r == 3)//处理无向网 
    {
        for (k = 1; k <= G->e; k++)
        {
            printf("输入第%d条边:", k);
            scanf("%d,%d,%d", &i, &j, &w);
            s = (EdgeNode*)malloc(sizeof(EdgeNode));
            s->adjvex = j;
            s->weight = w;
            s->next = G->adjlist[i].firstedge;
            G->adjlist[i].firstedge = s;
            s = (EdgeNode*)malloc(sizeof(EdgeNode));
            s->adjvex = i;
            s->weight = w;
            s->next = G->adjlist[j].firstedge;
            G->adjlist[j].firstedge = s;
        }
    }
    if (r == 4) //处理有向网
    {
        for (k = 0; k < G->e; k++)
        {
            printf("输入第%d条边:", k);
            scanf("%d,%d,%d", &i, &j, &w);
            s = (EdgeNode*)malloc(sizeof(EdgeNode));
            s->adjvex = j;
            s->weight = w;
            s->next = G->adjlist[i].firstedge;
            G->adjlist[i].firstedge = s;
        }
    }
    DispAdj(G, r);//调用打印图函数打印图
}

//深度优先遍历封装函数
void DFSTraverseAL(ALGraph* G) {
    int i, k;
    printf("深度优先遍历\n");
    for (i = 1; i <= G->n; i++)
        visited[i] = 0;
    printf("请输入遍历的初始顶点的地址下标（1-n):");
    scanf("%d", &k);
    DFSAL(G, k);
    for (i = 1; i <= G->n; i++) {
        // 此处非一般的深度优先，首先确保是深度优先，其次是按顺序遍历完所有结点
        if (!visited[i]) DFSAL(G, i);
    }
}

//深度优先遍历函数
void DFSAL(ALGraph* G, int i) {
    EdgeNode* p;
    printf("访问顶点:V%c\n", G->adjlist[i].vertex);
    visited[i] = 1;
    p = G->adjlist[i].firstedge;
    while (p) {
        if (!visited[p->adjvex]) DFSAL(G, p->adjvex);
        p = p->next;
    }
}

//广度优先遍历封装函数
void BFSTraverseAL(ALGraph* G) {
    int i, k;
    printf("广度优先遍历\n");
    for (i = 1; i <= G->n; i++) visited[i] = 0;
    printf("请输入遍历的初始顶点的地址下标（1-n):");
    scanf("%d", &k);
    BFSAL1(G, k);
    for (i = 1; i <= G->n; i++)
        if (!visited[i]) BFSAL1(G, i);
}

//广度优先遍历函数
void BFSAL1(ALGraph* G, int i)
{
    int k;

    CirQueue q;
    InitQueue(&q);
    EdgeNode* p;
    printf("访问顶点:V%c\n", G->adjlist[i].vertex);
    visited[i] = 1;
    EnQueue(&q, i);
    while (!QueueEmpty(&q))
        k = DeQueue(&q);
    p = G->adjlist[k].firstedge;
    while (p) {
        if (!visited[p->adjvex])
        {
            printf("访问顶点:V%c\n", G->adjlist[p->adjvex].vertex);
            visited[p->adjvex] = 1;
            EnQueue(&q, p->adjvex);
        }
        p = p->next;
    }
}
