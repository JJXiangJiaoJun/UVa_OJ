#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include<ctype.h>
using namespace std;
#define mem(a,b)  memset(a,b,sizeof(a))
#define INF  0x3f3f3f3f
const int maxn = 25;

char seat[maxn][maxn];
char ans[maxn][maxn];
int N, K;

bool dfs(int id, char ch)
{
	int row, col;
	//�����ҵ�ö�ٵ����
	while (ans[id / N][id%N] != '.')id++;
	if (id == N*N) return true;  //ö�ٵ����յ���ô���ش�ӡ���

	row = id / N;
	col = id % N;
	int max_c = N;
	
	//�Ե�ǰ��Ϊ���ε����Ͻǣ�ö�پ��ε��к���
	for(int r= row;r<N;r++)
		for (int c = col; c < max_c; c++)
		{
			//�ҵ�������ö����
			if (ans[r][c] != '.') { max_c = c; break; }
			//���㵱ǰö�ٵ����
			int area = (r - row + 1)*(c - col + 1);

			int number = INF;
			bool ok = true;
			//���ö�������ж�������
			for (int i = row; i <= r; i++) {
				for (int j = col; j <= c; j++)
				{
					if (isdigit(seat[i][j]))
					{
						if (number != INF) { ok = false; break; }
						else { number = seat[i][j] - '0'; }
					}
				}
				if (!ok) break;
			}
			//û���ҵ����֣����߸����������������
			if(!ok||area>number) { max_c = c; break; }
			//�������һ�����֣��ж����������
			if (area < number) continue;

			//��������������еݹ�
			//�����������
			for(int i= row;i<=r;i++)
				for (int j = col; j <= c; j++)
				{
					ans[i][j] = ch;
				}
			//������һ��ݹ�
			if (dfs(id + c - col + 1, ch + 1)) return true;


			for (int i = row; i<=r; i++)
				for (int j = col; j <= c; j++)
				{
					ans[i][j] = '.';
				}
		}
	return false;
}




int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	
	while (scanf("%d%d", &N, &K) == 2 && N)
	{
		//������λ��Ϣ
		for (int i = 0; i < N; i++)
			scanf("%s", seat[i]);
		mem(ans, '.');
		//�����������
		for (int i = 0; i < N; i++)
			ans[i][N] = '\0';
		dfs(0, 'A');
		//�����������
		//for (int i = 0; i < N; i++)
		//	ans[i][N] = '\0';
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%c", ans[i][j]);
			}
			printf("\n");
		}

	}

	return 0;
}