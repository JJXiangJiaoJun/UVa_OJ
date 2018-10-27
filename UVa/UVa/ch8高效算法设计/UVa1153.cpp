#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
struct Customers {
	int q;
	int d;

	bool operator <(const Customers&rhs)const
	{
		return d < rhs.d;
	}
};


const int maxn = 800000 + 1000;
int n;

Customers customer[maxn];


int solve()
{
	int ans = 0;
	int date = 0;
	priority_queue<int>  q;
	//°´½ØÖ¹ÈÕÆÚÉıĞòÅÅ
	sort(customer, customer + n);

	for (int i = 0; i < n; i++)
	{
		//¿¼ÂÇÌæ»»
		if (date + customer[i].q > customer[i].d)
		{
			if (q.empty()) continue;
			if (customer[i].q <= q.top())
			{
				date = date - q.top() + customer[i].q;
				q.pop();
				q.push(customer[i].q);
			}
		}
		else
		{
			date += customer[i].q;
			q.push(customer[i].q);
			ans++;
		}
	}

	return ans;
}


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d%d", &customer[i].q, &customer[i].d);
		int ans = solve();
		printf("%d\n", ans);
		if (T) printf("\n");
	}
	return 0;
}

