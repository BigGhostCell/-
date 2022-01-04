#include <iostream>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

string readFile()
{
    fstream fin;
    fin.open("input.txt", ios::in);
    if (!fin)
    {
        cout << "open failed!" << endl;
        exit(0);
    }
    string temp;
    getline (fin,temp); 
    fin.close();
    return temp;
}

void outFile(int result)
{
    fstream fin;
    fin.open("output.txt", ios::out);
    fin << result;
    fin.close();
}
int dnya(string S, int n)
{
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(3, 0)));//初始化一个大小为n*n*3的三维数组
    //dp[i][j][0]表示i-j端为a， dp[i][j][1]表示i-j端为b, dp[i][j][2]表示i-j端为c 的加括号总数
    for (int i = 0; i < n; i++)//初始化
    {
        if (S[i] == 'a') 
            dp[i][i][0] = 1;
        else 
            dp[i][i][0] = 0;
        if (S[i] == 'b') 
            dp[i][i][1] = 1;
        else 
            dp[i][i][1] = 0;
        if (S[i] == 'c') 
            dp[i][i][2] = 1;
        else 
            dp[i][i][2] = 0;
    }

    for (int r = 2; r <= n; r++)//接着从长度为 2 的子字符串计算，直至计算好整串 str
    {
        for (int i = 0; i <= n - r; i++)
        {
            int j = i + r - 1;//计算str[i:j]  
            for (int k = i; k < j; k++)
            {//根据题目中的表，计算加括号法
                dp[i][j][0] += dp[i][k][0] * dp[k + 1][j][2] + dp[i][k][1] * dp[k + 1][j][2] + dp[i][k][2] * dp[k + 1][j][0];
                dp[i][j][1] += dp[i][k][0] * dp[k + 1][j][0] + dp[i][k][0] * dp[k + 1][j][1] + dp[i][k][1] * dp[k + 1][j][1];
                dp[i][j][2] += dp[i][k][1] * dp[k + 1][j][0] + dp[i][k][2] * dp[k + 1][j][1] + dp[i][k][2] * dp[k + 1][j][2];
            }
        }
    }
    return dp[0][n - 1][0];


}

int main()
{
    string S = readFile();
    int n = S.size();
    int result = dnya(S,n);
    outFile(result);
}


