#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define INF 0x3f3f3f3f
const int maxn = 5000 + 100;
int dp[maxn][maxn];
char A[maxn];
char B[maxn];
int start_A[30];
int end_A[30];
int start_B[30];
int end_B[30];
int cnt[maxn][maxn];
int len_A;
int len_B;

void preprocess()
{
	memset(start_A, INF, sizeof(start_A));
	memset(end_A, -1, sizeof(end_A));
	memset(start_B, INF, sizeof(start_B));
	memset(end_B, -1, sizeof(end_B));
	//memset(cnt, 0, sizeof(cnt));

	for (int i = 1; i <= len_A; i++) {
		A[i] = A[i] - 'A';
		//printf("%d  ", A[i]);
	}
	for (int i = 1; i <= len_B; i++) {
		B[i] = B[i] - 'A';
	}

	for (int i = 1; i <= len_A; i++) {
		start_A[A[i]] = min(start_A[A[i]], i);
		end_A[A[i]] = i;
	}

	for (int i = 1; i <= len_B; i++) {
		start_B[B[i]] = min(start_B[B[i]], i);
		end_B[B[i]] = i;
	}
	//cnt[0][0] = 0;
	for(int i=0;i<=len_A;i++)
		for (int j = 0; j <= len_B; j++) {
			if(i)
			{
				cnt[i][j] = cnt[i - 1][j];
				if (start_A[A[i]] == i&&start_B[A[i]] > j) cnt[i][j]++;
				if (end_A[A[i]] == i&&end_B[A[i]] <= j)cnt[i][j]--;

			}
			 if (j)
			{
				cnt[i][j] = cnt[i][j - 1];
				if (start_B[B[j]] == j&&start_A[B[j]] > i)cnt[i][j]++;
				if (end_B[B[j]] == j&&end_A[B[j]] <= i) cnt[i][j]--;
			}
		}

}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", A+1);
		scanf("%s", B+1);
		len_A = strlen(A+1);
		len_B = strlen(B+1);
		preprocess();
		
		for(int i=0;i<=len_A;i++)
			for (int j = 0; j <= len_B; j++) {		
				if (!i && !j) continue;
				dp[i][j] = INF;
				if (i) dp[i][j] = min(dp[i][j], dp[i - 1][j] + cnt[i - 1][j]);
				if (j) dp[i][j] = min(dp[i][j], dp[i][j - 1] + cnt[i][j - 1]);
			}
		
		printf("%d\n", dp[len_A][len_B]);
	}

	return 0;
}