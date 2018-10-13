#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>;
using namespace std;
const int maxn = 100000 + 1000;
int D, N;
char p[maxn];
char ans[maxn];

void solve()
{
	memset(ans, 0, sizeof(ans));
	deque<int>  the_max;
	int max_index = 0;
	int cnt = 0;
	for (int i = 0; i <= D; i++)
	{
		while (!the_max.empty() && p[the_max.back()] < p[i]) the_max.pop_back();
		the_max.push_back(i);
		max_index = the_max.front();
	}
	ans[cnt++] = p[max_index];
	for (int i = D + 1; i < N; i++)
	{
		if (max_index +1== i) {
			for (int j = i; j < N; j++)
				ans[cnt++] = p[j];
			break;
		}
		//清除队头过期元素
		while (!the_max.empty() && the_max.front() <= max_index) the_max.pop_front();
		//加入新元素
		while (!the_max.empty() && p[the_max.back()] < p[i]) the_max.pop_back();
		the_max.push_back(i);
		max_index = the_max.front();
		ans[cnt++] = p[max_index];

	}
	ans[cnt] = '\0';
	printf("%s\n", ans);
}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d%d", &N, &D) == 2 && N)
	{
		scanf("%s", p);
		solve();
	}
	return 0;
}