#include<cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100, maxm = 63;
int k;
long long n, dp[maxn+5][maxm+5];

int main()
{
	memset(dp, 0, sizeof(dp));
	for(int i=1;i<maxn+3;i++)
		for (int j = 1; j < maxm+3; j++)
		{
			dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;
		}
	int t = 0;
	while (scanf("%d%lld", &k,&n) && k)
	{
		for(t =1; t <=maxm; t++)
			if (dp[k][t] >= n)
			{
				printf("%d\n", t);
				break;
			}
		if (t > maxm) printf("More than 63 trials needed.\n");
	}
	
	
	return 0;
}