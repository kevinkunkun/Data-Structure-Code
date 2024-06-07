#define _CRT_SECURE_NO_WARNINGS
//2-2单链表基本操作
#include<stdio.h>
#include<stdlib.h>
#include <malloc.h> 

typedef int ElemType;//顺序表元素整型初始化为整型

//结点的数据结构
typedef struct node
{
	ElemType data;
	struct node* next;
}LNode, slink, * Linklist;//结构体定义一个节点的数据域与指针域

//尾插法建立单链表
LNode* creatslink(int n)
{
	LNode* head, * p, * r;//初始化指针
	int i;//初始化变量
	if (n < 1) return NULL;//节点数小于1返回NULL
	r = head = (LNode*)malloc(sizeof(LNode));  //开辟一个新的空间并分配给头结点
	for (i = 1; i <= n; i++)
	{
		p = (LNode*)malloc(sizeof(LNode));//开辟新空间并分配给循环中的每一个新节点
		scanf("%d", &p->data);//录入节点的数据
		r->next = p;//让头节点指向新的节点      
		r = p;//让指针r指向p，便于下一次循环的继续尾插
	}
	r->next = NULL;   //处理尾结点，让尾节点指向NULL
	return(head);//返回头节点，便于链表的遍历
}

//链表不为空时，依次打印链表中的结点
void print(Linklist L)
{
	LNode* head;
	head = L->next;//让头指针指向L中的第一个元素
	if (head == NULL)//如果头节点指向NULL说明链表为空
	{
		printf("链表为空!");//输出错误信息
		return;
	}
	while (head != NULL)//遍历链表直至最后一个元素
	{
		printf("%4d", head->data);//打印每一个节点的数据
		head = head->next;//每打印一个节点就让指针指向下一个节点
	}
	printf("\n");
}

//计算链表的长度
int length(slink* L) {
	int num = 0;
	LNode* p;
	p = L->next;//让指针p指向L中的第一个元素
	while (p)//当链表中存在元素是执行
	{
		num++;//每遍历一个节点num加一
		p = p->next;//每遍历一个节点就让p指向下一个节点
	}
	return num;//返回节点个数
}

//删除链表中指定为位置的节点
int  del(slink* head, int  i, ElemType* e)
{//删除单链表中第i个结点
	slink* p, * q;//初始化指针
	int j;//初始化变量
	//判定删除位置是否正确
	if (i<1 || i>length(head))//当指定位置小于1或者大于链表总长度时
	{
		printf("没有这个结点\n");//输出错误信息
		return 0;
	}
	p = head; j = 0;//初始化指针p与变量j
	while (p->next && j < i - 1)
	{
		p = p->next;
		j++;
	} //寻找第i-1结点
	if (p->next == NULL || j > i - 1)
		return 0;//当i>n或i<1时，删除位置不合理
	q = p->next;//q指向被删除结点
	p->next = q->next;//让p指向下一个节点指向的节点
	*e = q->data;//用e保存被删除结点的值
	free(q);//释放q指针指向的节点资源
	return 1;//返回1表示删除成功
}

//寻找给定值的结点
LNode* locate(LNode* head, ElemType x)
{
	LNode* p;//初始化指针p
	p = head->next;    //让p指向第一个结点
	while (p && p->data != x)//当链表中存在元素且链表中的元素值不是寻找值时执行
		p = p->next;//让p指向下一个元素
	if (p == NULL)  //找到最后一个结点的指针域为空 
		return 0;//寻找失败则返回0表示未找到x
	return p;//寻找成功则返回此位置在链表中的位置
}

//寻找给定值为x的结点的位置，返回指向x的结点的前一个结点的指针q
LNode* locate1(LNode* head, ElemType x)
{
	LNode* p, * q;//初始化指针p与q
	p = head->next;//让p指向链表中的第一个元素
	q = head;//让q指向p的前一个元素
	while (p && p->data != x)//当链表中存在元素并且元素值不为x时执行
	{
		//让q与p同时向后移动
		q = q->next;
		p = p->next;
	}

	if (p == NULL)//如果p指向NULL
		return 0;//返回0说明寻找失败
	else return q;//否则返回q指向的位置
}

//删除给定值为k的结点
int del1(LNode* L, int k) {

	LNode* c, * b;//初始化指针c与b
	c = locate1(L, k);//寻找k节点的前一个节点，并将其位置赋给c
	if (c == 0)//如果没找到的处理方法
	{
		printf("不存在值为%d的结点\n", k);//输出错误信息
		return 0;//返回0说明删除失败
	}
	else
	{
		b = c->next; //指向被删除的结点
		c->next = b->next;//删除节点k
		free(b);//释放指针b的资源
		return 1;//返回1说明删除成功
	}
}

//在第i个结点之前插入值为x的新结点
int  insert(LNode* head, int  i, ElemType  x)
{
	LNode* p, * q;//初始化指针p与q
	int j = 0;//初始化变量j
	if (i < 1) return 0;//插入元素位置小于1时，返回0，说明插入失败
	p = head;//令p指向头节点
	while (p && j < i - 1)  //找第i-1个结点
	{
		p = p->next;
		j++;
	}
	if (p == NULL)  return 0;  //i值超过表长+1
	q = (LNode*)malloc(sizeof(LNode));//开辟一个新的空姐并赋给q
	q->data = x;//将x存入q的数据域
	q->next = p->next;//让q指向原来p指向的元素
	p->next = q;//让p指向q
	return  1;//返回1说明插入成功
}

//计算链表中指定元素之前含有几个元素
int loca(LNode* head, ElemType x)
{
	LNode* p;//初始化指针p
	int num = 0;//初始化变量num
	p = head;    //让p指向第一个结点
	while (p)//当链表中存在元素时
	{
		num++;
		p = p->next;
		if (p->data == x)
			break;//当遍历到x元素时，结束循环
	}
	return num;//返回节点个数
}

void main() {
	LNode* a;
	int m, n, k, l, o, p, u, e;
	printf("请输入创建的节点数:");
	scanf("%d", &m);
	printf("请输入节点值:");
	a = creatslink(m);
	printf("创建的单链表为:");
	print(a);

	printf("请输入被删除节点的位置:");
shuru:
	scanf("%d", &k);
	n = del(a, k, &e);
	if (n == 0) {
		printf("请输入正确的删除位置：");
		goto shuru; //输入位置不存在时重新输入
	}
	else
	{
		printf("删除后的单链表为:");
		print(a);
	}
	//查找第一个值为u的结点并删除
	printf("请输入被删除节点的值为:");
shuru1:
	scanf("%d", &u);
	n = del1(a, u);
	if (n == 0)
	{
		printf("请重新输入：");
		goto shuru1; //输入位置不存在时重新输入
	}
	else
	{
		printf("删除后的单链表为:");
		print(a);
	}

	printf("请输入插入节点的位置:");
shuru2:
	scanf("%d", &l);
	if (l > length(a) + 1 || l < 1) {
		printf("插入位置错误，请重新输入:");
		goto shuru2;
	}
	else
	{
		printf("请输入插入节点的值:");
		scanf("%d", &o);
		insert(a, l, o);
		printf("插入之后链表的值:");
		print(a);
		printf("此时链表的长度为:");
		printf("%4d \n", length(a));
	}

	printf("请输入要查询的值:");
	scanf("%d", &p);
	if (locate(a, p) != 0) {
		printf("要查询值的位置为:");
		printf("%4d \n", loca(a, p));
	}
	else { printf("所查询的值不存在 \n"); }
}