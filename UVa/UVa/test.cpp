#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10;
const long long  INF = (long long) 999999999 * (long long)999999999+100000;
int A[10];
int B[10];
int len_A, len_B;
int num[20 + 5];
int vis[20 + 5];
long long  ans;


long long compute(int len_a, int len_b)
{
	long long a = 0;
	for (int i = 0; i < len_a; i++)
		a = a * 10 + (long long)A[i];
	long long b = 0;
	for (int i = 0; i < len_b; i++)
		b = b * 10 + (long long)B[i];
	return a*b;
}

void dfs(int idx, int len_a, int len_b)
{
	if (idx == len_a + len_b)
	{
		long long temp = compute(len_A, len_B);
		if (temp < ans) ans = temp;
		return;
	}
	int *p;
	if (idx >= len_a) {
		//剪枝
		if (compute(len_A, len_B) > ans) return;
		p = &B[idx - len_a];
	}
	else
	{
		p = &A[idx];
	}

	//枚举
	for (int i = 0; i < len_a + len_b; i++)
	{
		if (!vis[i])
		{
			*p = num[i];
			vis[i] = 1;
			dfs(idx + 1, len_a, len_b);
			vis[i] = 0;
			*p = 0;

		}
	}
}


int main()
{
	while (1)
	{
		int cnt;
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		memset(vis, 0, sizeof(vis));
		memset(num, 0, sizeof(num));
		ans = INF;
		for (int i = 0; i < 10; i++)
		{
			if (scanf("%d", &cnt) == 1 && cnt >= 0) {
				for (int j = 0; j < cnt; j++)
					num[i + j] = i;
			}
			else
			{
				return 0;
			}
		}
		scanf("%d%d", &len_A, &len_B);

		dfs(0, len_A, len_B);
		printf("%lld\n", ans);
	}
	
	return 0;
}