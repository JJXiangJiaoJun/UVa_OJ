#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
/*
从度大的点开始往度小的点着色
*/
const int maxn = 10000 + 1500;

vector<int>  next_node[maxn];




int G[maxn][maxn];
int color[maxn];
//保存每个点有多少条边
int edge[maxn];

int n, m;



/*原则：必须从度数大的开始着色，因为度数大的点选择少，并且要实时更新，每次选择度数最大的点进行着色，这样才能保证有解*/
void solve(int max_k)
{
	//sort(node + 1, node + 1 + n, cmp);

	int k = max_k & 1 ? max_k : max_k + 1;

	for (int i = 1; i <= n; i++)
		edge[i] = k - edge[i];

	int cannot_sel[maxn];
	//对每个点进行着色
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			cannot_sel[j] = 0;
		}

		int min_edge = 20000;
		int p;
		for (int j = 1; j <= n; j++)
		{
			if (color[j] == 0 && min_edge > edge[j])
			{
				min_edge = edge[j];
				p = j;
			}
		}


		for (int j = 0; j < next_node[p].size(); j++)
		{
			//如果相邻，不能选择相同颜色
			if (color[next_node[p][j]] != 0)
			{
				cannot_sel[color[next_node[p][j]]] = 1;
			}
		}

		for (int col = 1; col <= k; col++)
		{
			if (cannot_sel[col] == 0) { color[p] = col; break; }
		}

		//更新没有着色点的个数
		for (int j = 0; j < next_node[p].size(); j++)
		{
			if (color[next_node[p][j]] == 0)
			{
				edge[next_node[p][j]]--;
			}
		}
		
	}
	printf("%d\n", k);
	for (int i = 1; i <= n; i++)
		printf("%d\n", color[i]);
	printf("\n");
}

int main()
{
	int u, v;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d%d", &n, &m)==2)
	{
		memset(G, 0, sizeof(G));
		for (int i = 1; i <= n; i++)
		{
			color[i] = 0;
			edge[i] = 0;
			next_node[i]=vector<int> ();
		}
		int max_k = 0;
		for (int i = 1; i <= m; i++)
		{
			scanf("%d%d", &u, &v);
			G[u][v] = G[v][u] = 1;
			edge[u]++;
			edge[v]++;
			next_node[u].push_back(v);
			next_node[v].push_back(u);
			
			max_k = max(edge[u], max_k);
			max_k = max(edge[v], max_k);
		}
		solve(max_k);
	}
	return 0;
}

