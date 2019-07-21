#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 70 + 30;
#define INF 0x3f3f3f3f
const int UP = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int DOWN = 3;

int n, need[maxn], d[maxn][4][4][3], opt[maxn][4][4][3];

char s[maxn];

//动态规划状态 d[i][a][b][s]
//i 已经踩了i个箭头，最小的能量消耗数
//a 此时左脚在箭头a
//b 此时右脚在箭头b
//s 上一周期脚移动的集合 s=0  没有脚动作  s=1 左脚动作  s=2 右脚动作

// opt内保存有两个数字，一个是移动的脚，一个是移动后脚处于的位置，用于递归输出最优解

const int w[4][4] = {
	{ 3,5,5,7 },
	{ 5,3,7,5 },
	{ 5,7,3,5 },
	{ 7,5,5,3 },
};

// ab:要改变位置的a,b其中之一的值，nab means newab，f为本次移动的脚，s为上次移动的脚

int energy(int ab, int nab, int f, int s) {
	if (f != s) return 1;
	else return w[ab][nab];
}



int dp(int i,int a,int b,int s,int oldab)
{
	//首先进行条件判断
	if (a == b) return INF;       //双脚踩在同一个箭头上
	if (a == RIGHT&&b == LEFT) return INF;  //左脚在右箭头，右脚在左箭头上
	if (b == LEFT && s==1&& a != oldab && oldab != -1) return INF;		//右脚在左箭头上，移动右脚之前不能左脚不能动
	if (a == RIGHT && s == 2 && b != oldab &&oldab != -1)return INF;	//左脚在左箭头上，移动左脚之前不能右脚不能动

	if (i == n) return 0;

	int &ans = d[i][a][b][s];
	if (ans != -1) return ans;
	ans = INF;

	//下面进行动态规划
	//本次不需要踩箭头
	if (need[i] == -1) 
	{
		//分别考虑移动到每个位置
		for (int k = 0; k < 4; k++) 
		{
			//移动左脚
			if (dp(i + 1, k, b, 1, a) + energy(a, k, 1, s) < ans)
			{
				ans = dp(i + 1, k, b, 1, a) + energy(a, k, 1, s);
				opt[i][a][b][s] = 4 + k;
			}
			//移动右脚
			if (dp(i + 1, a, k, 2, b) + energy(b, k, 2, s) < ans) 
			{
				ans = dp(i + 1, a, k, 2, b) + energy(b, k, 2, s);
				opt[i][a][b][s] = 8+ k;
			}

		}
		//不移动
		if(dp(i+1,a,b,0,-1)<ans)
		{
			ans = dp(i + 1, a, b, 0, -1);
			opt[i][a][b][s] = 0;
		}
	}
	//需要一只脚踩在need[i]上
	else
	{
		if (dp(i + 1, need[i], b, 1, a) + energy(a, need[i], 1, s) < ans)
		{
			ans = dp(i + 1, need[i], b, 1, a) + energy(a, need[i], 1, s);
			opt[i][a][b][s] = 4 + need[i];
		}
		if (dp(i + 1, a, need[i], 2, b) + energy(b, need[i], 2, s) < ans) 
		{ 
			ans = dp(i + 1, a, need[i], 2, b) + energy(b, need[i], 2, s);
			opt[i][a][b][s] = 8 + need[i]; 
		}
		
	}

	return ans;

}




int main()
{
	while (scanf("%s", s) == 1) {
		if (s[0] == '#') break;
		n = strlen(s);
		for (int i = 0; i < n; i++)
		{
			if (s[i] == '.') need[i] = -1;
			else if (s[i] == 'U') need[i] = 0;
			else if (s[i] == 'L') need[i] = 1;
			else if (s[i] == 'R') need[i] = 2;
			else if (s[i] == 'D') need[i] = 3;
		}
		memset(d, -1, sizeof(d));
		dp(0, 1, 2, 0, 1);
		int s = 0, a = 1, b = 2;
		for (int i = 0; i < n; i++) {
			int f = opt[i][a][b][s] / 4;
			int t = opt[i][a][b][s] % 4;
			if (f == 0) printf(".");
			else if (f == 1) printf("L");
			else printf("R");
			s = f;
			if (f == 1) a = t;
			else if (f == 2) b = t;

		}
		printf("\n");
	}
	
	return 0;
}