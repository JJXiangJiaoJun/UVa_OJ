#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;
const char color[] = {'E','B','W','R'};
const char turns[] = { 'N','S','E','W' };
int dx[5] = { -1, 1, 0, 0 };
int dy[5] = { 0, 0, -1, 1 };
const int hash_size = 1900500 + 7;
const int maxstate = 1000000+1000;

int head[hash_size];
int next_node[maxstate];

int head_inv[hash_size];
int next_node_inv[maxstate];

void generate_end(int index);


//保存整个游戏的状态
struct State {
	int up[9];//保存立方体朝上面的颜色
	int south[9];//保存立方体朝向为南面的颜色
	int east[9];//保存立方体朝向为东面的颜色

	int dist;  //保存距离起点的距离
};

State state[maxstate];
State endsta;
State end_state[maxstate];


void init_lookup_table()
{
	memset(head, 0, sizeof(head));
}


void init_lookup_table_inv()
{
	memset(head_inv, 0, sizeof(head));
}

//获取一个状态的哈希值
int try_hash(State sta)
{
	int h=0;
	for (int i = 0; i < 9; i++) h = h * 10 + (sta.up[i] << 2) + sta.south[i];
	return h%hash_size;
}


bool try_to_enque(int  index)
{
	int h = try_hash(state[index]);
	int u = head[h];
	int flag = 0;
	while (u)
	{
		for (int i = 0; i < 9; i++)
		{
			//如果有不相等的则不用继续查找
			if (state[u].up[i] != state[index].up[i] || state[u].south[i] != state[index].south[i] || state[u].east[i] != state[index].east[i])
			{
				flag = 1;
				break;
			}
		}
		//如果前一个不相等则继续查找
		if (flag) u = next_node[u];
		//否则，找到相等的则不能插入
		else  return false;
	}
	next_node[index] = head[h];
	head[h] = index;
	return true;
}

bool try_to_enque_inv(int index)
{
	int h = try_hash(end_state[index]);
	int u = head_inv[h];
	int flag = 0;
	while (u)
	{
		for (int i = 0; i < 9; i++)
		{
			//如果有不相等的则不用继续查找
			if (end_state[u].up[i] != end_state[index].up[i] || end_state[u].south[i] != end_state[index].south[i] || end_state[u].east[i] != end_state[index].east[i])
			{
				flag = 1;
				break;
			}
		}
		//如果前一个不相等则继续查找
		if (flag) u = next_node_inv[u];
		//否则，找到相等的则不能插入
		else  return false;
	}
	next_node_inv[index] = head_inv[h];
	head_inv[h] = index;
	return true;
}

//检查终点中是否有起点的值
int check(int index)
{
	//获得该正向的哈希值
	int h = try_hash(state[index]);

	int u = head_inv[h];
	int flag = 0;
	while (u)
	{
		for (int i = 0; i < 9; i++)
		{
			//如果有不相等的则不用继续查找
			if (end_state[u].up[i] != state[index].up[i] || end_state[u].south[i] != state[index].south[i] || end_state[u].east[i] != state[index].east[i])
			{
				flag = 1;
				break;
			}
		}
		//如果前一个不相等则继续查找
		if (flag) u = next_node_inv[u];
		//否则，找到相等的返回相等状态索引
		else  return u;
	}

	//若没有找到相等的，则返回没有
	return 0;
}


//检查终点中是否有起点的值
int check_inv(int index)
{
	//获得该正向的哈希值
	int h = try_hash(end_state[index]);

	int u = head[h];
	int flag = 0;
	while (u)
	{
		for (int i = 0; i < 9; i++)
		{
			//如果有不相等的则不用继续查找
			if (state[u].up[i] != end_state[index].up[i] || state[u].south[i] != end_state[index].south[i] || state[u].east[i] != end_state[index].east[i])
			{
				flag = 1;
				break;
			}
		}
		//如果前一个不相等则继续查找
		if (flag) u = next_node[u];
		//否则，找到相等的返回相等状态索引
		else  return u;
	}

	//若没有找到相等的，则返回没有
	return 0;
}


void init_node(int x, int y)
{
	int z = (y - 1) * 3 + (x - 1);

	for (int i = 0; i < 9; i++)
	{
		state[1].up[i] = 2;
		state[1].east[i] = 1;
		state[1].south[i] = 3;
	}
	state[1].up[z] = 0;
	state[1].east[z] = 0;
	state[1].south[z] = 0;
}

bool is_end(State mysta)
{
	for (int i = 0; i < 9; i++)
	{
		if (mysta.up[i] != endsta.up[i]) return false;
	}
	return true;
}




map<char, int> ch2num;

void init_map()
{
	ch2num['E'] = 0;
	ch2num['B'] = 1;
	ch2num['W'] = 2;
	ch2num['R'] = 3;
}


int count_inv = 2;

queue<int> q_end;

int bfs()
{

	//正向搜索和反向搜索的队列
	queue<int> q_start;
	if (is_end(state[1])) return 0;
	init_lookup_table();
	init_lookup_table_inv();

	//将初始状态入队
	state[1].dist = 0;
	//q.push(1);
	q_start.push(1);
	//标记正向初始状态已经访问
	try_to_enque(1);
	//状态索引，保存所有状态
	int count = 2;
	count_inv = 1;
	//标记反向初始状态已经访问
	generate_end(0);
	//count_inv = 257;
	//下面进行双向bfs，正搜一层，反搜一层
	int cnt1 = 21, cnt2 = 9;

	while (!q_start.empty()||!q_end.empty())
	{
		int start_size = q_start.size();
		int end_size = q_end.size();
		bool edge = true;
		/*if(count==2)
		printf("end_size 为: %d\n", end_size);*/

		//正向bfs
		while (start_size--&&state[q_start.front()].dist<=cnt1)
		{
			
			edge = false;
			int new_index = q_start.front();
			State new_sta = state[new_index];
			q_start.pop();

			//正搜15层都没有结果那么返回
			//if (new_sta.dist > 15) return -1;
			//判断终点是否搜到了相同的节点,找到相同节点那么结束搜索
			//if (int checked = check(new_index)) return new_sta.dist + end_state[checked].dist;
			

			//if (new_sta.dist > 30) return -1;
			//if (is_end(new_sta)) return new_sta.dist;


			int z;
			//首先寻找出空格的位置
			for (int i = 0; i < 9; i++) if (new_sta.up[i] == 0 ) { z = i; break; }

			//计算原来空格所在的行和列
			int r = z / 3;
			int c = z % 3;

			//对四个方向进行移动
			for (int d = 0; d < 4; d++)
			{
				int new_r = r + dx[d];
				int new_c = c + dy[d];
				int new_z = new_r * 3 + new_c;
				//如果没有出界再进行移动
				if (new_r >= 0 && new_r < 3 && new_c >= 0 && new_c < 3)
				{
					//获取原来的状态
					State &buf_sta = state[count];
					memcpy(&buf_sta, &new_sta, sizeof(State));

					//如果是东西的移动，那么 被移动的方格 up--->east  east---->up
					if (new_r == r)
					{
						//原来的空格变为立方体
						buf_sta.up[z] = new_sta.east[new_z];
						buf_sta.east[z] = new_sta.up[new_z];
						buf_sta.south[z] = new_sta.south[new_z];
					}
					//如果是南北的移动，那么 被移动的方格 up------>south south----->up
					else
					{
						//原来的空格变为立方体
						buf_sta.up[z] = new_sta.south[new_z];
						buf_sta.east[z] = new_sta.east[new_z];
						buf_sta.south[z] = new_sta.up[new_z];
					}
					//移动后的立方体位置变成空格
					buf_sta.up[new_z] = 0;
					buf_sta.south[new_z] = 0;
					buf_sta.east[new_z] = 0;
					//距离加一
					buf_sta.dist = new_sta.dist + 1;
					//判断是否能够入队
					if (try_to_enque(count))
					{
						//判断反向bfs是否搜到该节点
						if (int checked = check(count)) { 
							/*
							printf("正向向搜到与反向相同节点 : count = %d\n", count);

							printf("buf_sta.dist = %d  end_state[%d].dist = %d\n", buf_sta.dist, checked, end_state[checked].dist);

							printf("起始节点up状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", buf_sta.up[i]);
							}
							printf("\n");


							printf("起始节点south状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", buf_sta.south[i]);
							}
							printf("\n");


							printf("起始节点east状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", buf_sta.east[i]);
							}
							printf("\n");

							printf("相同结束节点up状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", end_state[checked].up[i]);
							}
							printf("\n");


							printf("相同结束节点south状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", end_state[checked].south[i]);
							}
							printf("\n");


							printf("相同结束节点east状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", end_state[checked].east[i]);
							}
							printf("\n");*/
							
							if (buf_sta.dist + end_state[checked].dist > 30) return -1;
							return buf_sta.dist + end_state[checked].dist; }
						q_start.push(count);
						count++;
					}
				}
			}
		}
		while (end_size--&&end_state[q_end.front()].dist <= cnt2)
		{
			int new_index_end = q_end.front();
			State new_sta_end = end_state[new_index_end];
			q_end.pop();

			//反搜15层都没有结果那么返回
			//if (new_sta_end.dist > 15) return -1;
			//判断终点是否搜到了相同的节点,找到相同节点那么结束搜索
			//if (int checked = check(new_index_end)) return new_sta_end.dist + state[checked].dist;


			//if (new_sta.dist > 30) return -1;
			//if (is_end(new_sta)) return new_sta.dist;


			int z;
			//首先寻找出空格的位置
			for (int i = 0; i < 9; i++) if (new_sta_end.up[i] == 0) { z = i; break; }

			//计算原来空格所在的行和列
			int r = z / 3;
			int c = z % 3;

			//对四个方向进行移动
			for (int d = 0; d < 4; d++)
			{
				int new_r = r + dx[d];
				int new_c = c + dy[d];
				int new_z = new_r * 3 + new_c;
				//如果没有出界再进行移动
				if (new_r >= 0 && new_r < 3 && new_c >= 0 && new_c < 3)
				{
					//获取原来的状态
					State &buf_sta_end = end_state[count_inv];
					memcpy(&buf_sta_end, &new_sta_end, sizeof(State));

					//如果是东西的移动，那么 被移动的方格 up--->east  east---->up
					if (new_r == r)
					{
						//原来的空格变为立方体
						buf_sta_end.up[z] = new_sta_end.east[new_z];
						buf_sta_end.east[z] = new_sta_end.up[new_z];
						buf_sta_end.south[z] = new_sta_end.south[new_z];
					}
					//如果是南北的移动，那么 被移动的方格 up------>south south----->up
					else
					{
						//原来的空格变为立方体
						buf_sta_end.up[z] = new_sta_end.south[new_z];
						buf_sta_end.east[z] = new_sta_end.east[new_z];
						buf_sta_end.south[z] = new_sta_end.up[new_z];
					}
					//移动后的立方体位置变成空格
					buf_sta_end.up[new_z] = 0;
					buf_sta_end.south[new_z] = 0;
					buf_sta_end.east[new_z] = 0;
					//距离加一
					buf_sta_end.dist = new_sta_end.dist + 1;
					//判断是否能够入队
					if (try_to_enque_inv(count_inv))
					{
						//判断正向bfs是否搜到该节点
						if (int checked = check_inv(count_inv)) 
						{
						/*	printf("反向搜到与正向相同节点 : count_inv = %d\n", count_inv);

							printf("buf_sta_end.dist = %d  state[%d].dist = %d\n", buf_sta_end.dist, checked, state[checked].dist);

							printf("结束节点up状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", buf_sta_end.up[i]);
							}
							printf("\n");


							printf("结束节点south状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", buf_sta_end.south[i]);
							}
							printf("\n");


							printf("结束节点east状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", buf_sta_end.east[i]);
							}
							printf("\n");

							printf("相同起始节点up状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", state[checked].up[i]);
							}
							printf("\n");


							printf("相同起始节点south状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", state[checked].south[i]);
							}
							printf("\n");


							printf("相同起始节点east状态:\n");
							for (int i = 0; i < 9; i++)
							{
								printf("%d ", state[checked].east[i]);
							}
							printf("\n");*/


							if (buf_sta_end.dist + state[checked].dist > 30) return -1;

							return buf_sta_end.dist + state[checked].dist; }
						q_end.push(count_inv);
						count_inv++;
					}
				}
			}
		}
		if (edge) return -1;


	}
	return -1;
}



void generate_end(int index)
{
	if (index == 9)
	{
		for (int i = 0; i < 9; i++)
		{
			end_state[count_inv].up[i] = endsta.up[i];
			end_state[count_inv].south[i] = endsta.south[i];
			end_state[count_inv].east[i] = endsta.east[i];
			end_state[count_inv].dist = endsta.dist;
		}
		try_to_enque_inv(count_inv);
		q_end.push(count_inv);

		////if (count_inv < 400) {
		////	printf("endsta.east: %d\n",count_inv);
		////	for (int i = 0; i < 9; i++)
		////		printf("%d ", endsta.east[i]);
		////	printf("\n");

		////	printf("endsta.south: %d\n", count_inv);
		////	for (int i = 0; i < 9; i++)
		////		printf("%d ", endsta.south[i]);
		////	printf("\n");
		////}
		count_inv++;
		return;
	}
	//如果当前格子是空格，那么直接进行下一个方块枚举
	if (endsta.up[index] == 0) generate_end(index + 1);
	else
	{
		for (int i = 1; i < 4; i++)
		{
			//如果是表面的颜色则不能进行枚举
			if (endsta.up[index] == i) continue;

			//if (endsta.up[index] == 0) printf("修改了空位");

			//东西面赋值为i
			endsta.east[index] = i;
			//南北面赋值为最后一种颜色
			for (int j = 1; j < 4; j++)
			{
				//与上面和东西面都不一样
				if (j != i&&j != endsta.up[index]) endsta.south[index] = j;
			}

			//枚举下一个位置
			generate_end(index + 1);
		}
	}
}

int main()
{
	int x, y;
	char ch[10];

	init_map();

	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);

	while (scanf("%d%d\n", &x, &y) == 2 && x)
	{
		//memset(head, 0, sizeof(head));
		memset(next_node, 0, sizeof(next_node));
		memset(state, 0, sizeof(state));
		memset(next_node_inv, 0, sizeof(next_node_inv));
		memset(end_state, 0, sizeof(end_state));
		init_node(x, y);
		q_end = queue<int>();
		memset(&endsta, 0, sizeof(endsta));
		//printf("q_end.size = %d\n", q_end.size());
		//for (int i = 0; i < 9; i++)
		//	printf("%d ", state[1].up[i]);
		//printf("\n");
		for (int i = 0; i < 9; i+=3)
		{
			fgets(ch,10,stdin);
			

			endsta.up[i] = ch2num[ch[0]];
			endsta.up[i + 1] = ch2num[ch[2]];
			endsta.up[i + 2] = ch2num[ch[4]];

		}
		endsta.dist = 0;
		//bfs();
		printf("%d\n", bfs());

		//for (int i = 0; i < 9; i++)
		//	printf("%d ", endsta.up[i]);
		//printf("\n");
	}
	
	return 0;
}

