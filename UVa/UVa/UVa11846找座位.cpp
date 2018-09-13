#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include<ctype.h>
using namespace std;
#define mem(a,b)  memset(a,b,sizeof(a))
#define INF  0x3f3f3f3f
const int maxn = 25;

char seat[maxn][maxn];
char ans[maxn][maxn];
int N, K;

bool dfs(int id, char ch)
{
	int row, col;
	//首先找到枚举的起点
	while (ans[id / N][id%N] != '.')id++;
	if (id == N*N) return true;  //枚举到了终点那么返回打印结果

	row = id / N;
	col = id % N;
	int max_c = N;
	
	//以当前点为矩形的左上角，枚举矩形的行和列
	for(int r= row;r<N;r++)
		for (int c = col; c < max_c; c++)
		{
			//找到最大的列枚举量
			if (ans[r][c] != '.') { max_c = c; break; }
			//计算当前枚举的面积
			int area = (r - row + 1)*(c - col + 1);

			int number = INF;
			bool ok = true;
			//检测枚举区域有多少数字
			for (int i = row; i <= r; i++) {
				for (int j = col; j <= c; j++)
				{
					if (isdigit(seat[i][j]))
					{
						if (number != INF) { ok = false; break; }
						else { number = seat[i][j] - '0'; }
					}
				}
				if (!ok) break;
			}
			//没有找到数字，或者该区域存在两个数字
			if(!ok||area>number) { max_c = c; break; }
			//区域存在一个数字，判断数字与面积
			if (area < number) continue;

			//满足条件下面进行递归
			//面积等于数字
			for(int i= row;i<=r;i++)
				for (int j = col; j <= c; j++)
				{
					ans[i][j] = ch;
				}
			//进行下一层递归
			if (dfs(id + c - col + 1, ch + 1)) return true;


			for (int i = row; i<=r; i++)
				for (int j = col; j <= c; j++)
				{
					ans[i][j] = '.';
				}
		}
	return false;
}




int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	
	while (scanf("%d%d", &N, &K) == 2 && N)
	{
		//读入座位信息
		for (int i = 0; i < N; i++)
			scanf("%s", seat[i]);
		mem(ans, '.');
		//加入结束符号
		for (int i = 0; i < N; i++)
			ans[i][N] = '\0';
		dfs(0, 'A');
		//加入结束符号
		//for (int i = 0; i < N; i++)
		//	ans[i][N] = '\0';
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%c", ans[i][j]);
			}
			printf("\n");
		}

	}

	return 0;
}