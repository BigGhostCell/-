#include<fstream>
#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;

void readFile(vector<int>& len, vector<double>& p)
{
    fstream in;
    in.open("input.txt", ios::in);
    if (!in)
    {
        return;
    }
    string temp;
    getline(in, temp);
    int n = stoi(temp);
    
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

double minTime(vector<int> len, vector<double> p)
{
    vector<double> result(len.size(), 0);
    computeP(p);//¼ÆËã¸ÅÂÊ
    result = computePL(len, p);
    sort(result.begin(), result.end());//Ì°ÐÄ
    double mint = 0;
    for (int i = 0; i < result.size(); i++)
    {
        mint = result[i] * (result.size() - i) + mint;
    }
    
    return mint;

}

void writeFile(double mint)
{
    fstream in;
    in.open("output.txt", ios::out);
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

