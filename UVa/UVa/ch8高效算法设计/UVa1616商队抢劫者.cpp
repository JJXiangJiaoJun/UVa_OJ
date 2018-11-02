#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 100000 + 1000;

const double eps = 1e-9;  //С�����ַ��ľ���

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b,a%b);
}

struct Gang {
	int a;
	int b;
	int L;

	bool operator  <(const Gang rhs) const
	{
		return a < rhs.a;
	}
};

int n;
Gang gangs[maxn];
int min_len;


//̰�ľ������󻮷�,�������жϽ�Ŀ�����
bool judge(double len)
{
	double t = gangs[0].a;
	bool ok = true;
	for (int i = 0; i < n; i++)
	{
		if (t < gangs[i].a) t = gangs[i].a;
		if (t + len > gangs[i].b) { ok = false; break; }
		t += len;
	}
	return ok;
}


void solve()
{
	//�������������
	sort(gangs, gangs + n);

	//���ֲ�������ĳ���
	double L = 0.0;
	double R = min_len;
	while ((R - L) > eps)
	{
		double mid = (R + L) / 2.0;
		if (judge(mid)) L = mid;
		else R = mid;
	}
	double ans = L;
	

	//С����������ö�ٷ�ĸ
	int rp = 0, rq = 1;//С��������
	for (int p, q = 1; q <= n; ++q) {
		p = round(ans * q);
		//���������С��
		if (fabs((double)p / q - ans) < fabs((double)rp / rq - ans)) {
			rp = p;  rq = q;
		}
	}
	int g = gcd(rp, rq);
	printf("%d/%d\n", rp / g, rq / g);
}


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d", &n) == 1 && n)
	{
	
		min_len = 10000000;
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d", &gangs[i].a, &gangs[i].b);
			gangs[i].L = gangs[i].b - gangs[i].a;
			min_len = min(min_len, gangs[i].L);
		}
		solve();
	}
	
	return 0;
}