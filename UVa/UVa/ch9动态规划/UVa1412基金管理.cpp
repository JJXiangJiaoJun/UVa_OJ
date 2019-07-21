#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/*题解思路：
*对于复杂状态，初始化映射表，变成整数下标。
*构建状态转换表，将复杂状态转换到整数下标。
*对于每天，每种情况，每只股票做决策，留，买，卖，对符合条件的进行刷表，刷表的前提是初始化到位
*分阶段思想从头刷到尾，利用数组保存解的前一个值，方便遍历。
*递归输出，可以利用保存的解并从前到后输出。
*/

const double INF = 1e10;
const int maxstate = 15000;
const int maxn = 8+1;
const int maxm = 100 + 5;
const int maxk = 8 + 1;

char stockname[maxn][10];
int n, m, kk;
int k[maxk];
double c;
double price[maxn][maxm];
//首先进行预处理，计算出所有的状态并进行编码
vector<vector<int> > states;
map<vector<int>, int> ID;

void dfs(int stock, vector<int>& lots, int totlot) {
	if (stock == n) {
		ID[lots] = states.size();
		states.push_back(lots);
	}
	else
	{
		for (int i = 0; i <= k[stock] && totlot + i <= kk; i++) {
			lots[stock] = i;
			dfs(stock + 1, lots, totlot + i);
		}
	}
}

//下面构造出状态转移表
int buy_next[maxstate][maxn], sell_next[maxstate][maxn];

void init()
{
	vector<int> lots(n);
	states.clear();
	ID.clear();
	dfs(0, lots, 0);
	//考虑每一个状态
	for (int s = 0; s < states.size(); s++) {
		//计算总股票手数
		int totlot = 0;
		for (int i = 0; i < n; i++) totlot += states[s][i];
		//考虑每种股票
		for (int i = 0; i < n; i++) {
			//不能转移的状态都赋值成-1
			buy_next[s][i] = sell_next[s][i] = -1;
			//买进股票
			if (states[s][i] < k[i] && totlot < kk) {
				vector<int> newstate = states[s];
				newstate[i]++;
				buy_next[s][i] = ID[newstate];
			}
			//卖出股票
			if (states[s][i] > 0) {
				vector<int> newstate = states[s];
				newstate[i]--;
				sell_next[s][i] = ID[newstate];
			}
		}
		

	}
}


//动态规划主程序，采用刷表法

double d[maxm][maxstate];
int opt[maxm][maxstate], previous[maxm][maxstate];


void update(int day, int s, int s2, double v, int o) {
	//如果现金大于当前值，那么进行节点更新
	if (v > d[day+1][s2]) {
		d[day + 1][s2] = v;
		opt[day + 1][s2] = o;
		previous[day + 1][s2] = s;
	}
}

//动态规划主程序
double dp() {
	for (int day = 0; day <= m; day++)
		for (int s = 0; s < states.size(); s++)
			d[day][s] = -INF;
	d[0][0] = c;

	for(int day=0;day<m;day++)
		for (int s = 0; s < states.size(); s++) {
			double v = d[day][s];
			if (v < -1) continue;    //保证一定是计算过的状态
			//选择1   HOLD
			update(day, s, s, v, 0);
			//考虑每只股票
			for (int i = 0; i < n; i++) {
				//BUY    需要能买 而且 有足够的现金
				if (buy_next[s][i] >= 0 && v >= price[i][day] - 1e-3) {
					update(day, s, buy_next[s][i], v - price[i][day], i + 1);
				}
				//SELL
				if (sell_next[s][i] >= 0) {
					update(day, s, sell_next[s][i], v + price[i][day], -i - 1);
				}
			}

		}
	return d[m][0];
}

void print_ans(int day, int s) {
	if (day == 0) return;
	print_ans(day - 1, previous[day][s]);
	if (opt[day][s] == 0) printf("HOLD\n");
	else if (opt[day][s] > 0) printf("BUY %s\n", stockname[opt[day][s] - 1]);
	else printf("SELL %s\n", stockname[-opt[day][s] - 1]);
}

int main()
{
	int s;
	int kcase = 0;
	while (scanf("%lf%d%d%d",&c,&m,&n,&kk)==4&&c&&m&&n&&k)
	{
		if (kcase++ > 0) printf("\n");
		for (int i = 0; i < n; i++) {
			scanf("%s", stockname[i]);
			scanf("%d%d", &s, &k[i]);

			for (int j = 0; j < m; j++)
			{
				double per;
				scanf("%lf", &per);
				price[i][j] = per*s; //每日买进的价格
			}
		}

		init();
		double ans = dp();
		printf("%.2lf\n", ans);
		print_ans(m, 0);
	}
	
	
	return 0;
}

