#include <iostream>
#include <fstream>
using namespace std;

int getn()
{
	fstream fin;
	fin.open("input.txt", ios::in);
	if (!fin)
	{
		cout << "can't open it!" << endl;
		return 0;
	}
	long n = 0;
	while (!fin.eof())
	{
		int temp = fin.get() - '0';
		if (temp < 0)
			break;
		n = temp + n * 10;
	}

	fin.close();
	return n;
}

long long F(long long n,long long m)
{
	if (m == 1)
		return 1;
	if (m == n)
		return 1;
	else
		return F(n - 1, m - 1) + F(n - 1, m )*m;
}

int main()
{
	int n = getn();
	long long sum = 0;
	for (int i = 1; i <= n; i++)
		sum = sum + F(n, i);
	fstream fout;
	fout.open("output.txt", ios::out);
	fout << sum;
	fout.close();
}

