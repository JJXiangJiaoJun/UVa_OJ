#include<cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long LL;
const int maxn = 500 + 100;
int book[maxn];
LL tot;
int N;
int k, m;
int space[maxn];

int solve(LL maxp)
{
	LL done = 0;
	int ans = 1;

	for (int i = 0; i < m; i++)
	{
		if ((done + book[i]) > maxp)
		{
			done = book[i];
			ans++;
		}
		else
			done += book[i];
	}
	return ans;
}

void print(LL ans)
{
	LL done = 0;
	//从后往前贪心
	int remain = k;
	memset(space, 0, sizeof(space));
	for (int i = m - 1; i >= 0; i--)
	{
		if (done + book[i] > ans || i + 1 < remain)
		{
			done = book[i]; remain--; space[i] = 1;
		}
		else
		{
			done += book[i];
		}
	}
	for (int i = 0; i < m - 1; i++)
	{
		printf("%d ", book[i]);
		if (space[i]) printf("/ ");
	}
	printf("%d\n", book[m - 1]);
}
int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &N);
	int a;
	while (N--)
	{
		
		tot = 0;
		int maxp = 0;
		scanf("%d%d", &m, &k);
		for (int i = 0; i < m; i++)
		{
			scanf("%d", &book[i]);
			tot += (LL)book[i];
			maxp = max(maxp, book[i]);
		}
		LL L = maxp;
		LL R = tot;
		//while (L <= R)
		//{
		//	LL m = L + (R - L) / 2;
		//	if (solve(m) <= k) R = m - 1;
		//	else L = m + 1;
		//}
		//LL L = maxp;
		//LL R = tot+1;
		while (L < R)
		{
			LL m = L + (R - L) / 2;
			if (solve(m) <= k) R = m;
			else L = m + 1;
		}
		//printf("%lld\n", L);
		print(L);
	}
	return 0;
}