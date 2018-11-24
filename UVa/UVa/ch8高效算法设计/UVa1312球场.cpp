#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int max_tree = 100 + 100;
const int maxn = 10000 + 1000;
struct Tree {
	int x;
	int y;

};

int W, H,N;
Tree tree[max_tree];

bool cmpx(Tree &a, Tree &b)
{
	if (a.x != b.x) {
		return a.x < b.x;
	}
	return a.y < b.y;

}

bool cmpy(Tree &a, Tree &b)
{
	if (a.y != b.y) {
		return a.y < b.y;
	}
	return a.x < b.x;

}


//以两个树作为边界枚举正方形的最大边长
void solve()
{
	//首先对X轴排序并进行遍历
	int P, Q, L;
	P = Q = L = 0;
	int miny, maxy;
	sort(tree, tree + N, cmpx);

	for (int i = 0; i < N; i++)
	{
		miny = 0; maxy = H;

		for (int j = i + 1; j < N; j++)
		{
			//判断最长的边长  x,y中最小值
			int l = min(tree[j].x - tree[i].x, maxy - miny);
			//找到最优解那么更新
			if (l > L)
			{
				P = tree[i].x;
				Q = miny;
				L = l;
			}
			//下面更新能够获得的y 最大值以及最小值
			//同一列不进行更新
			if (tree[i].x == tree[j].x) continue;

			if (tree[i].y < tree[j].y)
			{
				maxy = min(maxy, tree[j].y);
			}
			else
			{
				miny = max(miny, tree[j].y);
			}
		}
	}

	sort(tree, tree + N, cmpy);
	int minx, maxx;
	for (int i = 0; i < N; i++)
	{
		minx = 0; maxx = W;

		for (int j = i + 1; j < N; j++)
		{
			//判断最长的边长  x,y中最小值
			int l = min(tree[j].y - tree[i].y, maxx - minx);
			//找到最优解那么更新
			if (l > L)
			{
				P = minx;
				Q = tree[i].y;
				L = l;
			}
			//下面更新能够获得的y 最大值以及最小值
			//同一列不进行更新
			if (tree[i].y == tree[j].y) continue;

			if (tree[i].x < tree[j].x)
			{
				maxx = min(maxx, tree[j].x);
			}
			else
			{
				minx = max(minx, tree[j].x);
			}
		}
	}

	printf("%d %d %d\n", P, Q, L);
}



int main()
{
	int T;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	int kcase = 0;
	while (T--)
	{
		scanf("%d%d%d", &N, &W, &H);
		for (int i = 0; i < N; i++)
			scanf("%d%d", &tree[i].x, &tree[i].y);
		//将边界点上也放上树
		tree[N].x = 0; tree[N].y = 0;
		N++;
		tree[N].x = W; tree[N].y = 0;
		N++;
		tree[N].x = 0; tree[N].y = H;
		N++;
		tree[N].x = W; tree[N].y = H;
		N++;
		if (kcase++) printf("\n");
		solve();
	}

	return 0;
}