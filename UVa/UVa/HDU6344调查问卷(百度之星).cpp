#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 1000 + 10;
const int maxquestion = 10 + 5;
int T;
int n, m, k;
char Q[maxn][maxquestion];
int P[maxquestion];
int select[maxquestion];
//保存每种情况有多少可能
int my_set[1 << 12];

//枚举选的问题集合，当前枚举的是第 cur 个 元素
void generate_subset(int m,int cur)
{
	//枚举到了最终点
	if (cur == m)
	{

	}

}


void solve()
{

}

int main()
{
	scanf("%d", &T);
	int kcase = 1;
	while (T--)
	{
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 0; i < n; i++)
			scanf("%s", Q[i]);
		solve();
	}
	
	return 0;
}

