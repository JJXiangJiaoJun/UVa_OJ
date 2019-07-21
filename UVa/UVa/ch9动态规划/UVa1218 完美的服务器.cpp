#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10000 + 1000;

vector<int> sons[maxn];
int d[maxn][5];
int N;


void dfs(int u,int father) {

	d[u][0] = 1;
	d[u][1] = 0;
	d[u][2] = maxn;
	int k = sons[u].size();
	if (k == 1 && father != 0) return; 
	for (int i = 0; i < k; i++)
	{
		int son = sons[u][i];
		if (son == father) continue;
		dfs(son, u);
		d[u][0] += min(d[son][0], d[son][1]);
		d[u][1] += d[son][2];
	}

	for (int i = 0; i < k; i++)

	{
		int son = sons[u][i];
		if (son == father) continue;
		d[u][2] = min(d[u][2], d[u][1] - d[son][2] + d[son][0]);
	}
}


int main()
{
	int a, b;
	while (scanf("%d", &N) == 1 && N)
	{
		for (int i = 1; i <= N; i++)
			sons[i].clear();
		for (int i = 1; i < N; i++)
		{
			scanf("%d%d", &a, &b);
			sons[a].push_back(b);
			sons[b].push_back(a);
		}
		dfs(1, 0);
		printf("%d\n", min(d[1][0], d[1][2]));
		scanf("%d", &a);
		if (a == -1) break;

	}
	
	return 0;
}