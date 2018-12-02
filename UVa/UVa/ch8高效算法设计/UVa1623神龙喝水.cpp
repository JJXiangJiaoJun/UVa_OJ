#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000000 + 1000;
int lake[maxn];
int day[maxn];
int joint_set[maxn];
int ans[maxn];
int Z, n, m;



//int find(int x)
//{
//	//查找根节点
//	int r = x;
//	while (joint_set[r] != r)
//		r = joint_set[r];
//	//路径压缩
//	int j = x;
//	while (j != r)
//	{
//		//统一根节点
//		joint_set[j] = r;
//		//对下一个节点进行压缩
//		j = joint_set[j];
//	}
//	return r;
//}

int find(int x) {
	if (joint_set[x] == x) return x;
	joint_set[x] = find(joint_set[x]); return joint_set[x];
}

int solve()
{
	//lake 数组中保存每个 lake上一次出现的位置
	for (int i = 1; i <= n; i++) lake[i] = 0;
	for (int i = 1; i <= m; i++) ans[i] = 0;
	//遍历，查找能否对每个下雨天都满足条件
	for (int i = 1; i <= m; i++)
	{
		//如果是晴天则不用考虑
		if (!day[i]) continue;

		//查找当前下雨的湖上一次填满后最近的一个晴天 lake[day[i]]，表示当前湖上一次被填满的下标索引
		int x = find(lake[day[i]]);

		//如果满足条件
		if (x <= i) { 
			ans[x] = day[i];
			//由于x被使用了，所以要更新节点
			//更新离x最近的一次晴天应为 x+1的。
			joint_set[x] = find(x + 1);
		}
		else {
			return 0;
		}
		//保存湖出现的索引
		lake[day[i]] = i;
	}
	//输出结果
	printf("YES");
	printf("\n%d", ans[1]);
	for (int i = 2; i <= m; i++)
		if (!day[i]) printf(" %d", ans[i]);
	printf("\n");
	return 1;
}


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &Z);
	while (Z--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++)
			scanf("%d", &day[i]);
		//预处理
		int last_day = m+1; joint_set[m+1] = m+1;
		for (int i = m; i >= 0; i--)
		{
			if (!day[i]&&i!=0) last_day = i;
			//保存当前天，下一个最近的晴天
			joint_set[i] = last_day;
		}
		if (!solve()) printf("NO\n");
	}
	return 0;
}