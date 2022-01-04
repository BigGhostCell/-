#include <iostream>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

void readFile(int& N, int& k, int& A, int& B, int& C, vector<vector<int>>& map)
{
    fstream fin;
    fin.open("C:\\Users\\11732\\Desktop\\input.txt", ios::in);
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

    map.resize(N + 1);
    for (int i = 0; i < N + 1; i++)
        map[i].resize(N + 1);

    int line = 1;
    while (!fin.eof())
    {
        for (int i = 1; i < N; i++)//注意是从map[1][1]开始存的
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
    fin.open("C:\\Users\\11732\\Desktop\\output.txt", ios::out);
    fin << result;
    fin.close();
}
int dnya(int N, int K, int A, int B, int C, vector<vector<int>> map)
{
    vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(N + 1, vector<int>(3, 0)));//初始化一个大小为n*n*3的三维数组
    int s[4][3] = { {-1,0,0},{0,-1,0},{1,0,B},{0,1,B} };//4个方向，第三个参数是价格B 
   
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        {
            dp[i][j][0] = 99999;
            dp[i][j][1] = K;
        }//初始化 
    dp[1][1][0] = 0;
    dp[1][1][1] = K;//初始化
    for (int x = 1; x <= N; ++x)
    {
        for (int y = 1; y <= N; ++y)
        {
            if (x == 1 && y == 1) //当为起点，直接跳过，已做过初始化
                continue;
            int minmoney = 999999;
            int minstep;//minmoney存储（x,y）上个位置的最小money 
            int tmpmoney, tmpstep;

            for (int i = 0; i <= 3; ++i)//遍历上一个位置的所有可能情况 
            {
                if (x + s[i][0]<1 || x + s[i][0]>N || y + s[i][1]<1 || y + s[i][1]>N) //超出边界，不做处理
                    continue;
                tmpmoney = dp[x + s[i][0]][y + s[i][1]][0] + s[i][2];//按递推式写
                tmpstep = dp[x + s[i][0]][y + s[i][1]][1] - 1;
                if (map[x][y] == 1) //遇油站
                {
                    tmpmoney += A;
                    tmpstep = K;
                }
                if (map[x][y] == 0 && tmpstep == 0 && (x != N || y != N)) //没油了
                {
                    tmpmoney += A + C;
                    tmpstep = K;
                }
                if (minmoney > tmpmoney)//更新最小值 
                {
                    minmoney = tmpmoney;
                    minstep = tmpstep;
                }
            }
            if (dp[x][y][0] > minmoney)//更新dp 
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
    int N, K, A, B, C;//N表示格点数，k表示一桶油能走多远，A表示加油费用，B表示倒退费用， C表示增设油库费用
    vector<vector<int>> map;
    readFile(N, K, A, B, C, map);
    int result = dnya(N, K, A, B, C, map);
    outFile(result);
}

