#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 100000 + 1000;

struct Node {
	//每个点的x，y坐标
	int x;
	int y;
	
	//每个点在x轴上的可行区间
	long long start;
	long long end;

	//计算可行区间
	void caculate(int D,int maxlen)
	{
		start =round(((double)x-sqrt((double)D*(double)D - (double)y*(double)y))*100);

		end = round(((double)x + sqrt((double)D*(double)D - (double)y*(double)y)) * 100);

		start = start >= 0 ? start : 0;

		end = end <= maxlen*100 ? end : maxlen*100;
	}

	//对区间进行排序
	bool operator < (const Node &rhs)const
	{
		return (end < rhs.end) || ((end == rhs.end) && (start > rhs.start));
	}

	Node(){}
	Node(int _x,int _y):x(_x),y(_y){}
};

int D;
int N;
int L;
Node node[maxn];

int solve()
{
	int ans = 1;
	//对区间进行排序
	sort(node, node + N);
	//第一个点选择第一个区间的最后一点
	long long select = node[0].end;
	//下面贪心的进行选点
	//选择每个区间的最后一点
	for (int i = 1; i < N; i++)
	{
		//如果上一个选的点不在当前区间，则选择当前区间最后一点为新的点
		if (node[i].start > select) {
			select = node[i].end;
			ans++;
		}
	}

	return ans;
}

int main()
{
	int x, y;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d%d%d", &L, &D, &N) == 3 && L != EOF)
	{
		for (int i = 0; i < N; i++)
		{
			scanf("%d%d", &x, &y);
			node[i].x = x;
			node[i].y = y;
			//计算每个区间的起点和终点
			node[i].caculate(D, L);
		}
		int ans = solve();
		printf("%d\n", ans);
	}
	
	return 0;
}