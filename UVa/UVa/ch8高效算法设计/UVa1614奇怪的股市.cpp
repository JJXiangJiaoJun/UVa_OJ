#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 1000;
int A[maxn];
long long sum;
int n;
int sel[maxn];

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d", &n) == 1)
	{
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		sum = 0;
		for (int i = 0; i < n; i++)
			sum += A[i];
		if (sum & 1) {
			printf("No\n"); continue;
		}
		printf("Yes\n");
		sum >>= 1;
		for (int i = n - 1; i >= 0; i--)
		{
			if ( A[i]<= sum )
			{
				sum -= A[i];
				sel[i] = 1;
			}
			else
			{
				sel[i] = -1;
			}
		}
		for(int i=0;i<n-1;i++)
			printf("%d ", sel[i]);
		printf("%d\n", sel[n - 1]);
	}
	return 0;
}