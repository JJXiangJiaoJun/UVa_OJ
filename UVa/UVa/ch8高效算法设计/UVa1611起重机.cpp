#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;
const int maxn = 100000 + 1000;
const int maxstep = 5000000 + 10000;
int crates[maxn];
int n;
int start_index[maxstep];
int end_index[maxstep];

inline void change(int l, int r)
{
	for (int i = l, j = l + (r - l + 1) / 2; j <= r; j++, i++)
		swap(crates[i], crates[j]);
}

void solve()
{
	int ans = 0;
	int max_s;
	for (int search = 1; search <= n; search++)
	{
		//如果在相应位置则无需移动
		if (search == crates[search]) continue;
		int find;
		for (find = search + 1; find <= n; find++) {
			if (crates[find] ==search)break;
		}

		if (search + 2 * (find - search) - 1 <= n) {
			start_index[ans] = search;
			end_index[ans] = search + 2 * (find - search) - 1;
			ans++;
			change(search, search + 2 * (find - search) - 1);

		}
		else
		{
			if ((find - search) % 2==0) {
				start_index[ans] = search + 1;
				end_index[ans] = find;
				ans++;
				change(search + 1, find);
			}
			else {
				start_index[ans] = search;
				end_index[ans] = find;
				ans++;
				change(search, find);
			}
			search--;
		}
	}
	printf("%d\n",ans);
	for (int i = 0; i < ans; i++)
	{
		printf("%d %d\n", start_index[i], end_index[i]);
	}
}

int main() 
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &crates[i]);
		solve();
	}
	return 0;
}