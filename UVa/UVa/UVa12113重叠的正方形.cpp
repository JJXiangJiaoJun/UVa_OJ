#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>

using namespace std;
#define  mem(a,b) memset(a,b,sizeof(a))

char mp[5][9];
char p[5][9];
int visit[10];

bool is_ok()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 9; j++)
			if (mp[i][j] != p[i][j]) return false;
	return true;
}


bool dfs(int step)
{
	if (is_ok()) return true;

	if (step >= 6) return false;

	char temp[5][9];
	//保存移动之前的状态
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 9; j++)
			temp[i][j] = p[i][j];
	//枚举9种排列方式
	for (int i = 0; i < 9; i++)
	{
		if (visit[i]) continue;
		int r = i / 3; int c = 2 * (i % 3) + 1;

		p[r][c] = p[r][c + 2] = p[r + 2][c] = p[r + 2][c + 2] = '_';
		p[r + 1][c - 1] = p[r + 1][c + 3] = p[r + 2][c - 1] = p[r + 2][c + 3] = '|';
		p[r + 1][c] = p[r + 1][c + 1] = p[r + 1][c + 2] = p[r + 2][c + 1] = ' ';

		//p1[r][c] = p1[r][c + 2] = p1[r + 2][c] = p1[r + 2][c + 2] = '_';
		//p1[r + 1][c - 1] = p1[r + 2][c - 1] = p1[r + 1][c + 3] = p1[r + 2][c + 3] = '|';
		//p1[r + 1][c] = p1[r + 1][c + 1] = p1[r + 1][c + 2] = p1[r + 2][c + 1] = ' ';

		visit[i] = 1;
		if (dfs(step + 1)) return true;
		visit[i] = 0;

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 9; j++)
				p[i][j] = temp[i][j];
	}
	//
	return false;
}


int main()
{
	int kcase = 1;
	while (1)
	{
		for (int i = 0; i < 5; i++)
		{
			gets(mp[i]);
			if (mp[i][0] == '0') return 0;
		}

		for (int i = 0; i<5; i++)
			for (int j = 0; j<9; j++)
				p[i][j] = ' ';
		mem(visit, 0);
		if (dfs(0)) printf("Case %d: Yes\n", kcase++);
		else printf("Case %d: No\n", kcase++);
	}
	return 0;
}