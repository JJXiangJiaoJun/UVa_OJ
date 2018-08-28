#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define mem(a,b)  memset(a,b,sizeof(a))
#define FOR(a,max)   for(int a=0;a<max;a++)
const int maxn = 10000;
int num_of_stick;
int length[maxn];

int max_length;
int sum = 0;
int len_per_stick = 0;
int select_num = 0;
int sticknum = 0;
int is_selected[maxn];

//枚举第 cur 根木棒， 枚举小木棍的索引为 index ， 枚举总和为 cnt
bool dfs(int cur, int index, int cnt,int sel_num)
{
	if (cur*len_per_stick == sum) return true;
	

	//枚举木棍
	for (int i = index; i < num_of_stick; i++)
	{
		//如果之前没有选择同样的小木棍，则后面相同长度的小木棍不用选择
		if (i&& !is_selected[i-1] && (length[i - 1] == length[i])) continue;

		//如果当前木棍被选过了，那么跳过
		if (is_selected[i]) continue;

		//选择后长度大于规定值
		if (cnt + length[i] > len_per_stick) continue;

		if (cnt + length[i] == len_per_stick) {
			is_selected[i] = 1;
			if (dfs(cur + 1, 0, 0, 0)) return true;
			is_selected[i] = 0;
			return false;
		}

		//下面选择当前小木棍
		is_selected[i] = 1;
		if (dfs(cur, i + 1, cnt + length[i],sel_num+1)) return true;
		//如果当前组合没有成功

		//如果是当前最大的木棍长度
		is_selected[i] = 0;

		//若在匹配第cnt + 1根木棒时，最长的那根木棒stick会第一个被选择，
		//若此时第cnt + 1根等长木棒匹配失败，则第cnt + 1根等长木棒无须继续匹配
		//，返回第cnt根等长木棒的匹配即可，因为与stick在此次匹配时匹配的可选木棒范围要比以后更大，
		//此次都匹配不成，以后更匹配不成，要重新匹配第cnt根木棒，得以产生新的最长木棒stick’，再由此尝试匹配第cnt + 1根等长木棒。
		//if (sel_num == 0 && length[i] == length[index]) return false;
		if (sel_num == 0) return false;


	}
	return false;
}

void solve() {

	
	for (len_per_stick = max_length;len_per_stick<=sum/2; len_per_stick++)
	{
		mem(is_selected, 0);
		//如果该情况，不能整除，那么不进行枚举选择
		if (sum%len_per_stick) continue;
		//printf("sum%%len_per_stick=%d\n", sum%len_per_stick);
		sticknum = sum / len_per_stick;
		//printf("sticknum=%d len_per_stick=%d\n\n",sticknum,len_per_stick);

		if (dfs(0,0,0,0)) { printf("%d\n", len_per_stick); return; }
		//printf("退出dfs\n");
	}
	printf("%d\n", sum);

}

bool cmp(const int &a, const int &b) {
	     return a > b;
	
}


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	
	while (scanf("%d", &num_of_stick) == 1 && num_of_stick)
	{
		sum = 0;
		mem(length, 0);
		for (int i = 0; i < num_of_stick; i++)
		{
			scanf("%d", &length[i]);
			sum += length[i];
		}
		//sort(length, length + num_of_stick);
		
		//按照降序排列
		sort(length, length + num_of_stick,cmp);

		//FOR(i, num_of_stick)
		//{
		//	printf("%d ", length[i]);
		//}
		//printf("\n\nnum_of_stick=%d\n", num_of_stick);
		//printf("\n\n");
		//max_length = length[num_of_stick - 1];
		max_length = length[0];
		//printf("max_len = %d sum=%d\n", max_length,sum);
		solve();
	}
	
	
	return 0;
}

