#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;


const int INF = 1000;
const int maxn = 128 + 2;
const int maxm = 11 + 1;
int n, m, st[maxn], cnt[1 << maxm][1 << maxm], d[1 << maxm][1 << maxm];



int dp(int s, int a) {
	if (cnt[s][a] == 1) return 0;
	if (cnt[s][a] == 0) return INF;

	//记忆化搜索
	int &ans = d[s][a];
	if (ans != -1) return ans;
	ans = INF;

	for (int k = 0; k < m; k++) {
		if ((s&(1 << k)) == 0)
		{
			ans = min(ans, max(dp(s | (1 << k), a | (1 << k)), dp(s | (1 << k), a)) + 1);
		}
	}
	return ans;
}

int main() {
	while (scanf("%d%d", &m, &n) == 2 && m&&n) {
		char s[100];
		int code;
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			code = 0;
			for (int j = 0; j < m; j++)
			{
				if (s[m - j - 1] == '1')
					code |= (1 << j);
			}
			st[i] = code;
		}

		memset(cnt, 0, sizeof(cnt));
		//预处理cnt数组
		for(int s=0;s<(1<<m);s++)
			for (int i = 0; i < n; i++)
			{
				cnt[s][s&st[i]]++;
			}
		memset(d, -1, sizeof(d));
		printf("%d\n", dp(0, 0));
	}

}