#define _CRT_SECURE_NO_WARNINGS

//5-3 哈希表

#include <stdio.h>
#include <stdlib.h>

#define TableSize 100
#define  NULLKEY  0

//哈希表的存储结构
typedef struct  Hstable
{
	int* data;//数据元素存储地址
	int Length;//当前容量
	int num;//当前元素个数
}hstable;

//计算关键字k的哈希地址
int Hash(int k, int p)
{
	int h;
	h = k % p;
	return h;
}

//菜单函数
void MenuList()
{
	printf("\n\n\n");
	printf("*******************************************************************\n");
	printf("****************    开放寻址法构造哈希表算法             **********\n");
	printf("****************    1  ------生成开放定址哈希查表        **********\n");
	printf("****************    2  ------开放定址哈希查表查找        **********\n");
	printf("****************    3  ------开放定址哈希查表中插入元素  **********\n");
	printf("****************    0  ------结束运行                    **********\n");
	printf("*******************************************************************\n");
}

//哈希表的初始化
int initHash(Hstable* La)
{  
	int i;
	La->data = (int*)malloc(TableSize * sizeof(int));//分配La的存储空间
	printf("请输入哈希表的表长length和元素个数num\n");
	printf("表长length=");
	scanf("%d", &La->Length);
	printf("元素个数num=");
	scanf("%d", &La->num);
	if (La->Length < La->num)  //哈希表中关键字的个数不能大于当前表的空间长度
	{
		printf("哈希表的关键字个数大于表长,哈希表初始化失败\n");
		return 0;
	}
	else
	{
		int* p = La->data;
		for (i = 0; i < La->Length; i++)
			*(p + i) = NULLKEY; //初始化时，每个哈希地址的值都设置成0
		return 1;
	}
}

//开地址法哈希查找
int HashSearch(Hstable* ht, int K, int p)
{
	int h0, di = 0, hi; //di为增长序列，hi为冲突后的地址，h0为初始地址
	h0 = Hash(K, p);//根据哈希函数计算元素的初始地址
	hi = h0;
	while (di < ht->Length && ht->data[hi] != NULLKEY)
		// 如果di>0 发生冲突，用线性探测再散列计算冲突后的地址 
	{
		hi = (h0 + di) % ht->Length;//计算第di次冲突后的地址
		if (ht->data[hi] == K)
			return 1;//查找成功，返回1
		else
			di = di + 1;
	}
	return 0;//查找失败，返回0 
}

//创建开放地址法哈希表
void CreatHashTable(Hstable* La, int p)
{
	int i, j, K, h0, h1, di, num;
	int h[TableSize];
	printf("请输入哈希表的%d 个关键字：", La->num);
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
			printf("输入序列中关键字%d有重复，元素个数num减1\n", K);
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

//输出哈希表中的元素
void prtL(Hstable* La) {
	printf("输出哈希表的关键字:\n");
	for (int i = 0; i < La->Length; i++)
	{
		printf("%d  ", La->data[i]);
	}
	printf("\n");
}

//向开放地址法哈希表中插入元素
void inserthast1(Hstable* La, int k, int p)
{
	int h, r;
	h = k % p;
	if (La->Length == La->num)
	{
		printf("哈希表中已经没有存储空间，无法再插入元素！！\n");
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

//主函数
int main()
{
	int i, j, x, choice = 100, k, p;
	Hstable La;
	MenuList();
	printf("哈希函数为hash(key)=key mod p,请输入P的值：");
	scanf("%d", &p);
	printf("\n");
	while (choice != 0)
	{
		printf("请输入操作选项:");
		scanf("%d", &choice);
		if (choice == 1)//生成开地址法哈希查表
		{
			
			j = initHash(&La);
			if (j == 1)
			{
				CreatHashTable(&La, p);
				prtL(&La);
				printf("哈希表生成成功\n");
			}
		}
		if (choice == 2)//开地址法哈希查表查找
		{ 
			printf("请输入要查找的关键字的值：");
			scanf("%d", &k);
			printf("\n");
			j = HashSearch(&La, k, p);
			if (j == 1)
				printf("查找成功\n");
			else
				printf("查找失败\n");
		}
		if (choice == 3)//开地址法哈希查表中插入元素X
		{ 
			printf("请输入要插入的关键字的值：");
			scanf("%d", &k);
			j = HashSearch(&La, k, p);
			if (j == 1)
				printf("哈希表中已经存在该关键字，不能插入\n");
			else
			{
				inserthast1(&La, k, p);
				prtL(&La);
				printf("插入成功\n");
			}
		}
	}

	return 0;
}
