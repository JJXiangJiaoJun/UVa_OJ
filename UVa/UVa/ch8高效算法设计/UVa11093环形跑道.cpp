#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 1000;
int p[maxn];
int q[maxn];
int ans;
int T;
int N;

int solve()
{
	int sta = 1;
	int gas = 0;
	while (sta <= N)
	{
		int step = 0;
		bool is_ok = true;
		gas = 0;
		for (int i = sta; step<N; i = (i + 1) % N)
		{
			step++;
			gas += p[i] - q[i];
			if (gas < 0) {
				//如果所有点都走过了,那么表示没有解
				if (i < sta||i==N)
					return 0;
				else
				{
					sta = i + 1;
					is_ok = false;
					break;
				}
			}
			
		}
		if (is_ok) return sta;
	}	
	return 0;
}

int main()
{
	int kcase = 1;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &p[i]);
		for (int i = 1; i <= N; i++)
			scanf("%d", &q[i]);
		int ans = solve();
		if (ans) printf("Case %d: Possible from station %d\n",kcase++, ans);
		else printf("Case %d: Not possible\n", kcase++);
	}
	
	
	return 0;
}