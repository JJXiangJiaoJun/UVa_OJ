#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1000 + 10;
const int maxquestion = 10 + 5;
int T;
int n, m, k;
char Q[maxn][maxquestion];
int P[maxquestion];
int is_del[maxquestion];
int select[maxquestion];
//保存每种情况有多少可能
int my_set[1 << 12];
int id[maxn];

int exist[maxn];


int Cn2;


//获得索引为 index份 问卷的id
inline int get_id(int index)
{
	int id = 0;
	for (int i = 0; i < m; i++)
		if (!is_del[i])  id = id << 1 | (Q[index][i] - 'A');
	return id;
}



//判断函数，cur表示当前有 cur-1 个 问题已经被丢弃，将要枚举丢弃 cur 个问题
bool need_cut(int cur)
{
	//最优性剪枝,当前最大能产生的 不同问卷的对数为
	int max_select = m - cur - 2;
	int max_set = pow(2, m - cur - 1);
	max_select = pow(4, max_select);
	//printf("max_select = %d\n", max_select);
	//
	if (n>max_set)
	{
		if ((max_select*(n / max_set+1)*(n / max_set+1)) < k)
			return true;
	}

	return false;
}

bool judge(int cur)
{
	memset(is_del, 0, sizeof(is_del));
	memset(my_set, 0, sizeof(my_set));
	int count = 0;
	//进行判断
	for (int i = 0; i < cur; i++)
		is_del[P[i]] = 1;
	//获得每个问题的id,并统计集合
	for (int i = 0; i < n; i++)
	{
		id[i] = get_id(i);
		//判断是否重复
		if (my_set[id[i]] == 0)
		{
			exist[count] = id[i];
			count++;
		}
		//统计次数+1
		my_set[id[i]] += 1;
	}
	int ans = 0;
	for (int i = 0; i<count - 1; i++)
		for (int j = i + 1; j < count; j++)
		{
			ans += my_set[exist[i]] * my_set[exist[j]];
			if (ans >= k)
				return true;
		}
	return false;
}

int problem_set = 0;


//枚举选的问题集合，当前枚举的是第 cur 个 元素
void generate_subset(int m,int cur,int mini_index)
{
	//如果需要剪枝则不继续枚举
	//if (need_cut(cur))   return;
	//printf("cur = %d  need_cut return false\n",cur);

	//否则进行判断
	if (!judge(cur)) return;
	problem_set++;

	//if (need_cut(cur))   return;

	//枚举问题集合
	for (int i = mini_index; i < m; i++)
	{
		P[cur] = i;
		//if (need_cut(cur))   return;
		//枚举下一个不选择的子集
		generate_subset(m, cur + 1, i + 1);

	}
	//if (need_cut(cur))   return;
}


void solve()
{
	if (Cn2 < k)
	{
		printf("0\n");
		return;
	}
	problem_set = 0;
	generate_subset(m, 0, 0);
	printf("%d\n", problem_set);
}

int main()
{
	
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	int kcase = 1;
	while (T--)
	{
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 0; i < n; i++)
			scanf("%s", Q[i]);
		Cn2 = n*(n - 1) / 2;
		printf("Case #%d: ", kcase++);
		solve();
	}
	
	return 0;
}

