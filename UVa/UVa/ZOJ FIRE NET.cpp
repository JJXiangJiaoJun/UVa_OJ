#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;
int N;
const int maxn = 5+3;
const int maxnode = 16 + 4;
char city[maxn][maxn];

int max_cnt = 0;
int is_em[maxnode];
int num_of_space;
int num_of_wall;

int space_id[maxn][maxn];


int space_x[maxnode];
int space_y[maxnode];


//判断当前情况是否满足条件
bool judge() {
	int row, col;
	//对每个点进行判断
	for (int i = 0; i<num_of_space;i++)
	{
		//如果当前点为空，则不用判断
		if (is_em[i]) continue;
		//遍历该点的行和列，判断是否满足情况
		
		row = space_x[i];
		col = space_y[i];

		//对行进行判断
		for (int k = col+1; k < N; k++) {
			//如果碰到墙壁，说明可行
			if (city[row][k] == 'X') break;
			//同一行存在两个炮台，不满足情况
			if (!is_em[space_id[row][k]]) return false;
		}
		for (int k = col - 1; k >= 0; k--) {
			//如果碰到墙壁，说明可行
			if (city[row][k] == 'X') break;
			//同一行存在两个炮台，不满足情况
			if (!is_em[space_id[row][k]]) return false;
		}
		//对列进行判断
		for (int k = row + 1; k < N; k++) {
			//如果碰到墙壁，说明可行
			if (city[k][col] == 'X') break;
			//同一行存在两个炮台，不满足情况
			if (!is_em[space_id[k][col]]) return false;
		}
		for (int k = row - 1; k >= 0; k--) {
			//如果碰到墙壁，说明可行
			if (city[k][col] == 'X') break;
			//同一行存在两个炮台，不满足情况
			if (!is_em[space_id[k][col]]) return false;
		}
	}
	
	
	return true;
}


//枚举情况采用二进制枚举
int solve() {
	
	if (num_of_wall == 0)
		return N;
	if (num_of_wall == N*N)
		return 0;
	max_cnt = 0;
	
	//枚举并判断情况
	for (int i = 1; i <(1<<num_of_space); i++)
	{
		memset(is_em, 0, sizeof(is_em));
		int count = num_of_space;
		for (int j = 0; j < num_of_space; j++)
			if ((i&(1 << j))==0) { is_em[j] = 1; count--; }

		//如果该条件满足情况，则更新最大值
		if (judge()) max_cnt = max(max_cnt, count);
	}

	return max_cnt;
}

int main() 
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	
	while (scanf("%d", &N) == 1 && N)
	{
		num_of_space = 0;
		num_of_wall = 0;

		for (int i = 0; i < N; i++)
		{
			scanf("%s", city[i]);
			for (int j = 0; j < N; j++)
			{
				if (city[i][j] == '.') {
					space_x[num_of_space] = i;
					space_y[num_of_space] = j;
				

					space_id[i][j] = num_of_space;
					num_of_space++;
				}
				else {
					num_of_wall++;
				}
			}
		}

		int ans=0;
		ans = solve();
		printf("%d\n", ans);
	}
	
	return 0;
}