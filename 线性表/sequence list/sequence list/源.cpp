#define _CRT_SECURE_NO_WARNINGS
//2-1˳���Ļ�����������
#include <stdio.h>
#include <stdlib.h>


typedef  int ElemType;  //˳�����Ԫ�ص�����
#define INITSIZE   100  //˳���洢�ռ��ʼ������
#define LISTINCREMENT  10   //���Ա�洢�ռ�ķ�������

typedef  struct
{
	ElemType* data;    //�洢�ռ�Ļ���ַ
	int  length;       //���Ա�ĵ�ǰ����                                                      
	int  listsize;     //��ǰ����Ĵ洢����
}sqlist;

//���Ԫ��
void list(sqlist* L)
{
	int j;
	printf("˳����е�Ԫ��Ϊ��");
	for (j = 0; j < L->length; j++)
		printf("%d ", L->data[j]);//��ӡ˳����е�ֵ
	printf("\n");

}

//��ʼ�����Ա�
int initlist(sqlist* L)
{
	L->data = (ElemType*)malloc(INITSIZE * sizeof(ElemType));//Ϊ˳������ռ�
	if (L->data == NULL)//���˳����е�����ΪNULL
	{
		printf("����ʧ��");//���������Ϣ
		return 0;//������ռ䲻�ɹ�������0
	}        
	L->length = 0;//����ǰ���Ա�����0
	L->listsize = INITSIZE;//��ǰ˳��������Ϊ��ʼ��
	return 1;//��ʼ���ɹ��򷵻�1
}

//�������Ա�
void destroylist(sqlist* L)
{
	if (L->data)
		free(L->data);//�ͷ����Ա�ռ�ݵ����д洢�ռ�
}

//������Ա�
void clearlist(sqlist* L)
{
	L->length = 0;//�����Ա�ĳ�����Ϊ0����ȻҲ����������Ա��е���������
}

// ��˳���ĳ���
int getlen(sqlist* L)
{
	return (L->length);//����˳���ĳ���
}

//�ж��Ƿ�Ϊ��
int listempty(sqlist* L)
{
	if (L->length == 0)
		return 1;//���˳���Ϊ���򷵻�1
	else
		return 0;//���򷵻�0
}

//��ȡ˳�����ĳһ�������
int getelem(sqlist  L, int i, ElemType* e)
{
	if (i<1 || i>L.length)//����˵�С��1���ߴ���˳�����ܳ���
		return 0;//����0˵����ѯʧ��
	*e = L.data[i - 1];//�����е�i-1�ĵ�Ԫ�洢�����Ա��е�i������Ԫ�ص����ݣ��������e��
	return 1;//��ѯ�ɹ��򷵻�1
}

//��˳����м�����һ��ֵΪe��Ԫ��λ��
int locate(sqlist* L, ElemType  e)
{
	int i;
	for (i = 0; i < (*L).length; i++)
		if ((*L).data[i] == e)
			return i + 1;//��ѯ�ɹ�����i+1����Ԫ��e��˳����е�λ�ã�
	return 0;  //��ѯʧ���򷵻�0
}

//��˳�����ĳһλ�ò���Ԫ��
int insert_sq(sqlist* L, int i, ElemType e)
{
	ElemType* newbase, j;//��ʼ������
	if (i<1 || i>L->length + 1)  
		return 0;//�������λ�ò�������0
	if (L->length == L->listsize)//����ռ䲻��,�����Ӵ洢�ռ�
	{ 
		newbase = (ElemType*)realloc(L->data,
			(L->listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) 
			exit(0);//����ռ����ʧ�ܣ��˳����� 
		L->data = newbase;  //���»�ַ�����L
		L->listsize += LISTINCREMENT;//�������������L
	}
	for (j = L->length - 1; j >= i - 1; j--)
		//�����Ա��i��Ԫ��֮�������Ԫ������ƶ�
		L->data[j + 1] = L->data[j];
	L->data[i - 1] = e;
	//����Ԫ�ص����ݷ������Ա�ĵ�i��λ��
	L->length++;      //����1                
	return 1;//����ɹ��򷵻�1
}

//ɾ��˳�����ָ��λ�õ�Ԫ��
int delete_sq(sqlist* L, int i, ElemType* e)
{
	int j;//��ʼ������
	if (listempty(L))
		return 0; //������Ա��Ƿ�Ϊ��
	if (i<1 || i>L->length)
		return 0; //���iֵ�Ƿ����
	*e = L->data[i - 1]; //����ɾ��������Ԫ�����ݱ�����e��ָʾ�Ĵ洢��Ԫ��
	for (j = i; j < L->length; j++)
		L->data[j - 1] = L->data[j];//�����Ա��i+1��Ԫ��֮�������Ԫ����ǰ�ƶ�
	L->length--;//����1
	return 1;//ɾ���ɹ��򷵻�1
}

//��x������������L��
int Insert_Sqlist(sqlist* L, int x)
{
	ElemType* newbase, i;//��ʼ��ָ�������
	if (L->length == L->listsize)//����ռ䲻��,�����Ӵ洢�ռ�
	{ 
		newbase = (ElemType*)realloc(L->data,
			(L->listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) 
			exit(0);//����ռ����ʧ�ܣ��˳����� 
		L->data = newbase;  //���»�ַ�����L
		L->listsize += LISTINCREMENT;//���ռ����������L
	}
	for (i = L->length - 1; L->data[i] < x && i >= 0; i--)
		L->data[i + 1] = L->data[i];//����i��Ԫ�غ����Ԫ����������ƶ�һλ
	L->data[i + 1] = x;//��x����iԪ�غ�һλ
	L->length++;//����һ
	return 1;//����ɹ��򷵻�1
}


void main()
{
	int c, k, i, x, e, a, n;
	sqlist L;
	c = initlist(&L);
	if (c == 0)
		printf("�ڴ����ʧ�ܣ�");//���initlist��������0��˵���ڴ����ʧ�ܣ����������Ϣ

	printf("������˳���ĳ���n:\n");
	scanf("%d", &n);//¼����Ϣ
	L.length = n;//����˳���ĳ���Ϊ5
	//����5��Ԫ��
	printf("������%d���ݼ�������:\n", n);
	for (k = 0; k < n; k++)
	{
		scanf("%d", &a);
		L.data[k] = a;//����¼��˳����Ԫ��
	}
	list(&L);//��ӡ˳���

	printf("\n���Ա���=%d\n", getlen(&L));
	printf("���������Ԫ��x������λ��i:");
	scanf("%d%d", &x, &i);//¼��Ԫ��
	if (!insert_sq(&L, i, x))
		printf("����ʧ��\n");//������뺯������0��˵������ʧ�ܣ����������Ϣ
	else list(&L);//�������ɹ�����ӡ˳���

	printf("������ɾ����λ��i:");
	scanf("%d", &i);//¼����Ϣ
	if (!delete_sq(&L, i, &e)) 
		printf("ɾ��λ�ô���ɾ��ʧ��\n");//���ɾ����������0��˵������ʧ�ܣ����������Ϣ
	else list(&L);//����ɾ���ɹ�����ӡ˳���

	printf("������Ҫ���ҵ�Ԫ�ص�ֵ��");
	scanf("%d", &e);//¼����Ϣ
	c = locate(&L, e);//Ѱ��e��˳����е�λ��
	if (c == 0)
		printf("������ֵΪ%d��Ԫ��\n", e);//���locate��������0��˵�������ڴ��������������Ϣ
	else printf("ֵΪ%d��Ԫ���ڵ�%d��λ��\n", e, c);//�������λ��

	printf("������Ҫ��������xֵ:");
	scanf("%d", &x);//¼����Ϣ
	c = Insert_Sqlist(&L, x);//����Insert_Sqlist����Ѱ��xԪ����˳����е�λ��
	if (c == 0) 
		printf("���Ա���\n");//���Insert_Sqlist��������0��˵�����Ա��������ܲ��룬���������Ϣ
	else list(&L);//�����ӡ˳���
	destroylist(&L);//����������Ա�
}


