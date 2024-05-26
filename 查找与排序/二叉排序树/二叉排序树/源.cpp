#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef struct tnode
{
    int data;
    struct tnode* lchild, * rchild;
}TNODE;
void inOrder(TNODE* ptr);  //�������
TNODE* root = NULL;//�������Ķ�����������ȫ�ֱ���
int fx = 0;
//��������������������õ�һ����������
void inOrder(TNODE* ptr)
{
    if (ptr != NULL)
    {
        inOrder(ptr->lchild);//�������������
        printf("%d ", ptr->data);//������ֵ
        inOrder(ptr->rchild);//���������������
    }
}
//�ڶ����������в���һ���½��
void insert(int m)
{
    TNODE* p1, * p2;
    if (root == NULL) //����������Ϊ��ʱ���������Ϊ�����
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
                p1 = p1->lchild; //������������������������
            else if ((m > p1->data) && (p1->rchild != NULL))
                p1 = p1->rchild; //������������������������
            else if ((m < p1->data) && (p1->lchild == NULL))
            {//��ǰ���������Ϊ�գ�������Ϊ��ǰ��������
                p2 = (TNODE*)malloc(sizeof(TNODE));
                p2->data = m;
                p2->lchild = p2->rchild = NULL;
                p1->lchild = p2;
                return;
            }
            else if ((m > p1->data) && (p1->rchild == NULL))
            {//��ǰ���������Ϊ�գ�������Ϊ��ǰ�����Һ���
                p2 = (TNODE*)malloc(sizeof(TNODE));
                p2->data = m;
                p2->lchild = p2->rchild = NULL;
                p1->rchild = p2;
                return;
            }
        }
    }
}
void create()//������������
{
    int n, i;
    int k;
    printf("����������������еĹؼ��ָ���:\n");
    scanf("%d", &n);
    printf("��������������������еĹؼ���:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &k);//��������������еĹؼ���
        insert(k);
    }
}
//��̬���Ҷ������򣬲����Ƿ����ֵΪm��Ԫ��
int  search(int m)
{
    TNODE* p1;
    if (root == NULL)
    {
        printf("�ö���������Ϊ���������Ҳ��ɹ���\n");
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
                printf("���Ҳ��ɹ���\n");
                return 0;
            }
        }
    }
    printf("���ҳɹ�\n");
    return 1;
}
//��С��a�����Ԫ�غʹ���a����СԪ��
void findMax(int a, TNODE* p)
{
    if (p != NULL)
    {
        findMax(a, p->lchild);
        if (fx < a && p->data >= a)       //�ҵ�С��a�����Ԫ��
            printf("С��%d�����Ԫ��=%d\n", a, fx);
        if (fx <= a && p->data > a)       //�ҵ�����a����СԪ��
            printf("����%d����СԪ��=%d\n", a, p->data);
        fx = p->data;
        findMax(a, p->rchild);
    }
}
//ɾ����㺯��
int deleteNode(TNODE** b)
{
    TNODE* p, * s;
    if ((*b)->lchild == NULL)
    {  //��ɾ������������Ϊ��
        p = (*b);
        (*b) = (*b)->rchild;
        free(p);
    }
    else if ((*b)->rchild == NULL) {//��ɾ������������Ϊ��
        p = (*b);
        (*b) = (*b)->lchild;
        free(p);
    }
    else {  //��ɾ������������������Ϊ��
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
//�ڶ�����������ɾ��ֵΪkey�Ĺؼ���ֵ
int deleteK(TNODE** b, int key)
{
    if (!*b)
        return 0;
    else {
        if ((*b)->data == key) { //���ֵ��key�������ɾ����㺯��
            return deleteNode(&(*b));
        }
        else if ((*b)->data > key)
            return deleteK(&(*b)->lchild, key);
        else
            return deleteK(&(*b)->rchild, key);
    }
}
//�˵�����
void MenuList()
{
    printf("\n\n\n****************************************************\n");
    printf("****************        ����������      ************\n");
    printf("**** 1  ------���ɶ���������                    ****\n");
    printf("**** 2  ------�����������������                ****\n");
    printf("**** 3  ------����ֵΪX��Ԫ�أ���̬���ң�       ****\n");
    printf("**** 4  ------����ֵΪX��Ԫ�أ������������     ****\n");
    printf("**** 5  ------��С��x�����Ԫ�غʹ���x����СԪ��****\n");
    printf("**** 6  ------����ֵΪX��Ԫ�أ��ҵ���ɾ��       ****\n");
    printf("**** 0  ------��������                          ****\n");
    printf("****************************************************\n");
}

void  main()
{
    int i = 100, key, j;
    MenuList();
    while (i != 0)
    {
        printf("������ѡ��:");
        scanf("%d", &i);
        if (i == 1) { //���ɲ��ұ�
            root = NULL;
            create();
            printf("\n");
        }
        if (i == 2) { //���ɲ��ұ�
            printf("�����������Ϊ:");
            inOrder(root);
            printf("\n");
        }
        if (i == 3) {
            printf("������Ҫ���ҵĹؼ���ֵ:");
            scanf("%d", &key);
            search(key);
        }
        if (i == 4) {
            printf("������Ҫ���ң����룩�Ĺؼ���ֵ:");
            scanf("%d", &key);
            j = search(key);
            if (j == 1)  printf("\n");
            else
            {
                insert(key);
                printf("�Ѿ����ؼ��֣�%d  ���뵽������������\n", key);
            }
        }
        if (i == 5) {
            printf(" ��С��x�����Ԫ�غʹ���x����СԪ��\n");
            printf("������ؼ���ֵ:");
            scanf("%d", &key);
            findMax(key, root);
        }
        if (i == 6) {
            printf(" ����Ҫɾ���Ĺؼ���ֵ��");
            scanf("%d", &key);
            printf("\n");
            j = search(key);
            if (j == 0)
                printf("�����������в����ڱ�ɾ��Ԫ��: %d \n", key);
            else
            {
                deleteK(&root, key);
                printf("ɾ���ɹ� \n", key);
            }
        }
    }
    return;
}
