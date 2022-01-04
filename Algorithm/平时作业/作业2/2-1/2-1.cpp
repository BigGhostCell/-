#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

void split(int a[], int orrl,int orrr, int &r, int &l)
{
	int midnum = (orrr- orrl) / 2  + orrl;
	int mid = a[midnum];//找到中位数,如果是偶数取到左边那个
	for (l = midnum - 1; l > orrl; l--)
	{
		if (a[l] != mid)//当左边的位数不为中位数
		{
			l = l + 1;
			break;
		}
			
	}
	for (r = midnum + 1; r < orrr; r++)
	{
		if (a[r] > mid)
			break;
	}
}

void getMaxnum(int a[], int &num, int &maxnum, int l, int r)
{
	int newl=0, newr = 0;
	split(a, l, r, newr, newl);
	if (newr - newl > maxnum)//此时的中位数是计数最多的
	{
		maxnum = newr - newl;
		num = a[(r - l) / 2 + l];
	}
	
	if (newl + 1 > maxnum)
	{
		getMaxnum(a, num, maxnum, 0, newl);
	}
	if (r - newr + 1 > maxnum)
	{
		getMaxnum(a, num, maxnum, newr, r);
	}
}


int main()
{
	fstream fin;
	fin.open("input.txt", ios::in);
	if (!fin)
	{
		cout << "can't open it!" << endl;
		return 0;
	}
	int i = 0;
	string s;
	getline(fin, s);
	int size = atoi(s.c_str());
	int *a = new int[size+1];

	int num = 0;//num为众数
	int maxnum = 0;//maxnum为重数
	
	while (fin)
	{
		getline(fin,s);
		a[i] = 	atoi(s.c_str());
		i++;
	}
	fin.close();

	sort(a, a+size);//升序排序
	getMaxnum(a, num, maxnum, 0, size - 1);

	fstream fout;
	fout.open("output.txt", ios::out);
	
	fout << num <<  endl << maxnum ;
	fout.close();
}

