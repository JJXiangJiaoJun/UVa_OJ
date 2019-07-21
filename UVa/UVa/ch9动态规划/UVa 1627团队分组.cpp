#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;
const int maxn = 100 + 5;
//color 表示每个人所属的队伍 diff 表示每个连通块的差值 cc表示连通块索引
int n, G[maxn][maxn], color[maxn], diff[maxn], cc;
vector<int> team[maxn][2];  //team[cc][c] 是 连通块cc ，分组为c 的成员列表

//判断一个连通块是否为二分图
bool dfs(int u, int c) {
	color[u] = c;  //为当前节点染色  1,2
	team[cc][c - 1].push_back(u);
	for (int v = 0; v < n; v++) {
		if (v != u && !(G[u][v] && G[v][u])) {
			if (color[v] > 0 && color[v] == color[u]) return false;
			if (!color[v] && !dfs(v, 3 - c)) return false;
		}
	}
	return true;
}


bool build_graph() {
	memset(color, 0, sizeof(color));

	cc = 0;

	for (int i = 0; i < n; i++) {
		if (!color[i]) {
			team[cc][0].clear();
			team[cc][1].clear();

			if (!dfs(i, 1)) return false;
			diff[cc] = team[cc][0].size() - team[cc][1].size();
			cc++;
		}
	}
	return true;
}


int d[maxn][maxn * 2], teamno[maxn];



void print(int ans) 
{
	//从最后一个集合考试考虑，从后往前进行打印解
	vector<int> team1,team2;
	for (int i = cc-1; i >= 0; i--)
	{
		//如果是将染色为1的放入队1，染色为2的放入队2
		if (d[i][ans + n] == 1) 
		{
			for (int j = 0; j < team[i][0].size(); j++)
				team1.push_back(team[i][0][j]);
			for (int j = 0; j < team[i][1].size(); j++)
				team2.push_back(team[i][1][j]);
			ans -= diff[i];
		}
		else if (d[i][ans + n] == -1)
		{
			for (int j = 0; j < team[i][0].size(); j++)
				team2.push_back(team[i][0][j]);
			for (int j = 0; j < team[i][1].size(); j++)
				team1.push_back(team[i][1][j]);
			ans += diff[i];
		}
	}

	printf("%d", team1.size());

	for (int i = 0; i < team1.size(); i++) printf(" %d", team1[i] + 1);
	printf("\n");

	printf("%d", team2.size());
	for (int i = 0; i < team2.size(); i++) printf(" %d", team2[i] + 1);
	printf("\n");



}

void dp()
{
	memset(d, 0, sizeof(d));
	
	//下面进行dp 判断每个状态是否能达到
	//d[i][j] 表示考虑前i个集合，状态j是否能达到
	for(int i=0;i<cc;i++)
		//这样做是为了防止下标为负
		for (int j = -n; j <= n; j++)
		{
			
			if (i == 0) {
				d[i][diff[i] + n] = 1;
				d[i][-diff[i] + n] = -1;
			}
			else
			if (d[i-1][j + n] != 0)
			{
				//将染色为1的放入队1，染色为2的放入队2
				d[i][j + diff[i] + n] = 1;
				//将染色为1的放入队2，染色为2的放入队1
				d[i][j - diff[i] + n] = -1;
			}
		}
	
	//下面打印解，从小到大遍历

	for (int ans = 0; ans <= n; ans++) {
		if (d[cc - 1][ans + n]) { print(ans); return; }
		if (d[cc - 1][-ans + n]) { print(-ans); return; }
	}



}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		memset(G, 0, sizeof(G));
		for (int u = 0; u < n; u++)
		{
			int v;
			while (scanf("%d", &v) == 1 && v) G[u][v - 1] = 1;
		}

		if (n == 1 || !build_graph()) printf("No solution\n");
		else dp();

		if (T) printf("\n");
	}
	
	
	return 0;
}