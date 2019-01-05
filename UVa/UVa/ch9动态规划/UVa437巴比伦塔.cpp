#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 30+5;

struct Cube {
	int w1;
	int	w2;
	int h;

	Cube(int _h,int _w1, int _w2):h(_h),w1(_w1),w2(_w2){}
	Cube(){}
};

Cube cube[maxn * 4];
int dp[maxn * 3];
int n;

void _make_tower(int a, int b, int c,int idx) {
	cube[idx].h = a;
	cube[idx].w1 = b;
	cube[idx].w2 = c;

	cube[idx+1].h = b;
	cube[idx+1].w1 = a;
	cube[idx+1].w2 = c;

	cube[idx+2].h =c;
	cube[idx+2].w1 = a;
	cube[idx+2].w2 = b;
}
int G[maxn * 3][maxn * 3];
int degree[maxn * 3];
int dst[maxn * 3];

int solve(int index) {
	int &ans = dp[index];
	if (ans) return ans;
	ans = cube[index].h;
	for (int j = 0; j < n * 3; j++) {
		if (G[index][j]) ans = max(ans, solve(j) + cube[index].h);
	}
	return ans;
}


int main() {

	int kcase = 1;
	int a, b, c;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);

	while (scanf("%d", &n) == 1 && n) {
		int idx = 0;
		memset(dp, 0, sizeof(dp));
		memset(G, 0, sizeof(G));
		memset(degree, 0, sizeof(degree));
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &a, &b, &c);
			_make_tower(a, b, c, idx);
			idx += 3;
		}
		//建图
		for (int i = 0; i < idx; i++)
			for (int j = 0; j < idx; j++) {
				//i --> j
				if ((cube[i].w1 < cube[j].w1 && cube[i].w2 < cube[j].w2) || (cube[i].w1 < cube[j].w2&&cube[i].w2 < cube[j].w1))
				{
					if (!G[i][j]) {
						G[i][j] = 1;
						//出度+1
						degree[i]++;
					}
				}
				if ((cube[i].w1 > cube[j].w1 && cube[i].w2 > cube[j].w2) || (cube[i].w1 > cube[j].w2&&cube[i].w2 > cube[j].w1))
				{
					if (!G[j][i]) {
						G[j][i] = 1;
						//出度+1
						degree[j]++;
					}

				}

			}



		//找到终点初始化状态
		int cnt = 0;
		for (int i = 0; i < idx; i++) {
			if (!degree[i]) dp[i]=cube[i].h;
		}

		//for (int i = 0; i < idx; i++)
		//{
		//	printf("degree[%d] = %d\n", i,degree[i]);
		//	printf("dp[%d] = %d\n", i, dp[i]);
		//	for (int j = 0; j < idx; j++) {
		//		printf("G[%d][%d] = %d \n", i, j, G[i][j]);
		//	}
		//}
		//下面进行dp
		for (int i = 0; i < idx; i++)solve(i);

		int ans = 0;
		for (int i = 0; i < idx; i++) {
			ans = max(ans, dp[i]);
		}
		printf("Case %d: maximum height = %d\n", kcase++, ans);
	}
	return 0;
}
