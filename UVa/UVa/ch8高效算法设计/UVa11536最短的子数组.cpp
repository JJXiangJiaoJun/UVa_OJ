#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
#define INF 0x3f3f3f3f
const int maxn = 1000000 + 10000;
const int maxk = 1000+200;

int seq[maxn];

int cnt[maxk];
//前缀和


int N, M, K;

//尝试用长度为len的滑动窗口
bool judge(int len)
{
	//用来保存在滑动窗口中出现数字的总数
	int tot = 0;
	//cnt[i]记录出现数字i的次数
	memset(cnt, 0, sizeof(cnt));

	//滑动窗口
	for (int i = 1; i <= N; i++)
	{
		if (tot == K) return true;
		if (i == N + 1) return false;
		//滑动窗口新加入的元素
		if (seq[i] <= K&&cnt[seq[i]]++ == 0) tot++;
		//滑动窗口滑出去的元素
		if (i > len&&seq[i - len] <= K&&--cnt[seq[i - len]] == 0) tot--;
	}
	if (tot == K) return true;
	return false;
}


//二分枚举答案的长度
int solve()
{
	int L = 1;
	int R = N + 1;

	while (L < R)
	{
		int mid = (L + R) / 2;
		if (judge(mid)) R = mid;
		else L = mid + 1;
		//printf("mid = %d\n", mid);
	}
	if (L == N + 1) return -1;

	return L;
}

void init()
{
	

	seq[1] = 1;
	seq[2] = 2;
	seq[3] = 3;


	for (int i = 4; i <= N; i++)
	{
		seq[i] = (seq[i - 1] + seq[i - 2] + seq[i - 3]) % M + 1;
		
	}

}

int main()
{
	int T;
	int kcase = 1;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);

	while (T--)
	{
		scanf("%d%d%d", &N, &M, &K);
		//printf("N = %d M = %d K=%d\n", N, M, K);
		init();
		int min_len = solve();
		if (min_len > 0)
			printf("Case %d: %d\n", kcase++, min_len);
		else
			printf("Case %d: sequence nai\n", kcase++);
	}

	return 0;
}