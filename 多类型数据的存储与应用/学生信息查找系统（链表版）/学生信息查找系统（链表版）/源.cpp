#define _CRT_SECURE_NO_WARNINGS

//6-2 ѧ����Ϣ����ϵͳ������棩
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

// �ּܷ��㺯��
float sum(Student& a)
{
	return a.Chinese + a.Math + a.English;
}

// ����ѧ����Ϣ
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

// ���ܷ���������
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

// ��ѧ����������
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

// ��ѧ�Ŷ��ֲ���
void binarySearchBynum(Node* head, const string& num)
{
	sortStudentsByNum();
	Node* curr = head;
	while (curr != nullptr)
	{
		if (curr->data.num == num)
		{
			cout << "ѧ�ţ�" << curr->data.num << ' ';
			cout << "������" << curr->data.name << ' ';
			cout << "���ģ�" << curr->data.Chinese << ' ';
			cout << "��ѧ��" << curr->data.Math << ' ';
			cout << "Ӣ�" << curr->data.English << ' ';
			cout << "�ܷ֣�" << curr->data.Total << endl;
			return;
		}
		curr = curr->next;
	}
	cout << "û�д�ѧ����" << endl;
}

// ������˳�����
void queryByName(Node* head, const char name[])
{
	Node* curr = head;
	while (curr != nullptr)
	{
		if (strcmp(curr->data.name, name) == 0)
		{
			cout << "��ѧ���ľ�����Ϣ���£�" << endl;
			cout << "ѧ�ţ�" << curr->data.num << ' ';
			cout << "������" << curr->data.name << ' ';
			cout << "���ģ�" << curr->data.Chinese << ' ';
			cout << "��ѧ��" << curr->data.Math << ' ';
			cout << "Ӣ�" << curr->data.English << ' ';
			cout << "�ܷ֣�" << curr->data.Total << endl;
			return;
		}
		curr = curr->next;
	}
	cout << "��Ҫ���ҵ�ͬѧ���ڱ�ϵͳ��!" << endl;
}

// ��ӡ��������Ϣ��
void output_message()
{
	cout << "Ŀǰ�Ѳ���" << cnt << "��ѧ���������ֽܷ����������£�" << endl;
	Node* curr = head;
	while (curr != nullptr)
	{
		cout << "ѧ�ţ�" << curr->data.num << ' ';
		cout << "������" << curr->data.name << ' ';
		cout << "���ģ�" << curr->data.Chinese << ' ';
		cout << "��ѧ��" << curr->data.Math << ' ';
		cout << "Ӣ�" << curr->data.English << ' ';
		cout << "�ܷ֣�" << curr->data.Total << endl;
		curr = curr->next;
	}
}

// ��ѧ�����Բ���
void searchByNum(const string& num) 
{
	Node* curr = head;
	while (curr != nullptr) 
	{
		if (curr->data.num == num) 
		{
			cout << "ѧ�ţ�" << curr->data.num << ' ';
			cout << "������" << curr->data.name << ' ';
			cout << "���ģ�" << curr->data.Chinese << ' ';
			cout << "��ѧ��" << curr->data.Math << ' ';
			cout << "Ӣ�" << curr->data.English << ' ';
			cout << "�ܷ֣�" << curr->data.Total << endl;
			return;
		}
		curr = curr->next;
	}
	cout << "û�д�ѧ����" << endl;
}

// ��ӡ�˵�
void MenuList()
{
	printf("\n\n\n");
	printf("*************************************************************\n");
	printf("****************  ѧ����Ϣ��������ϵͳ������棩  ***********\n");
	printf("**** 1  -------¼��ѧ����Ϣ                              ****\n");
	printf("**** 2  -------ѧ����Ϣ���򣨰��ֽܷ������У�            ****\n");
	printf("**** 3  -------��ѧ�Ų���ѧ����Ϣ                        ****\n");
	printf("**** 4  -------����������ѧ����Ϣ                        ****\n");
	printf("**** 0  -------��������                                  ****\n");
	printf("*************************************************************\n");
}

int main()
{
	int op = 100;
	MenuList();

	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << "***�밴����ʾ��Ϣ����1��4֮����ַ�***" << endl;

	while (op != 0)
	{
		while (true)
		{
			puts("����������ѡ��");
			cin >> op;
			if (op < 0 || op > 4)
			{
				cout << "���������Ϣ����,���������룡" << endl;
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
			cout << "������ѧ����ѧ�š����������ĳɼ�����ѧ�ɼ���Ӣ��ɼ�" << endl;
			cin >> t.num >> t.name >> t.Chinese >> t.Math >> t.English;
			t.Total = sum(t);
			insertStudent(t);
			cout << "����ɹ���" << endl;
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
				cout << "������ѧ����ѧ�ţ�" << endl;
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
					cout << "û�д�ѧ�ŵ�ѧ�������������룡" << endl;
				}
			}
			sortStudentsByNum();
			searchByNum(t);
		}
		else if (op == 4)
		{
			char name[12];
			cout << "������ѧ��������:" << endl;
			cin >> name;
			queryByName(head, name);
		}
	}

	return 0;
}
