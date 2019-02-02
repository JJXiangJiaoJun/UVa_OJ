#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define INF 0x3f3f3f3f
const int maxn = 50 + 10;
int dp[maxn][maxn];
int c[maxn];
int l;
int n;

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d", &l) == 1 && l)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &c[i]);
		}
		c[0] = 0;
		c[n + 1] = l;

		memset(dp, 0, sizeof(dp));

			for(int len=2;len<=n+1;len++)
				for (int i = 0; i+len <= n + 1; i++) {
					int j = len + i;
					dp[i][j] = INF;
					for (int k = i + 1; k < j; k++)
						dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + c[j] - c[i]);

				}
				
		
		printf("The minimum cutting is %d.\n", dp[0][n + 1]);
	}
	return 0;
}