#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000 + 100;
int height[maxn];
char land[maxn][maxn];
int n, m;
int ans[maxn << 1];

struct Rect {
	int c, h;

	Rect(int cc=1,int hh=1):c(cc),h(hh){}
};

Rect rect[maxn];

void solve()
{
	memset(height, 0, sizeof(height));
	memset(ans, 0, sizeof(ans));


	/*总时间复杂度 O(m*n) 因为每个顶点最多入队出队一次*/

	for (int i = 0; i < n; i++)
	{
		int top = -1;			//每次计算新的一行则清空栈

		for (int j = 0; j < m; j++)
		{
			//如果遇到障碍，则直接清空栈
			if (land[i][j] == '#')
			{
				top = -1;
				height[j] = 0;
			}
			else
			{
				height[j]++; //当前列高度由上一列高度递推得到

				Rect r(j, height[j]);

				if (top < 0) rect[++top] = r;   //空栈直接赋值

				else
				{											//r.c存储当前最优的左上角顶点值
					while (top >= 0 && rect[top].h >= r.h) r.c = rect[top--].c; //栈中的h应等于最左边碰到墙位置的c，保证高度单调递增，并且保存最优的c值
					if (top<0 || r.h - r.c>rect[top].h - rect[top].c) rect[++top] = r;  //如果是最优解，那么入栈，否则不入栈

				}
				//此时栈顶即为最优的左上角顶点
				r = rect[top];
				ans[r.h + j - r.c + 1]++;
			}
		}
	}

	for (int i = 2; i <= m + n; i++)
		if (ans[i]) printf("%d x %d\n", ans[i], i * 2);
}

int main()
{
	int T;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", land[i]);

		solve();
	}
	return 0;
}