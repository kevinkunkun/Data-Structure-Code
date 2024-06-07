#define _CRT_SECURE_NO_WARNINGS

//6-1 学生信息查找系统（数组版）
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;

//定义学生信息的存储结构
typedef struct Stu
{
    string num;
    char name[12];
    float Chinese;
    float Math;
    float English;
    float Total;
}Stu, Student;

int cnt = 0;//计数器，其个数为已插入的学生个数

vector<Student> res;//用vector数组存储学生信息

//按照总分排序逻辑
bool compare1(Student& a, Student& b)
{
    return a.Total < b.Total;
}

//总分计算函数
float sum(Student& a)
{
    float total = 0;
    total = a.Chinese + a.Math + a.English;
    return total;
}

//按照学号排序逻辑
bool compare(Student& a, Student& b) {
    int x = atoi(a.num.c_str());
    int y = atoi(b.num.c_str());
    return x < y;
}

//字符串转整型函数
int toInt(string s) {
    return atoi(s.c_str());
}

//二分查找函数
void binarySearchBynum(int low, int high, string num)
{
    if (low > high)
    {
        cout << "没有此学生！" << endl;
    }
    else
    {
        int mid = (low + high) / 2;
        if (res[mid].num == num)
        {
            cout << "学号：" + res[mid].num << ' ';
            cout << "姓名：" << res[mid].name << ' ';
            cout << "语文：" << res[mid].Chinese << ' ';
            cout << "数学：" << res[mid].Math << ' ';
            cout << "英语：" << res[mid].English << ' ';
            cout << "总分：" << res[mid].Total << endl;
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
            cout << "已找到此学生，此学生在" << i + 1 << "位置上" << endl;//提示信息
            cout << "此学生的具体信息如下：" << endl;//提示信息
            cout << "学号：" + res[i].num << ' ';
            cout << "姓名：" << res[i].name << ' ';
            cout << "语文：" << res[i].Chinese << ' ';
            cout << "数学：" << res[i].Math << ' ';
            cout << "英语：" << res[i].English << ' ';
            cout << "总分：" << res[i].Total << endl;
            flag = 0;
            break;
        }
    }

    if (flag)  cout << "您要查找的同学不在本系统中!" << endl;
}

//打印菜单
void MenuList()
{
    printf("\n\n\n");
    printf("*************************************************************\n");
    printf("****************  学生信息查找排序系统（数组版）  ***********\n");
    printf("**** 1  -------录入学生信息                              ****\n");
    printf("**** 2  -------学生信息排序（按总分降序排列）            ****\n");
    printf("**** 3  -------按学号查找学生信息                        ****\n");
    printf("**** 4  -------按姓名查找学生信息                        ****\n");
    printf("**** 0  -------结束运行                                  ****\n");
    printf("*************************************************************\n");
}

//打印排序后的信息表函数
void output_message()
{
    cout << "目前已插入" << cnt << "个学生，按照总分降序排序如下：" << endl;
    for (int i = 0; i < cnt; i++)
    {
        cout << "学号：" + res[i].num << ' ';
        cout << "姓名：" << res[i].name << ' ';
        cout << "语文：" << res[i].Chinese << ' ';
        cout << "数学：" << res[i].Math << ' ';
        cout << "英语：" << res[i].English << ' ';
        cout << "总分：" << res[i].Total << endl;
    }
}

int main()
{
    int op = 100;//初始化option
    MenuList();//打印菜单

    cin.tie(nullptr);
    ios::sync_with_stdio(false);//输入输出优化

    cout << endl;
    cout << endl;
    cout << endl;//换行

    cout << "***请按照提示信息输入1—4之间的字符***" << endl;//提示信息

    while (op != 0)
    {
        while (true)
        {
            puts("请输入您的选择：");//提示信息
            cin >> op;
            if (op < 0 || op>4)
            {
                cout << "您输入的信息有误,请重新输入！" << endl;//如果输入的option不是系统提示的，退出系统
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
            cout << "请输入学生的学号、姓名、语文成绩、数学成绩、英语成绩" << endl;//提示信息
            cin >> t.num >> t.name >> t.Chinese >> t.Math >> t.English;
            cnt++;
            t.Total = sum(t);
            res.push_back(t);
            cout << "插入成功！" << endl;//提示信息
        }
        else if (op == 2)
        {
            sort(res.begin(), res.end(), compare1);//调用快速排序算法，对数据按照compare1的逻辑排序
            output_message();//输出排序后的信息
        }
        else if (op == 3)
        {
            int i;//初始化计数变量
            string t;//初始化学号

            //判断学号正确与否算法
            while (true)
            {
                cout << "请输入学生的学号：" << endl;//提示信息
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
                    cout << "没有此学号的学生，请重新输入！" << endl;//提示信息
                }
            }
            sort(res.begin(), res.end(), compare);//按照compare的逻辑对res排序
            binarySearchBynum(0, res.size() - 1, t);//二分查找
        }
        else if (op == 4)
        {
            char name[12];
            cout << "请输入学生的姓名:" << endl;//提示信息
            cin >> name;//录入姓名
            queryByName(res, name);//顺序查找
        }
    }

    return 0;
}