#define _CRT_SECURE_NO_WARNINGS
//2-3 顺序表的合并
#include <stdio.h>
#include <stdlib.h>


typedef  int ElemType;  //顺序表中元素的类型
#define INITSIZE   100  //顺序表存储空间初始分配量
#define LISTINCREMENT  10   //线性表存储空间的分配增量

typedef  struct
{
	ElemType* data;    //存储空间的基地址
	int  length;             //线性表的当前长度                                                      
	int  listsize;            //当前分配的存储容量
}sqlist;

//输出元素
void list(sqlist* L)
{
	int j;
	printf("顺序表中的元素为：");
	for (j = 0; j < L->length; j++)
		printf("%d ", L->data[j]);//打印链表中的所有值
	printf("\n");

}

//输入元素
void inputlist(sqlist* L, ElemType n)
{
	ElemType* newbase, k, a;
	L->length = n;//设置顺序表的长度为n

	if (L->length == L->listsize || L->length > L->listsize)//当所需内存大于等于链表内存时执行
	{ //空间不够,需增加存储空间
		newbase = (ElemType*)realloc(L->data,
			(L->listsize + LISTINCREMENT) * sizeof(ElemType));//开辟一个新的空间
		if (!newbase)  exit(0);//如果newbase返回0，说明分配空间失败，退出程序
		L->data = newbase;  //  否则将新的地址空间分配给L
		L->listsize += LISTINCREMENT;//并加上扩容的空间，防止溢出
	} // 增加存储容量
	if (L->length > L->listsize) { printf("无法分配"); exit(1); }//如果内存还是不能满足链表所需内存，退出程序
	else
	{
		printf("请输入%d个递减的整数:\n", n);
		for (k = 0; k < n; k++)
		{
			scanf("%d", &a);
			L->data[k] = a;//依次将输入的数存入链表中
		}
	}

}

//初始化线性表
int initlist(sqlist* L)
{
	L->data = (ElemType*)malloc(INITSIZE * sizeof(ElemType));//给线性表分配空间
	if (L->data == NULL)
	{
		return 0; printf("分配失败");
	}        //若分配空间不成功，返回0
	L->length = 0;//初始线性表长度为0
	L->listsize = INITSIZE;//初始线性表的容量为初始量
	return 1;//初始化成功则返回1
}

//销毁线性表
void destroylist(sqlist* L)
{
	if (L->data)
		free(L->data);
	//释放线性表占据的所有存储空间
}


int MergeList_Sq(sqlist* La, sqlist* Lb, sqlist* Lc)
{
	// 已知顺序线性表La和Lb的元素按值非递减排列。
	// 归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列。
	ElemType i, j, k;//初始化变量
	i = j = k = 0;//给变量赋初值
	Lc->listsize = Lc->length = La->length + Lb->length; //因为要将La与Lb存入Lc中，所以Lc的长度是La和Lb之和
	Lc->data = (ElemType*)malloc(Lc->listsize * sizeof(ElemType));//开辟pc的地址空间为Lc的长度大小
	if (!Lc->data)
	{
		printf("顺序表C内存分配失败！");   // 存储分配失败
		return 0;
	}

	while (i < La->length && j < Lb->length)   // 当La与Lb中都有值的时候进行以下操作
		if (La->data[i] >= Lb->data[j])//从头开始比较La与Lb对应位置元素的值
			Lc->data[k++] = La->data[i++];//如果La大则将La的值存入Lc中
		else  Lc->data[k++] = Lb->data[j++];//如果Lb大则将Lb的值存入Lc中

	//因为La与Lb不一定是等长的
	while (i < La->length)  Lc->data[k++] = La->data[i++];// 如果La中还存在值，那么Lb中一定不存在值，并且La中剩余的值一定是比Lc中的最小值更小，所以按原序列逐个插入La的剩余元素即可
	while (j < Lb->length) Lc->data[k++] = Lb->data[j++];// 跟上一行同理，插入Lb的剩余元素

	return 1;//归并成功则返回1
} // MergeList

//主程序
void main()
{
	sqlist A, B, C;//创建三个链表
	int c, c1, n, n1;//初始化变量

	c = initlist(&A);//初始化c链表
	if (c == 0) printf("顺序表A内存分配失败！");//如果初始化返回0，说明内存分配失败，返回错误信息
	else
	{
		printf("请输入顺序表A的长度n:\n");
		scanf("%d", &n);//录入顺序表A长度值
		inputlist(&A, n);//调用inputlist函数为链表录入值
		list(&A);//打印上一步录入的值
	}

	c1 = initlist(&B);//初始化量表c1
	if (c1 == 0) printf("顺序表B内存分配失败！");//如果初始化返回0，说明内存分配失败，返回错误信息
	else
	{
		printf("请输入顺序表B的长度n1:\n");
		scanf("%d", &n1);//录入顺序表B的长度值
		inputlist(&B, n1);//调用inputlist函数为链表录入值
		list(&B);//打印上一步录入的值
	}


	printf("合并线性表A与B到C中后，");
	if (MergeList_Sq(&A, &B, &C))//如果A与B表归并成功返回1
		list(&C);//打印归并后的链表C
	else printf("合并失败");//否侧说明归并失败，输出错误信息

	destroylist(&A);//销毁链表A
	destroylist(&B);//销毁链表B
	destroylist(&C);//销毁链表C

}