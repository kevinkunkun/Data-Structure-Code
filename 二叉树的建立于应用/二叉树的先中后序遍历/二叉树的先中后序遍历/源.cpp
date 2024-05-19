#define _CRT_SECURE_NO_WARNINGS
//3-1 ���������ȡ��С��������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef char TElemType;

//�ýṹ�嶨��ݹ鷽����Ҫ�����Ľṹ
typedef struct BiTNode
{
    TElemType data;
    BiTNode* lchild, * rchild;//���Һ���ָ��
}BiTNode, * BiTree;

//�ýṹ�嶨��ǵݹ鷽����Ҫ��ջ�Ľṹ
typedef struct {
    struct BiNode* base[100];
    int top;
}Sstack;

//��ʼ�����������һ���յĶ�����T
void InitBiTree(BiTree* T)
{   
    *T = NULL;
}

//�������������������н���ֵ����Ϊ�ַ��ͻ����ͣ�
//������������ʾ�Ķ�����T���ַ�'#'��ʾ�գ��ӣ���
void CreateBiTree(BiTree* T)
{ 
    TElemType ch;
    scanf("%c", &ch);
    if (ch == '#')//��
        *T = NULL;
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));//���ɸ����
        if (!T)  exit(-1);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);//�ݹ鹹��������
        CreateBiTree(&(*T)->rchild);//�ݹ鹹��������
    }
}

// ��α����㷨�����У� 
void LevelOrderTraverse(BiTNode* b)
{    
    BiTNode* Q[100], * p;
    int  rear = 0, front = 0;//�����ͷ���β
    if (b != NULL)
    {
        Q[rear] = b;
        rear = (rear + 1) % 100;
        while (front != rear)//����ͷ�����ڶ�βʱִ��
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

//��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú���
//�������������ݹ����T����ÿ�������ú���Visitһ���ҽ�һ��
void PreOrderTraverse(BiTree T, void(*Visit)(TElemType))
{
    if (T)//T����
    {
        Visit(T->data);//�ȷ��ʸ����
        PreOrderTraverse(T->lchild, Visit);//�ݹ鴦��������
        PreOrderTraverse(T->rchild, Visit);//�ݹ鴦��������
    }
}

//��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú���
//����������������T����ÿ�������ú���Visitһ���ҽ�һ��
void InOrderTraverse(BiTree T, void(*Visit)(TElemType))
{   
    if (T)
    {
        InOrderTraverse(T->lchild, Visit);//���������������
        Visit(T->data);//�ٷ��ʸ����
        InOrderTraverse(T->rchild, Visit);//����������������
    }
}

//��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú���
//�������������ݹ����T����ÿ�������ú���Visitһ���ҽ�һ��
void PostOrderTraverse(BiTree T, void(*Visit)(TElemType))
{   
    if (T)//T����
    {
        PostOrderTraverse(T->lchild, Visit);//�ݹ鴦��������
        PostOrderTraverse(T->rchild, Visit);//�ݹ鴦��������
        Visit(T->data);//�����ʸ����
    }
}

//�ǵݹ�ʽ�������
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

//�ǵݹ�ʽ�������
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

//�ǵݹ�ʽ�������
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
//�ǵݹ�ʽ���ʸ��ڵ�
void visitT(TElemType e)
{
    printf("%c ", e);
}

//���������
void safe_flush(FILE* fp)
{
    int ch;
    while ((ch = fgetc(fp)) != EOF && ch != '\n');//��ch�������ļ�������EOF���߻��з�ʱִ��
}

//��ӡ��ʾ��Ϣ
void MenuList()
{
    printf("\n **************************************************\n");
    printf(" **************** �����������ɺͱ���ʵ��***********\n");
    printf(" **** 1  -------���ɶ�����                     ****\n");
    printf(" **** 2  -------�������������(���ݹ�ͷǵݹ飩****\n");
    printf(" **** 3  -------�������������(���ݹ�ͷǵݹ飩****\n");
    printf(" **** 4  -------�������������(���ݹ�ͷǵݹ飩****\n");
    printf(" **** 5  -------��α���                       ****\n");
    printf(" **** 0  -------��������                       ****\n");
    printf(" **************************************************\n");
}

//������
int main(void)
{
    int i = 100;
    BiTree T;//����һ����T
    InitBiTree(&T);//��ʼ����T
    MenuList();//��ӡ��ʾ��Ϣ
    while (i != 0)
    {
        printf(" ������ѡ��:");
        scanf("%d", &i);
        if (i == 1)
        {
            safe_flush(stdin);
            printf(" �����������������������У���#�����������\n");
            printf(" ����:ab###��ʾֻ��������㣬aΪ����bΪ�������Ķ�����)\n");
            printf(" ���������������������У�");
            CreateBiTree(&T);
        }
        if (i == 2)
        {
            printf(" ����ݹ����������:");
            PreOrderTraverse(T, visitT);
            printf("\n ����ǵݹ����������:");
            PreOrder(T);
        }
        if (i == 3)
        {
            printf("\n ����ݹ����������:");
            InOrderTraverse(T, visitT);
            printf("\n ����ǵݹ����������:");
            InOrder(T);
        }
        if (i == 4)
        {
            printf("\n ����ݹ����������:");
            PostOrderTraverse(T, visitT);
            printf("\n ����ǵݹ����������:");
            PostOrder(T);
        }
        if (i == 5)
        {
            printf("\n ��α���������:");
            LevelOrderTraverse(T);
            printf("\n");
        }
    }
    printf("\n");

    return 0;
}

