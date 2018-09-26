#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 30 + 10;

int T;
int K,A, B;

LL c(LL k)
{
	return (k == 0)?1 : 3 * c(k - 1);
}


LL g(LL k, LL i)
{
	if (i <= 0)
		return 0;
	if (k == 0)
		return 1;
	int k2 = 1 << (k - 1);
	if (i >= k2)
		return 2 * g(k - 1, i - k2) + c(k - 1);
	else
		return g(k - 1, i);
}

LL solve()
{
	LL ans = g(K, A) - g(K, B - 1);
	return ans;
}

int main()
{
	int kcase = 1;
	scanf("%d", &T);
	LL ans;
	while (T--)
	{
		scanf("%d%d%d", &K, &A, &B);
		int k = 1 << K;
		A = k - A + 1;
		B = k - B + 1;
		ans = solve();
		printf("Case %d: %lld\n", kcase++, ans);
	}
	
	return 0;
}