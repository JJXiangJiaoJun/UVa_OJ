#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
const int maxn = 1000 + 100;
int dp[maxn];
#define INF 0x3f3f3f3f
struct Bulb {
	int V;
	int K;
	int C;
	int L;

	bool operator <(const Bulb &rhs)const {
		return this->V < rhs.V;
	}
};

Bulb bulb[maxn];
int cnt[maxn];

int n;
int main() {
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d%d%d", &bulb[i].V, &bulb[i].K, &bulb[i].C, &bulb[i].L);



		sort(bulb + 1, bulb + n + 1);

		//for (int i = 1; i <= n; i++)
		//	printf("%d %d %d %d\n", bulb[i].V, bulb[i].K, bulb[i].C, bulb[i].L);

		memset(dp, INF, sizeof(dp));

		dp[1] = bulb[1].K + bulb[1].C*bulb[1].L;
		dp[0] = 0;
		cnt[0] = 0;
		cnt[1] = bulb[1].L;
	
		for (int i = 2; i <= n; i++)
		{
			cnt[i] = cnt[i - 1] + bulb[i].L;
		}



		for(int i=2;i<=n;i++)
			for (int j = 0; j < i; j++)
			{					
				dp[i] = min(dp[i], dp[j] + bulb[i].K + (cnt[i] - cnt[j])*bulb[i].C);

			}
		
		printf("%d\n", dp[n]);
	 }

	return 0;
}