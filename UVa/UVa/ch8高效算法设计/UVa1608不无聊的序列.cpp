#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
#define INF 0x3f3f3f3f
const int maxn = 200000 + 1000;
int seq[maxn];

int L[maxn];
int R[maxn];

int T;
int n;
set<int>  s;
map<int, int> seq2id;

map<int, int>lastl;
map<int, int>lastr;


//从[l，r]区间寻找是否有唯一元素
bool is_unique(int l,int r)
{
	if (l>= r) return true;
	int l_index = l;
	int r_index = r;

	while (l_index <= r_index)
	{
		if (L[l_index]<l&&R[l_index]>r) return is_unique(l, l_index - 1) && is_unique(l_index + 1, r);
		if(L[r_index]<l&&R[r_index]>r) return  is_unique(l, r_index - 1) && is_unique(r_index + 1, r);
		l_index++;
		r_index--;
	}

	return false;
}

bool solve()
{
	//清除集合内元素
	s.clear();


	for (int i = 0; i < n; i++) {
		//当前元素第一次出现
		L[i] = -1;
		R[i] = INF;
		if (s.count(seq[i]) == 0) {
			s.insert(seq[i]);
			seq2id[seq[i]] = i;
		}
		//当前元素之前已经出现过，那么标记
		else
		{
			//获取当前元素左边最近元素索引
			int L_nearest = seq2id[seq[i]];
			//更新标记
			L[i] = L_nearest;
			R[L_nearest] = i;
			//更新当前保存的id
			seq2id[seq[i]] = i;
		}
	}
	//for (int i = 0, j = n-1; i < n; i++, j--)
	//{
	//	if (lastl[seq[i]] == 0) L[i] = -1;
	//	else L[i] = lastl[seq[i]];
	//	lastl[seq[i]] = i;
	//	if (lastr[seq[j]] == 0) R[j] = INF;
	//	else R[j] = lastr[seq[j]];
	//	lastr[seq[j]] = j;
	//}


	//for (int i = 0; i < n; i++)
	//	printf("L[%d] = %d , R[%d] = %d\n", i, L[i], i, R[i]);
	if (is_unique(0, n - 1)) return true;
	return false;
}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d",&seq[i]);
		bool ok = solve();
		if (ok)
			printf("non-");
		printf("boring\n");
	}
	
	return 0;
}



