#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000 + 100;
int N;

struct Node {
	int x, y;
	double rad;

	bool operator <(const Node &rhs) const
	{
		return rad < rhs.rad;
	}
};


Node node[maxn];
Node sorted_node[maxn];
int color[maxn];

int w_cnt;
int b_cnt;

//判断是否在左边,使用叉积
bool Left(int L,int R)
{
	return sorted_node[L].x*sorted_node[R].y - sorted_node[R].x*sorted_node[L].y >= 0;
}


int solve()
{
	//如果少于两个点,那么最大的情况一定是两个点
	if (N <= 3) return N;
	int ans = 0;
	//选定一个基准点,枚举
	for (int i = 0; i < N; i++) {
		//计算每个点相对于基准点的相对坐标,并且计算极角对其排序
		int k = 0;
		//printf("基准点 node[%d].x = %d node[%d].y = %d\n", i, node[i].x, i, node[i].y);
		for (int j = 0; j < N; j++) {
			//printf("基准点 node[%d].x = %d node[%d].y = %d\n", i, node[i].x, i, node[i].y);
			if (i != j) {
				//printf("基准点 node[%d].x = %d node[%d].y = %d\n", i, node[i].x, i, node[i].y);
				sorted_node[k].x = node[j].x - node[i].x;
				sorted_node[k].y = node[j].y - node[i].y;
				//printf("node[%d].x = %d node[%d].y = %d sorted_node[%d].x = %d sorted_node[%d].y =%d \n", j, node[j].x, j, node[j].y,k,sorted_node[k].x,k,sorted_node[k].y);

				//如果是黑色点，那么关于基准点旋转180，这样便于统计
				if (color[j]) { sorted_node[k].x = -sorted_node[k].x; sorted_node[k].y = -sorted_node[k].y; }

				//计算每个点的极角
				sorted_node[k].rad = atan2(sorted_node[k].y, sorted_node[k].x);
				k++;
			}
		}
		//for (int m = 0; m < k; m++)
		//	printf("(%d,%d)\n", sorted_node[m].x, sorted_node[m].y);
			//对极角进行排序
			sort(sorted_node, sorted_node + k);
			//printf("\n\n");
			//for (int m = 0; m < k; m++)
			//	printf("(%d,%d)\n", sorted_node[m].x, sorted_node[m].y);


			//printf("\n\n");
			//下面进行每种情况的统计
			int L = 0, R = 0;
			int cnt = 2;
			bool first = true;
			while (L < k)
			{
				if (L == R) {R = (R + 1) % k; cnt++; }//初始情况
				//if (first) { R = (R + 1) % k; }

				while (R!=L&&Left(L, R)) { R = (R + 1) % k; cnt++; }
				L++;
				cnt--;
				//if(!first)cnt--;
				//first = false;
				ans = max(ans, cnt);
			
			}
			
		}
	
	return ans;
}


int main()
{	
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);

	while (scanf("%d", &N) == 1 && N)
	{
		for (int i = 0; i < N; i++)
		{
			scanf("%d%d%d", &node[i].x, &node[i].y, &color[i]);
		}
		int ans;
		ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}


