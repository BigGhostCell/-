#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
int n = 0;
int k = 0;
int bestTime = 0;
vector<int> t;
vector<int> mech;
void readFile()
{
    fstream in;
    in.open("input.txt", ios::in);
    if (!in)
    {
        return;
    }
    string temp;
    getline(in, temp, ' ');
    n = stoi(temp);
    getline(in, temp);
    k = stoi(temp);

    t.resize(n + 1);

    for (int i = 1; i < n; i++)
    {
        getline(in, temp, ' ');
        t[i] = stoi(temp);
        bestTime += t[i];
    }
    getline(in, temp);
   t[n] = stoi(temp);
   bestTime += t[n];
   in.close();
}

int timeGet()
{
    int maxtime = 0;
    for (int i = 1; i <= k; i++)
    {
        maxtime = max(mech[i], maxtime);
    }
    return maxtime;
}

void backTrace(int level)
{
    if (level == n + 1)//�ߵ�Ҷ�ӽڵ�
    {
        bestTime = min(timeGet(), bestTime);
        return;
    }

    for (int i = 1; i <= k; i++)
    {
        mech[i] += t[level];//һֱ��һ̨�����������
        if (mech[i] < bestTime)//��ǰ����ʱ����Ȼ��С�����ţ����Լ�������
            backTrace(level + 1);
        mech[i] -= t[level];//��������
    }
}

void writeFile()
{
    fstream in;
    in.open("output.txt", ios::out);
    if (!in)
    {
        cout << "error";
    }
    in << bestTime;
    in.close();
}

int main()
{
    readFile();
    mech.resize(k + 1);//ÿ̨���������������ʱ��
    backTrace(1);
    writeFile();
}


