#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 50000;
char mp[maxn][2000];
int max_c[maxn];
int N;


void solve()
{
	memset(mp, '\0', sizeof(mp));
	for (int i = 0; i < maxn; i++) max_c[i] = -2000;
	string s = "ru";
	for (int i = 2; i <= N; i++) {
		int len = s.length();
		for (int j = 0; j < len; j++)
		{
			if (j < len / 2) {
				if (s[j] == 'r') s += "l";
				else if (s[j] == 'l')s += "r";
				else if (s[j] == 'u')s += "d";
				else if (s[j] == 'd') s += "u";
			}
			else s += s[j];
		}
	}
	
	//cout << s << endl;
	//计算出s s中保存的是当前的路径
	int cur_r = 25000, cur_c = 1000;
	int max_r = 25000, min_r = 25000, min_c = 1000;
	max_c[25000] = 1000;
	mp[cur_r][cur_c] = '_';
	for (int i = 1; i < s.length(); i++) {
		if (s[i - 1] == 'r') {
			if (s[i] == 'u') {
				cur_c++;
				mp[cur_r][cur_c] = '|';
			}
			else if (s[i] == 'd') {
				cur_r++;
				cur_c++;
				mp[cur_r][cur_c] = '|';
			}
		}
		else if (s[i - 1] == 'l') {
			if (s[i] == 'u') {
				cur_c--;
				mp[cur_r][cur_c] = '|';
			}
			else if (s[i] == 'd') {
				cur_r++;
				cur_c--;
				mp[cur_r][cur_c] = '|';
			}
		}
		else if (s[i - 1] == 'u') {
			if (s[i] == 'l') {
				cur_r--;
				cur_c--;
				mp[cur_r][cur_c] = '_';
			}
			else if (s[i] == 'r') {
				cur_r--;
				cur_c++;
				mp[cur_r][cur_c] = '_';
			}
		}
			else if (s[i - 1] == 'd') {
				if (s[i] == 'l') {
					cur_c--;
					mp[cur_r][cur_c] = '_';
				}
				else if (s[i] == 'r') {
					cur_c++;
					mp[cur_r][cur_c] = '_';
				}
			}
			min_r = min(min_r, cur_r);
			max_r = max(max_r, cur_r);
			min_c = min(min_c, cur_c);
			max_c[cur_r] = max(max_c[cur_r], cur_c);
		
	}

	for (int i = min_r; i <= max_r; i++) {
		for (int j = min_c; j <= max_c[i]; j++) {
			if (mp[i][j] == '\0') printf(" ");
			else printf("%c", mp[i][j]);
		}
		printf("\n");
	}
	printf("^\n");
}

int main()
{
	
	while (scanf("%d",&N)==1&&N)
	{
		solve();

	}
}