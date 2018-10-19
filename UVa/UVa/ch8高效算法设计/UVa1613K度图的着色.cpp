#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
/*
�Ӷȴ�ĵ㿪ʼ����С�ĵ���ɫ
*/
const int maxn = 10000 + 1500;

vector<int>  next_node[maxn];




int G[maxn][maxn];
int color[maxn];
//����ÿ�����ж�������
int edge[maxn];

int n, m;



/*ԭ�򣺱���Ӷ�����Ŀ�ʼ��ɫ����Ϊ������ĵ�ѡ���٣�����Ҫʵʱ���£�ÿ��ѡ��������ĵ������ɫ���������ܱ�֤�н�*/
void solve(int max_k)
{
	//sort(node + 1, node + 1 + n, cmp);

	int k = max_k & 1 ? max_k : max_k + 1;

	for (int i = 1; i <= n; i++)
		edge[i] = k - edge[i];

	int cannot_sel[maxn];
	//��ÿ���������ɫ
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
			//������ڣ�����ѡ����ͬ��ɫ
			if (color[next_node[p][j]] != 0)
			{
				cannot_sel[color[next_node[p][j]]] = 1;
			}
		}

		for (int col = 1; col <= k; col++)
		{
			if (cannot_sel[col] == 0) { color[p] = col; break; }
		}

		//����û����ɫ��ĸ���
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

