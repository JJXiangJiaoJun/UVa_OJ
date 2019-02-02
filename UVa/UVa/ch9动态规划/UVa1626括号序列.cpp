#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100 + 10;
int dp[maxn][maxn];
char s[maxn];

bool match(char i, char j)
{
	return (i == '('&&j == ')' )|| (i == '['&&j == ']') ? true : false;
}

void print(int i, int j)
{
	if (i > j) return;
	if (i == j)
	{
		if (s[i] == '(' || s[i] == ')') printf("()");
		else printf("[]");
		return;
	}

	int ans = dp[i][j];
	if (match(s[i], s[j]) && ans == dp[i + 1][j - 1])
	{
		printf("%c", s[i]); print(i + 1, j - 1); printf("%c", s[j]);
		return;
	}

	for (int k = i; k < j; k++)
	{
		if (ans == dp[i][k] + dp[k + 1][j])
		{
			print(i, k);
			print(k + 1, j);
			return;
		}
	}
}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	getchar();
	while (n--)
	{
		memset(dp, 0, sizeof(dp));
		getchar();
		fgets(s, maxn, stdin);
		
		//dynamic programing
		int len = strlen(s)-1;

	
		for (int i = 0; i < len; i++)
		{
			dp[i + 1][i] = 0;
			dp[i][i] = 1;
		}
		for(int i=len-2;i>=0;i--)
			for (int j = i + 1; j < len; j++)
			{
				dp[i][j] = len;
				if (match(s[i], s[j])) dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
				for (int k = i; k < j; k++)
					dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}
		print(0, len-1);
		printf("\n");
		if (n)
			printf("\n");
	}
	
	return 0;
}
