#include <iostream>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

void readFile(int &N, int &k , int &A, int &B, int &C, vector<vector<int>> &map)
{
    fstream fin;
    fin.open("input.txt", ios::in);
    if (!fin)
    {
        cout << "open failed!" << endl;
        exit(0);
    }
    string temp;
    getline(fin, temp, ' ');
    N = stoi(temp);
    getline(fin, temp, ' ');
    k = stoi(temp);
    getline(fin, temp, ' ');
    A = stoi(temp);
    getline(fin, temp, ' ');
    B = stoi(temp);
    getline(fin, temp);
    C = stoi(temp);

    map.resize(N+1);
    for(int i = 0; i < N+1; i++)
        map[i].resize(N+1);

    int line = 1;
    while (!fin.eof())
    {
        for (int i = 1; i < N; i++)//ע���Ǵ�map[1][1]��ʼ���
        {
            getline(fin, temp, ' ');
            map[line][i] = stoi(temp);
        }
        getline(fin, temp);
        map[line][N] = stoi(temp);
        line++;
    }
    fin.close();
}

void outFile(int result)
{
    fstream fin;
    fin.open("output.txt", ios::out);
    fin << result;
    fin.close();
}
int dnya(int N, int K, int A, int B, int C, vector<vector<int>> map)
{
    vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(N + 1, vector<int>(3, 0)));//��ʼ��һ����СΪn*n*3����ά����
    int s[4][3] = { {-1,0,0},{0,-1,0},{1,0,B},{0,1,B} };//4�����򣬵����������Ǽ۸�B 
    
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        {
            dp[i][j][0] = 99999; 
            dp[i][j][1] = K;
        }//��ʼ�� 
    dp[1][1][0] = 0; 
    dp[1][1][1] = K;//��ʼ��
    
    for (int x = 1; x <= N; ++x)
    {
        for (int y = 1; y <= N; ++y)
        {
            if (x == 1 && y == 1) //��Ϊ��㣬ֱ����������������ʼ��
                continue;
            int minmoney = 999999;
            int minstep;//minmoney�洢��x,y���ϸ�λ�õ���Сmoney 
            int tmpmoney, tmpstep;

            for (int i = 0; i <= 3; ++i)//������һ��λ�õ����п������ 
            {
                if (x + s[i][0]<1 || x + s[i][0]>N || y + s[i][1]<1 || y + s[i][1]>N) //�����߽磬��������
                    continue; 
                tmpmoney = dp[x + s[i][0]][y + s[i][1]][0] + s[i][2];//������ʽд
                tmpstep = dp[x + s[i][0]][y + s[i][1]][1] - 1;
                if (map[x][y] == 1) //����վ
                { 
                    tmpmoney += A; 
                    tmpstep = K; 
                } 
                if (map[x][y] == 0 && tmpstep == 0 && (x != N || y != N)) //û����
                {
                    tmpmoney += A + C; 
                    tmpstep = K; 
                }  
                if (minmoney > tmpmoney)//������Сֵ 
                {
                    minmoney = tmpmoney;
                    minstep = tmpstep;
                }
            }
            if (dp[x][y][0] > minmoney)//����dp 
            {
                dp[x][y][0] = minmoney;
                dp[x][y][1] = minstep;
            }
        }
    }
        
    return dp[N][N][0];
}

int main()
{
    int N, K, A, B, C;//N��ʾ�������k��ʾһͰ�����߶�Զ��A��ʾ���ͷ��ã�B��ʾ���˷��ã� C��ʾ�����Ϳ����
    vector<vector<int>> map;
    readFile(N, K, A, B, C, map);
    int result = dnya(N, K, A, B, C, map);
    outFile(result);
}


