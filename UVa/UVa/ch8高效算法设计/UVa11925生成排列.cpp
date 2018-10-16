#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

int const maxn = 300 + 200;
#define max_end  (maxn*maxn*8-5)
int per[maxn*maxn*8];
int n;
int ans[maxn*maxn * 2];


bool is_sorted(int start,int end)
{
	int i = start;
	int k = 1;
	for (; i <= end; i++,k++)
		if (per[i] != k) return false;
	return true;
}
/*冒泡排序的方法*/
void solve()
{
	//memset(ans, 0, sizeof(ans));
	//数组的起点和终点
	int start = max_end-n+1;
	//数组的起点和终点
	int end = max_end;
	if(is_sorted(start,end)) { printf("\n"); return; };

	//需要操作
	int index = 0;
	while (1)
	{
		if (per[start] == n) {
			ans[index++] = 2;
			per[--start] = per[end--];
			if (is_sorted(start, end)) break;
			continue;
		}

		//消除逆序对
		if (per[start] > per[start + 1])
		{
			swap(per[start], per[start + 1]);
			ans[index++] = 1;
			if (is_sorted(start, end)) break;
		}

		per[--start] = per[end--];
		ans[index++] = 2;
		if (is_sorted(start, end)) break;

	}
	for (int k = (index - 1); k >= 0; k--)
	{
		printf("%d", ans[k]);
	}
	printf("\n");
}



int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d", &n) == 1 && n)
	{
		for (int i = (max_end -n+1); i <= max_end; i++)
			scanf("%d", &per[i]);
		//for (int i = (max_end - n + 1); i <= max_end; i++)
		//	printf("%d", per[i]);
		solve();
	}
	return 0;
}