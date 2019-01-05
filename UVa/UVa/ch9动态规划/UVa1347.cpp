#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1000 + 5;


double dp[maxn][maxn];
double x[maxn];
double y[maxn];


double dist(int a, int b) {
	double dx = x[a] - x[b];
	double dy = y[a] - y[b];

	double  distance = pow(dx,2)+pow(dy,2);
	return sqrt(distance);
}

int n;

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 1; i <= n; i++) {
			scanf("%lf%lf", &x[i], &y[i]);
		}
		memset(dp, 0, sizeof(dp));

		for (int j = 1; j < n - 1; j++) {
			dp[n - 1][j] = dist(n, n - 1) + dist(n, j);
		}

		for(int i = n-2;i>=2;i--)
			for (int j = i - 1; j >= 1; j--) {

				dp[i][j] = min(dp[i + 1][i] + dist(j, i + 1), dp[i + 1][j] + dist(i, i + 1));
			}

		double ans = dp[2][1] + dist(1, 2);

		printf("%.2lf\n", ans);


	}
	
	return 0;
}