#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 200000 + 1000;
typedef long long LL;
int resistance[maxn];
//�����߶������������
LL sum[maxn << 2];
LL add[maxn << 2];

int N;

//����߶����ڵ�rt��ֵ    �ýڵ�ĺ͵�����������ֵ������������ֵ  ����Ϊ��ͳ��������)
void PushUp(int rt) { sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }

//�����߶���
void Build(int l, int r,int rt)
{
	//����ҵ���Ҷ�ӽڵ���ô������Ҷ�ӽڵ��ֵ
	if (l == r)
	{
		sum[rt] = (LL)resistance[l];
		return;
	}

	int  m = (l + r) >> 1;

	//���ҵݹ齨��
	Build(l, m, rt << 1);
	Build(m + 1, r, rt << 1 | 1);

	//����������ɣ�������и��½ڵ�
	PushUp(rt);
}

//�޸�ĳһ���ڵ��ֵ��  resistance[L]=C
void UpDate(int L, int C, int l, int r,int rt)
{
	//����Ҷ�ӽڵ���ô�޸�
	if (l==r)
	{
		sum[rt] = (LL)C;
		return;
	}

	int m = (l + r) >> 1;

	//�����ӽڵ�
	if (L <= m) UpDate(L, C, l, m,rt<<1);
	else UpDate(L, C, m + 1, r,rt<<1|1);
	//�ӽڵ������ɣ����±��ڵ�
	PushUp(rt);

}

//������ƺ��� ln , �ֱ�Ϊ��������������
void PushDown(int ln,int rn,int rt)
{
	if (add[rt])
	{
		add[rt << 1] += add[rt];
		add[rt << 1 | 1] += add[rt];
		sum[rt << 1] += ln*add[rt << 1];
		sum[rt << 1 | 1] += rn*add[rt << 1 | 1];
		add[rt] = 0;
	}
}
//��ǲ�ѯ��������ѯ resistance[L,R]����ĺ�
LL Search(int L, int R, int l, int r, int rt)
{
	//���(L,R)��ȫ���� ��ѯ(l,r)������ôֱ�ӷ���ֵ
	if (L <= l&&R >= r)
	{
		return (LL)sum[rt];
	}

	int m = (l + r) >> 1;
	//���Ʊ��
	PushDown(m-l+1,r-m,rt);

	LL temp_sum = 0;
	if (m >= L)
		temp_sum += Search(L, R, l, m, rt << 1);
	if (m < R)
		temp_sum += Search(L, R, m + 1, r, rt << 1 | 1);

	//�ӽڵ������ϣ���ô���µ�ǰ�ڵ�
	//PushUp(rt);
	return temp_sum;

}


//�޸�ĳһ������ĺ��� A[L-R]+=C

void UpDate_Section(int L, int R, int C, int l, int r, int rt)
{
	//�����ǰ�������䣬�����ڸ��������У���ֱ�Ӹ���
	if (L <= l&&R >= r)
	{
		sum[rt] += (LL)(r - l + 1)*C;
		add[rt] += C;
		return;
	}

	int m = (l + r) >> 1;
	//���Ʊ��
	PushDown(m - l + 1, r - m, rt);
	//�ж����޽������н����Ž��еݹ�
	if (m >= L) UpDate_Section(L, R, C, l, m, rt << 1);
	if (m < R) UpDate_Section(L, R, C, m + 1, r, rt << 1 | 1);

	PushUp(rt);
}



void solve()
{
	char cmd[4];
	int left, right;
	int index, ohms;
	LL ans;
	while (scanf("%s", &cmd) && cmd[0] != 'E')
	{
		switch (cmd[0])
		{
		case 'M':
			scanf("%d %d\n", &left, &right);
			ans = Search(left, right, 1, N, 1);
			printf("%lld\n", ans);
			break;
		case 'S':
			scanf("%d %d\n", &index, &ohms);
			UpDate(index, ohms, 1, N, 1);
			break;
		default:
			break;
		}
	}
}


int main()
{
	LL kcase = 1;
	//freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	//freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	memset(add, 0, sizeof(add));
	bool first = true;
	while (scanf("%d", &N) == 1 && N)
	{
		//����ÿ������ֵ
		for (int i = 1; i <= N; i++)
			scanf("%d", &resistance[i]);
		Build(1, N, 1);
		if(!first) printf("\n");
		printf("Case %lld:\n", kcase++);		
		solve();
		first = false;
	}
	
	return 0;
}
