#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 200000 + 1000;
typedef long long LL;
int resistance[maxn];
//定义线段树的求和数组
LL sum[maxn << 2];
LL add[maxn << 2];

int N;

//求和线段树节点rt的值    该节点的和等于左子树的值加上右子树的值  （因为是统计整个和)
void PushUp(int rt) { sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }

//建立线段树
void Build(int l, int r,int rt)
{
	//如果找到了叶子节点那么，保存叶子节点的值
	if (l == r)
	{
		sum[rt] = (LL)resistance[l];
		return;
	}

	int  m = (l + r) >> 1;

	//左右递归建树
	Build(l, m, rt << 1);
	Build(m + 1, r, rt << 1 | 1);

	//子树构建完成，下面进行更新节点
	PushUp(rt);
}

//修改某一个节点的值即  resistance[L]=C
void UpDate(int L, int C, int l, int r,int rt)
{
	//到达叶子节点那么修改
	if (l==r)
	{
		sum[rt] = (LL)C;
		return;
	}

	int m = (l + r) >> 1;

	//更新子节点
	if (L <= m) UpDate(L, C, l, m,rt<<1);
	else UpDate(L, C, m + 1, r,rt<<1|1);
	//子节点更新完成，更新本节点
	PushUp(rt);

}

//标记下推函数 ln , 分别为左右子树的数量
void PushDown(int ln,int rn,int rt)
{
	if (add[rt])
	{
		add[rt << 1] += add[rt];
		add[rt << 1 | 1] += add[rt];
		sum[rt << 1] += ln*add[rt << 1];
		sum[rt << 1 | 1] += rn*add[rt << 1 | 1];
		add[rt] = 0;
	}
}
//标记查询函数，查询 resistance[L,R]区间的和
LL Search(int L, int R, int l, int r, int rt)
{
	//如果(L,R)完全包含 查询(l,r)区间那么直接返回值
	if (L <= l&&R >= r)
	{
		return (LL)sum[rt];
	}

	int m = (l + r) >> 1;
	//下推标记
	PushDown(m-l+1,r-m,rt);

	LL temp_sum = 0;
	if (m >= L)
		temp_sum += Search(L, R, l, m, rt << 1);
	if (m < R)
		temp_sum += Search(L, R, m + 1, r, rt << 1 | 1);

	//子节点更新完毕，那么更新当前节点
	//PushUp(rt);
	return temp_sum;

}


//修改某一个区间的函数 A[L-R]+=C

void UpDate_Section(int L, int R, int C, int l, int r, int rt)
{
	//如果当前查找区间，包含在更新区间中，则直接更新
	if (L <= l&&R >= r)
	{
		sum[rt] += (LL)(r - l + 1)*C;
		add[rt] += C;
		return;
	}

	int m = (l + r) >> 1;
	//下推标记
	PushDown(m - l + 1, r - m, rt);
	//判断有无交集，有交集才进行递归
	if (m >= L) UpDate_Section(L, R, C, l, m, rt << 1);
	if (m < R) UpDate_Section(L, R, C, m + 1, r, rt << 1 | 1);

	PushUp(rt);
}



void solve()
{
	char cmd[4];
	int left, right;
	int index, ohms;
	LL ans;
	while (scanf("%s", &cmd) && cmd[0] != 'E')
	{
		switch (cmd[0])
		{
		case 'M':
			scanf("%d %d\n", &left, &right);
			ans = Search(left, right, 1, N, 1);
			printf("%lld\n", ans);
			break;
		case 'S':
			scanf("%d %d\n", &index, &ohms);
			UpDate(index, ohms, 1, N, 1);
			break;
		default:
			break;
		}
	}
}


int main()
{
	LL kcase = 1;
	//freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	//freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	memset(add, 0, sizeof(add));
	bool first = true;
	while (scanf("%d", &N) == 1 && N)
	{
		//读入每个电阻值
		for (int i = 1; i <= N; i++)
			scanf("%d", &resistance[i]);
		Build(1, N, 1);
		if(!first) printf("\n");
		printf("Case %lld:\n", kcase++);		
		solve();
		first = false;
	}
	
	return 0;
}
