#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;
const int maxn = 30 + 10;
int pancakes[maxn];
int sort_pancakes[maxn];
int cnt;
int len;

bool cmp(int a, int b)
{
	return a > b;
}

void solve() {
	memcpy(sort_pancakes, pancakes, sizeof(pancakes));
	sort(sort_pancakes+1, sort_pancakes + cnt, cmp);

	//for (int i = 1; i < cnt - 1; i++)
	//	printf("%d ", sort_pancakes[i]);
	//printf("%d\n", sort_pancakes[cnt - 1]);


 for(int index =1; index<cnt; index++)
	for (int i = 1; i < cnt; i++)
	{
		//找到当前排序最大值，将其换到最上边
		if (pancakes[i] == sort_pancakes[index])
		{
			
			//如果位置正确则不用移动
			if (i == cnt - index) continue;
			
			//如果不是在第一个则换到第一个
			if (i != 1) {
				//交换
				for (int j = 1; j <= i/2; j++)
				{
					int temp;
					temp = pancakes[j];
					pancakes[j] = pancakes[i - j + 1];
					pancakes[i - j + 1] = temp;
				}
				printf("%d ", cnt - i);
			}
			//将该点换到相应的位置
			int exchange = cnt - index;
			for (int j = 1; j <= exchange/2; j++)
			{
				int temp;
				temp = pancakes[j];
				pancakes[j] = pancakes[exchange - j + 1];
				pancakes[exchange - j + 1] = temp;
			}
			printf("%d ", index);

		}
	}
	printf("0\n");
}

int main()
{
	string str;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	//ifstream mycin("C:\\Users\\lenovo\\Desktop\\test\\in.txt");
	//cin.rdbuf(mycin.rdbuf());
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (getline(cin, str)) {
		stringstream ss(str);
		int num;
		cnt = 1;
		while (ss >> num) {
			pancakes[cnt++] = num;
		}
		len = cnt - 1;

		for (int i = 1; i < cnt - 1; i++)
			printf("%d ", pancakes[i]);
		printf("%d\n", pancakes[cnt - 1]);
		solve();

	}

	
	
	return 0;
}
