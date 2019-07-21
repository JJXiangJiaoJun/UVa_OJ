#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int maxn = 10000 + 100;
const int maxL = 10000;
int T, L;
int n;
map<int, int> idx2order;
char dir[3][100] = { 
	"L",
	"Turning",
	"R" };
struct Ant
{
	int pos;
	int num;
	int turn;

	bool operator<(const Ant &rhs)
	{
		return pos < rhs.pos;
	}
};

Ant ant[maxn];
int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	int k;
	int kcase = 1;
	scanf("%d", &k);
	while (k--)
	{
		scanf("%d%d%d", &L, &T, &n);
		idx2order.clear();
		for (int i = 0; i < n; i++)
		{
			char t;
			scanf("%d %c", &ant[i].pos, &t);
			ant[i].num = i;
			ant[i].turn = (t == 'L' ? -1 : 1);
		}
		//sort by the position
		sort(ant, ant + n);
		for (int i = 0; i < n; i++)
			idx2order[ant[i].num] = i;

		for (int i = 0; i < n; i++)
		{
			ant[i].pos += ant[i].turn*T;

		}
		sort(ant, ant + n);
		for (int i = 0; i < n - 1; i++)
		{
			if (ant[i].pos == ant[i + 1].pos) ant[i].turn = ant[i + 1].turn = 0;
		}

		printf("Case #%d:\n", kcase++);
		for (int i = 0; i < n; i++)
		{
			int idx = idx2order[i];
			if (ant[idx].pos<0 || ant[idx].pos>L) printf("Fell off\n");
			else printf("%d %s\n", ant[idx].pos, dir[ant[idx].turn + 1]);
		}
		printf("\n");
	}


	return 0;
}