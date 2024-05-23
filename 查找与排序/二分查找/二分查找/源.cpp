#define _CRT_SECURE_NO_WARNINGS

//二分查找

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define ListSize 101

using namespace std;

//查找表的存储结构
typedef struct List
{
	int* data;
	int length;
	int listsize;
} sql;

//索引表的存储结构
typedef struct
{
	int key; //关键字
	int start;//块的起始地址
	int len;//块的元素个数
}IDX;

//菜单函数
void MenuList()
{
	printf("\n\n\n");
	printf("******************************************************\n");
	printf("****************       顺序查找算法        ***********\n");
	printf("**************** 1  -------二分查找        ***********\n");
	printf("**************** 0  -------结束运行        ***********\n");
	printf("******************************************************\n");
}

//链表的存储结构
typedef struct LNode
{
	int  data;
	struct LNode* next;
}LNode, * LinkList;

LNode* Lc;

//初始化链表，生成头结点
void initList()
{
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	p->next = NULL;
	Lc = p;
}

//生成顺序查找表
void initli(List* La, List* Lb, int j)
{
	int e;
	LinkList q;
	La->data = (int*)malloc(ListSize * sizeof(int));//分配La的存储空间
	Lb->data = (int*)malloc(ListSize * sizeof(int));//分配Lb的存储空间
	int* p = La->data;
	int* r = Lb->data;
	int i = 1;
	initList();//初始化Lc
	srand((unsigned int)(time(NULL)));
	for (i = 1; i <= j; i++)
	{
		//srand(655+i);
		e = rand() % 99 + 1;//产生随机整数，并将其作为关键字存储到查找表中
		*(p + i) = e;
		*(r + i) = e;
		q = (LinkList)malloc(sizeof(LNode));//将关键字值采用头插入法插入到链表中
		q->data = e;
		q->next = Lc->next;
		Lc->next = q;
	}
	La->length = j;//设置La中的元素个数
	Lb->length = j;//设置Lb中的元素个数  
}

//输出查找表中的关键字值
void prtL(List* La)
{
	for (int i = 1; i <= La->length; i++)
	{
		printf("%d  ", La->data[i]);
	}
	printf("\n");
}

//对查找表排序，形成有序表
void bubbleSort(List* L)
{
	int i, j, num, change;
	for (i = 1; i <= L->length; i++)
	{
		num = i;
		for (j = i + 1; j <= L->length; j++)
		{
			if (L->data[j] < L->data[num])
				num = j;
		}
		change = L->data[i];
		L->data[i] = L->data[num];
		L->data[num] = change;
	}
}

//折半查找法查找元素，传入顺序表和要查找的元素m
int  find_Two(List* L, int m)
{
	int k = 0;
	int low = 1;
	int high = L->length;
	int mid = (low + high) / 2;
	while (low <= high) {
		k++;//记录比较次数
		if (L->data[mid] == m)
		{
			printf("查找成功！该元素所在位置为：%d\n", mid);
			break;
		}
		else if (L->data[mid] > m)
		{
			high = mid - 1;
			mid = (low + high) / 2;
		}
		else
		{
			low = mid + 1;
			mid = (low + high) / 2;
		}
	}
	if (low > high)
	{
		printf("查找不成功！\n");
		k = 0;
	}
	return k;//返回记录比较次数，如果查找失败，返回0
}

int main()
{
	List La, Lb;
	float  asl;
	int i = 100, j = 0, r, key, b;
	IDX idx[10];
	int a[10], num[3], sum[3];
	MenuList();

	//生成查找表
	printf("即将生成查找表\n");     //生成表La
	printf("请您输入顺序表的长度：");
	scanf("%d", &j);
	initli(&La, &Lb, j);            //打印表La
	printf("顺序查找表为：");
	prtL(&La);

	while (i != 0)
	{
		printf("请输入选择(输入1二分查找元素；输入0退出程序):");

		scanf("%d", &i);

		if (i != 1 && i != 0)
		{
			cout << "输入错误，即将退出程序！" << endl;
			exit(0);
		}

		//折半查找
		if (i == 1)
		{
			printf("****折半查找法查找元素***\n");
			printf("递增的有序表为：\n");
			bubbleSort(&Lb); //生成递增的有序表          	 
			prtL(&Lb);//输出有序表中的元素
			printf("请输入要查找的元素（整数）：");
			scanf("%d", &key);
			r = find_Two(&Lb, key);
			if (r >= 1)
				printf("比较了：%d 次\n", r);
			else
				printf("该元素不在索引表中\n");
		}
	}

	return 0;
}