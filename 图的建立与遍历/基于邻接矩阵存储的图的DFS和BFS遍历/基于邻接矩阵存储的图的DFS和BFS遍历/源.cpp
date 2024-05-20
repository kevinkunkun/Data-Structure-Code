#define _CRT_SECURE_NO_WARNINGS
//4-1ͼ��������ȱ����������ȱ����������ڽӾ���

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define INFINITE 9999//���������Ϊ9999
#define MAX 10

int  A[MAX][MAX];
int visited[MAX];
int V[MAX];

//��������������
void safe_flush(FILE* fp)
{
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n');
}

//����ͼ
void creatadj(int n, int e, int t)
{
	int i, j, k, w, v1;
	printf(" ����ͼG\n");
	printf(" �����붥��ֵ�������ʽ�� number��or char)<�س�>):\n");
	for (i = 1; i <= n; i++)
	{
		safe_flush(stdin);//��������������
		scanf("%c", &V[i]);//¼�붥��
	}
	printf(" ����Ϊ��");
	for (i = 1; i <= n; i++)
		printf(" V%c   ", V[i]);//��ӡ����
	printf("\n");
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			if (t > 2) //����ͼ��1��ʾ������Ȩͼ��2��ʾ������Ȩͼ��3��ʾ�����Ȩͼ��4��ʾ�����Ȩͼ  
				A[i][j] = INFINITE;//��Ϊ����ͼ�����ڽӾ����и��߳�ʼ��Ϊ�����
			else
				A[i][j] = 0;//��Ϊ����ͼ���򽫸��߳�ʼ��Ϊ0

	//������Ȩͼ
	if (t == 1 || t == 2)
	{
		printf(" ����ߣ������ʽ��i,j<�س�>�����У�i,jΪ����Ĵ洢�±꣬1<=i<=%d,1<=j<=%d)\n", n, n);
		for (k = 1; k <= e; k++)
		{	//printf("�����%d���ߣ������ʽ��i,j<CR>):\n",k);
			scanf("%d,%d", &i, &j);
			while (i > n || j > n || i < 1 || j < 1)
			{
				printf(" ����Ĵ洢�±�Խ�磬�����������%d���� ", k);
				scanf("%d,%d", &i, &j);
			}
			A[i][j] = 1;
			if (t == 1)
				A[j][i] = 1;
		}
	}

	//�����Ȩͼ
	if (t == 3 || t == 4)
	{
		printf(" �������߼���Ȩֵ�������ʽ(w<9999,1<=i<=%d,1<=j<=%d)��i,j,w<CR>):\n", n, n);
		for (k = 1; k <= e; k++)
		{
			scanf("%d,%d,%d", &i, &j, &w);
			while (i > n || j > n || i < 1 || j < 1)
			{
				printf(" ����Ĵ洢�±�Խ�磬�����������%d���� ", k);
				scanf("%d,%d,%d", &i, &j, &w);
			}
			A[i][j] = w;
			if (t == 3)//���������ͼ
				A[j][i] = w;//����һ�����ĶԳ�λ��Ҳ��ֵΪw
		}
	}
}

//���ʽڵ㺯��
void visit(int i)
{
	printf("V%c   ", V[i]);
}

//����ڽӾ���g
void DispMG(int n)
{
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			if (A[i][j] == INFINITE)
				printf(" %3s", "��");//�����������������
			else
				printf(" %3d", A[i][j]);//�������ֵ
		printf("\n");
	}
}

//��������ͼ������ͼ��������ȱ�����װ���� 
void dfs(int i, int n)        
{  //����ͼ������ͼ 
	int j;
	visit(i);//���v[i]���� 
	visited[i] = 1;//��־�Ѿ���� 
	for (j = 1; j <= n; j++)
		if ((A[i][j] == 1) && (!visited[j])) //��û��������б� 
			dfs(j, n);//�ݹ�

}

//������������������������ȱ�����װ����
void dfs34(int i, int n)
{
	int j;
	visit(i);//���v[i]���� 
	visited[i] = 1;//��־�Ѿ���� 
	for (j = 1; j <= n; j++)
		if ((A[i][j] < INFINITE) && (!visited[j])) //��û��������б� 
			dfs34(j, n);//�ݹ�   
}

//����dfs��dfs34��������������ȱ�������
void dfs1(int i, int n, int t) {

	int k, j;
	printf(" ������ȱ������У�");
	for (k = 1; k <= n; k++)
		visited[k] = 0;
	if (t == 1 || t == 2)//����ͼ
	{
		dfs(i, n);
		for (j = 1; j <= n; j++)
			if (!visited[j]) dfs(j, n);
	}
	else//������
	{
		dfs34(i, n);
		for (j = 1; j <= n; j++)
			if (!visited[j]) dfs34(j, n);
	}
	printf("\n");
}

//������ȱ����ķ�װ����
void bfs(int i, int n, int t)
{
	int q[10] = { 0 };  //����һ��˳�����  
	int j, r = 0, f = 0; //���еĶ�ͷ��βָ���ʼ��Ϊ0
	visit(i);//���v[i]���� 
	visited[i] = 1;//��־�Ѿ���� 
	q[f] = i;
	f++;
	if (t == 1 || t == 2) //����ͼ������ͼ 
	{
		while (r != f)
		{
			i = q[r];
			r++;
			for (j = 1; j <= n; j++)
			{
				if ((A[i][j] == 1) && (!visited[j]))//��û��������б�
				{
					visit(j);//���v[i]���� 
					visited[j] = 1;//��־�Ѿ���� 
					q[f] = j;
					f++;
				}
			}
		}
	}
	if (t == 3 || t == 4) //��������������
	{
		while (r != f)
		{
			i = q[r];
			r++;
			for (j = 1; j <= n; j++)
			{
				if ((A[i][j] < INFINITE) && (!visited[j]))//��û��������б�
				{
					visit(j);               //���v[i]���� 
					visited[j] = 1;           //��־�Ѿ���� 
					q[f] = j;
					f++;
				}
			}
		}
	}
}


//���÷�װ����bfs��ɹ�����ȱ���
void bfs1(int i, int n, int t) { //b 
	int k;
	printf(" ������ȱ������У�");
	for (k = 1; k <= n; k++)
		visited[k] = 0;
	bfs(i, n, t);
	int j;
	for (j = 1; j <= n; i++) {//�ж��Ƿ�ȫ����� 
		if (!visited[j]) {
			bfs(j, n, t);
		}
		j++;
	}
	printf("\n");
}

//���ɲ˵�
void MenuList()
{
	printf("\n\n\n **************************\n");
	printf("  1  -------  ����ͼ\n");
	printf("  2  -------  �������\n");
	printf("  3  -------  �������\n");
	printf("  0  -------  �˳�\n");
	printf(" **************************\n");

}

//������
int main()
{
	int n = 0, e, t, i;
	int k = 100;
	//system("color E0");
	MenuList();
	while (k != 0)
	{
		printf(" ��ѡ�����:");
		scanf("%d", &k);
		if (k == 1)
		{
			printf(" �����붥������������ͼ�����ͣ������ʽ��v,e,t):");
			scanf("%d,%d,%d", &n, &e, &t);
			creatadj(n, e, t);
			printf(" ͼ���ڽӾ���Ϊ��\n");
			DispMG(n);
		}
		if (k == 2)//��Ⱥ���ȶ�ֻ����һ��  
		{
			if (n <= 0)
				printf(" ͼ�����ڣ������й���1����ͼ\n");
			else
			{
				printf(" ������������ȱ����ĳ�ʼ���㣺");
				scanf("%d", &i);
				dfs1(i, n, t);
			}
		}
		if (k == 3)
		{
			if (n <= 0)
				printf(" ͼ�����ڣ������й���1����ͼ\n");
			else
			{
				printf(" �����������ȱ����ĳ�ʼ���㣺");
				scanf("%d", &i);
				bfs1(i, n, t);
			}
		}
	}

	return 0;
}
