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
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(3, 0)));//��ʼ��һ����СΪn*n*3����ά����
    //dp[i][j][0]��ʾi-j��Ϊa�� dp[i][j][1]��ʾi-j��Ϊb, dp[i][j][2]��ʾi-j��Ϊc �ļ���������
    for (int i = 0; i < n; i++)//��ʼ��
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

    for (int r = 2; r <= n; r++)//���Ŵӳ���Ϊ 2 �����ַ������㣬ֱ����������� str
    {
        for (int i = 0; i <= n - r; i++)
        {
            int j = i + r - 1;//����str[i:j]  
            for (int k = i; k < j; k++)
            {//������Ŀ�еı���������ŷ�
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


