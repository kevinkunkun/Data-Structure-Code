#define _CRT_SECURE_NO_WARNINGS
//2-2�������������
#include<stdio.h>
#include<stdlib.h>
#include <malloc.h> 

typedef int ElemType;//˳���Ԫ�����ͳ�ʼ��Ϊ����

//�������ݽṹ
typedef struct node
{
	ElemType data;
	struct node* next;
}LNode, slink, * Linklist;//�ṹ�嶨��һ���ڵ����������ָ����

//β�巨����������
LNode* creatslink(int n)
{
	LNode* head, * p, * r;//��ʼ��ָ��
	int i;//��ʼ������
	if (n < 1) return NULL;//�ڵ���С��1����NULL
	r = head = (LNode*)malloc(sizeof(LNode));  //����һ���µĿռ䲢�����ͷ���
	for (i = 1; i <= n; i++)
	{
		p = (LNode*)malloc(sizeof(LNode));//�����¿ռ䲢�����ѭ���е�ÿһ���½ڵ�
		scanf("%d", &p->data);//¼��ڵ������
		r->next = p;//��ͷ�ڵ�ָ���µĽڵ�      
		r = p;//��ָ��rָ��p��������һ��ѭ���ļ���β��
	}
	r->next = NULL;   //����β��㣬��β�ڵ�ָ��NULL
	return(head);//����ͷ�ڵ㣬��������ı���
}

//����Ϊ��ʱ�����δ�ӡ�����еĽ��
void print(Linklist L)
{
	LNode* head;
	head = L->next;//��ͷָ��ָ��L�еĵ�һ��Ԫ��
	if (head == NULL)//���ͷ�ڵ�ָ��NULL˵������Ϊ��
	{
		printf("����Ϊ��!");//���������Ϣ
		return;
	}
	while (head != NULL)//��������ֱ�����һ��Ԫ��
	{
		printf("%4d", head->data);//��ӡÿһ���ڵ������
		head = head->next;//ÿ��ӡһ���ڵ����ָ��ָ����һ���ڵ�
	}
	printf("\n");
}

//��������ĳ���
int length(slink* L) {
	int num = 0;
	LNode* p;
	p = L->next;//��ָ��pָ��L�еĵ�һ��Ԫ��
	while (p)//�������д���Ԫ����ִ��
	{
		num++;//ÿ����һ���ڵ�num��һ
		p = p->next;//ÿ����һ���ڵ����pָ����һ���ڵ�
	}
	return num;//���ؽڵ����
}

//ɾ��������ָ��Ϊλ�õĽڵ�
int  del(slink* head, int  i, ElemType* e)
{//ɾ���������е�i�����
	slink* p, * q;//��ʼ��ָ��
	int j;//��ʼ������
	//�ж�ɾ��λ���Ƿ���ȷ
	if (i<1 || i>length(head))//��ָ��λ��С��1���ߴ��������ܳ���ʱ
	{
		printf("û��������\n");//���������Ϣ
		return 0;
	}
	p = head; j = 0;//��ʼ��ָ��p�����j
	while (p->next && j < i - 1)
	{
		p = p->next;
		j++;
	} //Ѱ�ҵ�i-1���
	if (p->next == NULL || j > i - 1)
		return 0;//��i>n��i<1ʱ��ɾ��λ�ò�����
	q = p->next;//qָ��ɾ�����
	p->next = q->next;//��pָ����һ���ڵ�ָ��Ľڵ�
	*e = q->data;//��e���汻ɾ������ֵ
	free(q);//�ͷ�qָ��ָ��Ľڵ���Դ
	return 1;//����1��ʾɾ���ɹ�
}

//Ѱ�Ҹ���ֵ�Ľ��
LNode* locate(LNode* head, ElemType x)
{
	LNode* p;//��ʼ��ָ��p
	p = head->next;    //��pָ���һ�����
	while (p && p->data != x)//�������д���Ԫ���������е�Ԫ��ֵ����Ѱ��ֵʱִ��
		p = p->next;//��pָ����һ��Ԫ��
	if (p == NULL)  //�ҵ����һ������ָ����Ϊ�� 
		return 0;//Ѱ��ʧ���򷵻�0��ʾδ�ҵ�x
	return p;//Ѱ�ҳɹ��򷵻ش�λ���������е�λ��
}

//Ѱ�Ҹ���ֵΪx�Ľ���λ�ã�����ָ��x�Ľ���ǰһ������ָ��q
LNode* locate1(LNode* head, ElemType x)
{
	LNode* p, * q;//��ʼ��ָ��p��q
	p = head->next;//��pָ�������еĵ�һ��Ԫ��
	q = head;//��qָ��p��ǰһ��Ԫ��
	while (p && p->data != x)//�������д���Ԫ�ز���Ԫ��ֵ��Ϊxʱִ��
	{
		//��q��pͬʱ����ƶ�
		q = q->next;
		p = p->next;
	}

	if (p == NULL)//���pָ��NULL
		return 0;//����0˵��Ѱ��ʧ��
	else return q;//���򷵻�qָ���λ��
}

//ɾ������ֵΪk�Ľ��
int del1(LNode* L, int k) {

	LNode* c, * b;//��ʼ��ָ��c��b
	c = locate1(L, k);//Ѱ��k�ڵ��ǰһ���ڵ㣬������λ�ø���c
	if (c == 0)//���û�ҵ��Ĵ�����
	{
		printf("������ֵΪ%d�Ľ��\n", k);//���������Ϣ
		return 0;//����0˵��ɾ��ʧ��
	}
	else
	{
		b = c->next; //ָ��ɾ���Ľ��
		c->next = b->next;//ɾ���ڵ�k
		free(b);//�ͷ�ָ��b����Դ
		return 1;//����1˵��ɾ���ɹ�
	}
}

//�ڵ�i�����֮ǰ����ֵΪx���½��
int  insert(LNode* head, int  i, ElemType  x)
{
	LNode* p, * q;//��ʼ��ָ��p��q
	int j = 0;//��ʼ������j
	if (i < 1) return 0;//����Ԫ��λ��С��1ʱ������0��˵������ʧ��
	p = head;//��pָ��ͷ�ڵ�
	while (p && j < i - 1)  //�ҵ�i-1�����
	{
		p = p->next;
		j++;
	}
	if (p == NULL)  return 0;  //iֵ������+1
	q = (LNode*)malloc(sizeof(LNode));//����һ���µĿս㲢����q
	q->data = x;//��x����q��������
	q->next = p->next;//��qָ��ԭ��pָ���Ԫ��
	p->next = q;//��pָ��q
	return  1;//����1˵������ɹ�
}

//����������ָ��Ԫ��֮ǰ���м���Ԫ��
int loca(LNode* head, ElemType x)
{
	LNode* p;//��ʼ��ָ��p
	int num = 0;//��ʼ������num
	p = head;    //��pָ���һ�����
	while (p)//�������д���Ԫ��ʱ
	{
		num++;
		p = p->next;
		if (p->data == x)
			break;//��������xԪ��ʱ������ѭ��
	}
	return num;//���ؽڵ����
}

void main() {
	LNode* a;
	int m, n, k, l, o, p, u, e;
	printf("�����봴���Ľڵ���:");
	scanf("%d", &m);
	printf("������ڵ�ֵ:");
	a = creatslink(m);
	printf("�����ĵ�����Ϊ:");
	print(a);

	printf("�����뱻ɾ���ڵ��λ��:");
shuru:
	scanf("%d", &k);
	n = del(a, k, &e);
	if (n == 0) {
		printf("��������ȷ��ɾ��λ�ã�");
		goto shuru; //����λ�ò�����ʱ��������
	}
	else
	{
		printf("ɾ����ĵ�����Ϊ:");
		print(a);
	}
	//���ҵ�һ��ֵΪu�Ľ�㲢ɾ��
	printf("�����뱻ɾ���ڵ��ֵΪ:");
shuru1:
	scanf("%d", &u);
	n = del1(a, u);
	if (n == 0)
	{
		printf("���������룺");
		goto shuru1; //����λ�ò�����ʱ��������
	}
	else
	{
		printf("ɾ����ĵ�����Ϊ:");
		print(a);
	}

	printf("���������ڵ��λ��:");
shuru2:
	scanf("%d", &l);
	if (l > length(a) + 1 || l < 1) {
		printf("����λ�ô�������������:");
		goto shuru2;
	}
	else
	{
		printf("���������ڵ��ֵ:");
		scanf("%d", &o);
		insert(a, l, o);
		printf("����֮�������ֵ:");
		print(a);
		printf("��ʱ����ĳ���Ϊ:");
		printf("%4d \n", length(a));
	}

	printf("������Ҫ��ѯ��ֵ:");
	scanf("%d", &p);
	if (locate(a, p) != 0) {
		printf("Ҫ��ѯֵ��λ��Ϊ:");
		printf("%4d \n", loca(a, p));
	}
	else { printf("����ѯ��ֵ������ \n"); }
}