//�ȼ�Ϊ�����������̰�Ľⷨ

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
    cout << "����ʻ����Ϊnkm��" << n << endl;
    cout << "����վ����Ϊ" << k << endl;
    for(int i = 0; i < k + 1; i++)
        cout << "����վ" << i << "��" << i+1 <<"֮�����Ϊ" << dis[i] << endl;*/ 
}

int getGas(int n,int k, vector<int> dis)
{
    int cnt = 0;
    int sum = 0;
    //cout <<  "ͣ��վ������Ϊbegin  ";
    int i = 0;
    while(i < k + 1)
    {
        if (sum >= n)
        {
            if (sum > n)//����
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
    //cout << endl << "���ټ��ʹ���" << cnt;
    writeFile(cnt);


}

