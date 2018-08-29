#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
#define  mem(a,b)  memset(a,b,sizeof(a))

const int maxn = 15 + 5;
int G[maxn][maxn];
int vis[maxn];
int degree[maxn];
int is_break[maxn];
int N;
int count;

int pre[maxn];

void init_joinset()
{
	for (int i = 0; i < maxn; i++)
		pre[i] = i;
}

int find(int x)
{
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

bool join(int x, int y)
{
	int find_x = find(x);
	int find_y = find(y);

	if (find_x != find_y)
	{
		pre[find_x] = find_y;
		return true;
	}
	return false;
}

//Ѱ����ͨ��ĸ�����������ڻ����򷵻�0
int connect_area()
{
	int cnt = 0;
	init_joinset();
	for (int i = 1; i <= N; i++)
	{
		//�����Բ���Ͽ������ж�
		if (is_break[i]) continue;

		for (int j = i + 1; j <= N; j++)
		{
			if (G[i][j] && !is_break[j]) {
				//����Ѿ����ڣ�˵�����ڻ�
				if (!join(i, j)) return 0;
			}
		}
	}

	for (int i = 1; i <= N; i++)
		if (!is_break[i] && (pre[i] == i))cnt++;
	return cnt;
}


//Ѱ����ͨ���ж���ͨ���Ƿ���������
bool dfs(int i, int pre)
{
	vis[i] = 1;
	for (int j = 1; j <= N; j++)
	{
		//if (j==pre||is_break[j]) continue;
		if (G[i][j]&&!is_break[j])
		{
			if (!vis[j])
			{
				if(dfs(j,i))
				return true;
			}
			else if (j != pre)  //������ʹ����Ҳ����丸�ڵ㣬��ô�͹��ɻ�
				return true;
		}
	}
	return false;
}

//????????????????????????????????Ϊʲô���
//�����������ظ�ͳ�Ƶı������� 1 2 1 2  ��ʵֻ��һ���ߣ����� ���������Σ����Դ��󣡣���������������
bool two()
{
	int deg;
	for (int i = 1; i <= N; i++)
	{
		if (!is_break[i])
		{
			deg = degree[i];
			for (int j = 1; j <= N; j++)
				if (G[i][j] && is_break[j]) deg--;
			if (deg > 2) return true;
		}
	}
	return false;
}


int judge(int n)
{
	int cnt = 0;
	int connect = 0;

	//�ҳ��Ͽ��Ļ������Ҽ�¼����
	for (int i = 0; i < N; i++)
		if (n & 1 << i) { is_break[i + 1] = 1; cnt++; }
	//for (int i = 1; i <= N; i++)
	//	printf("is_break[%d] = %d  ", i, is_break[i]);
	//printf("\n");
	if (two()) {/* printf("�� %d ������������������",n);*/ return -1; }
	
	mem(vis, 0);

	//����ͨ�����
	connect = connect_area();
	if (!connect) return -1;
	//for(int k=1;k<=N;k++)
	//	if (!vis[k]&&!is_break[k])
	//	{
	//		if (dfs(k, -1))
	//		{
	//			/*printf("dfs(%d,-1)���ڻ�\n", k);*/
	//			return -1;
	//		}
	//		connect++;
	//	}
	if (connect - 1 <= cnt)
		return cnt;
	return -1;
}

//����ö��
int solve()
{
	int n;
	int ans;
	int min_ans = 100000;

	//ö�ٶϿ����ļ���
	for (n = 0; n < 1 << N; n++)
	{
		mem(vis, 0);
		mem(is_break, 0);
		ans = judge(n);
		/*printf("�� %d �� �� ans Ϊ %d\n", n, ans);*/
		if (ans!=-1) { min_ans = min(ans, min_ans); }
	}	

	return min_ans;
}

int main()
{
	int kcase = 1;
	int u, v;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d",&N)==1&&N)
	{
		mem(G, 0);
		mem(vis, 0);
		mem(degree, 0);
		while (scanf("%d%d", &u, &v) == 2 && u != -1 && v != -1)
		{
			
			//�ǳ���Ҫ��������������������������ͳ�Ƶ�һ�γ��ֵı���������ñ��Լ���������Ͳ�Ҫ�ظ�ͳ�� ��1 2 1 2
			if (!G[u][v]) { degree[u]++; degree[v]++; }
			G[u][v] = 1; G[v][u] = 1;
			//degree[u]++; degree[v]++;
		}

		printf("Set %d: Minimum links to open is %d\n", kcase++, solve());
	}
	
	
	return 0;

}