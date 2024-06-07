#define _CRT_SECURE_NO_WARNINGS
//2-3 ˳���ĺϲ�
#include <stdio.h>
#include <stdlib.h>


typedef  int ElemType;  //˳�����Ԫ�ص�����
#define INITSIZE   100  //˳���洢�ռ��ʼ������
#define LISTINCREMENT  10   //���Ա�洢�ռ�ķ�������

typedef  struct
{
	ElemType* data;    //�洢�ռ�Ļ���ַ
	int  length;             //���Ա�ĵ�ǰ����                                                      
	int  listsize;            //��ǰ����Ĵ洢����
}sqlist;

//���Ԫ��
void list(sqlist* L)
{
	int j;
	printf("˳����е�Ԫ��Ϊ��");
	for (j = 0; j < L->length; j++)
		printf("%d ", L->data[j]);//��ӡ�����е�����ֵ
	printf("\n");

}

//����Ԫ��
void inputlist(sqlist* L, ElemType n)
{
	ElemType* newbase, k, a;
	L->length = n;//����˳���ĳ���Ϊn

	if (L->length == L->listsize || L->length > L->listsize)//�������ڴ���ڵ��������ڴ�ʱִ��
	{ //�ռ䲻��,�����Ӵ洢�ռ�
		newbase = (ElemType*)realloc(L->data,
			(L->listsize + LISTINCREMENT) * sizeof(ElemType));//����һ���µĿռ�
		if (!newbase)  exit(0);//���newbase����0��˵������ռ�ʧ�ܣ��˳�����
		L->data = newbase;  //  �����µĵ�ַ�ռ�����L
		L->listsize += LISTINCREMENT;//���������ݵĿռ䣬��ֹ���
	} // ���Ӵ洢����
	if (L->length > L->listsize) { printf("�޷�����"); exit(1); }//����ڴ滹�ǲ����������������ڴ棬�˳�����
	else
	{
		printf("������%d���ݼ�������:\n", n);
		for (k = 0; k < n; k++)
		{
			scanf("%d", &a);
			L->data[k] = a;//���ν������������������
		}
	}

}

//��ʼ�����Ա�
int initlist(sqlist* L)
{
	L->data = (ElemType*)malloc(INITSIZE * sizeof(ElemType));//�����Ա����ռ�
	if (L->data == NULL)
	{
		return 0; printf("����ʧ��");
	}        //������ռ䲻�ɹ�������0
	L->length = 0;//��ʼ���Ա���Ϊ0
	L->listsize = INITSIZE;//��ʼ���Ա������Ϊ��ʼ��
	return 1;//��ʼ���ɹ��򷵻�1
}

//�������Ա�
void destroylist(sqlist* L)
{
	if (L->data)
		free(L->data);
	//�ͷ����Ա�ռ�ݵ����д洢�ռ�
}


int MergeList_Sq(sqlist* La, sqlist* Lb, sqlist* Lc)
{
	// ��֪˳�����Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С�
	// �鲢La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����С�
	ElemType i, j, k;//��ʼ������
	i = j = k = 0;//����������ֵ
	Lc->listsize = Lc->length = La->length + Lb->length; //��ΪҪ��La��Lb����Lc�У�����Lc�ĳ�����La��Lb֮��
	Lc->data = (ElemType*)malloc(Lc->listsize * sizeof(ElemType));//����pc�ĵ�ַ�ռ�ΪLc�ĳ��ȴ�С
	if (!Lc->data)
	{
		printf("˳���C�ڴ����ʧ�ܣ�");   // �洢����ʧ��
		return 0;
	}

	while (i < La->length && j < Lb->length)   // ��La��Lb�ж���ֵ��ʱ��������²���
		if (La->data[i] >= Lb->data[j])//��ͷ��ʼ�Ƚ�La��Lb��Ӧλ��Ԫ�ص�ֵ
			Lc->data[k++] = La->data[i++];//���La����La��ֵ����Lc��
		else  Lc->data[k++] = Lb->data[j++];//���Lb����Lb��ֵ����Lc��

	//��ΪLa��Lb��һ���ǵȳ���
	while (i < La->length)  Lc->data[k++] = La->data[i++];// ���La�л�����ֵ����ôLb��һ��������ֵ������La��ʣ���ֵһ���Ǳ�Lc�е���Сֵ��С�����԰�ԭ�����������La��ʣ��Ԫ�ؼ���
	while (j < Lb->length) Lc->data[k++] = Lb->data[j++];// ����һ��ͬ������Lb��ʣ��Ԫ��

	return 1;//�鲢�ɹ��򷵻�1
} // MergeList

//������
void main()
{
	sqlist A, B, C;//������������
	int c, c1, n, n1;//��ʼ������

	c = initlist(&A);//��ʼ��c����
	if (c == 0) printf("˳���A�ڴ����ʧ�ܣ�");//�����ʼ������0��˵���ڴ����ʧ�ܣ����ش�����Ϣ
	else
	{
		printf("������˳���A�ĳ���n:\n");
		scanf("%d", &n);//¼��˳���A����ֵ
		inputlist(&A, n);//����inputlist����Ϊ����¼��ֵ
		list(&A);//��ӡ��һ��¼���ֵ
	}

	c1 = initlist(&B);//��ʼ������c1
	if (c1 == 0) printf("˳���B�ڴ����ʧ�ܣ�");//�����ʼ������0��˵���ڴ����ʧ�ܣ����ش�����Ϣ
	else
	{
		printf("������˳���B�ĳ���n1:\n");
		scanf("%d", &n1);//¼��˳���B�ĳ���ֵ
		inputlist(&B, n1);//����inputlist����Ϊ����¼��ֵ
		list(&B);//��ӡ��һ��¼���ֵ
	}


	printf("�ϲ����Ա�A��B��C�к�");
	if (MergeList_Sq(&A, &B, &C))//���A��B��鲢�ɹ�����1
		list(&C);//��ӡ�鲢�������C
	else printf("�ϲ�ʧ��");//���˵���鲢ʧ�ܣ����������Ϣ

	destroylist(&A);//��������A
	destroylist(&B);//��������B
	destroylist(&C);//��������C

}