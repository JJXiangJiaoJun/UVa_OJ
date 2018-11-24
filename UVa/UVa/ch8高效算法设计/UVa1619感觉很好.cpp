#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 100000 + 1000;
int A[maxn];
int n;
long long sum[maxn];
int stack[maxn];
int top;
int L[maxn], R[maxn];

int kcase = 0;

void solve()
{
	memset(sum, 0, sizeof(sum));
	//计算前缀和
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] +(long long) A[i];

	//利用单调栈预处理出 left[i]  表示第i个数字最左能延伸到的位置
	top = 0;
	memset(stack, 0, sizeof(stack));
	memset(L, 0, sizeof(L));
	memset(R, 0, sizeof(R));

	for (int i = 1; i <= n; i++)
	{
		//栈非空，而且栈顶元素大于当前元素，说明栈顶元素能延伸到的位置，当前元素一定能延伸到
		while (top > 0 && A[stack[top - 1]] >= A[i]) top--;
		
		L[i] = top == 0 ? 1 : (stack[top - 1] + 1);

		//当前元素入栈
		stack[top++] = i;
	}

	top = 0;
	memset(stack, 0, sizeof(stack));
	for (int i = n; i >= 1; i--)
	{
		while (top > 0 && A[stack[top - 1]] >= A[i]) top--;

		R[i] = top == 0 ? n : (stack[top - 1] - 1);

		stack[top++] = i;
	}

	int left=1, right=1;
	long long  max_val = 0;

	for (int i = 1; i <= n; i++)
	{
		long long  temp_val = (sum[R[i]] - sum[L[i] - 1])*(long long )A[i];

		if (temp_val > max_val ||( temp_val == max_val && (right - left) > (R[i] - L[i])))
		{
			max_val = temp_val;
			left = L[i];
			right = R[i];
		}
	}

	printf("%lld\n%d %d\n", max_val, left, right);
}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d", &n) == 1 && n)
	{
		if (kcase++) printf("\n");
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		solve();
	}
	return 0;
}