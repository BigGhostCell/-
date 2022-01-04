#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
int n = 0;
int k = 0;
int d = 0;//最低价格
int minW = INT_MAX;//最轻重量
vector<int> result;
vector<vector<int>> w;//从供应商j处购得部件i的重量
vector<vector<int>> c;//从供应商j处购得部件i的价格

//0-n的部件每样都需要，只能访问一次

void testPrint()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cout << "部件" << i;
            cout << " 供应商" << j;
            cout << " 重量 " << w[i][j];
            cout << " 价格 " << c[i][j];
            cout << "\t";
        }
        cout << "\n";
    }
}

void readFile()
{
    fstream in;
    in.open("C:\\Users\\11732\\Desktop\\input.txt", ios::in);
    if (!in)
    {
        return;
    }
    
    string temp;
    getline(in, temp, ' ');
    n = stoi(temp);
    getline(in, temp, ' ');
    k = stoi(temp);
    getline(in, temp);
    d = stoi(temp);

    w.resize(n);
    c.resize(n);
    for (int i = 0; i < n; i++)
    {
        c[i].resize(k);
        for (int j = 0; j < k - 1; j++)
        {
            getline(in, temp, ' ');
            c[i][j] = stoi(temp);
        }
        getline(in, temp);
        c[i][k - 1] = stoi(temp);
    }
   

    for (int i = 0; i < n; i++)
    {
        w[i].resize(k);
        for (int j = 0; j < k - 1; j++)
        {
            getline(in, temp, ' ');
            w[i][j] = stoi(temp);
        }
        getline(in, temp);
        w[i][k - 1] = stoi(temp);
    }
    result.resize(n);
    testPrint();
    in.close();
}

void dpTrans()
{
    vector<vector<vector<int>>> dp ();
}

void backTrace(int money, int weight, int index, vector<int> &visited)
{
    if (index == n)
    {
        if (minW > weight)
        {
            minW = weight;
            result = visited;
        }
        minW = min(weight, minW);
        return;
    }

    for (int j = 0; j < k; j++)
    {
        if (money + c[index][j] <= d && weight < minW)
        {
            visited[index] = j + 1;
            backTrace(money + c[index][j], weight + w[index][j], index + 1, visited);
        }
    }
}

void writeFile()
{
    fstream in;
    in.open("C:\\Users\\11732\\Desktop\\output.txt", ios::out);
    if (!in)
    {
        cout << "error";
    }
   in << minW << "\n";
    for (int i = 0; i < n; i++)
        in << result[i] << " ";
    in.close();
}

int main()
{
    readFile();
    vector<int> visited (n, 0);//访问路径
    backTrace(0,0,0, visited);
    cout << minW << endl;
    for (int i = 0; i < n; i++)
        cout << result[i] << "  ";
    writeFile();
}

