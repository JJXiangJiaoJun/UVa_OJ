#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;
const int maxn = 15+3;
const int maxstate = 150000;
const int maxt = 3;
int count_inv = 0;

int vis[maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt];
int end_index[maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt];
int start_index[maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt][maxt];

struct State {
	//当前状态
	int sta[maxn];
	//父节点
	int father;
	//移动的节点
	int move_index;
	//移动到的位置
	int dest_index;
	//距离
	int dist;
};
//使用哈希判重
int n, m, s, t;
int G[maxn][maxn];
int init_state, target_state;

State state[maxstate*2];
State end_state[maxstate];
int A[maxn];

bool is_start = false;


void inline mark_vis(int index)
{
	
	vis[state[index].sta[0]][state[index].sta[1]][state[index].sta[2]][state[index].sta[3]][state[index].sta[4]][state[index].sta[5]][state[index].sta[6]]\
		[state[index].sta[7]][state[index].sta[8]][state[index].sta[9]][state[index].sta[10]][state[index].sta[11]][state[index].sta[12]][state[index].sta[13]]\
		[state[index].sta[14]]=1;
}

void inline mark_vis_inv(int index)
{
	vis[end_state[index].sta[0]][end_state[index].sta[1]][end_state[index].sta[2]][end_state[index].sta[3]][end_state[index].sta[4]][end_state[index].sta[5]][end_state[index].sta[6]]\
		[end_state[index].sta[7]][end_state[index].sta[8]][end_state[index].sta[9]][end_state[index].sta[10]][end_state[index].sta[11]][end_state[index].sta[12]][end_state[index].sta[13]]\
		[end_state[index].sta[14]] = 2;
}

void inline mark_idx_inv(int index)
{
	end_index[end_state[index].sta[0]][end_state[index].sta[1]][end_state[index].sta[2]][end_state[index].sta[3]][end_state[index].sta[4]][end_state[index].sta[5]][end_state[index].sta[6]]\
		[end_state[index].sta[7]][end_state[index].sta[8]][end_state[index].sta[9]][end_state[index].sta[10]][end_state[index].sta[11]][end_state[index].sta[12]][end_state[index].sta[13]]\
		[end_state[index].sta[14]] = index;
}

void inline mark_idx(int index)
{
	start_index[state[index].sta[0]][state[index].sta[1]][state[index].sta[2]][state[index].sta[3]][state[index].sta[4]][state[index].sta[5]][state[index].sta[6]]\
		[state[index].sta[7]][state[index].sta[8]][state[index].sta[9]][state[index].sta[10]][state[index].sta[11]][state[index].sta[12]][state[index].sta[13]]\
		[state[index].sta[14]] = index;
}

int inline get_idx(int index)
{
	return end_index[state[index].sta[0]][state[index].sta[1]][state[index].sta[2]][state[index].sta[3]][state[index].sta[4]][state[index].sta[5]][state[index].sta[6]]\
		[state[index].sta[7]][state[index].sta[8]][state[index].sta[9]][state[index].sta[10]][state[index].sta[11]][state[index].sta[12]][state[index].sta[13]]\
		[state[index].sta[14]];
}

int inline get_idx_inv(int index)
{
	return start_index[end_state[index].sta[0]][end_state[index].sta[1]][end_state[index].sta[2]][end_state[index].sta[3]][end_state[index].sta[4]][end_state[index].sta[5]][end_state[index].sta[6]]\
		[end_state[index].sta[7]][end_state[index].sta[8]][end_state[index].sta[9]][end_state[index].sta[10]][end_state[index].sta[11]][end_state[index].sta[12]][end_state[index].sta[13]]\
		[end_state[index].sta[14]];
}

int inline check_vis(int index)
{
	return vis[state[index].sta[0]][state[index].sta[1]][state[index].sta[2]][state[index].sta[3]][state[index].sta[4]][state[index].sta[5]][state[index].sta[6]]\
		[state[index].sta[7]][state[index].sta[8]][state[index].sta[9]][state[index].sta[10]][state[index].sta[11]][state[index].sta[12]][state[index].sta[13]]\
		[state[index].sta[14]];
}

int inline check_vis_inv(int index)
{
	return vis[end_state[index].sta[0]][end_state[index].sta[1]][end_state[index].sta[2]][end_state[index].sta[3]][end_state[index].sta[4]][end_state[index].sta[5]][end_state[index].sta[6]]\
		[end_state[index].sta[7]][end_state[index].sta[8]][end_state[index].sta[9]][end_state[index].sta[10]][end_state[index].sta[11]][end_state[index].sta[12]][end_state[index].sta[13]]\
		[end_state[index].sta[14]];
}



void generate_obstacle(int cnt, int cur);
queue<int> q_end;

int bfs()
{
	//初始化整个状态
	state[0].father = -1;
	state[0].dist = 0;
	queue<int> q;
	int cnt = 1;
	//将初始状态入队
	q.push(0);
	//标记起点状态
	mark_vis(0);
	mark_idx(0);
	count_inv = 0;
	generate_obstacle(0, 0);

	int cnt2 = 5;

	while (!q.empty())
	{
		int start_size = q.size();
		int end_size = q_end.size();
		//if (cnt == 1) printf("end_size = %d\n", end_size);
		while (start_size--)
		{
			int index = q.front();
			q.pop();
			/*		printf("index = %d\n", index);
			for (int i = 0; i < 15; i++)

			printf("%d ", state[index].sta[i]);
			printf("\n")*/;

			//if (is_end(index)) return index;

			//下面穷举移动方式，对障碍和物体穷举移动,最多有14个节点,遍历每一个节点
			for (int i = 0; i < n; i++)
			{
				if (state[index].sta[i] == 0) continue;//如果该节点为空格，那么跳过枚举
													   //如果该节点是障碍或者机器人则枚举移动方式
				for (int j = 0; j < n; j++)
				{
					//两点条件 1、该节点与其他节点连通  2、连通节点为空
					if (G[i][j] && !state[index].sta[j])
					{
						//复制原始状态
						memcpy(state[cnt].sta, state[index].sta, sizeof(State::sta));
						//移动节点,原来的节点位置变为0
						state[cnt].sta[i] = 0;
						state[cnt].sta[j] = state[index].sta[i];


						state[cnt].father = index;
						state[cnt].move_index = i;
						state[cnt].dest_index = j;
						state[cnt].dist = state[index].dist + 1;

						int checked = check_vis(cnt);
						//判重,如果不重复则入队
						if (checked == 0)
						{
							mark_vis(cnt);
							mark_idx(cnt);

							//state[cnt].father = index;
							//state[cnt].move_index = i;
							//state[cnt].dest_index = j;
							//state[cnt].dist = state[index].dist + 1;

							/*printf("正向入队:%d dist = %d\n",cnt, state[cnt].dist);

							for (int i = 0; i < 15; i++)
							printf("%d ", state[cnt].sta[i]);
							printf("\n");*/

							q.push(cnt);
							cnt++;
						}
						//说明结束节点遍历到了这个节点
						else if (checked == 2)
						{
							//printf("正向bfs找到相同点:%d\n", cnt);
							//for (int i = 0; i < 15; i++)
							//	printf("%d ", state[cnt].sta[i]);
							//printf("\n");

							//int get_index = get_idx(cnt);
							//printf("反向bfs相同点的索引为:%d\n", get_index);
							//for (int i = 0; i < 15; i++)
							//	printf("%d ", end_state[get_index].sta[i]);
							//printf("\n");

							//printf("正向距离 state[%d].dist = %d  反向距离 end_state[%d].dist = %d\n", cnt, state[cnt].dist, get_index, end_state[get_index].dist);
							//
							is_start = true;
							return cnt;
							//return state[cnt].dist + end_state[get_idx(cnt)].dist;
						}

					}
				}
			}

		}
		
		while (end_size--&&end_state[q_end.front()].dist<=cnt2)
		{
			int index = q_end.front();
			q_end.pop();
			/*		printf("index = %d\n", index);
			for (int i = 0; i < 15; i++)

			printf("%d ", state[index].sta[i]);
			printf("\n")*/;

			//if (is_end(index)) return index;

			//下面穷举移动方式，对障碍和物体穷举移动,最多有14个节点,遍历每一个节点
			for (int i = 0; i < n; i++)
			{
				if (end_state[index].sta[i] == 0) continue;//如果该节点为空格，那么跳过枚举
													   //如果该节点是障碍或者机器人则枚举移动方式
				for (int j = 0; j < n; j++)
				{
					//两点条件 1、该节点与其他节点连通  2、连通节点为空
					if (G[i][j] && !end_state[index].sta[j])
					{
						//复制原始状态
						memcpy(end_state[count_inv].sta, end_state[index].sta, sizeof(State::sta));
						//移动节点,原来的节点位置变为0
						end_state[count_inv].sta[i] = 0;
						end_state[count_inv].sta[j] = end_state[index].sta[i];

						end_state[count_inv].father = index;
						end_state[count_inv].move_index = i;
						end_state[count_inv].dest_index = j;
						end_state[count_inv].dist = end_state[index].dist + 1;

						int checked = check_vis_inv(count_inv);

						//判重,如果不重复则入队
						if (checked == 0)
						{
							mark_vis_inv(count_inv);
							mark_idx_inv(count_inv);
							//end_state[count_inv].father = index;
							//end_state[count_inv].move_index = i;
							//end_state[count_inv].dest_index = j;
							//end_state[count_inv].dist = end_state[index].dist + 1;
							
						/*	printf("反向入队:%d dist = %d\n", count_inv, end_state[count_inv].dist);
							for (int i = 0; i < 15; i++)
								printf("%d ", end_state[count_inv].sta[i]);
							printf("\n");*/
							
							q_end.push(count_inv);
							count_inv++;
						}
						//说明起点节点遍历到了这个节点
						else if (checked == 1)
						{
						
						/*	printf("反向bfs找到相同点:%d\n", count_inv);
							for (int i = 0; i < 15; i++)
								printf("%d ", end_state[count_inv].sta[i]);
							printf("\n");

							int get_index = get_idx_inv(count_inv);
							printf("正向bfs相同点的索引为:%d\n", get_index);
							for (int i = 0; i < 15; i++)
								printf("%d ", state[get_index].sta[i]);
							printf("\n");

							printf("反向距离 end_state[%d].dist = %d  正向距离 state[%d].dist = %d\n", count_inv, end_state[count_inv].dist, get_index, state[get_index].dist);*/
							
							is_start = false;
							return count_inv;
							//return end_state[count_inv].dist + state[get_idx_inv(count_inv)].dist;
						}

					}
				}
			}
		}
		
	}
	return -1;
}

int iter = 0;

void print_ans(int index)
{
	iter++;
	if (state[index].dist == 0)
	{
		//printf("正向打印state[%d].dist = %d\n ", index, state[index].dist);
		return;
	}
	else {
		
		//printf("正向打印父节点state[%d].father = %d\n", index, state[index].father);
		print_ans(state[index].father);
		printf("%d %d\n", state[index].move_index + 1, state[index].dest_index + 1);
	}
}

int iter_inv = 0;

void print_ans_inv(int index)
{
	iter_inv++;
	if (end_state[index].dist == 0)

	{
		//printf("反向打印 end_state[%d].dist = %d\n ", index, end_state[index].dist);

		return;
	}
	else {
		//printf("反向打印父节点end_state[%d].father = %d\n", index, end_state[index].father);
		print_ans_inv(end_state[index].father);
		printf("%d %d\n", end_state[index].move_index + 1, end_state[index].dest_index + 1);
	}
}


//当前枚举障碍个数为n，枚举位置为cur
void generate_obstacle(int cnt, int cur)
{
	//如果枚举完成，那么入队
	if (cnt == m)
	{
		memcpy(end_state[count_inv].sta, A, sizeof(State::sta));
		//标记访问
		mark_vis_inv(count_inv);
		mark_idx_inv(count_inv);
		q_end.push(count_inv);

		count_inv++;
		return;
	}
	//枚举位置是终点
	if (cur == target_state) { generate_obstacle(cnt, cur + 1); return; }
	else
	{
		for (int i = cur; i < n; i++)
		{
			
			if (i == target_state) continue;
			//该位置标记为障碍，枚举下一个位置
			A[i] = 1;
			generate_obstacle(cnt + 1, i + 1);
			A[i] = 0;
		}
	}
}


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);

	int T;
	int obstacle;
	int u, v;
	int ans;
	int kcase = 1;
	scanf("%d", &T);
	while (T--)
	{
		memset(state, 0, sizeof(state));
		memset(end_state, 0, sizeof(end_state));
		//memset(end_index, 0, sizeof(end_index));
		//memset(start_index, 0, sizeof(start_index));
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		memset(A, 0, sizeof(A));
		q_end = queue<int>();
		scanf("%d %d %d %d\n", &n, &m, &s, &t);
		//保存初始状态
		state[0].sta[s-1]= 2;
		target_state = t - 1;
		A[target_state] = 2;
		for (int i = 0; i < m; i++)
		{
			//读入障碍的位置
			scanf("%d", &obstacle);
			//保存障碍初始状态
			state[0].sta[obstacle-1] = 1;
		}
		for (int i = 0; i < n - 1; i++)
		{
			scanf("%d %d\n", &u, &v);
			G[u-1][v-1] = G[v-1][u-1] = 1;
		}
		//for (int i = 0; i < 15; i++)
		//{
		//	printf("\n");
		//	for (int j = 0; j < 15; j++)
		//	{
		//		printf("%d ", G[i][j]);
		//	}
		//}
		//printf("\n");
	/*	for (int i = 0; i < 15; i++)
			printf("%d ", state[0].sta[i]);
		printf("\n");*/
		ans = bfs();
		//printf("Case %d:  %d\n");
		if (ans == -1)
		{
			printf("Case %d: %d\n",kcase++,-1);
		}
		//如果是由开始节点遍历得到的
		else
		{
			if (is_start)
			{
				int sta_index = get_idx(ans);

				printf("Case %d: %d\n", kcase++, state[ans].dist + end_state[sta_index].dist);
				print_ans(ans);
				//print_ans_inv(end_state[sta_index].father);
				print_ans_inv(sta_index);
			}
			else
			{
				int sta_index = get_idx_inv(ans);
				printf("Case %d: %d\n", kcase++, end_state[ans].dist + state[sta_index].dist);
				print_ans(sta_index);
				//print_ans_inv(end_state[ans].father);
				print_ans_inv(ans);
			}
		}
		//printf("正向打印个数 iter = %d  反向打印个数 iter_inv = %d\n", iter, iter_inv);
		printf("\n");
	}
	return 0;
}