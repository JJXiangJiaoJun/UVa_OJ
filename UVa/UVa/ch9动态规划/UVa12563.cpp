#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 180 * 50 + 5;

int n, max_t;
int t[50 + 5]; //每首歌曲的时间
struct Node
{
	int num; //总歌曲数
	int time;//歌总时间
	bool operator<(const Node &rhs)const//判断是否更优
	{
		return num<rhs.num || (num == rhs.num && time<rhs.time);
	}
}dp[maxn];

int main()
{
	int T;
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++)
	{
		printf("Case %d: ", kase);

		scanf("%d%d", &n, &max_t);
		memset(dp, 0, sizeof(dp));

		int sum = 0;//所有歌曲总时长
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &t[i]);
			sum += t[i];
		}
		//max_t是我们最大需要考虑的时间
		max_t = min(sum, max_t - 1);
		//注意max_t==sum和max_t==0时的情况.

		int ans = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = max_t; j >= t[i]; j--)
			{
				Node tmp;//tmp表示当选择第i首歌时的情况
				tmp.num = dp[j - t[i]].num + 1;
				tmp.time = dp[j - t[i]].time + t[i];
				if (dp[j]<tmp)//tmp更优
				{
					dp[j] = tmp;
				}
			}
		}
		printf("%d %d\n", dp[max_t].num + 1, dp[max_t].time + 678);
	}
	return 0;
}
