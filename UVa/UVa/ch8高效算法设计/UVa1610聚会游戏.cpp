#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 1000 + 100;
int n;
vector<string>  A;
char ans[maxn];


void solve_b()
{

	sort(A.begin(), A.end());
	memset(ans, 0, sizeof(ans));

	string s;
	string b;
	string ans="A";

	int small = (n - 1) / 2;
	int big = small + 1;
	s = A[small];
	b = A[big];
	int len1 = A[small].size();
	int len2 = A[big].size();

	int len = 0;
	while (len<len1)
	{
		while (ans[len] <= 'Z'&&ans < s) ++ans[len];
		if (ans[len] <= 'Z'&&ans >= s&&ans < b) break;
		if (ans[len] != s[len]) --ans[len];
		ans += 'A';
		len++;

	}
	cout << ans << endl;
}

int main()

{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	string s;
	while (scanf("%d", &n) == 1 && n) {
		A.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> s;
			A.push_back(s);
		}
		solve_b();

	}
	return 0;
}