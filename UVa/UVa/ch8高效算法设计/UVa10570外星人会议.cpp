#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
 
const int MAXN = 510;
const int INF = 0x3f3f3f3f;
 
int a[MAXN*2];
 
int n;
 
int f(int a[], int n) //求最小交换次数 
{
	bool vis[MAXN] = {0};
	int c = 0;
	for(int i = 0; i < n; i++) if(!vis[i])
	{
		c++;
		for(int x = i; !vis[x]; x = a[x]) vis[x] = 1;
	}
	return n-c;
}
 
int read_case()
{
	scanf("%d", &n);
	if(!n) return 0;
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
		a[i]--;
	}
	return 1;
}
 
void solve()
{
	int ans = INF;
	for(int k = 0; k < 2; k++) //正、反两次 
	{
		for(int i = 0; i < n; i++) a[n+i] = a[i];
		for(int i = 0; i < n; i++) ans = min(ans, f(a+i, n)); //枚举起点 
		reverse(a, a+n); //取反 
	}
	printf("%d\n", ans);
}
 
int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
