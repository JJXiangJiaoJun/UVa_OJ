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
const int hash_size = 14000003;
const int maxstate = 10000000;
int head[hash_size];
int next_node[hash_size];

//保存整个游戏的状态
struct State {
	int up[9];//保存立方体朝上面的颜色
	int south[9];//保存立方体朝向为南面的颜色
	int east[9];//保存立方体朝向为东面的颜色

	int dist;  //保存距离起点的距离
};

State state[maxstate];
State endsta;

void init_lookup_table()
{
	memset(head, 0, sizeof(head));
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

//int bfs()
//{
//	queue<int> q;
//	init_lookup_table();
//	//将初始状态入队
//	state[1].dist = 0;
//	q.push(1);
//	//标记初始状态已经访问
//	try_to_enque(1);
//	//状态索引，保存所有状态
//	int count = 2;
//	//printf("进入bfs");
//	//下面进行bfs
//
//	while (!q.empty())
//	{
//		int new_index = q.front();
//		State new_sta = state[new_index];
//		q.pop();
//		//printf("出队");
//		/*if(count==2)
//		for (int i = 0; i < 9; i++)
//		printf("%d ", new_sta.up[i]);*/
//
//		if (new_sta.dist > 30) return -1;
//		if (is_end(new_sta)) return new_sta.dist;
//
//
//		int z;
//		//首先寻找出空格的位置
//		for (int i = 0; i < 9; i++) if (new_sta.up[i] == 0 && new_sta.east[i] == 0 && new_sta.south[i] == 0) { z = i; break; }
//
//		//计算原来空格所在的行和列
//		int r = z / 3;
//		int c = z % 3;
//
//		//对四个方向进行移动
//		for (int d = 0; d < 4; d++)
//		{
//			int new_r = r + dx[d];
//			int new_c = c + dy[d];
//			int new_z = new_r * 3 + new_c;
//			//如果没有出界再进行移动
//			if (new_r >= 0 && new_r < 3 && new_c >= 0 && new_c < 3)
//			{
//				//获取原来的状态
//				State &buf_sta = state[count];
//				memcpy(&buf_sta, &new_sta, sizeof(State));
//
//				//如果是东西的移动，那么 被移动的方格 up--->east  east---->up
//				if (new_r == r)
//				{
//					//原来的空格变为立方体
//					buf_sta.up[z] = new_sta.east[new_z];
//					buf_sta.east[z] = new_sta.up[new_z];
//					buf_sta.south[z] = new_sta.south[new_z];
//				}
//				//如果是南北的移动，那么 被移动的方格 up------>south south----->up
//				else
//				{
//					//原来的空格变为立方体
//					buf_sta.up[z] = new_sta.south[new_z];
//					buf_sta.east[z] = new_sta.east[new_z];
//					buf_sta.south[z] = new_sta.up[new_z];
//				}
//				//移动后的立方体位置变成空格
//				buf_sta.up[new_z] = 0;
//				buf_sta.south[new_z] = 0;
//				buf_sta.east[new_z] = 0;
//				//距离加一
//				buf_sta.dist = new_sta.dist + 1;
//				//判断是否能够入队
//				if (try_to_enque(count))
//				{
//					q.push(count);
//					count++;
//				}
//			}
//		}
//
//	}
//	return 0;
//}



int main()
{
	int x, y;
	char ch[10];

	init_map();

	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	//freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);

	while (scanf("%d%d\n", &x, &y) == 2 && x)
	{
		memset(head, 0, sizeof(head));
		memset(next_node, 0, sizeof(next_node));
		memset(state, 0, sizeof(state));
		init_node(x, y);

		//for (int i = 0; i < 9; i++)
		//	printf("%d ", state[1].up[i]);
		//printf("\n");
		for (int i = 0; i < 9; i+=3)
		{
			gets_s(ch);
			//printf("%d", i);
			endsta.up[i] = ch2num[ch[0]];
			endsta.up[i+1] = ch2num[ch[2]];
			endsta.up[i+2] = ch2num[ch[4]];

		}

		//bfs();
		printf("%d\n", bfs());

		//for (int i = 0; i < 9; i++)
		//	printf("%d ", endsta.up[i]);
		//printf("\n");
	}
	
	return 0;
}

//#include <cstdio>
//#include <cstring>
//#include <iostream>
//#include <algorithm>
//#include <queue>
//
//using namespace std;
//const int rot[7][4] = {
//	{ 0, 0, 0, 0 },
//	{ 2, 2, 6, 6 },
//	{ 1, 1, 3, 3 },
//	{ 4, 4, 2, 2 },
//	{ 3, 3, 5, 5 },
//	{ 6, 6, 4, 4 },
//	{ 5, 5, 1, 1 }
//};
//const int state_color[] = { 0, 1, 2, 3, 1, 2 ,3 };
//const int dx[] = { 1, -1, 0, 0 };
//const int dy[] = { 0, 0, 1, -1 };
//int G[5][5];
//int cod(int ctrl) {
//	int temp = 0;
//	if (ctrl) {
//		for (int i = 1; i <= 3; i++) {
//			for (int j = 1; j <= 3; j++) {
//				temp = temp * 10 + G[i][j];
//			}
//		}
//	}
//	else {
//		for (int i = 1; i <= 3; i++) {
//			for (int j = 1; j <= 3; j++) {
//				temp = temp * 10 + state_color[G[i][j]];
//			}
//		}
//	}
//	return temp;
//}
//void decode(int temp) {
//	int cnt = 100000000;
//	for (int i = 1; i <= 3; i++) {
//		for (int j = 1; j <= 3; j++) {
//			G[i][j] = temp / cnt;
//			temp = temp % cnt;
//			cnt /= 10;
//		}
//	}
//}
//void change(int x, int y, int xx, int yy, int p) {
//	G[x][y] = rot[G[xx][yy]][p];
//	G[xx][yy] = 0;
//}
//********************************************
//const int hashsize = 1000000 + 7;
//struct HASH {
//	int data;
//	vector<int> link;
//}haxi1[hashsize], haxi2[hashsize];
//
//void hash_init() {
//	for (int i = 0; i < hashsize; i++) {
//		haxi1[i].data = 0; haxi1[i].link.clear();
//	}
//	for (int i = 0; i < hashsize; i++) {
//		haxi2[i].data = 0; haxi2[i].link.clear();
//	}
//}
//
//bool ha_sh(int x, int who, int ok) {
//	int y = x % hashsize;
//	if (who == 1) {
//		if (haxi1[y].data == 0) {
//			if (ok) haxi1[y].data = x; return false;
//		}
//		if (haxi1[y].data == x) return true;
//		if (haxi1[y].data != x) {
//			int len = haxi1[y].link.size();
//			for (int i = 0; i < len; i++) {
//				if (haxi1[y].link[i] == x) return true;
//			}
//			if (ok) haxi1[y].link.push_back(x);
//			return false;
//		}
//	}
//	else if (who == 2) {
//		if (haxi2[y].data == 0) {
//			if (ok) haxi2[y].data = x; return false;
//		}
//		if (haxi2[y].data == x) return true;
//		if (haxi2[y].data != x) {
//			int len = haxi2[y].link.size();
//			for (int i = 0; i < len; i++) {
//				if (haxi2[y].link[i] == x) return true;
//			}
//			if (ok) haxi2[y].link.push_back(x);
//			return false;
//		}
//	}
//}
//*********************************************8
//int m, n, mr, nr, goal, ans;
//struct Node {
//	int x, y, step, passwd;
//}node;
//queue<Node> q1, q2;
//const int mp[4][2] = {
//	{ 0, 0 },
//	{ 1, 4 },
//	{ 2, 5 },
//	{ 3, 6 }
//};
//void dfs(int x, int y) {
//	if (x > 3) {
//		node.passwd = cod(1);
//		if (!ha_sh(node.passwd, 2, 1)) {
//			q2.push(node);
//		}
//		return;
//	}
//	int temp = G[x][y];
//	if (temp == 0) {
//		if (y + 1 <= 3) dfs(x, y + 1);
//		else dfs(x + 1, 1);
//	}
//	else {
//		for (int i = 0; i < 2; i++) {
//			G[x][y] = mp[temp][i];
//			if (y + 1 <= 3) dfs(x, y + 1);
//			else dfs(x + 1, 1);
//			G[x][y] = temp;
//		}
//	}
//}
//bool init() {
//	hash_init();
//	while (!q1.empty()) q1.pop();
//	while (!q2.empty()) q2.pop();
//	goal = 0, ans = 0;
//	for (int i = 1; i <= 3; i++) {
//		for (int j = 1; j <= 3; j++) {
//			char c; cin >> c;
//			int temp;
//			if (c == 'E') { mr = i, nr = j; temp = 0; }
//			else if (c == 'W') temp = 1;
//			else if (c == 'R') temp = 2;
//			else if (c == 'B') temp = 3;
//			goal = goal * 10 + temp;
//		}
//	}
//	for (int i = 1; i <= 3; i++) {
//		for (int j = 1; j <= 3; j++) {
//			G[i][j] = 1;
//		}
//	}
//	G[m][n] = 0;
//
//	if (cod(0) == goal) return false;
//
//	node.x = m, node.y = n, node.step = 0, node.passwd = cod(1);
//	ha_sh(node.passwd, 1, 1);
//	q1.push(node);
//	decode(goal);
//	node.x = mr, node.y = nr, node.step = 0;
//	dfs(1, 1);
//
//	return true;
//}
//void bfs() {
//	int cnt1 = 0, cnt2 = 0;
//	while (true) {
//		bool edge = true;
//		while (!q1.empty() && q1.front().step <= cnt1) {
//			edge = false;
//			node = q1.front(); q1.pop();
//			int x = node.x, y = node.y, step = node.step, passwd = node.passwd, pw;
//			if (ha_sh(passwd, 2, 0)) { ans = step + cnt2;  return; }
//			for (int i = 0; i < 4; i++) {
//				int xx = x + dx[i], yy = y + dy[i];
//				if (1 <= xx && xx <= 3 && 1 <= yy && yy <= 3 && step < 21) {
//					decode(passwd);
//					change(x, y, xx, yy, i);
//					pw = cod(1);
//					if (!ha_sh(pw, 1, 1)) {
//						node.x = xx, node.y = yy, node.step = step + 1, node.passwd = pw;
//						q1.push(node);
//					}
//				}
//			}
//		}
//		if (cnt1 < 21) cnt1++;
//		while (!q2.empty() && q2.front().step <= cnt2) {
//			edge = false;
//			node = q2.front(); q2.pop();
//			int x = node.x, y = node.y, step = node.step, passwd = node.passwd, pw;
//			if (ha_sh(passwd, 1, 0)) { ans = step + cnt1; return; }
//			for (int i = 0; i < 4; i++) {
//				int xx = x + dx[i], yy = y + dy[i];
//				if (1 <= xx && xx <= 3 && 1 <= yy && yy <= 3 && step < 9) {
//					decode(passwd);
//					change(x, y, xx, yy, i);
//					pw = cod(1);
//					if (!ha_sh(pw, 2, 1)) {
//						node.x = xx, node.y = yy, node.step = step + 1, node.passwd = pw;
//						q2.push(node);
//					}
//				}
//			}
//		}
//		if (cnt2 < 9) cnt2++;
//		if (edge) { ans = -1; return; }
//	}
//}
//int main()
//{
//	while (scanf("%d %d", &n, &m) == 2 && n && m) {
//		if (init()) bfs();
//		printf("%d\n", ans);
//	}
//	return 0;
//}

