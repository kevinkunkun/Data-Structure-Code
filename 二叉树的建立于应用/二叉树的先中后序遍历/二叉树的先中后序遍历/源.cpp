#define _CRT_SECURE_NO_WARNINGS
//3-1 二叉树的先、中、后序遍历
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef char TElemType;

//用结构体定义递归方法需要的树的结构
typedef struct BiTNode
{
    TElemType data;
    BiTNode* lchild, * rchild;//左右孩子指针
}BiTNode, * BiTree;

//用结构体定义非递归方法需要的栈的结构
typedef struct {
    struct BiNode* base[100];
    int top;
}Sstack;

//初始化树，构造出一个空的二叉树T
void InitBiTree(BiTree* T)
{   
    *T = NULL;
}

//按先序次序输入二叉树中结点的值（可为字符型或整型）
//构造二叉链表表示的二叉树T，字符'#'表示空（子）树
void CreateBiTree(BiTree* T)
{ 
    TElemType ch;
    scanf("%c", &ch);
    if (ch == '#')//空
        *T = NULL;
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));//生成根结点
        if (!T)  exit(-1);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);//递归构造左子树
        CreateBiTree(&(*T)->rchild);//递归构造右子树
    }
}

// 层次遍历算法（队列） 
void LevelOrderTraverse(BiTNode* b)
{    
    BiTNode* Q[100], * p;
    int  rear = 0, front = 0;//定义队头与队尾
    if (b != NULL)
    {
        Q[rear] = b;
        rear = (rear + 1) % 100;
        while (front != rear)//当队头不等于队尾时执行
        {
            p = Q[front];
            printf("%c ", p->data);
            front = (front + 1) % 100;
            if (p->lchild)
            {
                Q[rear] = p->lchild;
                rear = (rear + 1) % 100;
            }
            if (p->rchild)
            {
                Q[rear] = p->rchild;
                rear = (rear + 1) % 100;
            }
        }
    }
}

//初始条件：二叉树T存在，Visit是对结点操作的应用函数
//操作结果：先序递归遍历T，对每个结点调用函数Visit一次且仅一次
void PreOrderTraverse(BiTree T, void(*Visit)(TElemType))
{
    if (T)//T不空
    {
        Visit(T->data);//先访问根结点
        PreOrderTraverse(T->lchild, Visit);//递归处理左子树
        PreOrderTraverse(T->rchild, Visit);//递归处理右子树
    }
}

//初始条件：二叉树T存在，Visit是对结点操作的应用函数
//操作结果：中序遍历T，对每个结点调用函数Visit一次且仅一次
void InOrderTraverse(BiTree T, void(*Visit)(TElemType))
{   
    if (T)
    {
        InOrderTraverse(T->lchild, Visit);//先中序遍历左子树
        Visit(T->data);//再访问根结点
        InOrderTraverse(T->rchild, Visit);//最后中序遍历右子树
    }
}

//初始条件：二叉树T存在，Visit是对结点操作的应用函数
//操作结果：后序递归遍历T，对每个结点调用函数Visit一次且仅一次
void PostOrderTraverse(BiTree T, void(*Visit)(TElemType))
{   
    if (T)//T不空
    {
        PostOrderTraverse(T->lchild, Visit);//递归处理左子树
        PostOrderTraverse(T->rchild, Visit);//递归处理右子树
        Visit(T->data);//最后访问根结点
    }
}

//非递归式先序遍历
void PreOrder(BiTNode* b)
{   
    BiTNode* stack[100], * p;
    int top = -1;
    if (b != NULL)
    {
        top++;
        stack[top] = b;
        while (top > -1)
        {
            p = stack[top];
            top--;
            printf("%c ", p->data);
            if (p->rchild != NULL)
            {
                top++;
                stack[top] = p->rchild;
            }
            if (p->lchild != NULL)
            {
                top++;
                stack[top] = p->lchild;
            }
        }
        printf("\n");
    }
}

//非递归式中序遍历
void InOrder(BiTNode* b)
{   
    BiTNode* stack[100], * p;
    int top = -1;
    if (b != NULL)
    {
        p = b;
        while (top > -1 || p != NULL)
        {
            while (p != NULL)
            {
                top++;
                stack[top] = p;
                p = p->lchild;
            }
            if (top > -1)
            {
                p = stack[top];
                top--;
                printf("%c ", p->data);
                p = p->rchild;
            }
        }
    }
    printf("\n");
}

//非递归式后序遍历
void PostOrder(BiTNode* b)
{  
    BiTNode* stack[100], * p;
    int sign, top = -1;
    if (b != NULL)
    {
        do
        {
            while (b != NULL)
            {
                top++;
                stack[top] = b;
                b = b->lchild;
            }
            p = NULL;
            sign = 1;
            while (top != -1 && sign)
            {
                b = stack[top];
                if (b->rchild == p)
                {
                    printf("%c ", b->data);
                    top--;
                    p = b;
                }
                else
                {
                    b = b->rchild;
                    sign = 0;
                }
            }
        } while (top != -1);
        printf("\n");
    }
}
//非递归式访问根节点
void visitT(TElemType e)
{
    printf("%c ", e);
}

//清除缓冲区
void safe_flush(FILE* fp)
{
    int ch;
    while ((ch = fgetc(fp)) != EOF && ch != '\n');//当ch不等于文件结束符EOF或者换行符时执行
}

//打印提示信息
void MenuList()
{
    printf("\n **************************************************\n");
    printf(" **************** 二叉树的生成和遍历实验***********\n");
    printf(" **** 1  -------生成二叉树                     ****\n");
    printf(" **** 2  -------先序遍历二叉树(含递归和非递归）****\n");
    printf(" **** 3  -------中序遍历二叉树(含递归和非递归）****\n");
    printf(" **** 4  -------后序遍历二叉树(含递归和非递归）****\n");
    printf(" **** 5  -------层次遍历                       ****\n");
    printf(" **** 0  -------结束运行                       ****\n");
    printf(" **************************************************\n");
}

//主程序
int main(void)
{
    int i = 100;
    BiTree T;//定义一棵树T
    InitBiTree(&T);//初始化树T
    MenuList();//打印提示信息
    while (i != 0)
    {
        printf(" 请输入选择:");
        scanf("%d", &i);
        if (i == 1)
        {
            safe_flush(stdin);
            printf(" 请输入二叉树的先序遍历序列，用#代表构造空树。\n");
            printf(" 例如:ab###表示只有两个结点，a为根，b为左子树的二叉树)\n");
            printf(" 构造二叉树的先序遍历序列：");
            CreateBiTree(&T);
        }
        if (i == 2)
        {
            printf(" 先序递归遍历二叉树:");
            PreOrderTraverse(T, visitT);
            printf("\n 先序非递归遍历二叉树:");
            PreOrder(T);
        }
        if (i == 3)
        {
            printf("\n 中序递归遍历二叉树:");
            InOrderTraverse(T, visitT);
            printf("\n 中序非递归遍历二叉树:");
            InOrder(T);
        }
        if (i == 4)
        {
            printf("\n 后序递归遍历二叉树:");
            PostOrderTraverse(T, visitT);
            printf("\n 后序非递归遍历二叉树:");
            PostOrder(T);
        }
        if (i == 5)
        {
            printf("\n 层次遍历二叉树:");
            LevelOrderTraverse(T);
            printf("\n");
        }
    }
    printf("\n");

    return 0;
}

