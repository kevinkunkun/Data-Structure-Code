#define _CRT_SECURE_NO_WARNINGS
//3-3 进制转换
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define INITSIZE  100  

typedef int ElemType;

typedef struct
{
	int  top;
	ElemType* base;
	int  stacksize;
}sqstack;//用一个结构体定义一个栈的栈顶、指针域及栈的大小

//栈的初始化 
void initstack(sqstack* S)     
{
	S->base = (ElemType*)malloc(INITSIZE * sizeof(ElemType));//开辟一个新的空间并赋给栈S
	if (!S->base) 
		exit(-1);//如果开辟空间失败，退出程序
	S->top = 0;//将0压入栈顶
	S->stacksize = INITSIZE;//将栈的大小设置为100
}

//新元素进栈
void  push(sqstack* S, ElemType x) 
{
	if (S->top == S->stacksize)//如果栈顶的大小未超过站的总大小
	{
		S->base = (ElemType*)realloc(S->base,(S->stacksize + 1) * sizeof(ElemType));//让栈S的空间加一
		if (!S->base)
			exit(-1);//如果增加空间失败，退出程序
		S->stacksize++;//让栈的大小加一
	}
	S->base[S->top++] = x; //将x压入栈顶
}

//元素出栈
int  pop(sqstack* S) 
{
	int j;//初始化变量
	if (S->top == 0)//如果栈顶没有元素
	{
		printf("Stack is empty");//输出错误信息
		return 0;//返回0说明弹出元素失败
	}
	j = S->base[--S->top];//将栈顶元素存储在j中，并弹出栈顶元素
	return j; //返回已弹出的元素j
}

void main() {
	sqstack L;
	initstack(&L);
	int n, m, k = 0, a[100];
	printf("请输入一个十进制整数:");
	scanf("%d", &n);//录入信息
	printf("请输入要转化的进制:");
	scanf("%d", &m);//录入信息

	while (n != 0)//当输入的整数不为0时执行
	{
		push(&L, n % m);//将n mod m的值压入栈中
		n = n / m;//让n整除m
		k++;//位数加一
	}

	for (int j = 0; j < k; j++) a[j] = pop(&L);//按照位数依次弹出栈中的元素

	printf("转化的%d进制数为:", m);

	//16进制的特殊输出形式
	if (m == 16) {//如果是16进制则进行如下转换
		for (int l = 0; l < k; l++) {
			if (a[l] == 10) { printf("A"); }
			else if (a[l] == 11) { printf("B"); }
			else if (a[l] == 12) { printf("C"); }
			else if (a[l] == 13) { printf("D"); }
			else if (a[l] == 14) { printf("E"); }
			else if (a[l] == 15) { printf("F"); }
			else { printf("%d", a[l]); }
		}
	}

	//其他进制的输出方式
	else 
	{
		for (int j = 0; j < k; j++) {
			printf("%d ", a[j]);
		}
	}
	printf("\n");
}