#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 50 + 5;
const int INF = 100000000;

int n;
int x[maxn], y[maxn];
double d[maxn][maxn];

//叉积求三角形面积
double area(int a, int b, int c)
{
	double s = (double)(1.0 / 2)*(x[a] * y[b] + x[b] * y[c] + x[c] * y[a] - x[a] * y[c] - x[b] * y[a] - x[c] * y[b]);
	if (s < 0) return -s;
	return s;
}

//判断三角形内部是否有点（分割线是否为对角线)
bool check(int a, int b, int c)
{
	int i;
	for (i = 1; i <= n; i++)
	{
		if (i == a || i == b || i == c) continue;
		double d = area(a, b, i) + area(a, c, i) + area(b, c, i) - area(a, b, c);
		if (d < 0) d = -d;
		if (d <= 0.01) return false;

	}
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d%d", &x[i], &y[i]);
		}

		for (int i = n; i >= 1; i--)
		{
			d[i][i + 1] = 0;
			for (int j = i + 2; j <= n; j++)
			{
				d[i][j] = INF;
				for (int k = i + 1; k < j; k++)
				{
					if (check(i, j, k))
						d[i][j] = min(d[i][j], max(max(area(i, j, k), d[i][k]), d[k][j]));
				}
			}
		}
		printf("%.1lf\n", d[1][n]);
	}
	
	return 0;
}