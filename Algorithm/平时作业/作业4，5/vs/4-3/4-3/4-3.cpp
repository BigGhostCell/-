// 4-3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<fstream>
#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;

void readFile(vector<int>& len, vector<double>& p)
{
    fstream in;
    in.open("C:\\Users\\11732\\Desktop\\input.txt", ios::in);
    if (!in)
    {
        return;
    }
    string temp;
    getline(in, temp);
    int n = stoi(temp);
    cout << "程序数量为" << n << endl;
    len.resize(n);
    p.resize(n);
    int i = 0;
    while (!in.eof())
    {
        getline(in, temp, ' ');
        len[i] = stoi(temp);
        getline(in, temp);
        p[i] = stoi(temp);
        i++;
    }
    in.close();
}

void computeP(vector<double>& p)
{
    double sum = 0;
    for (int i = 0; i < p.size(); i++)
    {
        sum = sum + p[i];
    }
    for (int i = 0; i < p.size(); i++)
    {
        p[i] = p[i] / sum;
    }
}

vector<double> computePL(vector<int> len, vector<double> p)
{

    vector<double> temp(len.size(), 0);
    for (int i = 0; i < len.size(); i++)
    {
        temp[i] = len[i] * p[i];
    }
    return temp;
}

/*void myMerge(vector<double>& result, int begin, int mid, int end)
{
    vector<int> temp(result.size(), 0);
    int p1 = begin, p2 = mid + 1, p = 0;

    // 比较两个有序小数组的元素，依次放入大数组中
    while (p1 <= mid && p2 <= end)
    {
        if (result[p1] < result[p2])
            temp[p++] = result[p1++];
        else
              temp[p++] = result[p2++];
    }

    while (p1 <= mid)
        temp[p++] = result[p1++];
    while (p2 <= end)
        temp[p++] = result[p2++];

    for (int i = 0; i < temp.size(); i++)
        result[i + begin] = temp[i];
}

void mySort(vector<double>& result, int begin, int end)//归并排序
{
    if (end != begin)
    {
        int mid = (end + begin)/ 2;//前一段的end就是mi d
        mySort(result, begin, mid);
        mySort(result, mid + 1, end);
        myMerge(result, begin, mid, end);
    }

}*/

int minTime(vector<int> len, vector<double> p)
{
    vector<double> result(len.size(), 0);
    computeP(p);//计算概率
    result = computePL(len, p);
    sort(result.begin(), result.end());//贪心
    //mySort(result, 0, result.size() - 1);
    double mint = 0;
    for (int i = 0; i < result.size(); i++)
    {
        mint = result[i] * (result.size() - i) + mint;
    }
    cout << "最短时间为" << mint << endl;
    return mint;

}

void writeFile(double mint)
{
    fstream in;
    in.open("C:\\Users\\11732\\Desktop\\output.txt", ios::out);
    in << mint;
    in.close();
}

int main()
{
    vector<int> len;
    vector<double> p;
    readFile(len, p);
    double mint = minTime(len, p);
    writeFile(mint);
}
