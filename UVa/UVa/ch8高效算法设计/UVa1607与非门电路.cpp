#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 1000;
const int maxm = 200000+1000;
struct Gate
{
	int in1;
	int in2;
	int output;
};
int d;
int n, m;
int ans[maxn];
Gate gates[maxm];

//1--->index����Ϊ1   index+1----->n����Ϊ0
int getoutput(int index)
{
	//��������
	int in1_index;
	int in2_index;

	//��ʵ����
	int input1;
	int input2;
	for (int i = 1; i <= m; i++)
	{
		in1_index = gates[i].in1;
		in2_index = gates[i].in2;

		//������ӵ�������
		if (in1_index < 0)
		{
			in1_index = -in1_index;
			if (in1_index <= index)
			{
				input1 = 1;
			}
			else
			{
				input1 = 0;
			}
		}
		else
		{
			input1 = gates[in1_index].output;
		}

		if (in2_index < 0)
		{
			in2_index = -in2_index;
			if (in2_index <= index)
			{
				input2 = 1;
			}
			else
			{
				input2 = 0;
			}
		}
		else
		{
			input2 = gates[in2_index].output;
		}

		gates[i].output = !(input1&input2);
	}
	return gates[m].output;
}


void solve()
{
	//����ȫΪ1
	int ans1 = getoutput(n);
	//printf("ans1 = %d\n", ans1);
	//����ȫΪ0
	int ans0 = getoutput(0);
	//printf("ans0 = %d\n", ans0);

	//printf("100  = %d\n", getoutput(1));
	//printf("110  = %d\n", getoutput(2));
	//˵����·���Ϊ����
	if (ans1 == ans0)
	{
		for (int i = 1; i <= n; i++)
			printf("1");
		printf("\n");
		return;
	}
	//˵����·�������ȣ�������ж������

	int L = 1, R = n;
	while (L <= R)
	{
		//�����е�
		int mid = L + (R - L) / 2;
		//printf("mid = %d", mid);

		//�ж�
		if (getoutput(mid) == ans1) R = mid - 1;
		else L = mid + 1;
	}
	printf("L = %d\n", L);
	for (int i = 1; i < L; i++)
		printf("1");
	printf("x");
	for (int i = L + 1; i <= n; i++)
		printf("0");
	printf("\n");
}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &d);
	while (d--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++)
		{
			scanf("%d%d", &gates[i].in1, &gates[i].in2);
		}
		//for (int i = 1; i <= m; i++)
		//{
		//	printf("%d %d\n", gates[i].in1, gates[i].in2);
		//}
		solve();
	}
	return 0;
}