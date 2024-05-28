#define _CRT_SECURE_NO_WARNINGS

//6-2 学生信息查找系统（链表版）
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

typedef struct Stu
{
	string num;
	char name[12];
	float Chinese;
	float Math;
	float English;
	float Total;
} Stu, Student;

typedef struct Node
{
	Student data;
	Node* next;
} Node;

Node* head = nullptr;
int cnt = 0;

// 总分计算函数
float sum(Student& a)
{
	return a.Chinese + a.Math + a.English;
}

// 插入学生信息
void insertStudent(const Student& t)
{
	Node* newNode = new Node
	{
		t, nullptr
	};
	if (head == nullptr)
	{
		head = newNode;
	}
	else
	{
		Node* curr = head;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr->next = newNode;
	}
	cnt++;
}

// 按总分排序链表
void sortStudentsByTotal()
{
	if (head == nullptr) return;

	vector<Node*> nodes;
	Node* curr = head;
	while (curr != nullptr)
	{
		nodes.push_back(curr);
		curr = curr->next;
	}

	sort(nodes.begin(), nodes.end(), [](Node* a, Node* b)
		{
			return a->data.Total > b->data.Total;
		});

	for (int i = 0; i < nodes.size() - 1; ++i)
	{
		nodes[i]->next = nodes[i + 1];
	}
	nodes.back()->next = nullptr;
	head = nodes.front();
}

// 按学号排序链表
void sortStudentsByNum()
{
	if (head == nullptr) return;

	vector<Node*> nodes;
	Node* curr = head;
	while (curr != nullptr)
	{
		nodes.push_back(curr);
		curr = curr->next;
	}

	sort(nodes.begin(), nodes.end(), [](Node* a, Node* b)
		{
			return stoi(a->data.num) < stoi(b->data.num);
		});

	for (int i = 0; i < nodes.size() - 1; ++i)
	{
		nodes[i]->next = nodes[i + 1];
	}
	nodes.back()->next = nullptr;
	head = nodes.front();
}

// 按学号二分查找
void binarySearchBynum(Node* head, const string& num)
{
	sortStudentsByNum();
	Node* curr = head;
	while (curr != nullptr)
	{
		if (curr->data.num == num)
		{
			cout << "学号：" << curr->data.num << ' ';
			cout << "姓名：" << curr->data.name << ' ';
			cout << "语文：" << curr->data.Chinese << ' ';
			cout << "数学：" << curr->data.Math << ' ';
			cout << "英语：" << curr->data.English << ' ';
			cout << "总分：" << curr->data.Total << endl;
			return;
		}
		curr = curr->next;
	}
	cout << "没有此学生！" << endl;
}

// 按姓名顺序查找
void queryByName(Node* head, const char name[])
{
	Node* curr = head;
	while (curr != nullptr)
	{
		if (strcmp(curr->data.name, name) == 0)
		{
			cout << "此学生的具体信息如下：" << endl;
			cout << "学号：" << curr->data.num << ' ';
			cout << "姓名：" << curr->data.name << ' ';
			cout << "语文：" << curr->data.Chinese << ' ';
			cout << "数学：" << curr->data.Math << ' ';
			cout << "英语：" << curr->data.English << ' ';
			cout << "总分：" << curr->data.Total << endl;
			return;
		}
		curr = curr->next;
	}
	cout << "您要查找的同学不在本系统中!" << endl;
}

// 打印排序后的信息表
void output_message()
{
	cout << "目前已插入" << cnt << "个学生，按照总分降序排序如下：" << endl;
	Node* curr = head;
	while (curr != nullptr)
	{
		cout << "学号：" << curr->data.num << ' ';
		cout << "姓名：" << curr->data.name << ' ';
		cout << "语文：" << curr->data.Chinese << ' ';
		cout << "数学：" << curr->data.Math << ' ';
		cout << "英语：" << curr->data.English << ' ';
		cout << "总分：" << curr->data.Total << endl;
		curr = curr->next;
	}
}

// 按学号线性查找
void searchByNum(const string& num) 
{
	Node* curr = head;
	while (curr != nullptr) 
	{
		if (curr->data.num == num) 
		{
			cout << "学号：" << curr->data.num << ' ';
			cout << "姓名：" << curr->data.name << ' ';
			cout << "语文：" << curr->data.Chinese << ' ';
			cout << "数学：" << curr->data.Math << ' ';
			cout << "英语：" << curr->data.English << ' ';
			cout << "总分：" << curr->data.Total << endl;
			return;
		}
		curr = curr->next;
	}
	cout << "没有此学生！" << endl;
}

// 打印菜单
void MenuList()
{
	printf("\n\n\n");
	printf("*************************************************************\n");
	printf("****************  学生信息查找排序系统（链表版）  ***********\n");
	printf("**** 1  -------录入学生信息                              ****\n");
	printf("**** 2  -------学生信息排序（按总分降序排列）            ****\n");
	printf("**** 3  -------按学号查找学生信息                        ****\n");
	printf("**** 4  -------按姓名查找学生信息                        ****\n");
	printf("**** 0  -------结束运行                                  ****\n");
	printf("*************************************************************\n");
}

int main()
{
	int op = 100;
	MenuList();

	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << "***请按照提示信息输入1—4之间的字符***" << endl;

	while (op != 0)
	{
		while (true)
		{
			puts("请输入您的选择：");
			cin >> op;
			if (op < 0 || op > 4)
			{
				cout << "您输入的信息有误,请重新输入！" << endl;
			}
			else break;
		}

		if (op == 0)
		{
			exit(0);
		}
		else if (op == 1)
		{
			Student t;
			cout << "请输入学生的学号、姓名、语文成绩、数学成绩、英语成绩" << endl;
			cin >> t.num >> t.name >> t.Chinese >> t.Math >> t.English;
			t.Total = sum(t);
			insertStudent(t);
			cout << "插入成功！" << endl;
		}
		else if (op == 2)
		{
			sortStudentsByTotal();
			output_message();
		}
		else if (op == 3) 
		{
			string t;
			while (true) 
			{
				cout << "请输入学生的学号：" << endl;
				cin >> t;

				Node* curr = head;
				while (curr != nullptr) 
				{
					if (curr->data.num == t)
						break;
					curr = curr->next;
				}

				if (curr != nullptr)
				{
					break;
				}
				else 
				{
					cout << "没有此学号的学生，请重新输入！" << endl;
				}
			}
			sortStudentsByNum();
			searchByNum(t);
		}
		else if (op == 4)
		{
			char name[12];
			cout << "请输入学生的姓名:" << endl;
			cin >> name;
			queryByName(head, name);
		}
	}

	return 0;
}
