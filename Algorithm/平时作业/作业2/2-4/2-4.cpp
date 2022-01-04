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
		{
			break;
		}
		n = temp + n * 10;
	}

	fin.close();
	return n;
}

int halfSet(int num)
{
	int count = 1;
	if (num == 1)
		return 1;
	for (int i = 1; i <= num / 2; i++)
	{
		count = count + halfSet(i);
		if ((i / 10) * 2 <= (i % 10) && (i > 10))
			count -= halfSet(i / 10);
	}
	return count;
}

int main()
{
	int n = getn();
	n = halfSet(n);
	fstream fout;
	fout.open("output.txt", ios::out);
	fout << n;
	fout.close();
}

