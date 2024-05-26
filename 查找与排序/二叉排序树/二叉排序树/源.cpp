#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef struct tnode
{
    int data;
    struct tnode* lchild, * rchild;
}TNODE;
void inOrder(TNODE* ptr);  //中序遍历
TNODE* root = NULL;//所创建的二叉排序树，全局变量
int fx = 0;
//中序遍历二叉排序树，得到一个有序序列
void inOrder(TNODE* ptr)
{
    if (ptr != NULL)
    {
        inOrder(ptr->lchild);//中序遍历左子树
        printf("%d ", ptr->data);//输出结点值
        inOrder(ptr->rchild);//中序遍历右左子树
    }
}
//在二叉排序树中插入一个新结点
void insert(int m)
{
    TNODE* p1, * p2;
    if (root == NULL) //二叉排序树为空时，插入结点点为根结点
    {
        root = (TNODE*)malloc(sizeof(TNODE));
        root->data = m;
        root->lchild = root->rchild = NULL;
    }
    else
    {
        p1 = root;
        while (m != p1->data)
        {
            if ((m < p1->data) && (p1->lchild != NULL))
                p1 = p1->lchild; //往二叉排序树左子树方向走
            else if ((m > p1->data) && (p1->rchild != NULL))
                p1 = p1->rchild; //往二叉排序树右子树方向走
            else if ((m < p1->data) && (p1->lchild == NULL))
            {//当前结点左子树为空，插入结点为当前结点的左孩子
                p2 = (TNODE*)malloc(sizeof(TNODE));
                p2->data = m;
                p2->lchild = p2->rchild = NULL;
                p1->lchild = p2;
                return;
            }
            else if ((m > p1->data) && (p1->rchild == NULL))
            {//当前结点右子树为空，插入结点为当前结点的右孩子
                p2 = (TNODE*)malloc(sizeof(TNODE));
                p2->data = m;
                p2->lchild = p2->rchild = NULL;
                p1->rchild = p2;
                return;
            }
        }
    }
}
void create()//创建二叉排序
{
    int n, i;
    int k;
    printf("请输入二叉排序树中的关键字个数:\n");
    scanf("%d", &n);
    printf("请依次输入二叉排序树中的关键字:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &k);//输入二叉排序树中的关键字
        insert(k);
    }
}
//静态查找二叉排序，查找是否存在值为m的元素
int  search(int m)
{
    TNODE* p1;
    if (root == NULL)
    {
        printf("该二叉排序树为空树，查找不成功。\n");
        return 0;
    }
    else
    {
        p1 = root;
        while (m != p1->data)
        {
            if ((m < p1->data) && (p1->lchild != NULL))
                p1 = p1->lchild;
            else if ((m > p1->data) && (p1->rchild != NULL))
                p1 = p1->rchild;
            else
                //if(((m<p1->data) && (p1->lchild==NULL)) 
 //||((m>p1->data) && (p1->rchild==NULL))
            {
                printf("查找不成功。\n");
                return 0;
            }
        }
    }
    printf("查找成功\n");
    return 1;
}
//求小于a的最大元素和大于a的最小元素
void findMax(int a, TNODE* p)
{
    if (p != NULL)
    {
        findMax(a, p->lchild);
        if (fx < a && p->data >= a)       //找到小于a的最大元素
            printf("小于%d的最大元素=%d\n", a, fx);
        if (fx <= a && p->data > a)       //找到大于a的最小元素
            printf("大于%d的最小元素=%d\n", a, p->data);
        fx = p->data;
        findMax(a, p->rchild);
    }
}
//删除结点函数
int deleteNode(TNODE** b)
{
    TNODE* p, * s;
    if ((*b)->lchild == NULL)
    {  //被删除结点的左子树为空
        p = (*b);
        (*b) = (*b)->rchild;
        free(p);
    }
    else if ((*b)->rchild == NULL) {//被删除结点的右子树为空
        p = (*b);
        (*b) = (*b)->lchild;
        free(p);
    }
    else {  //被删除结点的左、右子树均不为空
        p = (*b);
        s = (*b)->lchild;
        while (s->rchild != NULL) {
            p = s;
            s = s->rchild;
        }
        (*b)->data = s->data;
        if (p != (*b))
            p->rchild = s->lchild;
        else
            p->lchild = s->lchild;
        free(s);
        return 1;
    }
}
//在二叉排序树中删除值为key的关键字值
int deleteK(TNODE** b, int key)
{
    if (!*b)
        return 0;
    else {
        if ((*b)->data == key) { //结点值等key，则调用删除结点函数
            return deleteNode(&(*b));
        }
        else if ((*b)->data > key)
            return deleteK(&(*b)->lchild, key);
        else
            return deleteK(&(*b)->rchild, key);
    }
}
//菜单函数
void MenuList()
{
    printf("\n\n\n****************************************************\n");
    printf("****************        二叉排序树      ************\n");
    printf("**** 1  ------生成二叉排序树                    ****\n");
    printf("**** 2  ------中序遍历二叉排序树                ****\n");
    printf("**** 3  ------查找值为X的元素（静态查找）       ****\n");
    printf("**** 4  ------查找值为X的元素，不存在则插入     ****\n");
    printf("**** 5  ------求小于x的最大元素和大于x的最小元素****\n");
    printf("**** 6  ------查找值为X的元素，找到则删除       ****\n");
    printf("**** 0  ------结束运行                          ****\n");
    printf("****************************************************\n");
}

void  main()
{
    int i = 100, key, j;
    MenuList();
    while (i != 0)
    {
        printf("请输入选择:");
        scanf("%d", &i);
        if (i == 1) { //生成查找表
            root = NULL;
            create();
            printf("\n");
        }
        if (i == 2) { //生成查找表
            printf("中序遍历序列为:");
            inOrder(root);
            printf("\n");
        }
        if (i == 3) {
            printf("请输入要查找的关键字值:");
            scanf("%d", &key);
            search(key);
        }
        if (i == 4) {
            printf("请输入要查找（插入）的关键字值:");
            scanf("%d", &key);
            j = search(key);
            if (j == 1)  printf("\n");
            else
            {
                insert(key);
                printf("已经将关键字：%d  插入到二叉排序树中\n", key);
            }
        }
        if (i == 5) {
            printf(" 求小于x的最大元素和大于x的最小元素\n");
            printf("请输入关键字值:");
            scanf("%d", &key);
            findMax(key, root);
        }
        if (i == 6) {
            printf(" 输入要删除的关键字值：");
            scanf("%d", &key);
            printf("\n");
            j = search(key);
            if (j == 0)
                printf("二叉排序树中不存在被删除元素: %d \n", key);
            else
            {
                deleteK(&root, key);
                printf("删除成功 \n", key);
            }
        }
    }
    return;
}
