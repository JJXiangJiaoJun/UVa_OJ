#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;
#define INF 1000000000
const int maxs = 8;
const int maxm = 20 + 2;
const int maxn = 100 + 20+5;
int m, n, s;
int c[maxn];
int st[maxn];
int d[maxn][1 << maxs][1 << maxs];


int dp(int i, int s0, int s1, int s2) {
	if (i == m + n) return s2 == (1 << s) - 1 ? 0 : INF;
	int& ans = d[i][s1][s2];
	if (ans >= 0) return ans;

	ans = INF;
	if (i >= m) ans = dp(i + 1, s0, s1, s2); // 不选

											 // 选
	int m0 = st[i] & s0, m1 = st[i] & s1;
	s0 ^= m0;
	s1 = (s1 ^ m1) | m0;
	s2 |= m1;
	ans = min(ans, c[i] + dp(i + 1, s0, s1, s2));
	return ans;
}

int main()
{
	while (scanf("%d%d%d", &s, &m, &n) == 3 && n && m && s)
	{
		memset(d, -1, sizeof(d));
		memset(c, 0, sizeof(c));
		memset(st, 0, sizeof(st));
		for (int i = 0; i < m + n; i++)
		{
			scanf("%d", &c[i]);
			int t = 0;
			char ch;
			while (scanf("%c", &ch)) {
				if (ch == '\n')
					break;
				if (ch >= '1'&&ch <= '9')
				{
					st[i] |= 1 << ((ch - '0') - 1);
				}

			}
		}
		printf("%d\n", dp(0, (1 << s) - 1, 0, 0));
	}
	
	return 0;
}