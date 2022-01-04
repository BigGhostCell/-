#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

void split(int a[], int orrl,int orrr, int &r, int &l)
{
	int midnum = (orrr- orrl) / 2  + orrl;
	int mid = a[midnum];//�ҵ���λ��,�����ż��ȡ������Ǹ�
	for (l = midnum - 1; l > orrl; l--)
	{
		if (a[l] != mid)//����ߵ�λ����Ϊ��λ��
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
	if (newr - newl > maxnum)//��ʱ����λ���Ǽ�������
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

	int num = 0;//numΪ����
	int maxnum = 0;//maxnumΪ����
	
	while (fin)
	{
		getline(fin,s);
		a[i] = 	atoi(s.c_str());
		i++;
	}
	fin.close();

	sort(a, a+size);//��������
	getMaxnum(a, num, maxnum, 0, size - 1);

	fstream fout;
	fout.open("output.txt", ios::out);
	
	fout << num <<  endl << maxnum ;
	fout.close();
}

