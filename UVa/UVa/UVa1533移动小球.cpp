#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int nodenum = 15;
const int maxn = 15+3;
const int maxdir = 4;  //每个棋子能够跳转的最大方向
const int maxnjumpnode = 4; //每个棋子一步最多能跳的步数
const int maxstate = 20 + 10;
int maxd;
int step = 0;
int state[maxn];
int end_state[maxn];
int start_state[maxn];
struct Node {
	int path;
	int space;
	int father;
	int dist;
};

Node node[maxstate];

//保存每一步走的下标
int jump[maxn][maxdir][maxnjumpnode] = \
{
	{ {2,5,9,14}, {1,3,6,10}, {-1,-1,-1,-1}, {-1,-1,-1,-1}} ,  //0节点
	{ {4, 8, 13,-1}, { 3,6,10,-1 }, { -1,-1,-1,-1 }, { -1,-1,-1,-1 }} ,	 //1节点
	{ {5, 9, 14, -1}, { 4,7,11,-1 }, { -1,-1,-1,-1 }, { -1,-1,-1,-1 }},   //2节点
	{ {1, 0, -1, -1}, { 4,5,-1,-1 }, { 7,12,-1,-1 }, { 6,10,-1,-1 }},   //3节点
	{ { 8, 13, -1, -1 },{ 7,11,-1,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //4节点
	{ { 2, 0, -1, -1 },{ 9,14,-1,-1 },{ 8,12,-1,-1 },{ 4,3,-1,-1 } },   //5节点
	{ { 3, 1, 0, -1 },{ 7,8,9,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //6节点
	{ { 4, 2, -1, -1 },{ 8,9,-1,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //7节点
	{ { 7, 6, -1, -1 },{ 4,1,-1,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //8节点
	{ { 5, 2, 0, -1 },{ 8,7,6,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //9节点
	{ { 6, 3, 1, 0 },{ 11,12,13,14},{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //10节点
	{ { 7, 4, 2, -1 },{12,13,14,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //11节点
	{ { 8, 5, -1, -1 },{ 13,14,-1,-1 },{ 11,10,-1,-1 },{ 7,3,-1,-1 } },   //12节点
	{ { 8, 4, 1, -1 },{12,11,10,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //13节点
	{ { 9,5,2,0},{ 13,12,11,10 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //14节点

};


int max_dir[maxn] = \
{
		2,     //0节点
		2,     //1节点
		2,     //2节点
		4,     //3节点
		2,     //4节点
		4,     //5节点
		2,     //6节点
		2,    //7节点
		2,    //8节点
		2,     //9节点
		2,    //10节点
		2,		//11节点
		4,		//12节点
		2,		//13节点
		2,     //14节点
};


int max_step[maxn] = \
{
		4,     //0节点
		3,     //1节点
		3,     //2节点
		2,     //3节点
		2,     //4节点
		2,     //5节点
		3,     //6节点
		2,    //7节点
		2,    //8节点
		3,     //9节点
		4,    //10节点
		3,		//11节点
		2,		//12节点
		3,		//13节点
		4,     //14节点
};

int is_line[maxn][maxn] = \
{
	{0,1,2,3,5,6,9,10,14},  //节点0
	{0,1,2,3,4,6,8,10,13},	//节点1
	{0,1,2,4,5,7,9,11,14},	//节点2
	{0,1,3,4,5,6,7,10,12},	//节点3
	{1,2,3,4,5,7,8,11,13}, //节点4
	{0,2,3,4,5,8,9,12,14}, //节点5
	{0,1,3,6,7,8,9,10,11}, //节点6
	{2,3,4,6,7,8,9,11,12}, //节点7
	{1,4,5,6,7,8,9,12,13}, //节点8
	{0,2,5,6,7,8,9,13,14}, //节点9
	{},
};

bool is_end(int *sta)
{
	for (int i = 0; i < nodenum; i++)
		if (sta[i] != end_state[i]) return false;
	return true;
}

int h()
{
	int cnt=0;

	for (int i = 0; i < nodenum; i++)
		cnt += state[nodenum];

	return cnt-1;
}

//尝试跳动 索引为index的棋子



//迭代加深搜索,解答树最深有13层
int dfs(int d)
{
	//如果达到要求状态
	//if (d == maxd) { if (is_end(state)) return true; return false; }
	if (is_end(state)) return true;

	if (d >maxd) return false;

	//启发式函数，进行最优性剪枝,每次最多去掉3个棋子
	if ((maxd - d)*3 < h()) return false;

	int sta_temp[maxn];
	//保存移动前的状态
	memcpy(sta_temp, state, sizeof(state));

	//穷举每个棋子移动
	
	for (int index = 0; index < nodenum; index++)
	{
		//如果当前位置有棋子则进行枚举
		if (state[index] == 1)
		{

			for (int i = 0; i < max_dir[index]; i++)
			{
				//如果周围是空格则不能跳跃,直接寻找下一个方向
				if (state[jump[index][i][0]] == 0)
				{
					//printf("点 index = %d state[jump[%d][%d][0]]==0 不能跳跃，因为 点jump[%d][%d][0]=%d 为%d\n", index, index, i, index, i, jump[index][i][0],state[jump[index][i][0]]);
					continue;
				}

				//printf("跳跃点 index = %d state[jump[%d][%d][0]]==1 可以跳跃,因为 点jump[%d][%d][0]=%d 为%d\n\n", index, index, i, index,i, jump[index][i][0],state[jump[index][i][0]]);

				//printf("此时状态为:\n");
				//for (int p = 0; p < nodenum; p++)
				//	printf("%d ", state[p]);
				//printf("\n");
				//
				//printf("开始查找跳跃路径.....\n");
				//否则根据每个方向查找跳跃路径
				int jum_st = 1;
				bool have_space = false;
				for (; jum_st < max_step[index]; jum_st++)
				{
					//找到第一个空格
					if (state[jump[index][i][jum_st]] == 0) { 
						//printf("小球从 index= %d 跳跃到空格  space=%d ,清除了%d个小球\n\n", index, jump[index][i][jum_st],jum_st);
						
						have_space = true; break; }
				}
				//如果找到空格则进行移动
				if (have_space)
				{
					//原来的棋子跳走
					state[index] = 0;
					//跳到空格位置
					state[jump[index][i][jum_st]] = 1;
					//途中的棋子都清零
					for (int k = 0; k < jum_st; k++)
						state[jump[index][i][k]] = 0;

					node[d].path = index;
					node[d].space = jump[index][i][jum_st];
					//if (d == 0) { printf("小球从 index=%d 跳跃到空格  space=%d ,清除了%d个小球\n\n", index, jump[index][i][jum_st], jum_st); }
					//printf("跳跃后的状态为:\n");

					//for (int p = 0; p < nodenum; p++)
					//	printf("%d ", state[p]);
					//printf("\n");
					//printf("此时深度为d = %d,将进行下一层搜索\n\n", d);
					//已经移动,进行下一次深度搜索
					if (dfs(d + 1)) return true;
					//printf("通过深度 d= %d , 节点index =%d未获得解答，重置状态\n", d, index);
					//还原状态
					memcpy(state, sta_temp, sizeof(state));
				}
				//printf("跳跃点index = %d 未找到空格不能跳跃\n", index);

			}
		}
	}
	return false;
}

void print_ans(int max)
{
	for (int i = 0; i < max-1; i++)
		printf("%d %d ", node[i].path+1, node[i].space+1);
	printf("%d %d", node[max - 1].path + 1, node[max - 1].space + 1);
	printf("\n");
}


void inline init(int index)
{
	for (int i = 0; i < nodenum; i++)
		start_state[i] = 1;
	start_state[index] = 0;
	memset(end_state, 0, sizeof(end_state));
	end_state[index] = 1;
}

int kcase = 1;

void solve()
{
	int pos;
	scanf("%d", &pos);
	//初始化两个数组
	init(pos-1); 
	bool have_solution = false;
	memset(node, 0, sizeof(node));

	for (maxd = 1; maxd < 14; maxd++)
	{
		memcpy(state, start_state, sizeof(state));
	
		if (dfs(0)) { have_solution = true; break; }
	}
	if (have_solution)
	{
		printf("%d\n",maxd+1);
		print_ans(maxd+1);
	}
}

int main()
{
	int T;
	int ans = 0;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);

	scanf("%d", &T);
	while (T--)
	{
		solve();
	}
	
	return 0;
}