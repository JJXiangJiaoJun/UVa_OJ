#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000 + 100;
int height[maxn];
char land[maxn][maxn];
int n, m;
int ans[maxn << 1];

struct Rect {
	int c, h;

	Rect(int cc=1,int hh=1):c(cc),h(hh){}
};

Rect rect[maxn];

void solve()
{
	memset(height, 0, sizeof(height));
	memset(ans, 0, sizeof(ans));


	/*��ʱ�临�Ӷ� O(m*n) ��Ϊÿ�����������ӳ���һ��*/

	for (int i = 0; i < n; i++)
	{
		int top = -1;			//ÿ�μ����µ�һ�������ջ

		for (int j = 0; j < m; j++)
		{
			//��������ϰ�����ֱ�����ջ
			if (land[i][j] == '#')
			{
				top = -1;
				height[j] = 0;
			}
			else
			{
				height[j]++; //��ǰ�и߶�����һ�и߶ȵ��Ƶõ�

				Rect r(j, height[j]);

				if (top < 0) rect[++top] = r;   //��ջֱ�Ӹ�ֵ

				else
				{											//r.c�洢��ǰ���ŵ����ϽǶ���ֵ
					while (top >= 0 && rect[top].h >= r.h) r.c = rect[top--].c; //ջ�е�hӦ�������������ǽλ�õ�c����֤�߶ȵ������������ұ������ŵ�cֵ
					if (top<0 || r.h - r.c>rect[top].h - rect[top].c) rect[++top] = r;  //��������Ž⣬��ô��ջ��������ջ

				}
				//��ʱջ����Ϊ���ŵ����ϽǶ���
				r = rect[top];
				ans[r.h + j - r.c + 1]++;
			}
		}
	}

	for (int i = 2; i <= m + n; i++)
		if (ans[i]) printf("%d x %d\n", ans[i], i * 2);
}

int main()
{
	int T;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", land[i]);

		solve();
	}
	return 0;
}