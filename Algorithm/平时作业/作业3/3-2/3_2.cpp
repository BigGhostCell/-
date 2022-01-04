#include<fstream>
#include<iostream>
#include<string>
#include<vector> 
using namespace std;

void readFile(int& n, int& S, vector<int>& fee, vector<int>& time)//读文件
{

	fstream fin;
	fin.open("input.txt", ios::in);
	if (!fin)
	{
		cout << "wrong!!/a can't open it…" << endl;
		exit(0);
	}
	int lines = 1;
	while (!fin.eof())
	{
		string temp;
		if (lines == 1)//第一行是总事件数量
		{
			getline(fin, temp);
			n = stoi(temp);
			lines++;
		}
		else if (lines == 2)//启动时间
		{
			getline(fin, temp);
			S = stoi(temp);
			lines++;
		}
		else
		{
			getline(fin, temp, ' ');
			time.push_back(stoi(temp));
			getline(fin, temp);
			fee.push_back(stoi(temp));
		}
	}
	fin.close();
}

void outFile(int result)//输出
{
	fstream fin;
	fin.open("output.txt", ios::out);
	if (!fin)
	{
		cout << "wrong!!/a can't open it…" << endl;
		exit(0);
	}
	fin << result;
	fin.close();
}

int dyna(int n, int S, vector<int> time, vector<int> fee)
{
	vector<int> z(n+1, 999999);
	vector<int> st(n+1, 0);
	vector<int> sw(n+1, 0);

	for (int i = n - 1; i >= 0; i--)
	{
		st[i] = st[i + 1] + time[i];
		sw[i] = sw[i + 1] + fee[i];
	}
	z[n] = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = i + 1; j <= n; j++)
		{
			z[i] = min(z[i], z[j] + sw[i] * (S + st[i] - st[j]));
		}
	}
	return z[0];
}

int main()
{
	int n, S;
	vector<int> fee;
	vector<int> time;
	readFile(n, S, fee, time);
	int result = dyna(n, S, time, fee);
	outFile(result);
}
