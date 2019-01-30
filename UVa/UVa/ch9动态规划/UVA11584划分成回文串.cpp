#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
#define INF 0x3f3f3f3f
const int maxn = 1000 + 100;
int dp[maxn];
int p[maxn][maxn];
char ch[maxn];
int len;

void judge()
{
	
	for (int i = 1; i <= len; i++)
		p[i][i] = 1;
	for (int i = 1; i <= len - 1; i++)
		p[i][i + 1] = ch[i] == ch[i + 1] ? 1 : 0;

	for(int l=2;l<=len-1;l++)
		for (int i = 1; i <= len-l; i++)
		{
			p[i][i + l] = (p[i + 1][i + l - 1] && ch[i] == ch[i + l]) ? 1 : 0;
		}
}


int main()
{

	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	while (n--) {
		scanf("%s", ch+1);
		memset(dp, INF, sizeof(dp));
		memset(p, 0, sizeof(p));
		len = strlen(ch+1);
		//printf("len  = %d\n", len);
		judge();
		dp[0] = 0;
		/*for (int i = 1; i <= len; i++)
			for (int j = 1; j <= len; j++)
				printf("p[%d][%d] = %d  ", i, j, p[i][j]);*/
		//printf("\n");
		//dynamic programing
		for (int i = 1; i <= len; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (p[j + 1][i])
					dp[i] = min(dp[i], dp[j] + 1);
			}
		}
		printf("%d\n", dp[len]);
	}

	return 0;
}