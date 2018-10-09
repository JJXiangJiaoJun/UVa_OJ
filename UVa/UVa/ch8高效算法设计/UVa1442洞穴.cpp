#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 10000000 + 1000;
int p[maxn];
int s[maxn];

int fuel[maxn];
//左端最大值
int h1[maxn];
//右端最大值
int h2[maxn];
int n;

int solve()
{
	//h1[0] = maxp;
	//int maxleft = 0;
	int level = s[0];
	for (int i = 0; i < n; i++) {
		if (s[i] < level) level = s[i];
		if (p[i] > level) level = p[i];
		h1[i] = level;
	}

	level = s[n - 1];

	for (int i = n - 1; i >= 0; i--) {
		if (s[i] < level) level = s[i];
		if (p[i] > level) level = p[i];
		h2[i] = level;
	}

	int height,sum;
	sum = 0;
	//先不考虑天花板对整个数组扫描
	for (int i = 0; i < n; i++)
	{
		height = min(h1[i], h2[i]);
			sum += height - p[i];
	}

	return sum;
}

int main()
{
	int Z;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &Z);
	while (Z--)
	{
		scanf("%d", &n);

		for (int i = 0; i < n; i++)
		{
			scanf("%d", &p[i]);
		}
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &s[i]);
		}
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}
