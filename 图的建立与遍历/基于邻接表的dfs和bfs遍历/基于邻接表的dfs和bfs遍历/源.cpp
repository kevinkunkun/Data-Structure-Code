#define _CRT_SECURE_NO_WARNINGS
//4-2 ͼ��������ȱ����������ȱ����������ڽӱ�

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0 //����״̬����FALSEΪ0
#define TRUE 1 //����״̬����TRUEΪ1
#define NULL 0 //����NULL��ʾ0

#define Error printf //���������ʾ��Ϣ�������ΪError
#define MaxVNum 10 //��󶥵���Ϊ10��
#define QueueSize 10 //���д�СΪ10

//����ߵĽṹ
typedef struct node 
{  
    int adjvex;        /*�߽��ṹ*/
    int weight;        /*Ȩ*/
    struct node* next; /*��һ���ڽӵ�*/
} EdgeNode;

//���嶥��Ľṹ
typedef struct vnode 
{ 
    int vertex;          /*������Ϣ*/
    //   int pre;             /*��¼��һ�����*/
    EdgeNode* firstedge; /*ָ���һ���ڽӵ��ָ��*/
} VertexNode;

//����һ����������
typedef VertexNode AdjList[MaxVNum + 1];

//����ͼ
typedef struct 
{
    AdjList adjlist;
    int n, e;//������������
} ALGraph;

int visited[MaxVNum + 1];     /*���ʱ�־��*/
typedef int DataType;

//�������
typedef struct 
{
    int front; /*��ͷָ��*/
    int rear;  /*��βָ��*/
    //int count; /*��������������*/
    DataType data[MaxVNum];
} CirQueue;

void CreateALGraph(ALGraph* G);//����ͼ
void DFSTraverseAL(ALGraph* G);//������ȱ���
void DFSAL(ALGraph* G, int i);
void BFSTraverseAL(ALGraph* G);//������ȱ���
void BFSAL(ALGraph* G, int i);
void BFSAL1(ALGraph* G, int i);

//��ʼ������
void InitQueue(CirQueue* Q) 
{
    Q->front = Q->rear = 0;
}

//�ж϶����Ƿ�Ϊ��
int QueueEmpty(CirQueue* Q) 
{
    return Q->front == Q->rear;
}

//�ж϶����Ƿ�����
int QueueFull(CirQueue* Q) 
{
    if (Q->rear + 1 == Q->front)
        return 1;
    else
        return 0;
}

//���Ӻ���
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
        Error("��������");
        exit(1);
    }
}

//���Ӻ���
DataType DeQueue(CirQueue* Q)
{
    DataType temp;
    if (QueueEmpty(Q))
        Error("����Ϊ��");
    else {
        temp = Q->data[Q->front];
        // Q->count--;
        Q->front = (Q->front + 1) % QueueSize;
        return temp;
    }
    return NULL;
}

//��ӡͼ����������ڽӱ�G
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

//��ӡ�˵�
void MenuList() 
{
    printf("\n\n\n******************************\n");
    printf("  1  -------  ����ͼ���ڽӱ�\n");
    printf("  2  -------  ������ȱ���\n");
    printf("  3  -------  ������ȱ���\n");
    printf("******************************\n");
}

//������
int main() 
{
    ALGraph* G; /*����һ��ͼ����*/
    int i = 100;
    //	system("color E0");
    MenuList();//��ӡ�˵�
    G = (ALGraph*)malloc(sizeof(ALGraph));
    G->n = 0;
    G->e = 0;
    while (i != 0) 
    {
        printf("��ѡ�����:");
        scanf("%d", &i);
        if (i == 1)   CreateALGraph(G);
        if (i == 2) DFSTraverseAL(G);
        if (i == 3) BFSTraverseAL(G);
    }
    return 0;
}

//����ͼ����
void CreateALGraph(ALGraph* G) 
{
    int i, j, k, r, w;
    EdgeNode* s;
    printf("ͼ������Ϊ��1��4,�ֱ��ʾ����ͼ������ͼ����Ȩ����ͼ����Ȩ����ͼ");
    printf("�����붥������������ͼ�����ͣ������ʽ��������,������ͼ������<�س�>):");
    scanf("%d,%d,%d", &(G->n), &(G->e), &r);
    //	scanf("%d,%d",&(G->n),&(G->e));
    //printf("������ͼ�����ͣ������ʽ�� number<CR>):\n");
   // scanf("%d", &r);

    printf("�����붥��ֵ�������ʽ�� number<CR>):\n");
    for (i = 1; i <= G->n; i++) 
    {
        printf("�������%d������ֵ:", i);
        scanf("\n%c", &(G->adjlist[i].vertex));  // ¼�붥��
        G->adjlist[i].firstedge = NULL;
    }
    printf("����ߣ������ʽ(1<=i,j<=n)��i,j<�س�>:\n");

    //��������ͼ
    if (r == 1) 
    {
        for (k = 1; k <= G->e; k++) 
        {
            printf("�����%d����:", k);
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
    if (r == 2) // ��������ͼ
    {  
        for (k = 1; k <= G->e; k++) 
        {
            printf("�����%d����:", k);
            scanf("\n%d,%d", &i, &j);
            s = (EdgeNode*)malloc(sizeof(EdgeNode));
            s->adjvex = j;
            s->next = G->adjlist[i].firstedge;
            G->adjlist[i].firstedge = s;
            //G->adjlist[j].indegree++; /*���j����ȼ�1*/
           // G->adjlist[j].pre = -1;   /*Ĭ����һ�����Ϊ-1��û�У�*/
        }
    }

    if (r == 3)//���������� 
    {
        for (k = 1; k <= G->e; k++)
        {
            printf("�����%d����:", k);
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
    if (r == 4) //����������
    {
        for (k = 0; k < G->e; k++)
        {
            printf("�����%d����:", k);
            scanf("%d,%d,%d", &i, &j, &w);
            s = (EdgeNode*)malloc(sizeof(EdgeNode));
            s->adjvex = j;
            s->weight = w;
            s->next = G->adjlist[i].firstedge;
            G->adjlist[i].firstedge = s;
        }
    }
    DispAdj(G, r);//���ô�ӡͼ������ӡͼ
}

//������ȱ�����װ����
void DFSTraverseAL(ALGraph* G) {
    int i, k;
    printf("������ȱ���\n");
    for (i = 1; i <= G->n; i++)
        visited[i] = 0;
    printf("����������ĳ�ʼ����ĵ�ַ�±꣨1-n):");
    scanf("%d", &k);
    DFSAL(G, k);
    for (i = 1; i <= G->n; i++) {
        // �˴���һ���������ȣ�����ȷ����������ȣ�����ǰ�˳����������н��
        if (!visited[i]) DFSAL(G, i);
    }
}

//������ȱ�������
void DFSAL(ALGraph* G, int i) {
    EdgeNode* p;
    printf("���ʶ���:V%c\n", G->adjlist[i].vertex);
    visited[i] = 1;
    p = G->adjlist[i].firstedge;
    while (p) {
        if (!visited[p->adjvex]) DFSAL(G, p->adjvex);
        p = p->next;
    }
}

//������ȱ�����װ����
void BFSTraverseAL(ALGraph* G) {
    int i, k;
    printf("������ȱ���\n");
    for (i = 1; i <= G->n; i++) visited[i] = 0;
    printf("����������ĳ�ʼ����ĵ�ַ�±꣨1-n):");
    scanf("%d", &k);
    BFSAL1(G, k);
    for (i = 1; i <= G->n; i++)
        if (!visited[i]) BFSAL1(G, i);
}

//������ȱ�������
void BFSAL1(ALGraph* G, int i)
{
    int k;

    CirQueue q;
    InitQueue(&q);
    EdgeNode* p;
    printf("���ʶ���:V%c\n", G->adjlist[i].vertex);
    visited[i] = 1;
    EnQueue(&q, i);
    while (!QueueEmpty(&q))
        k = DeQueue(&q);
    p = G->adjlist[k].firstedge;
    while (p) {
        if (!visited[p->adjvex])
        {
            printf("���ʶ���:V%c\n", G->adjlist[p->adjvex].vertex);
            visited[p->adjvex] = 1;
            EnQueue(&q, p->adjvex);
        }
        p = p->next;
    }
}
