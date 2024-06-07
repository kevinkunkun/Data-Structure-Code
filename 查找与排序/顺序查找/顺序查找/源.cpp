#define _CRT_SECURE_NO_WARNINGS

//5-1 ˳�����
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define ListSize 101

using namespace std;

//���ұ�Ĵ洢�ṹ
typedef struct List
{
	int* data;
	int length;
	int listsize;
} sql;

//������Ĵ洢�ṹ
typedef struct
{
	int key; //�ؼ���
	int start;//�����ʼ��ַ
	int len;//���Ԫ�ظ���
}IDX;

//�˵�����
void MenuList()
{
	printf("\n\n\n");
	printf("******************************************************\n");
	printf("****************       ˳������㷨        ***********\n");
	printf("**************** 1  -------˳�����        ***********\n");
	printf("**************** 0  -------��������        ***********\n");
	printf("******************************************************\n");
}

//����Ĵ洢�ṹ
typedef struct LNode
{
	int  data;
	struct LNode* next;
}LNode, * LinkList;

LNode* Lc;

//��ʼ����������ͷ���
void initList()
{
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	p->next = NULL;
	Lc = p;
}

//����˳����ұ�
void initli(List* La, List* Lb, int j)
{
	int e;
	LinkList q;
	La->data = (int*)malloc(ListSize * sizeof(int));//����La�Ĵ洢�ռ�
	Lb->data = (int*)malloc(ListSize * sizeof(int));//����Lb�Ĵ洢�ռ�
	int* p = La->data;
	int* r = Lb->data;
	int i = 1;
	initList();//��ʼ��Lc
	srand((unsigned int)(time(NULL)));
	for (i = 1; i <= j; i++)
	{
		//srand(655+i);
		e = rand() % 99 + 1;//���������������������Ϊ�ؼ��ִ洢�����ұ���
		*(p + i) = e;
		*(r + i) = e;
		q = (LinkList)malloc(sizeof(LNode));//���ؼ���ֵ����ͷ���뷨���뵽������
		q->data = e;
		q->next = Lc->next;
		Lc->next = q;
	}
	La->length = j;//����La�е�Ԫ�ظ���
	Lb->length = j;//����Lb�е�Ԫ�ظ���  
}

//������ұ��еĹؼ���ֵ
void prtL(List* La)
{
	for (int i = 1; i <= La->length; i++)
	{
		printf("%d  ", La->data[i]);
	}
	printf("\n");
}

//˳����ҷ�����Ԫ��,����˳����Ҫ���ҵ�Ԫ��key
int Listfind(List* L, int key)
{
	int i = L->length, j = 0, k = 0;
	int* p, * q;
	q = L->data;
	*q = key;
	for (p = q + L->length; *p != key; p--, i--);
	if (i != 0)
	{
		printf("������Ԫ�ش��ڣ���洢λ��Ϊ��%d\n", i);
		return L->length - i + 1;  //���رȽϴ���	
	}
	else
	{
		printf("��Ԫ�ز��ڴ�˳�����\n");
		return 0;//����ʧ�ܷ���0
	}
}

int main()
{
	List La, Lb;
	float  asl;
	int i = 100, j = 0, r, key, b;
	IDX idx[10];
	int a[10], num[3], sum[3];
	MenuList();

	//���ɲ��ұ�
	printf("�������ɲ��ұ�\n");     //���ɱ�La
	printf("��������˳���ĳ��ȣ�");
	scanf("%d", &j);
	initli(&La, &Lb, j);            //��ӡ��La
	printf("˳����ұ�Ϊ��");
	prtL(&La);

	while (i != 0)
	{
		printf("������ѡ��(����1˳�����Ԫ�أ�����0�˳�����):");

		scanf("%d", &i);

		if (i != 1 && i != 0)
		{
			cout << "������󣬼����˳�����" << endl;
			exit(0);
		}

		if (i == 1) //˳�����
		{
			printf("****˳����ҷ�����Ԫ��***\n");
			printf("����������Ҫ���ҵĹؼ��֣�������:");
			scanf("%d", &key);
			r = Listfind(&La, key);
			if (r != 0)
				printf("���Ƚ��ˣ�%d ��\n", r);
			else
				printf("��Ԫ�ز��ڴ�˳�����\n");
		}
	}

	return 0;
}
