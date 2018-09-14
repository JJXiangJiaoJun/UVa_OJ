#include <cstring>
#include <cstdio>
#include <ctype.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 10;
int x;
int y;

int maxd;
char turns[] = "WNES";
int dirs[4][2] = { { 0,-1 },{ -1,0 },{ 0,1 },{ 1,0 } };
char road[1000];
int vis[maxn][maxn];

int walls[4] = { 1,2,4,8 };
int walls_inv[4] = {4,8,1,2};
int G[maxn][maxn];
int graph[maxn][maxn];


//��״̬�ǳ����ʱ����Կ���ʹ��IDA*����Ϊ��������-
bool dfs(int x0, int y0, int d)
{
	//�ж��Ƿ��Ѿ��߳��Թ�
	if (d == maxd)
	{
		if (x0 == 0 || x0 == 5 || y0 == 0 || y0 == 7)
			return true;
		return false;
	}
	
	//vis[x0][y0] = 1;
	//��WNES�ĸ��ƶ��������ö��
	for (int i = 0; i < 4; i++)
	{
		int x1 = x0 + dirs[i][0];
		int y1 = y0 + dirs[i][1];
		int x2 = x1 + dirs[i][0];
		int y2 = y1 + dirs[i][1];

		//����Ѿ�������ô��������ƶ�
		
		
		//ע�⣡����������������IDA*�� ������Ҳ�ܵõ����Ž⣬����ʱ���������
		if (vis[x1][y1]) continue;
		//��������ƶ�
		//�����ǰ����û��ǽ����ôֱ�ӽ����ƶ�
		if ((graph[x0][y0] & walls[i]) == 0) {
			//������һ��dfs
			road[d] = turns[i];
			vis[x1][y1] = 1;
			if (dfs(x1, y1, d + 1)) { vis[x0][y0] = 0; return true; }
			vis[x1][y1] = 0;
		}
		//û������������ǽ��˵�����Խ����ƶ�
		else if ((graph[x1][y1] & walls[i]) == 0) {
			//������ͼ���иı�
			road[d] = turns[i];
			graph[x0][y0] -= walls[i];
			graph[x1][y1] += walls[i] - walls_inv[i];
			graph[x2][y2] += walls_inv[i];
			vis[x1][y1] = 1;
			if (dfs(x1, y1, d + 1)) {
				vis[x0][y0] = 0;
				graph[x0][y0] += walls[i];
				graph[x1][y1] -= walls[i] - walls_inv[i];
				graph[x2][y2] -= walls_inv[i];
	
				return true;
			}

			graph[x0][y0] += walls[i];
			graph[x1][y1] -= walls[i] - walls_inv[i];
			graph[x2][y2] -= walls_inv[i];
			vis[x1][y1] = 0;

		}
	}
	//vis[x0][y0] = 0;

	return false;
}


int main() 
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d%d", &y, &x) == 2 && x)
	{
		memset(graph, 0, sizeof(graph));
		memset(vis, 0, sizeof(vis));
		//��������
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 6; j++)
				scanf("%d", &graph[i][j]);
		//����߽磬���������ǽ�������Ͳ����жϱ߽���
		for (int i = 1; i <= 6; i++)
		{
			graph[0][i] = 2;
			graph[5][i] = 8;
		}
		for (int i = 1; i <= 4; i++)
		{
			graph[i][0] = 1;
			graph[i][7] = 4;
		}

		//memcpy(graph, G, sizeof(G));
		vis[x][y] = 1;
		for (maxd = 0;; maxd++)
		{
			if (dfs(x, y, 0)) break;
		}
		for (int i = 0; i < maxd; i++)
			printf("%c", road[i]);
		printf("\n");
	}
	return 0;
}

