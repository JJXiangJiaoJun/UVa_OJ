#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctype.h>

using namespace std;
#define mem(a,b)  memset(a,b,sizeof(a))
const int maxn = 7 + 2;
const int maxnode = 70;
char deg[maxn][maxn];
char ans[maxn][maxn];
int N, n;
int G[maxnode][maxnode];
int pre[maxnode];
char ans_buf[maxn][maxn];

int lines[2][4] = {
	{0,1,1,0},
	{1,0,0,1} };

int dx[5] = { 0,0,1,1 };
int dy[5] = { 0,1,0,1 };

//利用并查集判断环
void init()
{
	for (int i = 0; i < maxnode; i++)
		pre[i] = i;
}

int find(int x)
{
	//找到x的根节点
	int r = x;

	while (r != pre[r])
		r = pre[r];
	int i = x, j;
	while (i != r)
	{
		j = pre[i];
		pre[i] = r;
		i = j;
	}

	return r;
}


bool join(int x,int y) {
	int fx = find(x);
	int fy = find(y);

	if (fx != fy)
	{
		 pre[fx]=fy;
		 return true;
	}
	return false;
}


void connect_area()
{
	for(int i = 0;i<=(n+1)*(n+1);i++)
		for (int j = 0; j <= (n + 1)*(n + 1); j++)
		{
			if (G[i][j])
				join(i, j);
		}

}

bool have_circle() {
	for (int i = 0; i <= (n + 1)*(n + 1); i++)
		for (int j = i+1; j <= (n + 1)*(n + 1); j++)
		{
			if (G[i][j])
				if (!join(i, j)) { return 1; }
		}
	return 0;
}

bool is_right(int row, int col)
{
	if (row == n - 1)
	{
		if (col == n - 1) {
			for (int k = 0; k<4; k++)
				if (isdigit(deg[row + dx[k]][col + dy[k]]))  if (deg[row + dx[k]][col + dy[k]] != '0') { return false; }
		}
		else {
			if (isdigit(deg[row][col])) if (deg[row][col] != '0') { return false; }
			if (isdigit(deg[row + 1][col])) if (deg[row + 1][col] != '0') { return false; }

		}
	}
	else if (col == n - 1)
	{
		if (isdigit(deg[row][col])) if (deg[row][col] != '0') { return false; }
		if (isdigit(deg[row][col + 1])) if (deg[row][col + 1] != '0') { return false; }
	}
	else {
		if (isdigit(deg[row][col])) if (deg[row][col] != '0')  return false;
	}
	return true;
}


// id为当前枚举的正方形
bool dfs(int id)
{
	int r, c;

	while (ans_buf[id / n][id%n] != '.') { if (!is_right(id / n, id%n)) return false; id++; }
	
	if (id == n*n) return true;   //枚举到终点则已经得到答案
	//计算出当前枚举正方形的行和列
	

	int row = id / n;
	int col = id%n;
	
	char temp_buf[maxn][maxn];
	int  temp_G[maxnode][maxnode];
	//char temp_ans[maxn][maxn];
	int  temp_pre[maxnode];

	memcpy(temp_buf, deg, sizeof(deg));
	memcpy(temp_G, G, sizeof(G));
	//memcpy(temp_ans,ans, sizeof(ans));
	memcpy(temp_pre, pre, sizeof(pre));

	//保存之前的状态


	//下面对两种划线结果进行枚举  0表示 '/'  1表示'\'
	for (int i = 0; i < 2; i++)
	{
		
		bool ok = true;
		int number;
		char ch;
		
		//printf("数字的行数  r=%d c = %d", row, col);

		//对正方形的四个顶点进行修改
		for (int j = 0; j < 4; j++)
		{
			//正方形的顶点坐标
			ch = deg[row + dx[j]][col + dy[j]];

			//如果该顶点是数字
			if (isdigit(ch))
			{
				
				number = ch - '0';
				number = number - lines[i][j];
				//如果出现度数不满足要求，不继续进行本次枚举
				if (number < 0) { ok = false; break; }
				//修改枚举之后的顶点
				deg[row + dx[j]][col + dy[j]] = number + '0';
			}
		}

		int u, v;
		if (ok)
		{
			if (i == 0) {
				u = row * (n+1) + col + 1;
				v = (row + 1)*(n + 1) + col;
				//printf("u = %d v = %d\n", u, v);
				G[u][v] = 1;
				G[v][u] = 1;
			}
			else if(i==1) {
				u = row*(n + 1) + col;
				v = (row + 1)*(n + 1) + col + 1;
				//printf("u = %d v = %d\n", u, v);
				G[u][v] = 1;
				G[v][u] = 1;
			}

			//下面判断是否符合要求
			//最后一行
			if (row == n - 1)
			{
				if (col == n - 1) {
					for(int k=0;k<4;k++)
						if (isdigit(deg[row + dx[k]][col + dy[k]]))  if (deg[row + dx[k]][col + dy[k]] != '0') { ok = false; break; }
				}
				else {
					if (isdigit(deg[row][col])) if (deg[row][col] != '0') { ok = false; }
					if (isdigit(deg[row + 1][col])) if (deg[row + 1][col] != '0') { ok = false; }

				}
			}
			else if (col == n - 1)
			{
				if (isdigit(deg[row][col])) if (deg[row][col] != '0') { ok = false; }
				if (isdigit(deg[row][col + 1])) if (deg[row][col + 1] != '0') { ok = false; }
			}
			else {
				if (isdigit(deg[row][col])) if (deg[row][col] != '0') ok = false;
			}
		}
		//判断是否存在环
		if (ok)
		{
			if (!join(u, v)) { ok = false; }
		}

		if (ok)
		{
			if (i == 0)
				ans[row][col] = '/';
			else
				ans[row][col] = '\\';

			//printf("id=%d \n", id);
			//for (int k = 0; k <= n; k++)
			//	printf("%s\n", deg[k]);
			//printf("\n");

			//for (int k = 0; k < n; k++)
			//	printf("%s\n", ans[k]);
			//printf("\n");
		
			//如果当前情况可行则进行下一次枚举
			if (dfs(id + 1)) return true;
		}
		////还原初始状态
		memcpy(G, temp_G, sizeof(G));
		memcpy(deg, temp_buf, sizeof(deg));
		//memcpy(ans, temp_ans, sizeof(ans));
		memcpy(pre, temp_pre, sizeof(pre));
		//for (int u = 0; u < n + 1; u++)
		//	for (int v = 0; v < n + 1; v++)
		//		G[u][v] = temp_G[u][v];
	}


	
	return false;
}


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	
	scanf("%d", &N);
	while (N--)
	{
		mem(deg, 0);
		mem(G, 0);
		mem(ans, '.');
		
		init();
		scanf("%d", &n);
		for (int i = 0; i <= n; i++)
			scanf("%s", deg[i]);


		for(int r=0;r<=n;r++)
			for (int c = 0; c <= n; c++)
			{
				//如果是第一行
				if (r == 0) {
					//如果是左上角顶点
					if (c == 0)
					{
						if (deg[r][c] == '1')
						{
							ans[r][c] = '\\';
						}
						else if (deg[r][c] == '0')
						{
							ans[r][c] = '/';
						}
					}
					//右上角顶点
					else if (c == n)
					{
						if (deg[r][c] == '0')
							ans[r][c - 1] = '\\';
						else if (deg[r][c] == '1')
						{
							ans[r][c - 1] = '/';
						}
					}
					else
					{
						if (deg[r][c] == '2') {
							ans[r][c - 1] = '/';
							ans[r][c] = '\\';
						}
						else if (deg[r][c] == '0') {
							ans[r][c - 1] = '\\';
							ans[r][c] = '/';
						}
					}

				}
				//如果是最后一行
				else if (r == n)
				{
					//第一列
					if (c == 0) {
						if (deg[r][c] == '0')
							ans[r - 1][c] = '\\';
						else if (deg[r][c] == '1')
						{
							ans[r - 1][c] = '/';
						}
					}
					//最后一列
					else if (c == n) {
						if (deg[r][c] == '0')
							ans[r - 1][c - 1] = '/';
						else if (deg[r][c] == '1')
						{
							ans[r - 1][c - 1] = '\\';
						}
					}
					else
					{
						if (deg[r][c] == '2') {
							ans[r - 1][c - 1] = '\\';
							ans[r - 1][c] = '/';
						}
						else if (deg[r][c] == '0') {
							ans[r - 1][c - 1] = '/';
							ans[r - 1][c] = '\\';
						}
					}
				}
				//如果是第一列
				else if (c == 0)
				{
					if (deg[r][c] == '2') {
						ans[r - 1][c] = '/';
						ans[r][c] = '\\';
					}
					else if (deg[r][c] == '0') {
						ans[r - 1][c] = '\\';
						ans[r][c] = '/';
					}
				}
				//如果是最后一列
				else if (c == n) {
					if (deg[r][c] == '2') {
						ans[r - 1][c - 1] = '\\';
						ans[r][c - 1] = '/';
					}
					else if (deg[r][c] == '0') {
						ans[r - 1][c - 1] = '/';
						ans[r][c - 1] = '\\';
					}
				}
				else {
					if (deg[r][c] == '4')
					{
						ans[r - 1][c - 1] = '\\';
						ans[r - 1][c] = '/';
						ans[r][c - 1] = '/';
						ans[r][c] = '\\';
					}

				}
			}
		
		for (int i = 0; i < n; i++)
			ans[i][n] = '\0';
		
		int id1, id2;

		for(int r=0;r<n;r++)
			for (int c = 0; c < n; c++)
			{
				if (ans[r][c] == '/') {

					if (isdigit(deg[r][c + 1]))deg[r][c + 1] -= 1;
					if (isdigit(deg[r + 1][c]))deg[r + 1][c] -= 1;

					id1 = r*(n + 1) + c + 1;
					id2 = (r + 1)*(n + 1) + c;
					G[id1][id2] = G[id2][id1] = 1;

				}
				else if (ans[r][c] == '\\') {
					if (isdigit(deg[r][c])) deg[r][c] -= 1;
					if (isdigit(deg[r + 1][c + 1]))deg[r + 1][c + 1] -= 1;

					id1 = r*(n + 1) + c;
					id2 = (r + 1)*(n + 1) + c + 1;
					G[id1][id2] = G[id2][id1] = 1;
				}
			}

		connect_area();
		memcpy(ans_buf, ans, sizeof(ans));
		//for (int i = 0; i < n; i++)
		//	printf("%s\n", ans_buf[i]);
		//printf("\n");
		dfs(0);

		for (int i = 0; i < n; i++)
			printf("%s\n", ans[i]);


	}
	
	return 0;
}