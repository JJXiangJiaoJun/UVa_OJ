#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
const int maxn = 1000000 + 500;
int snowflake[maxn];
int N;

int main()
{
	int T;
	scanf("%d", &T);
	int L, R;
	int maxlen;
	//freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	//freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (T--)
	{
		scanf("%d", &N);
		L = R = 0;
		maxlen = 0;
		set<int> id;

		for (int i = 0; i < N; i++)
			scanf("%d", &snowflake[i]);
		id.insert(snowflake[0]);
		//while (R < N)
		//{
		//	//每次情况要不是L+1，则是R+1
		//	//先尝试R+1,如果出现重复，则将L+1
		//	while (R < N && !id.count(snowflake[R]))id.insert(snowflake[R++]);
		//	maxlen = max(maxlen, R - L);
		//	id.erase(snowflake[L++]);
		//}

		while (R < N-1)
		{
			if (id.count(snowflake[R+1]))
			{
				id.erase(snowflake[L]);
				L++;
			}
			else
			{
				R++;
				id.insert(snowflake[R]);
			}
			maxlen = max(maxlen, R - L + 1);
		}
		printf("%d\n", maxlen);
	}
	return 0;
}
