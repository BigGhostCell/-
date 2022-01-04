#include<iostream>

using namespace std;

int q(int n, int m)
{
	if(n == 1)
	{
		return 1;
	}
	else if(m == 1)
	{
		return 1;
	}
	else if(n == m)
	{
		return q(n,n-1) + 1;
	}
	else if(n > m)
	{
		return q(n - m, m) + q(n, m - 1);
	}
	else if(n < m)
	{
		return q(n, n);
	}
}

int main()
{
	cout << "input the integer which you want to divide: ";
	int m;
	cin >> m;
	cout << "the numbers of division: " << q(m, m);
		
}
