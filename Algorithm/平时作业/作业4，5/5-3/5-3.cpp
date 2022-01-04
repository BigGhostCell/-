#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
int n = 0;
int k = 0;
int d = 0;//��ͼ۸�
int minW = INT_MAX;//��������
vector<int> result;
vector<vector<int>> w;//�ӹ�Ӧ��j�����ò���i������
vector<vector<int>> c;//�ӹ�Ӧ��j�����ò���i�ļ۸�

//0-n�Ĳ���ÿ������Ҫ��ֻ�ܷ���һ��

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
    in.close();
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
    in.open("output.txt", ios::out);
   in << minW << "\n";
    for (int i = 0; i < n; i++)
        in << result[i] << " ";
    in.close();
}

int main()
{
    readFile();
    vector<int> visited (n, 0);//����·��
    backTrace(0,0,0, visited);
    writeFile();
}


