//等价为跳数组问题的贪心解法

#include <iostream>
#include <fstream>
#include <vector>
#include<string>
using namespace std;

void readFile(int &n, int &k, vector<int> &dis)
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
    dis.resize(k + 1);
    for(int i = 0; i < k; i++)
    {
        getline(in, temp, ' ');
        dis[i] = stoi(temp);
    }
    getline(in, temp);
    dis[k] = stoi(temp);
    in.close();
    /*test
    cout << "可行驶距离为nkm：" << n << endl;
    cout << "加油站个数为" << k << endl;
    for(int i = 0; i < k + 1; i++)
        cout << "加油站" << i << "与" << i+1 <<"之间距离为" << dis[i] << endl;*/ 
}

int getGas(int n,int k, vector<int> dis)
{
    int cnt = 0;
    int sum = 0;
    //cout <<  "停靠站点依次为begin  ";
    int i = 0;
    while(i < k + 1)
    {
        if (sum >= n)
        {
            if (sum > n)//回退
            {
                sum = sum - dis[i];
            } 
            cnt++;
            sum = 0;
            //cout << i << "  ";
        }
        else
        {
            sum = sum + dis[i];
            if(sum <= n)
                i++;
        }
    }
    //cout << "end" << endl;
    return cnt;
}

void writeFile(int cnt)
{
    fstream in;
    in.open("output.txt", ios::out);
    in << cnt;
    in.close();
}

int main()
{
    int n = 0, k = 0;
    vector<int> dis;
    readFile(n, k, dis);
    int cnt = getGas(n, k, dis);
    //cout << endl << "最少加油次数" << cnt;
    writeFile(cnt);


}

