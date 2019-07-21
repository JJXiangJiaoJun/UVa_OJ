#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;
const int maxn = 200 + 100;

int dp[maxn][4];
int f[maxn][4];
vector<int> sons[maxn];
map<string, int> name2id;
int cnt, n;


void init()
{
	for (int i = 1; i <= n; i++) sons[i].clear();
	memset(f, 0, sizeof(f));
	memset(dp, 0, sizeof(dp));
	cnt = 0;
	name2id.clear();
}


int getid(string &s)
{
	if (name2id.count(s)) return name2id[s];
	return name2id[s] = ++cnt;
}


//动态规划
void dfs(int u)
{
	if (!sons[u].size()) {//叶子节点
		dp[u][0] = 0;
		dp[u][1] = 1;
		return;
	}

	for (int i = 0; i < sons[u].size(); i++) {
		int son = sons[u][i];
		//计算子节点的动态规划
		dfs(son);
		dp[u][1] += dp[son][0];  //不选择子节点
		if (f[son][0]) f[u][1] = 1;
		
		if (dp[son][0] > dp[son][1]) {//dp[u][0]的计算
			dp[u][0] += dp[son][0];
			if (f[son][0]) f[u][0] = 1;
		}
		else if (dp[son][0] == dp[son][1]) {
			dp[u][0] += dp[son][0];
			f[u][0] = 1;
		}
		else
		{
			dp[u][0] += dp[son][1];
			if (f[son][1]) f[u][0] = 1;
		}
	}
	dp[u][1]++;   //加上选了自己
}

int main()
{
	string s1;
	string s2;
	int id1;
	int id2;
	while (scanf("%d", &n) == 1 && n)
	{
		init();
		cin >> s1;
		int root = getid(s1);
		for (int i = 1; i < n; i++)
		{
			cin >> s1 >> s2;
			id1 = getid(s1);
			id2 = getid(s2);
			sons[id2].push_back(id1);
		}

		dfs(1);

		if (dp[1][0] == dp[1][1]) printf("%d No\n", dp[1][0]);
		else if (dp[1][0] > dp[1][1]) printf("%d %s\n", dp[1][0], f[1][0] ? "No" : "Yes");
		else printf("%d %s\n", dp[1][1], f[1][1] ? "No" : "Yes");
	}
	return 0;
}