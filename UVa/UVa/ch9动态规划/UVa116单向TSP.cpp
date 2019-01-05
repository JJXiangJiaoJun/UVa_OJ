#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f

const int max_col = 100 + 100;
const int max_row = 10 + 20;
int dp[max_row][max_col];
int r, c;
int ans[max_row][max_col];
int path[max_row][max_col];

int root[max_col];


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d%d", &r, &c) == 2 && r) {
		memset(dp, 0, sizeof(dp));
		memset(path, 0, sizeof(path));

		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++)
				scanf("%d", &path[i][j]);

		for (int i = r; i >= 1; i--)
			dp[i][c] = path[i][c];

		for(int j=c-1;j>=1;j--)
			for (int i = 1; i <=r ; i++)
			{
				int p;
				int rows[3] = { i,i - 1,i + 1 };
				if (i == 1) rows[1] = r;
				if (i == r) rows[2] = 1;

				sort(rows, rows + 3);
				dp[i][j] = INF;
				for (int k = 0; k < 3; k++)
				{
					int v = path[i][j] + dp[rows[k]][j+1];
					if (v < dp[i][j]) { dp[i][j] = v; ans[i][j] = rows[k]; }
				}

			}

		int min_ans = INF;
		int min_idx = 0;
		for (int i = 1; i <= r; i++)
		{
			if (dp[i][1] < min_ans) {
				min_ans = dp[i][1];
				min_idx = i;
			}
		}
		for (int i = 1; i <= c; i++)
		{
			root[i] = min_idx;
			min_idx = ans[min_idx][i];
		}
		
		for (int i = 1; i < c; i++)
			printf("%d ", root[i]);
		printf("%d\n", root[c]);
		printf("%d\n", min_ans);

	}
	
	return 0;
}