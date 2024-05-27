#define _CRT_SECURE_NO_WARNINGS

//6-1 ѧ����Ϣ����ϵͳ������棩
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;

//����ѧ����Ϣ�Ĵ洢�ṹ
typedef struct Stu
{
    string num;
    char name[12];
    float Chinese;
    float Math;
    float English;
    float Total;
}Stu, Student;

int cnt = 0;//�������������Ϊ�Ѳ����ѧ������

vector<Student> res;//��vector����洢ѧ����Ϣ

//�����ܷ������߼�
bool compare1(Student& a, Student& b)
{
    return a.Total < b.Total;
}

//�ּܷ��㺯��
float sum(Student& a)
{
    float total = 0;
    total = a.Chinese + a.Math + a.English;
    return total;
}

//����ѧ�������߼�
bool compare(Student& a, Student& b) {
    int x = atoi(a.num.c_str());
    int y = atoi(b.num.c_str());
    return x < y;
}

//�ַ���ת���ͺ���
int toInt(string s) {
    return atoi(s.c_str());
}

//���ֲ��Һ���
void binarySearchBynum(int low, int high, string num)
{
    if (low > high)
    {
        cout << "û�д�ѧ����" << endl;
    }
    else
    {
        int mid = (low + high) / 2;
        if (res[mid].num == num)
        {
            cout << "ѧ�ţ�" + res[mid].num << ' ';
            cout << "������" << res[mid].name << ' ';
            cout << "���ģ�" << res[mid].Chinese << ' ';
            cout << "��ѧ��" << res[mid].Math << ' ';
            cout << "Ӣ�" << res[mid].English << ' ';
            cout << "�ܷ֣�" << res[mid].Total << endl;
        }
        else if (toInt(num) < toInt(res[mid].num))
        {
            return binarySearchBynum(low, mid - 1, num);
        }
        else if (toInt(num) > toInt(res[mid].num))
        {
            return binarySearchBynum(mid + 1, high, num);
        }
    }
}

void queryByName(vector<Student> a, char name[])
{
    int i = 0;
    int flag = 1;
    for (int i = 0; i < cnt; i++)
    {
        if (strcmp(a[i].name, name) == 0)
        {
            cout << "���ҵ���ѧ������ѧ����" << i + 1 << "λ����" << endl;//��ʾ��Ϣ
            cout << "��ѧ���ľ�����Ϣ���£�" << endl;//��ʾ��Ϣ
            cout << "ѧ�ţ�" + res[i].num << ' ';
            cout << "������" << res[i].name << ' ';
            cout << "���ģ�" << res[i].Chinese << ' ';
            cout << "��ѧ��" << res[i].Math << ' ';
            cout << "Ӣ�" << res[i].English << ' ';
            cout << "�ܷ֣�" << res[i].Total << endl;
            flag = 0;
            break;
        }
    }

    if (flag)  cout << "��Ҫ���ҵ�ͬѧ���ڱ�ϵͳ��!" << endl;
}

//��ӡ�˵�
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

//��ӡ��������Ϣ����
void output_message()
{
    cout << "Ŀǰ�Ѳ���" << cnt << "��ѧ���������ֽܷ����������£�" << endl;
    for (int i = 0; i < cnt; i++)
    {
        cout << "ѧ�ţ�" + res[i].num << ' ';
        cout << "������" << res[i].name << ' ';
        cout << "���ģ�" << res[i].Chinese << ' ';
        cout << "��ѧ��" << res[i].Math << ' ';
        cout << "Ӣ�" << res[i].English << ' ';
        cout << "�ܷ֣�" << res[i].Total << endl;
    }
}

int main()
{
    int op = 100;//��ʼ��option
    MenuList();//��ӡ�˵�

    cin.tie(nullptr);
    ios::sync_with_stdio(false);//��������Ż�

    cout << endl;
    cout << endl;
    cout << endl;//����

    cout << "***�밴����ʾ��Ϣ����1��4֮����ַ�***" << endl;//��ʾ��Ϣ

    while (op != 0)
    {
        while (true)
        {
            puts("����������ѡ��");//��ʾ��Ϣ
            cin >> op;
            if (op < 0 || op>4)
            {
                cout << "���������Ϣ����,���������룡" << endl;//��������option����ϵͳ��ʾ�ģ��˳�ϵͳ
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
            cout << "������ѧ����ѧ�š����������ĳɼ�����ѧ�ɼ���Ӣ��ɼ�" << endl;//��ʾ��Ϣ
            cin >> t.num >> t.name >> t.Chinese >> t.Math >> t.English;
            cnt++;
            t.Total = sum(t);
            res.push_back(t);
            cout << "����ɹ���" << endl;//��ʾ��Ϣ
        }
        else if (op == 2)
        {
            sort(res.begin(), res.end(), compare1);//���ÿ��������㷨�������ݰ���compare1���߼�����
            output_message();//�����������Ϣ
        }
        else if (op == 3)
        {
            int i;//��ʼ����������
            string t;//��ʼ��ѧ��

            //�ж�ѧ����ȷ����㷨
            while (true)
            {
                cout << "������ѧ����ѧ�ţ�" << endl;//��ʾ��Ϣ
                cin >> t;

                for (i = 0; i < cnt; i++)
                    if (t == res[i].num)
                        break;

                if (i != cnt)
                {
                    break;
                }
                else
                {
                    cout << "û�д�ѧ�ŵ�ѧ�������������룡" << endl;//��ʾ��Ϣ
                }
            }
            sort(res.begin(), res.end(), compare);//����compare���߼���res����
            binarySearchBynum(0, res.size() - 1, t);//���ֲ���
        }
        else if (op == 4)
        {
            char name[12];
            cout << "������ѧ��������:" << endl;//��ʾ��Ϣ
            cin >> name;//¼������
            queryByName(res, name);//˳�����
        }
    }

    return 0;
}