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

//���ò��鼯�жϻ�
void init()
{
	for (int i = 0; i < maxnode; i++)
		pre[i] = i;
}

int find(int x)
{
	//�ҵ�x�ĸ��ڵ�
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


// idΪ��ǰö�ٵ�������
bool dfs(int id)
{
	int r, c;

	while (ans_buf[id / n][id%n] != '.') { if (!is_right(id / n, id%n)) return false; id++; }
	
	if (id == n*n) return true;   //ö�ٵ��յ����Ѿ��õ���
	//�������ǰö�������ε��к���
	

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

	//����֮ǰ��״̬


	//��������ֻ��߽������ö��  0��ʾ '/'  1��ʾ'\'
	for (int i = 0; i < 2; i++)
	{
		
		bool ok = true;
		int number;
		char ch;
		
		//printf("���ֵ�����  r=%d c = %d", row, col);

		//�������ε��ĸ���������޸�
		for (int j = 0; j < 4; j++)
		{
			//�����εĶ�������
			ch = deg[row + dx[j]][col + dy[j]];

			//����ö���������
			if (isdigit(ch))
			{
				
				number = ch - '0';
				number = number - lines[i][j];
				//������ֶ���������Ҫ�󣬲��������б���ö��
				if (number < 0) { ok = false; break; }
				//�޸�ö��֮��Ķ���
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

			//�����ж��Ƿ����Ҫ��
			//���һ��
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
		//�ж��Ƿ���ڻ�
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
		
			//�����ǰ��������������һ��ö��
			if (dfs(id + 1)) return true;
		}
		////��ԭ��ʼ״̬
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
				//����ǵ�һ��
				if (r == 0) {
					//��������ϽǶ���
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
					//���ϽǶ���
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
				//��������һ��
				else if (r == n)
				{
					//��һ��
					if (c == 0) {
						if (deg[r][c] == '0')
							ans[r - 1][c] = '\\';
						else if (deg[r][c] == '1')
						{
							ans[r - 1][c] = '/';
						}
					}
					//���һ��
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
				//����ǵ�һ��
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
				//��������һ��
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