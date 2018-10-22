#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 100000 + 1000;

struct Node {
	//ÿ�����x��y����
	int x;
	int y;
	
	//ÿ������x���ϵĿ�������
	long long start;
	long long end;

	//�����������
	void caculate(int D,int maxlen)
	{
		start =round(((double)x-sqrt((double)D*(double)D - (double)y*(double)y))*100);

		end = round(((double)x + sqrt((double)D*(double)D - (double)y*(double)y)) * 100);

		start = start >= 0 ? start : 0;

		end = end <= maxlen*100 ? end : maxlen*100;
	}

	//�������������
	bool operator < (const Node &rhs)const
	{
		return (end < rhs.end) || ((end == rhs.end) && (start > rhs.start));
	}

	Node(){}
	Node(int _x,int _y):x(_x),y(_y){}
};

int D;
int N;
int L;
Node node[maxn];

int solve()
{
	int ans = 1;
	//�������������
	sort(node, node + N);
	//��һ����ѡ���һ����������һ��
	long long select = node[0].end;
	//����̰�ĵĽ���ѡ��
	//ѡ��ÿ����������һ��
	for (int i = 1; i < N; i++)
	{
		//�����һ��ѡ�ĵ㲻�ڵ�ǰ���䣬��ѡ��ǰ�������һ��Ϊ�µĵ�
		if (node[i].start > select) {
			select = node[i].end;
			ans++;
		}
	}

	return ans;
}

int main()
{
	int x, y;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d%d%d", &L, &D, &N) == 3 && L != EOF)
	{
		for (int i = 0; i < N; i++)
		{
			scanf("%d%d", &x, &y);
			node[i].x = x;
			node[i].y = y;
			//����ÿ������������յ�
			node[i].caculate(D, L);
		}
		int ans = solve();
		printf("%d\n", ans);
	}
	
	return 0;
}