#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

int maxLen = 0;

int getNum(vector<int> &nums, int size)
{
    int sum = 0;
    srand((int)time(0));  // 产生随机种子
    for (int i = 1; i <= size; i++)
    {
        nums[i] = rand() % 100;
        sum = nums[i] + sum;
        cout << nums[i] << "  ";
    }
    cout << endl;
    cout << "总长度为" << sum << endl;
    return sum;
}

int hungry(vector<int> nums, int m)//贪心是无法解决的，无法得到最优解
{
    vector<bool> visited(nums.size(), false);
    int pre = 0;
    int temp = m;
    while (m != pre)
    {
        int maxNum = 0;
        int pos = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] < m && visited[i] == false) //每次都去选剩余长度里最长的,注意不能重选。。。。
            {
                if (nums[i] > maxNum)
                {
                    maxNum = nums[i];
                    pos = i;
                }
            }
        }
        pre = m;
        visited[pos] = true;
        m = m - maxNum;
        cout << maxNum << "  ";
    }
    cout << endl;
    return temp - m;
}

int updateQues(vector<int> nums, int m)
{
    int n = nums.size();
    //将二维优化为一维，因为i的变化只在相邻的两位
    //dp[m] = max (dp[m-nums[i]] + nums[i], dp[m]) m表示剩余容量
    vector<int> dp(m + 1, 0);
    for (int i = 1; i < n; i++)
    {
        for (int j = m; j > 0; j--)
        {
            if(nums[i] <= j)
                dp[j] = max(dp[j - nums[i]] + nums[i], dp[j]);
        }
    }
    return dp[m];
}

int bagQues(vector<int> nums, int m)//路径保存未写
{
    int n = nums.size();
    //转化为0-1背包问题，背包容量为sum/2——动态规划
    //dp[i][j] = dp[i-1][j-nums[i]] + nums[i]  dp[i][j]表示i件物品放入容量为j的背包的最大价值
    vector<vector<int>> dp(n, vector<int>(m+1, 0));
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j < nums[i])
                dp[i][j] = dp[i - 1][j];//装不下该长度的，所以相同
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - nums[i]] + nums[i]);//决定是否能得到最大价值
        }
    }
    return dp[n - 1][m];
}

void backTrace(vector<int> nums, int nowpos, int sum, int m)//m代表0-i中的最长长度
{
    int temp = maxLen;
    
    if (nowpos == nums.size() - 1)//或者nospos到末尾
    {
        maxLen = max(maxLen - nums[nowpos], sum);
        return;
    }

    if ((maxLen == m && m <= sum))//当maxLen不再变化，
    {
        maxLen = max(maxLen - nums[nowpos], sum);
        return;
    }

    for (int i = nowpos; i < nums.size(); i++)
    {
        backTrace(nums, i + 1, sum, temp);
    }
}

int main()
{
    int size = 0;
    cout << "请输入序列长度：";
    cin >> size;
    vector<int> nums(size+1, 0);
    int sum = getNum(nums, size);//得到长度为n的n个程序,总长度为sum
    cout << "A中长度为：" << bagQues(nums, sum / 2) << endl;
    cout << "A中长度为：" << hungry(nums, sum / 2) << endl;
    cout << "A中长度为：" << updateQues(nums, sum / 2) << endl; 
    backTrace(nums, 1, sum / 2, 0);
    cout << "A中长度为：" << maxLen << endl;
}

