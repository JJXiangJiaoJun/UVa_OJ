#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int T;
const int maxn = 100000 + 1000;
char b[maxn];
int a[maxn];
int sum[maxn];
int p[maxn];
int ansL, ansR;
int n, L;
//�Ƚ�x1--x2 �� x3---x4֮���б��
int compare_aver(int x1, int x2, int x3, int x4)
{
	
	return (sum[x2] - sum[x1 - 1]) * (x4 - x3 + 1) - (sum[x4] - sum[x3 - 1]) * (x2 - x1 + 1);

}
void solve()
{
	//����ǰ׺��
	sum[0] = 0;
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i];
	int ansL = 1, ansR = L;
	int i=0, j = 0;
	//ö�ټ���
	for (int t = L; t <= n; t++)
	{
		//��������д���������,���ұ��ֺ�ѡ��ĵ�����,����β�����ϵĵ�ɾ��
		//while (j - i > 1 && compare(p[j - 2], t - L, p[j - 1], t - L) >= 0) j--;
		while (j - i > 1 && compare_aver(p[j - 2], t - L, p[j - 1], t - L) >= 0) j--;
		//���¼���ĵ����
		p[j++] = t - L+1;
		//Ѱ���е�
		while (j - i > 1 && compare_aver(p[i], t, p[i + 1], t) <= 0) i++;
			//��֮ǰ�Ľ���бȽ�
		int c = compare_aver(p[i], t, ansL, ansR);
		if ((c > 0) || (c == 0 && t - p[i] < ansR - ansL))
		{
			ansL = p[i];
			ansR = t;
		}
	}
	printf("%d %d\n", ansL, ansR);
}

int main()
{
	scanf("%d", &T);
	char ch;
	while (T--)
	{
		scanf("%d%d", &n, &L);
		scanf("%s", b+1);
		for (int i = 1; i <= n; i++)
			a[i] = b[i] - '0';
		solve();
	}
	return 0;
}