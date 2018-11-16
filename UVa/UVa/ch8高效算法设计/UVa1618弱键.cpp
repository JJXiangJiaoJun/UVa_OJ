#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int maxn = 5000 + 1000;
int k;
int ACM[maxn];

vector<int> L[maxn], R[maxn];

bool judge()
{
	//预处理,找出对于每一个数，左边比他大，而右边比他小的数
	for (int i = 0; i < k; i++)
	{
		L[i].clear();
		R[i].clear();

		for (int j = i - 1; j >= 0; j--) if (ACM[j] > ACM[i]) L[i].push_back(ACM[j]);
		for (int j = i + 1; j < k; j++) if (ACM[j] < ACM[i]) R[i].push_back(ACM[j]);

		//排序为之后的二分做准备

		sort(L[i].begin(), L[i].end());
		sort(R[i].begin(), R[i].end());
	}

	//下面进行二分查找，首先枚举中间两个数，分别是最大值和最小值

	for(int i=0;i<k;i++)
		for (int j = i + 1; j < k - 1; j++)
		{
			//如果满足条件
			if (ACM[i] < ACM[j]&&L[i].size()>0&&R[j].size()>0)
			{
				//贪心解法
				//进行二分查找,往左侧找出小于 ACM[j] 最大的数字
				int p = lower_bound(L[i].begin(), L[i].end(), ACM[j]) - L[i].begin();
				//在右侧找出大于ACM[i]最小的数字
				int s = lower_bound(R[j].begin(), R[j].end(), ACM[i]) - R[j].begin();

				//如果找不到会越界，需要判断
				if (p == 0 || s == R[j].size()) continue;

				//判断是否满足题目条件
				if (L[i][p-1] > R[j][s])  return true;
			}

			
		}

	return false;
}


bool solve()
{
	bool ok1 = judge();
	reverse(ACM, ACM + k);
	bool ok2 = judge();
	return ok1 || ok2;
}

int main()
{
	int T;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &k);
		for (int i = 0; i < k; i++)
			scanf("%d", &ACM[i]);
		bool ok = solve();
		if (ok)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}