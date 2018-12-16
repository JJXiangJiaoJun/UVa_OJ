#include<cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define INF  0x3f3f3f3f



const int maxn = 100+20;
const int maxt = 300;
int N, T,M1,M2;
int t[maxn];
int d[maxn];
int e[maxn];

int has_train[maxt][maxn][3];

int dp[maxt][maxn];


int solve() {

	dp[T][N] = 0;
	
	for (int i = 1; i <= M1; i++)
	{
		int time = d[i];
		for (int j = 1; j <= N; j++) { time += t[j-1];  has_train[time][j][0] = 1; }
	}

	for (int i = 1; i <= M2; i++)
	{
		int time = e[i];
		for (int j = N; j >= 1; j--) { time += t[j]; has_train[time][j][1] = 1; }
	}

	//动态规划
	for(int i = T-1;i>=0;i--)
		for (int j = 1; j <= N; j++) {
			//等待一分钟
			dp[i][j] = dp[i + 1][j] + 1;
			//考虑上左边来的车
			if (j < N && has_train[i][j][0]&&(i+t[j]<=T)) dp[i][j] = min(dp[i][j], dp[i + t[j]][j + 1]);
			//考虑上右边来的车
			if(j > 1 && has_train[i][j][1]&&(i+t[j-1]<=T)) dp[i][j] = min(dp[i][j], dp[i + t[j-1]][j - 1]);
		}




	//printf("dp [0 ][1] = %d\n", dp[0][1]);

	//输出答案
	return dp[0][1];

}


int main()
{
	int kcase = 1;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	
	while (scanf("%d",&N)==1&&N)
	{
		//终止输入
		scanf("%d", &T);

		memset(t, 0, sizeof(t));
		memset(has_train, 0, sizeof(has_train));
		memset(dp, INF, sizeof(dp));

		for (int i = 1; i <N; i++)
			scanf("%d", &t[i]);

		scanf("%d", &M1);
		for (int i = 1; i <= M1; i++)
			scanf("%d", &d[i]);
		scanf("%d", &M2);
		for (int i = 1; i <= M2; i++)
			scanf("%d", &e[i]);

		int ans = solve();
		printf("Case Number %d: ", kcase++);
		if (ans >= INF) printf("impossible\n");
		else printf("%d\n", ans);

	}
	
	return 0;
}