
#include<cstring>
#include<cstdio>
#include<iostream>
#include<climits>
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>

using namespace std;
const int maxn = 100 + 15;
const int maxm = 3000 + 10;

//dp[i][j]数组中保存 使用i根火柴，摆出的 %m=j的最大数

char dp[maxn][maxm][80],s[80],ans[80];
int p[maxn][maxm];

int n, m;

const int needs[] = { 6,2,5,5,4,5,6,3,7,6, };


int compare(char *a, char *b) {
	int la = strlen(a), lb = strlen(b);
	if (la>lb) return 1;
	else if (la<lb) return -1;
	return strcmp(a, b);
}


void DP(char *a, char *b, int k)
{
	strcpy(s, b);
	int l = strlen(s);
	if (l == 1 && s[0] == '0')
	{
		s[l - 1] = '0' + k;
		s[l] = 0;
	}
	else
	{
		s[l] = '0' + k;
		s[l + 1] = 0;
	}

	if (compare(s, a)>0) strcpy(a, s);
}



int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	int kcase = 0;
	while (scanf("%d", &n)==1&&n)
	{
		scanf("%d", &m);
		memset(dp, 0, sizeof(dp));
		dp[0][0][0] = '0';
		for(int i=0;i<=n;i++)
			for (int j = 0; j < m; j++)
				//采用刷表法
			{
					if (strlen(dp[i][j]) > 0)
					{
						for (int d = 0; d <= 9; d++)
							DP(dp[i + needs[d]][(j * 10 + d) % m], dp[i][j], d);
					}
			}
		ans[0] = 0;
		for (int i = n; i > 0; i--)  if (compare(ans, dp[i][0]) < 0) strcpy(ans, dp[i][0]);
		printf("Case %d: ", ++kcase);
		if (ans[0] == 0) printf("-1\n");
		else printf("%s\n", ans);

	}
	return 0;
}