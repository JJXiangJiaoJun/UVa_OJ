#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 1000 + 100;
int pre[maxn];
int N,M;

int find(int x)
{
	int r = x;
	//找到根节点
	while (r != pre[r])
		r = pre[r];

	int i = x,j;
	while (i != r)
	{
		j = pre[i];
		pre[i] = r;
		i = j;

	}
	return r;
}


bool join(int x, int y)
{
	int fx = find(x);
	int fy = find(y);
	if (fx != fy)
	{
		pre[fx] = fy;
		return true;
	}
	return false;
}



void init()
{
	//初始化并查集
	for (int i = 0; i <= N; i++)
		pre[i] = i;
}

int main()
{
	int u, v;
	int cnt;
	while (scanf("%d%d", &N, &M) == 2 && N)
	{
		init();
		cnt = 0;
		for (int i = 0; i < M; i++)
		{
			scanf("%d%d", &u, &v);
			//不能有环,直接用join函数进行建图
			join(u, v);
			//if(pre[v]!=u) pre[u] = v;
		}
		if (M == 0) printf("%d\n", N - 1);
		else {
			for (int i = 1; i < N; i++)
			{
				if (join(i, i + 1)) cnt++;
			}
			printf("%d\n", cnt);
		}
	}
	
	return 0;
}