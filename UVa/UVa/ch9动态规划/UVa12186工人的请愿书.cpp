#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 100000 + 1000;
int N, T;
vector<int> sons[maxn];

int dp(int u)
{
	if (sons[u].empty()) return 1;
	vector<int> d;
	int k = sons[u].size();
	for (int i = 0; i < k; i++)
		d.push_back(dp(sons[u][i]));
	//排序
	sort(d.begin(), d.end());
	int c = (k*T - 1) / 100 + 1;
	int ans = 0;
	for (int i = 0; i < c; i++) ans += d[i];
	return ans;
}

int main()
{
	int t;                                                       
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d%d", &N, &T) == 2 && N != 0)
	{
		for (int i = 0; i <= N; i++)
			sons[i].clear();
		
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &t);
			sons[t].push_back(i);
		}
		int ans = dp(0);
		printf("%d\n", ans);
	}
	
	return 0;
}