#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 5000 + 500;
int r_sel[maxn];
int c_sel[maxn];
int n;

int ans_x[maxn];
int ans_y[maxn];


struct Node {
	int low;
	int up;
	int id;
	bool operator < (const Node &rhs) const {
		if (up < rhs.up)
			return true;
		else if (up == rhs.up)
			return low >= rhs.low;
		else
			return false;
		

	}
};




Node x[maxn];
Node y[maxn];

//当前枚举第i个车

void solve() {
	//对x进行排序
	sort(x, x + n);
	bool ok;

	//贪心选择每个区间最左边不重复的点
	for (int i = 0; i < n; i++) {
		ok = false;
		for (int j = x[i].low - 1; j < x[i].up; j++) {
			if (!r_sel[j]) {
				r_sel[j] = 1;
				ans_x[x[i].id] = j + 1;
				ok = true;
				break;
			}
		}
		if (!ok) {
			printf("IMPOSSIBLE\n");
			return;
		}
	}
	
	sort(y, y + n);
	
	for (int i = 0; i < n; i++) {
		ok = false;
		for (int j = y[i].low - 1; j < y[i].up; j++) {
			if (!c_sel[j]) {
				c_sel[j] = 1;
				ans_y[y[i].id] = j + 1;
				ok = true;
				break;
			}
		}
		if (!ok) {
			printf("IMPOSSIBLE\n");
			return;
		}
	}

	for (int i = 0; i < n; i++)
		printf("%d %d\n", ans_x[i], ans_y[i]);
}


int main() 
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	
	while (scanf("%d", &n) == 1 && n) {
		
		memset(x, 0, sizeof(x));
		memset(y, 0, sizeof(y));
		memset(r_sel, 0, sizeof(r_sel));
		memset(c_sel, 0, sizeof(c_sel));
		bool ok = true;
		int min_x = n;
		int min_y = n;
		int max_x = 0;
		int max_y = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d%d%d", &x[i].low, &y[i].low, &x[i].up, &y[i].up);
			min_x = min(min_x, x[i].low);
			max_x = max(max_x, x[i].up);
			min_y = min(min_y, y[i].low);
			max_y = max(max_y, y[i].up);
			x[i].id = i;
			y[i].id = i;
			if (x[i].low > x[i].up || y[i].low > y[i].up)
				ok = false;
		}
		
		if (min_x != 1 || max_x != n || min_y != 1 || max_y != n)
			ok = false;

		if(ok)solve();
		else {
			printf("IMPOSSIBLE\n");
		}
		//solve();
	
	}
	return 0;
}