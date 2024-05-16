#define _CRT_SECURE_NO_WARNINGS
//2-1顺序表的基本操作程序
#include <stdio.h>
#include <stdlib.h>


typedef  int ElemType;  //顺序表中元素的类型
#define INITSIZE   100  //顺序表存储空间初始分配量
#define LISTINCREMENT  10   //线性表存储空间的分配增量

typedef  struct
{
	ElemType* data;    //存储空间的基地址
	int  length;       //线性表的当前长度                                                      
	int  listsize;     //当前分配的存储容量
}sqlist;

//输出元素
void list(sqlist* L)
{
	int j;
	printf("顺序表中的元素为：");
	for (j = 0; j < L->length; j++)
		printf("%d ", L->data[j]);//打印顺序表中的值
	printf("\n");

}

//初始化线性表
int initlist(sqlist* L)
{
	L->data = (ElemType*)malloc(INITSIZE * sizeof(ElemType));//为顺序表分配空间
	if (L->data == NULL)//如果顺序表中的数据为NULL
	{
		printf("分配失败");//输出错误信息
		return 0;//若分配空间不成功，返回0
	}        
	L->length = 0;//将当前线性表长度置0
	L->listsize = INITSIZE;//当前顺序表的容量为初始量
	return 1;//初始化成功则返回1
}

//销毁线性表
void destroylist(sqlist* L)
{
	if (L->data)
		free(L->data);//释放线性表占据的所有存储空间
}

//清空线性表
void clearlist(sqlist* L)
{
	L->length = 0;//将线性表的长度置为0，自然也就清空了线性表中的所有数据
}

// 求顺序表的长度
int getlen(sqlist* L)
{
	return (L->length);//返回顺序表的长度
}

//判定是否为空
int listempty(sqlist* L)
{
	if (L->length == 0)
		return 1;//如果顺序表为空则返回1
	else
		return 0;//否则返回0
}

//获取顺序表中某一点的数据
int getelem(sqlist  L, int i, ElemType* e)
{
	if (i<1 || i>L.length)//如果此点小于1或者大于顺序表的总长度
		return 0;//返回0说明查询失败
	*e = L.data[i - 1];//数组中第i-1的单元存储着线性表中第i个数据元素的内容，将其存入e中
	return 1;//查询成功则返回1
}

//在顺序表中检索第一个值为e的元素位序
int locate(sqlist* L, ElemType  e)
{
	int i;
	for (i = 0; i < (*L).length; i++)
		if ((*L).data[i] == e)
			return i + 1;//查询成功返回i+1（即元素e在顺序表中的位置）
	return 0;  //查询失败则返回0
}

//向顺序表中某一位置插入元素
int insert_sq(sqlist* L, int i, ElemType e)
{
	ElemType* newbase, j;//初始化变量
	if (i<1 || i>L->length + 1)  
		return 0;//如果插入位置不合理返回0
	if (L->length == L->listsize)//如果空间不够,需增加存储空间
	{ 
		newbase = (ElemType*)realloc(L->data,
			(L->listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) 
			exit(0);//如果空间分配失败，退出程序 
		L->data = newbase;  //将新基址分配给L
		L->listsize += LISTINCREMENT;//并将增量分配给L
	}
	for (j = L->length - 1; j >= i - 1; j--)
		//将线性表第i个元素之后的所有元素向后移动
		L->data[j + 1] = L->data[j];
	L->data[i - 1] = e;
	//将新元素的内容放入线性表的第i个位置
	L->length++;      //表长增1                
	return 1;//插入成功则返回1
}

//删除顺序表中指定位置的元素
int delete_sq(sqlist* L, int i, ElemType* e)
{
	int j;//初始化变量
	if (listempty(L))
		return 0; //检测线性表是否为空
	if (i<1 || i>L->length)
		return 0; //检查i值是否合理
	*e = L->data[i - 1]; //将欲删除的数据元素内容保留在e所指示的存储单元中
	for (j = i; j < L->length; j++)
		L->data[j - 1] = L->data[j];//将线性表第i+1个元素之后的所有元素向前移动
	L->length--;//表长减1
	return 1;//删除成功则返回1
}

//把x插入递增有序表L中
int Insert_Sqlist(sqlist* L, int x)
{
	ElemType* newbase, i;//初始化指针与变量
	if (L->length == L->listsize)//如果空间不够,需增加存储空间
	{ 
		newbase = (ElemType*)realloc(L->data,
			(L->listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) 
			exit(0);//如果空间分配失败，退出程序 
		L->data = newbase;  //将新基址分配给L
		L->listsize += LISTINCREMENT;//将空间增量分配给L
	}
	for (i = L->length - 1; L->data[i] < x && i >= 0; i--)
		L->data[i + 1] = L->data[i];//将第i个元素后面的元素依次向后移动一位
	L->data[i + 1] = x;//将x插入i元素后一位
	L->length++;//表长加一
	return 1;//插入成功则返回1
}


void main()
{
	int c, k, i, x, e, a, n;
	sqlist L;
	c = initlist(&L);
	if (c == 0)
		printf("内存分配失败！");//如果initlist函数返回0，说明内存分配失败，输出错误信息

	printf("请输入顺序表的长度n:\n");
	scanf("%d", &n);//录入信息
	L.length = n;//设置顺序表的长度为5
	//输入5个元素
	printf("请输入%d个递减的整数:\n", n);
	for (k = 0; k < n; k++)
	{
		scanf("%d", &a);
		L.data[k] = a;//依次录入顺序表的元素
	}
	list(&L);//打印顺序表

	printf("\n线性表长度=%d\n", getlen(&L));
	printf("请输入插入元素x及插入位置i:");
	scanf("%d%d", &x, &i);//录入元素
	if (!insert_sq(&L, i, x))
		printf("插入失败\n");//如果插入函数返回0，说明插入失败，输出错误信息
	else list(&L);//否则插入成功，打印顺序表

	printf("请输入删除的位置i:");
	scanf("%d", &i);//录入信息
	if (!delete_sq(&L, i, &e)) 
		printf("删除位置错误，删除失败\n");//如果删除函数返回0，说明插入失败，输出错误信息
	else list(&L);//否则删除成功，打印顺序表

	printf("请输入要查找的元素的值：");
	scanf("%d", &e);//录入信息
	c = locate(&L, e);//寻找e在顺序表中的位置
	if (c == 0)
		printf("不存在值为%d的元素\n", e);//如果locate函数返回0，说明不存在此数，输出错误信息
	else printf("值为%d的元素在第%d个位置\n", e, c);//否则输出位置

	printf("请输入要有序插入的x值:");
	scanf("%d", &x);//录入信息
	c = Insert_Sqlist(&L, x);//调用Insert_Sqlist函数寻找x元素在顺序表中的位置
	if (c == 0) 
		printf("线性表满\n");//如果Insert_Sqlist函数返回0，说明线性表已满不能插入，输出错误信息
	else list(&L);//否则打印顺序表
	destroylist(&L);//最后销毁线性表
}


