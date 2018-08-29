#include<cstdio>
#include<cstring>
#include<iostream>
#include <algorithm>
#include <fstream>
#include <queue>
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

char buffer[maxn];



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

bool cmp_mp(const char &a, const char &b)
{
	return a > b;
}

int dist = 0;

int bfs(int cur_position)
{
	bool vis_bak[maxn];

	int count = 0;
	//������ǰ�ķ���״̬
	memcpy(vis_bak, vis, sizeof(vis));
	mem(buffer, 0);
	//�������Ѿ�����
	vis_bak[cur_position] = 1;
	queue<int> q;
	q.push(cur_position);

	//printf("��� cur_position = %d ��� \n", cur_position);

	while (!q.empty()) {
		int step = q.front();
		q.pop();

		//printf("�ڵ� step = %d ���� \n", step);
		//printf("����\n");
		for (int i = 0; i < deg[step]; i++)
		{
			//printf("map[%d][%d] = %d vis_bak[%d]=%d\n", step, i, map[step][i], map[step][i], vis_bak[map[step][i]]);
			
			if (!vis_bak[map[step][i]])
			{
				//printf("�ڵ� %d ���\n", map[step][i]);
				vis_bak[map[step][i]] = 1;
				buffer[count] = number[map[step][i]];
				count++;
				q.push(map[step][i]);
			}
		}

	}
	buffer[count] = '\0';
	return count;

}



//��λ������Ϊ position �����ֿ�ʼ����,����ö��cur ������
void dfs(int position,int cur)
{
	char temp_buf[maxn];
	bool is_end = true;
	memcpy(temp_buf, search_num, sizeof(search_num));

	//search_num[cur] = number[position];
	//���������Լ�֦
	//printf("����bfs\n");
	int cnt = bfs(position);
	//printf("position = %d  cnt= %d\n", position, cnt);
	if ((cnt + cur)< dist) return;
	//�����ǰö�ٵ��������ж������� ��ǰ������
	if ((cnt + cur) == dist)
	{
		//�����ֵ�����������
		sort(buffer, buffer + cnt,cmp_mp);
		char optimal[maxn + 1];
		memcpy(optimal, search_num, sizeof(search_num));
		strcat(optimal, buffer);
		//�Ƚ�
		if (strcmp(max_number, optimal) > 0)
		{
			return;
		}
	}
	//printf("�˳�bfs\n");

	for (int i = 0; i < deg[position]; i++)
	{
		//����ýڵ�û�б����ʹ�
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
	//����ýڵ��Ѿ�û�нڵ���Է��ʣ���ʾ�Ѿ��ߵ��˾�ͷ
	if (is_end) {

		search_num[cur] = '\0';
		//printf("search_num = %s\n", search_num);
		
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
		//������ֵ���ڵ�ǰ���ֵ����ô�滻
		//dist = max(dist, cur);
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




void solve()
{
	//��ÿһ���ո����������Ѱ��������ֵ
	memcpy(max_number, min_ch, sizeof(min_ch));
	//char max_numb='0';
	
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
		////������ֵ���ڵ�ǰ���ֵ����ô�滻
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
		//		//�����������ô����λ��
		//		if (maze[i][j] != '#') number[cnt++] = maze[i][j];
		//	}

		//for (int i = 0; i < cnt_of_num; i++)
		//	printf("number[%d]=%c\n", i,number[i]);

		//�Կո�ͼ,���ȶ�ÿ���ո����
		for (int i = 0; i < cnt_of_num; i++)
		{
			deg[i] = 0;
			//���ĸ���������ƶ�
			for (int dir = 0; dir < 4; dir++)
			{
				int new_x = space_x[i] + dx[dir];
				int new_y = space_y[i] + dy[dir];
				//printf("i = %d ,dir=%d\n", i,dir);
				//printf("new_x = %d,new_y = %d maze[new_x][new_y]=%c\n", new_x, new_y, maze[new_x][new_y]);
				//�ж��Ƿ��ǿո���Ƿ����
				if (new_x >= 0 && new_x < R&&new_y >= 0 && new_y < C&&maze[new_x][new_y] != '#')
				{
					//�����߹�һ����ֵ
					map[i][deg[i]++] = id[new_x][new_y];
				}
			}

			//sort(map[i], map[i] + deg[i], cmp_mp);
		}
		
		

		//for (int i = 0; i < cnt_of_num; i++)
		//	printf("deg[%d] = %d ", i, deg[i]);
		sort(node, node + cnt_of_num, cmp);
		//printf("\n�����Ŀո�ͼΪ\n");
		//for (int i = 0; i < cnt_of_num; i++)
		//{
		//	printf("\n");
		//	for (int j = 0; j < deg[i]; j++)
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