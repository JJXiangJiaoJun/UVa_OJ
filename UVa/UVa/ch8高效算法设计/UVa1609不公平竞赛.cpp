#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int maxn = 1024 + 5;
char table[maxn][maxn];


int main()
{
	int n;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d", &n) == 1)
	{
		for (int i = 1; i <= n; i++) scanf("%s", table[i] + 1);

		vector<int>  win, lose;
		for (int i = 2; i <= n; i++)
			if (table[1][i]=='1') win.push_back(i);
			else lose.push_back(i);
		int nt = n;
		
		while (nt > 1)
		{
			vector<int>  win2, lose2, final;
			//在会输给1 中的队伍配对
			for (int i = 0; i < lose.size(); i++)
			{
				int tlose = lose[i];
				bool matched = false;
				for (int j = 0; j < win.size(); j++)
				{
					int &twin = win[j];
					if (twin > 0 && table[twin][tlose] == '1')
					{
						printf("%d %d\n", twin, tlose);
						win2.push_back(twin);         //晋级到下一轮
						twin = 0;
						matched = true;
						break;
					}
				}
				if (!matched) final.push_back(tlose);
			}

				bool first = true;
				for (int i = 0; i < win.size(); i++) {
					int twin = win[i];
					if (twin > 0) {
						if (first) { printf("1 %d\n", twin); first = false; }
						else final.push_back(twin);
					}
				}
				//剩下的队伍两两配对
				for (int i = 0; i < final.size(); i += 2) {
					printf("%d %d\n", final[i], final[i + 1]);
					int keep = final[i];
					if (table[final[i + 1]][keep] == '1') keep = final[i + 1];
					if (table[1][keep] == '1') win2.push_back(keep);
					else lose2.push_back(keep);
				}


				//更新下一轮的比赛人数
				win = win2;
				lose = lose2;
				nt >>=1;

			}
		}
	
	return 0;
}