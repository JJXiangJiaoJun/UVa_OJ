#include<cstdio>
#include<cstring>
#include<iostream>
#include <algorithm>
#include <fstream>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn = 30 + 5;
int R, C;
char maze[maxn][maxn];
int G[maxn][maxn];
char number[maxn];
int space_x[maxn];
int space_y[maxn];
int map[maxn][maxn];
int id[maxn][maxn];
int deg[maxn];
int cnt_of_num = 0;

char search_num[maxn];

bool vis[maxn];
char max_number[maxn];
int index_to_fill = 0;

int dx[] = { 0,0,1,-1 };
int dy[] = { -1,1,0,0 };

int edge[maxn][maxn];


const char *min_ch = "0";


struct Node {
	char number;
	int space_x;
	int space_y;
	int id;
	bool operator  >(Node &rhs) const
	{
		return number > rhs.number;
	}
	bool operator ==(Node &rhs) const
	{
		return number == rhs.number;
	}
	bool operator <(Node &rhs) const
	{
		return number < rhs.number;
	}

};

bool cmp(const Node &a, const Node &b) {
	return a.number > b.number;
}


Node node[maxn];

bool cmp_mp(const int &a, const int &b)
{
	return node[a].number > node[b].number;
}
int dist = -1;


//从位置索引为 position 的数字开始遍历,已经遍历到cur 个数字
void dfs(int position,int cur)
{
	char temp_buf[maxn];
	bool is_end = true;
	memcpy(temp_buf, search_num, sizeof(search_num));
	search_num[cur] = number[position];

	for (int i = 0; i < deg[position]; i++)
	{
		//如果该节点没有被访问过
		if (!vis[map[position][i]])
		{
			is_end = false;
			vis[map[position][i]] = 1;

			search_num[cur] = number[map[position][i]];
			dfs(map[position][i], cur + 1);

			memcpy(search_num, temp_buf, sizeof(search_num));
			vis[map[position][i]] = 0;
		}
	}
	//如果该节点已经没有节点可以访问，表示已经走到了尽头
	if (is_end) {

		search_num[cur] = '\0';
		//printf("search_num = %s\n", search_num);
		//dist = max(dist, cur);
		if (dist < cur)
		{
			dist = cur;
			memcpy(max_number, search_num, sizeof(max_number));
		}
		else if (dist == cur)
		{
			if (strcmp(max_number, search_num)<0)
				memcpy(max_number, search_num, sizeof(max_number));
		}
		////如果最大值大于当前最大值，那么替换
		//if (strlen(search_num) > strlen(max_number))
		//{
		//	memcpy(max_number, search_num, sizeof(max_number));
		//}
		//else if (strlen(search_num) == strlen(max_number))
		//{
		//	if(strcmp(max_number,search_num)<0)
		//	memcpy(max_number, search_num, sizeof(max_number));
		//}
		memcpy(search_num, temp_buf, sizeof(search_num));
	}
}


//void dfs(int position, int cur,int first)
//{
//	char temp_buf[maxn];
//	bool is_end = true;
//	bool have_path = false;;
//	memcpy(temp_buf, search_num, sizeof(search_num));
//	//search_num[cur] = number[position];
//
//	for (int i = 0; i < deg[position]; i++)
//	{
//		
//		if (first) { if (edge[position][map[position][i]]) continue; }
//
//		have_path = true;
//		//如果该节点没有被访问过
//		if (!vis[map[position][i]])
//		{
//			is_end = false;
//			vis[map[position][i]] = 1;
//
//			search_num[cur] = number[map[position][i]];
//
//			edge[position][map[position][i]] = 1;
//
//			dfs(map[position][i], cur + 1,0);
//
//			memcpy(search_num, temp_buf, sizeof(search_num));
//			vis[map[position][i]] = 0;
//		}
//	}
//	//如果该节点已经没有节点可以访问，表示已经走到了尽头
//	if (is_end&&have_path) {
//
//
//		search_num[cur] = '\0';
//		printf("search_num = %s\n", search_num);
//
//		for (int i = 0; i < deg[position]; i++)
//		{
//			edge[position][map[position][i]] = 0;
//			edge[map[position][i]][position] = 0;
//		}
//		//如果最大值大于当前最大值，那么替换
//		if (strlen(search_num) > strlen(max_number))
//		{
//			memcpy(max_number, search_num, sizeof(max_number));
//		}
//		else if (strlen(search_num) == strlen(max_number))
//		{
//			if (strcmp(max_number, search_num)<0)
//				memcpy(max_number, search_num, sizeof(max_number));
//		}
//		memcpy(search_num, temp_buf, sizeof(search_num));
//	}
//}


//void dfs(int position, int cur, int first,int start)
//{
//	char temp_buf[maxn];
//	bool is_end = true;
//	bool have_path = false;
//	memcpy(temp_buf, search_num, sizeof(search_num));
//	//search_num[cur] = number[position];
//
//	for (int i = 0; i < deg[position]; i++)
//	{
//
//		if (first) { if (edge[position][map[position][i]]) continue; }
//
//		have_path = true;
//		//如果该节点没有被访问过
//		if (!vis[map[position][i]])
//		{
//			is_end = false;
//			vis[map[position][i]] = 1;
//
//			search_num[cur] = number[map[position][i]];
//
//			bool save = true;
//			for (int j = 0; j < deg[start]; j++) {
//				if (position == map[start][j]) { save = false; break; }
//			}
//			if(save)edge[position][map[position][i]] = 1;
//
//			dfs(map[position][i], cur + 1, 0,start);
//
//
//			memcpy(search_num, temp_buf, sizeof(search_num));
//			vis[map[position][i]] = 0;
//		}
//	}
//	//如果该节点已经没有节点可以访问，表示已经走到了尽头
//	if (is_end&&have_path) {
//
//
//		search_num[cur] = '\0';
//		printf("search_num = %s\n", search_num);
//		dist = max(cur, dist);
//		//for (int i = 0; i < deg[position]; i++)
//		//{
//		//	edge[position][map[position][i]] = 0;
//		//	edge[map[position][i]][position] = 0;
//		//}
//
//		//如果最大值大于当前最大值，那么替换
//		if (strlen(search_num) > strlen(max_number))
//		{
//			memcpy(max_number, search_num, sizeof(max_number));
//		}
//		else if (strlen(search_num) == strlen(max_number))
//		{
//			if (strcmp(max_number, search_num)<0)
//				memcpy(max_number, search_num, sizeof(max_number));
//		}
//		memcpy(search_num, temp_buf, sizeof(search_num));
//	}
//}

void solve()
{
	//从每一个空格出发遍历，寻找最大的数值
	memcpy(max_number, min_ch, sizeof(min_ch));
	//char max_numb='0';
	mem(edge, 0);
	dist = 0;
	for (int pos = 0; pos < cnt_of_num; pos++)
	{
		mem(vis, 0);
		mem(search_num, 0);
		

		int search_pos = node[pos].id;

		//if (node[pos - 1].number!=node[pos].number)  max_numb = node[pos].number;

		vis[search_pos] = 1;
		index_to_fill = 0;
		search_num[index_to_fill] = number[search_pos];
		dfs(search_pos,1);

		if(node[pos+1].number!=node[pos].number)
			if (dist == cnt_of_num) break;
		//search_num[index_to_fill] = '\0';
		////如果最大值大于当前最大值，那么替换
		//if (strcmp(max_number, search_num) < 0)
		//{
		//	memcpy(max_number, search_num, sizeof(max_number));
		//}

	}
	printf("%s\n", max_number);

}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	
	while (scanf("%d%d\n", &R, &C) == 2 && R)
	{		
		cnt_of_num = 0;
		mem(number, 0);
		mem(G, 0);
		mem(node, 0);
		mem(id, 0);
		for (int i = 0; i < R; i++)
		{
			fgets(maze[i], maxn, stdin);
			for (int j = 0; j < C; j++)
			{
				if (maze[i][j] != '#') { 
					node[cnt_of_num].number = maze[i][j]; node[cnt_of_num].id = cnt_of_num;
					number[cnt_of_num] = maze[i][j];
					space_x[cnt_of_num] = i; space_y[cnt_of_num] = j; id[i][j] = cnt_of_num; cnt_of_num++; }
			}
		}
		//printf("cnt_of_num=%d\n", cnt_of_num);
		//for(int i=0;i<R;i++)
		//	for (int j = 0; j < C; j++)
		//	{
		//		//如果是数字那么保存位置
		//		if (maze[i][j] != '#') number[cnt++] = maze[i][j];
		//	}

		//for (int i = 0; i < cnt_of_num; i++)
		//	printf("number[%d]=%c\n", i,number[i]);

		//对空格建图,首先对每个空格遍历
		for (int i = 0; i < cnt_of_num; i++)
		{
			deg[i] = 0;
			//对四个方向进行移动
			for (int dir = 0; dir < 4; dir++)
			{
				int new_x = space_x[i] + dx[dir];
				int new_y = space_y[i] + dy[dir];
				//printf("i = %d ,dir=%d\n", i,dir);
				//printf("new_x = %d,new_y = %d maze[new_x][new_y]=%c\n", new_x, new_y, maze[new_x][new_y]);
				//判断是否是空格和是否出界
				if (new_x >= 0 && new_x < R&&new_y >= 0 && new_y < C&&maze[new_x][new_y] != '#')
				{
					//保存走过一步的值
					map[i][deg[i]++] = id[new_x][new_y];
				}
			}

			//sort(map[i], map[i] + deg[i], cmp_mp);
		}
		
		

		//for (int i = 0; i < cnt_of_num; i++)
		//	printf("deg[%d] = %d ", i, deg[i]);
		sort(node, node + cnt_of_num, cmp);
		//printf("\n建立的空格图为\n");
		//for (int i = 0; i < cnt_of_num; i++)
		//{
		//	printf("\n");
		//	for (int j = 0; j < cnt_of_num; j++)
		//	{
		//		printf("map[%d][%d] = %d ", i, j, map[i][j]);
		//	}
		//}



		//for (int i = 0; i < cnt_of_num; i++)
		//{
		//	printf("\n");
		//	printf("node[%d].number = %c , node[%d].id = %d", i, node[i].number, i, node[i].id);
		//}

		solve();
	}
	
	return 0;
}