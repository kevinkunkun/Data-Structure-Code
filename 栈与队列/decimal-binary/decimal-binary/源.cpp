#define _CRT_SECURE_NO_WARNINGS
//3-3 ����ת��
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
}sqstack;//��һ���ṹ�嶨��һ��ջ��ջ����ָ����ջ�Ĵ�С

//ջ�ĳ�ʼ�� 
void initstack(sqstack* S)     
{
	S->base = (ElemType*)malloc(INITSIZE * sizeof(ElemType));//����һ���µĿռ䲢����ջS
	if (!S->base) 
		exit(-1);//������ٿռ�ʧ�ܣ��˳�����
	S->top = 0;//��0ѹ��ջ��
	S->stacksize = INITSIZE;//��ջ�Ĵ�С����Ϊ100
}

//��Ԫ�ؽ�ջ
void  push(sqstack* S, ElemType x) 
{
	if (S->top == S->stacksize)//���ջ���Ĵ�Сδ����վ���ܴ�С
	{
		S->base = (ElemType*)realloc(S->base,(S->stacksize + 1) * sizeof(ElemType));//��ջS�Ŀռ��һ
		if (!S->base)
			exit(-1);//������ӿռ�ʧ�ܣ��˳�����
		S->stacksize++;//��ջ�Ĵ�С��һ
	}
	S->base[S->top++] = x; //��xѹ��ջ��
}

//Ԫ�س�ջ
int  pop(sqstack* S) 
{
	int j;//��ʼ������
	if (S->top == 0)//���ջ��û��Ԫ��
	{
		printf("Stack is empty");//���������Ϣ
		return 0;//����0˵������Ԫ��ʧ��
	}
	j = S->base[--S->top];//��ջ��Ԫ�ش洢��j�У�������ջ��Ԫ��
	return j; //�����ѵ�����Ԫ��j
}

void main() {
	sqstack L;
	initstack(&L);
	int n, m, k = 0, a[100];
	printf("������һ��ʮ��������:");
	scanf("%d", &n);//¼����Ϣ
	printf("������Ҫת���Ľ���:");
	scanf("%d", &m);//¼����Ϣ

	while (n != 0)//�������������Ϊ0ʱִ��
	{
		push(&L, n % m);//��n mod m��ֵѹ��ջ��
		n = n / m;//��n����m
		k++;//λ����һ
	}

	for (int j = 0; j < k; j++) a[j] = pop(&L);//����λ�����ε���ջ�е�Ԫ��

	printf("ת����%d������Ϊ:", m);

	//16���Ƶ����������ʽ
	if (m == 16) {//�����16�������������ת��
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

	//�������Ƶ������ʽ
	else 
	{
		for (int j = 0; j < k; j++) {
			printf("%d ", a[j]);
		}
	}
	printf("\n");
}