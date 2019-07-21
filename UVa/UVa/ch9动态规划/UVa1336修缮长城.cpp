#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1000+10;
const int maxv = 100+10;
const int maxx = 500000 + 500;
const int LEFT = 0, RIGHT = 1;
const double INF = 1e30;

int n, v, x;
int start_index;
int vis[maxn][maxn][2];
int kcase = 0;

struct Point {
	int point;
	double c;
	double d;

	bool operator < (const Point &rhs) const
	{
		return point < rhs.point;
	}

};

Point p[maxn];
double sum_d[maxn];

double dp[maxn][maxn][3];

//
//当前区间为 （l，r）  出发点为start，目标点为target
double cost(int l, int r, int start, int target)
{
	double c = 0.0;
	double sumd = sum_d[n] - (sum_d[r] - sum_d[l] + p[l].d);
	int dist = abs(p[start].point - p[target].point);
	double tm = (double)dist / (double)v;
	c = sumd*tm;
	return c;

}


double dfs(int l, int r, int k)
{
	if (l == 0 && r == n) return 0;
	double &ans = dp[l][r][k];
	if (vis[l][r][k] == kcase) return ans;
	vis[l][r][k] = kcase;
	ans = INF;

	int start = (k == LEFT) ? l : r;

	//向左走
	if (l > 0)
	{
		ans = min(ans, dfs(l - 1, r, LEFT) + cost(l, r, start, l - 1));
	}
	//向右走
	if (r < n)
	{
		ans = min(ans, dfs(l, r + 1, RIGHT) + cost(l, r, start, r + 1));
	}
	return ans;

}




int main()
{
	memset(vis, 0, sizeof(vis));
	while (scanf("%d%d%d",&n,&v,&x)==3&&n)
	{
		kcase++;
		//把起点标志为第一个需要修缮的点
		p[0].point = x;
		p[0].c = 0;
		p[0].d = 0;
		double sum_c = 0.0;
		for (int i = 1; i < n+1; i++)
		{
			scanf("%d%lf%lf", &p[i].point, &p[i].c, &p[i].d);
			sum_c += p[i].c;
		}

		//对区间进行排序
		sort(p, p + n + 1);
		//下面预处理出前缀和
		//memset(sum_d, 0, sizeof(sum_d));
		sum_d[0] = p[0].d;
		for (int i = 1; i < n+1; i++)
		{
			sum_d[i] = sum_d[i - 1] + p[i].d;
		}
		//首先找到起点
		for (int i = 0; i < n + 1; i++)
		{
			if (p[i].point == x) { start_index = i; break; }
		}

		printf("%.0f\n", floor(dfs(start_index, start_index, LEFT) + (double)sum_c));

	}
	
	return 0;
}


//递推法

//#include<bits/stdc++.h>
//#define maxn 1010
//#define INF 0X3F3F3F3F
//using namespace std;
//
//int n;
//double v, x;
//double sum[maxn];
//double dp[maxn][maxn][2];
//
//struct pt
//{
//	double x, c, d;
//	bool operator < (const pt& rhs)const
//	{
//		return x<rhs.x;
//	}
//}PT[maxn];
//
//inline double cost(int l, int r)
//{
//	return sum[n] - sum[r] + sum[l - 1];
//}
//
//int main()
//{
//	while (scanf("%d %lf %lf", &n, &v, &x) == 3 && n)
//	{
//		for (int i = 1; i <= n; i++)
//			scanf("%lf %lf %lf", &PT[i].x, &PT[i].c, &PT[i].d);
//		n++;
//		PT[n].x = x; PT[n].c = PT[n].d = 0;
//		sort(PT + 1, PT + 1 + n);
//		for (int i = 1; i <= n; i++)
//			sum[i] = sum[i - 1] + PT[i].d;
//		for (int i = 1; i <= n; i++)
//			for (int j = i; j <= n; j++)
//				dp[i][j][0] = dp[i][j][1] = INF;
//		for (int i = 1; i <= n; i++)
//			if (PT[i].x == x)
//			{
//				dp[i][i][0] = dp[i][i][1] = 0;
//				break;
//			}
//		for (int i = 1; i <= n; i++)
//			for (int j = 1; j + i - 1 <= n; j++)
//			{
//				int l = j;
//				int r = j + i - 1;
//				if (l >= 2)
//				{
//					double t = (PT[l].x - PT[l - 1].x) / v;
//					dp[l - 1][r][0] = min(dp[l - 1][r][0], dp[l][r][0] + cost(l, r)*t + PT[l - 1].c);
//					t = (PT[r].x - PT[l - 1].x) / v;
//					dp[l - 1][r][0] = min(dp[l - 1][r][0], dp[l][r][1] + cost(l, r)*t + PT[l - 1].c);
//				}
//				if (r<n)
//				{
//					double t = (PT[r + 1].x - PT[r].x) / v;
//					dp[l][r + 1][1] = min(dp[l][r + 1][1], dp[l][r][1] + cost(l, r)*t + PT[r + 1].c);
//					t = (PT[r + 1].x - PT[l].x) / v;
//					dp[l][r + 1][1] = min(dp[l][r + 1][1], dp[l][r][0] + cost(l, r)*t + PT[r + 1].c);
//				}
//			}
//		printf("%.lf\n", floor(min(dp[1][n][0], dp[1][n][1])));
//	}
//	return 0;
//}

