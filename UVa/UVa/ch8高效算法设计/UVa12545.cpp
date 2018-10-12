#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 100;
char S[maxn];
char T[maxn];

//保存S、T中1的个数
int cntS1;
int cntT1;

int solve()
{
	//首先处理 S中的?字符
	int ans = 0;
	int lens = strlen(S);
	cntS1 = cntT1 = 0;
	for (int i = 0; i < lens; i++)
	{
		if (S[i] == '1')	cntS1++;
		if (T[i] == '1')	cntT1++;
	}
	if (cntS1 > cntT1) return -1; //无解;
	//printf("ans = %d\n", ans);
	for (int i = 0; i < lens; i++)
	{
		if (S[i] == '?') {
			if (T[i] == '1')
			{
				S[i] = (cntS1 < cntT1) ? '1' : '0';
				if (S[i] == '1')
					cntS1++;
		
			}
			else
				S[i] = T[i];
			ans++;
		}
	}
	int is_diff = 0;

	for (int i = 0; i < lens; i++)
	{
		if (S[i] != T[i]) is_diff++;
	}

//	printf("cntS1 = %d cntT1= %d  diff = %d\n", cntS1, cntT1,is_diff);
	//if (cntS1 < cntT1) {
	//	ans += cntT1 - cntS1;
	//	ans += (is_diff - (cntT1 - cntS1)) / 2;
	//}
	//else
	//{
	//	ans += is_diff / 2;
	//}

	ans += (is_diff + cntT1 - cntS1) / 2;

	return ans;
}

int main()
{
	int kcase = 1;
	int C;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &C);
	while (C--)
	{
		scanf("%s", S);
		scanf("%s", T);
		int ans = solve();
		printf("Case %d: %d\n", kcase++, ans);
	}
	return 0;
}