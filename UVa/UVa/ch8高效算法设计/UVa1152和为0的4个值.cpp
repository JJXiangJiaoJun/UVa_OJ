#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 4000 + 500;
int A[maxn], B[maxn], C[maxn], D[maxn];
int K;
int n;

const int maxnode = 4000 * 4000 + 5000;
const int maxsel = 4000 * 4000 + 5000;



struct Hash_map {
	static const int hashsize = 0x7fffff;

	int sum[hashsize], cnt[hashsize];

	void clear() {
		memset(cnt, 0, sizeof(cnt));
	}

	int& operator [] (int k) {
		int i;
		for (i = k&hashsize; cnt[i] && sum[i] != k; i = (i + 1)&hashsize);
		sum[i] = k;
		return cnt[i];
	}

};

Hash_map hash_m;

int solve() {
	
	int temp;
	LL ans = 0;
	int index = 0;
	int index_neg = 0;
	//ö��a+b������������б���
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			//�����
			temp = A[i] + B[j];

			//�����ͳ����+1
			hash_m[temp] ++;
		}
	//sort(sum, sum + index);
	//for (int i = 0; i < 4; i++)
	//{
	//	printf("head[%d].index = %d nextnode[%d].index = %d\n", i,head[i].index,i,nextnode[i].index);
	//	printf("head[%d].cnt = %d nextnode[%d].cnt = %d\n", i, head[i].cnt, i, nextnode[i].cnt);
	//}
	//for (int i = 0; i < 4; i++)
	//	printf("sum[%d] = %d ", i, sum[i]);
	//printf("\n");
	//ö��c+d�����
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			//�����
			temp = -C[i] - D[j];

			//�����A+B�ĺ����ҵ���ͬ����ôѡ�񷽷� ����ѡ�񷽷�

			//ans += upper_bound(sum, sum + index, temp) - lower_bound(sum, sum + index, temp);
			ans += (LL)hash_m[temp];
		}
	return ans;
}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &K);
	while (K--) {
		getchar();
		scanf("%d", &n);

		//��������
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
		}

		//for (int i = 0; i < n; i++)
		//{
		//	printf("%d %d %d %d\n", A[i], B[i], C[i], D[i]);
		//}
		hash_m.clear();
		LL ans = solve();
		printf("%lld\n", ans);
		if(K)printf("\n");
	}
	
	return 0;
}