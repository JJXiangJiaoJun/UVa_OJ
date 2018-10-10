#include<cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 1000;
int item[maxn];
int N;
int num;
int maxl;
int solve()
{
	if (num == 1) return 1;
	sort(item, item + num);
	int ans = 0;
	int i = 0;
	int j = num - 1;
	while (i <j)
	{
	
		while ((item[j] + item[i]) > maxl&&(i < j)) { j--; ans++; }
		i++; j--; ans++;

	}
	if (i == j) ans++;
	return ans;
}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &N);
	while (N--)
	{
		scanf("%d%d", &num,&maxl);
		for (int i = 0; i < num; i++)
			scanf("%d", &item[i]);


		int ans = solve();
		printf("%d\n", ans);
		if (N > 0)
			printf("\n");
	}
	return 0;
}