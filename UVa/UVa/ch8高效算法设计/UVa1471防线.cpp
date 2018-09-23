#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;
#define INF 0x3f3f3f3f
const int maxn = 2 * 100000 + 1000;
int Z;
int n;
int towers[maxn];
int G[maxn];
int F[maxn];
int S[maxn];
struct Node {
	int a, g;
	 Node(int a_,int g_):a(a_),g(g_){}
	 bool operator <(const Node& rhs) const {
		 return a < rhs.a;
	 }
};
set<Node> candidate;
int solve()
{
	int ans = 1;
	if (n == 1) { return 1; }

	G[0] = 1;
	for (int i = 1; i < n; i++)
		if (towers[i - 1] < towers[i]) G[i] = G[i - 1] + 1;
		else G[i] = 1;

		// f[i] is the length of longest increasing continuous subsequence starting from i
		F[n - 1] = 1;
		for (int i = n - 2; i >= 0; i--)
			if (towers[i] < towers[i + 1]) F[i] = F[i + 1] + 1;
			else F[i] = 1;
	candidate.clear();
	//插入第一个点
	candidate.insert(Node(towers[0], G[0]));

	//枚举以i为起点的序列
	for (int i = 1; i < n; i++)
	{
		Node c(towers[i], G[i]);
		bool keep=true;
		//判断是否插入,查找插入位置
		set<Node>::iterator  low_iter = candidate.lower_bound(c);
		if (low_iter != candidate.begin())
		{
			Node can = *(--low_iter);
			int len = F[i] + can.g;
			ans = max(ans, len);
			if (c.g <= can.g) { keep = false; }
		}

		if (keep)
		{
			candidate.erase(c);
			candidate.insert(c);
			low_iter = candidate.find(c);
			low_iter++;
			//while (low_iter != candidate.end() && low_iter->g <= c.g&&low_iter->a > c.a) candidate.erase(low_iter++);
			while (low_iter != candidate.end() && low_iter->g <= c.g) candidate.erase(low_iter++);

		}
	}
	return ans;
}

//不用set采用LIS的方法
int solve2()
{
	int ans = 1;
	if (n == 1) { return 1; }
	G[0] = 1;
	for (int i = 1; i < n; i++)
		if (towers[i - 1] < towers[i]) G[i] = G[i - 1] + 1;
		else G[i] = 1;

	// f[i] is the length of longest increasing continuous subsequence starting from i
	F[n - 1] = 1;
	for (int i = n - 2; i >= 0; i--)
		if (towers[i] < towers[i + 1]) F[i] = F[i + 1] + 1;
		else F[i] = 1;

	memset(S, INF, sizeof(S));

	S[1] = towers[0];

	for (int i = 1; i < n; i++)
	{
		int p = lower_bound(S + 1, S + n+1, towers[i])-S;
		int len = p - 1 + F[i];
		ans = max(ans, len);
		
		if (towers[i] < S[G[i]]) S[G[i]] = towers[i];
	}

	return ans;
}

int main()
{
	
	scanf("%d", &Z);
	while (Z--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &towers[i]);
		int ans;
		//ans = solve();
		ans = solve2();
		printf("%d\n", ans);
	}
	return  0;
}