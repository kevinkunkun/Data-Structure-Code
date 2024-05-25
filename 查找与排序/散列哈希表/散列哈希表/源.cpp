#define _CRT_SECURE_NO_WARNINGS

//5-3 ��ϣ��

#include <stdio.h>
#include <stdlib.h>

#define TableSize 100
#define  NULLKEY  0

//��ϣ��Ĵ洢�ṹ
typedef struct  Hstable
{
	int* data;//����Ԫ�ش洢��ַ
	int Length;//��ǰ����
	int num;//��ǰԪ�ظ���
}hstable;

//����ؼ���k�Ĺ�ϣ��ַ
int Hash(int k, int p)
{
	int h;
	h = k % p;
	return h;
}

//�˵�����
void MenuList()
{
	printf("\n\n\n");
	printf("*******************************************************************\n");
	printf("****************    ����Ѱַ�������ϣ���㷨             **********\n");
	printf("****************    1  ------���ɿ��Ŷ�ַ��ϣ���        **********\n");
	printf("****************    2  ------���Ŷ�ַ��ϣ������        **********\n");
	printf("****************    3  ------���Ŷ�ַ��ϣ����в���Ԫ��  **********\n");
	printf("****************    0  ------��������                    **********\n");
	printf("*******************************************************************\n");
}

//��ϣ��ĳ�ʼ��
int initHash(Hstable* La)
{  
	int i;
	La->data = (int*)malloc(TableSize * sizeof(int));//����La�Ĵ洢�ռ�
	printf("�������ϣ��ı�length��Ԫ�ظ���num\n");
	printf("��length=");
	scanf("%d", &La->Length);
	printf("Ԫ�ظ���num=");
	scanf("%d", &La->num);
	if (La->Length < La->num)  //��ϣ���йؼ��ֵĸ������ܴ��ڵ�ǰ��Ŀռ䳤��
	{
		printf("��ϣ��Ĺؼ��ָ������ڱ�,��ϣ���ʼ��ʧ��\n");
		return 0;
	}
	else
	{
		int* p = La->data;
		for (i = 0; i < La->Length; i++)
			*(p + i) = NULLKEY; //��ʼ��ʱ��ÿ����ϣ��ַ��ֵ�����ó�0
		return 1;
	}
}

//����ַ����ϣ����
int HashSearch(Hstable* ht, int K, int p)
{
	int h0, di = 0, hi; //diΪ�������У�hiΪ��ͻ��ĵ�ַ��h0Ϊ��ʼ��ַ
	h0 = Hash(K, p);//���ݹ�ϣ��������Ԫ�صĳ�ʼ��ַ
	hi = h0;
	while (di < ht->Length && ht->data[hi] != NULLKEY)
		// ���di>0 ������ͻ��������̽����ɢ�м����ͻ��ĵ�ַ 
	{
		hi = (h0 + di) % ht->Length;//�����di�γ�ͻ��ĵ�ַ
		if (ht->data[hi] == K)
			return 1;//���ҳɹ�������1
		else
			di = di + 1;
	}
	return 0;//����ʧ�ܣ�����0 
}

//�������ŵ�ַ����ϣ��
void CreatHashTable(Hstable* La, int p)
{
	int i, j, K, h0, h1, di, num;
	int h[TableSize];
	printf("�������ϣ���%d ���ؼ��֣�", La->num);
	for (i = 0; i < La->num; i++)
		scanf("%d", &h[i]);
	num = La->num;
	printf("\n");
	for (i = 0; i < num; i++)
	{
		K = h[i];
		j = HashSearch(La, K, p);
		if (j == 1)
		{
			printf("���������йؼ���%d���ظ���Ԫ�ظ���num��1\n", K);
			La->num = La->num - 1;
		}
		if (j == 0)
		{
			h0 = K % p;
			for (di = 0; di < La->Length; di++)
			{
				h1 = (h0 + di) % La->Length;
				if (La->data[h1] == NULLKEY)
				{
					La->data[h1] = K;
					break;
				}
			}
		}
	}
}

//�����ϣ���е�Ԫ��
void prtL(Hstable* La) {
	printf("�����ϣ��Ĺؼ���:\n");
	for (int i = 0; i < La->Length; i++)
	{
		printf("%d  ", La->data[i]);
	}
	printf("\n");
}

//�򿪷ŵ�ַ����ϣ���в���Ԫ��
void inserthast1(Hstable* La, int k, int p)
{
	int h, r;
	h = k % p;
	if (La->Length == La->num)
	{
		printf("��ϣ�����Ѿ�û�д洢�ռ䣬�޷��ٲ���Ԫ�أ���\n");
		return;
	}
	else
	{
		for (r = 0; r < La->Length; r++)
		{
			h = (h + r) % La->Length;
			if (La->data[h] == NULLKEY)
			{
				La->data[h] = k;
				La->num++;
				break;
			}
		}
	}
}

//������
int main()
{
	int i, j, x, choice = 100, k, p;
	Hstable La;
	MenuList();
	printf("��ϣ����Ϊhash(key)=key mod p,������P��ֵ��");
	scanf("%d", &p);
	printf("\n");
	while (choice != 0)
	{
		printf("���������ѡ��:");
		scanf("%d", &choice);
		if (choice == 1)//���ɿ���ַ����ϣ���
		{
			
			j = initHash(&La);
			if (j == 1)
			{
				CreatHashTable(&La, p);
				prtL(&La);
				printf("��ϣ�����ɳɹ�\n");
			}
		}
		if (choice == 2)//����ַ����ϣ������
		{ 
			printf("������Ҫ���ҵĹؼ��ֵ�ֵ��");
			scanf("%d", &k);
			printf("\n");
			j = HashSearch(&La, k, p);
			if (j == 1)
				printf("���ҳɹ�\n");
			else
				printf("����ʧ��\n");
		}
		if (choice == 3)//����ַ����ϣ����в���Ԫ��X
		{ 
			printf("������Ҫ����Ĺؼ��ֵ�ֵ��");
			scanf("%d", &k);
			j = HashSearch(&La, k, p);
			if (j == 1)
				printf("��ϣ�����Ѿ����ڸùؼ��֣����ܲ���\n");
			else
			{
				inserthast1(&La, k, p);
				prtL(&La);
				printf("����ɹ�\n");
			}
		}
	}

	return 0;
}
