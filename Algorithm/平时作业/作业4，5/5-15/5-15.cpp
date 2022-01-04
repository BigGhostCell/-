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
    if (level == n + 1)//走到叶子节点
    {
        bestTime = min(timeGet(), bestTime);
        return;
    }

    for (int i = 1; i <= k; i++)
    {
        mech[i] += t[level];//一直往一台机器里加任务
        if (mech[i] < bestTime)//当前调度时间仍然最小于最优，可以继续向下
            backTrace(level + 1);
        mech[i] -= t[level];//撤销做法
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
    mech.resize(k + 1);//每台机器完成任务所需时间
    backTrace(1);
    writeFile();
}


